/*
 * 	Command & Conquer Renegade(tm)
 * 	Copyright 2025 Electronic Arts Inc.
 * 	Copyright 2025 CnC: Rebel Developers.
 *
 * 	This program is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 * 	This program is distributed in the hope that it will be useful,
 * 	but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 	GNU General Public License for more details.
 *
 * 	You should have received a copy of the GNU General Public License
 * 	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdio>

#include "textureloader.h"
#include "thread.h"
#include "wwdebug.h"
#include "texture.h"
#include "ffactory.h"
#include "wwstring.h"
#include "bufffile.h"
#include "ww3d.h"
#include "texfcach.h"
#include "assetmgr.h"
#include "dx8wrapper.h"
#include "dx8caps.h"
#include "dxdefs.h"
#include "missingtexture.h"
#include "targa.h"
#include "wwmemlog.h"
#include "texture.h"
#include "formconv.h"
#include "texturethumbnail.h"
#include "ddsfile.h"
#include "bitmaphandler.h"

bool TextureLoader::TextureLoadSuspended;

#define USE_MANAGED_TEXTURES

////////////////////////////////////////////////////////////////////////////////
//
// TextureLoadTaskListClass implementation
//
////////////////////////////////////////////////////////////////////////////////

TextureLoadTaskListClass::TextureLoadTaskListClass(void) : Root() { Root.Next = Root.Prev = &Root; }

void TextureLoadTaskListClass::Push_Front(TextureLoadTaskClass *task) {
  // task should non-null and not on any list
  WWASSERT(task != NULL && task->Next == NULL && task->Prev == NULL);

  // update inserted task to point to list
  task->Next = Root.Next;
  task->Prev = &Root;
  task->List = this;

  // update list to point to inserted task
  Root.Next->Prev = task;
  Root.Next = task;
}

void TextureLoadTaskListClass::Push_Back(TextureLoadTaskClass *task) {
  // task should be non-null and not on any list
  WWASSERT(task != NULL && task->Next == NULL && task->Prev == NULL);

  // update inserted task to point to list
  task->Next = &Root;
  task->Prev = Root.Prev;
  task->List = this;

  // update list to point to inserted task
  Root.Prev->Next = task;
  Root.Prev = task;
}

TextureLoadTaskClass *TextureLoadTaskListClass::Pop_Front(void) {
  // exit early if list is empty
  if (Is_Empty()) {
    return 0;
  }

  // otherwise, grab first task and remove it.
  TextureLoadTaskClass *task = (TextureLoadTaskClass *)Root.Next;
  Remove(task);
  return task;
}

TextureLoadTaskClass *TextureLoadTaskListClass::Pop_Back(void) {
  // exit early if list is empty
  if (Is_Empty()) {
    return 0;
  }

  // otherwise, grab last task and remove it.
  TextureLoadTaskClass *task = (TextureLoadTaskClass *)Root.Prev;
  Remove(task);
  return task;
}

void TextureLoadTaskListClass::Remove(TextureLoadTaskClass *task) {
  // exit early if task is not on this list.
  if (task->List != this) {
    return;
  }

  // update list to skip task
  task->Prev->Next = task->Next;
  task->Next->Prev = task->Prev;

  // update task to no longer point at list
  task->Prev = 0;
  task->Next = 0;
  task->List = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// SynchronizedTextureLoadTaskListClass implementation
//
////////////////////////////////////////////////////////////////////////////////

SynchronizedTextureLoadTaskListClass::SynchronizedTextureLoadTaskListClass(void)
    : TextureLoadTaskListClass(), CriticalSection() {}

void SynchronizedTextureLoadTaskListClass::Push_Front(TextureLoadTaskClass *task) {
  std::lock_guard lock(CriticalSection);
  TextureLoadTaskListClass::Push_Front(task);
}

void SynchronizedTextureLoadTaskListClass::Push_Back(TextureLoadTaskClass *task) {
  std::lock_guard lock(CriticalSection);
  TextureLoadTaskListClass::Push_Back(task);
}

TextureLoadTaskClass *SynchronizedTextureLoadTaskListClass::Pop_Front(void) {
  // this duplicates code inside base class, but saves us an unnecessary lock.
  if (Is_Empty()) {
    return 0;
  }

  std::lock_guard lock(CriticalSection);
  return TextureLoadTaskListClass::Pop_Front();
}

TextureLoadTaskClass *SynchronizedTextureLoadTaskListClass::Pop_Back(void) {
  // this duplicates code inside base class, but saves us an unnecessary lock.
  if (Is_Empty()) {
    return 0;
  }

  std::lock_guard lock(CriticalSection);
  return TextureLoadTaskListClass::Pop_Back();
}

void SynchronizedTextureLoadTaskListClass::Remove(TextureLoadTaskClass *task) {
  std::lock_guard lock(CriticalSection);
  TextureLoadTaskListClass::Remove(task);
}

// Locks

// To prevent deadlock, threads should acquire locks in the order in which
// they are defined below. No ordering is necessary for the task list locks,
// since one thread can never hold two at once.

static std::recursive_mutex _ForegroundCriticalSection;
static std::recursive_mutex _BackgroundCriticalSection;

// Lists

static SynchronizedTextureLoadTaskListClass _ForegroundQueue;
static SynchronizedTextureLoadTaskListClass _BackgroundQueue;
static TextureLoadTaskListClass _FreeList;

// The background texture loading thread.
static class LoaderThreadClass : public ThreadClass {
public:
#ifdef Exception_Handler
  LoaderThreadClass(const char *thread_name = "Texture loader thread") : ThreadClass(thread_name, &Exception_Handler) {}
#else
  LoaderThreadClass(const char *thread_name = "Texture loader thread") : ThreadClass(thread_name) {}
#endif

  void Thread_Function();
} _TextureLoadThread;

// TODO: Legacy - remove this call!
DX_IDirect3DTexture *Load_Compressed_Texture(const StringClass &filename, unsigned reduction_factor,
                                             TextureClass::MipCountType mip_level_count, WW3DFormat dest_format) {
  // If DDS file isn't available, use TGA file to convert to DDS.

  DDSFileClass dds_file(filename, reduction_factor);
  if (!dds_file.Is_Available())
    return NULL;
  if (!dds_file.Load())
    return NULL;

  unsigned width = dds_file.Get_Width(0);
  unsigned height = dds_file.Get_Height(0);
  unsigned mips = dds_file.Get_Mip_Level_Count();

  // If format isn't defined get the nearest valid texture format to the compressed file format
  // Note that the nearest valid format could be anything, even uncompressed.
  if (dest_format == WW3D_FORMAT_UNKNOWN)
    dest_format = Get_Valid_Texture_Format(dds_file.Get_Format(), true);

  DX_IDirect3DTexture *d3d_texture =
      DX8Wrapper::_Create_DX8_Texture(width, height, dest_format, (TextureClass::MipCountType)mips);

  for (unsigned level = 0; level < mips; ++level) {
    DX_IDirect3DSurface *d3d_surface = NULL;
    WWASSERT(d3d_texture);
    DX8_ErrorCode(d3d_texture->GetSurfaceLevel(level /*-reduction_factor*/, &d3d_surface));
    dds_file.Copy_Level_To_Surface(level, d3d_surface);
    d3d_surface->Release();
  }
  return d3d_texture;
}

static bool Is_Format_Compressed(WW3DFormat texture_format, bool allow_compression) {
  // Verify that the user isn't requesting compressed texture without hardware support

  bool compressed = false;
  if (texture_format != WW3D_FORMAT_UNKNOWN) {
    if (!DX8Wrapper::Get_Current_Caps()->Support_DXTC() || !allow_compression) {
      WWASSERT(texture_format != WW3D_FORMAT_DXT1);
      WWASSERT(texture_format != WW3D_FORMAT_DXT2);
      WWASSERT(texture_format != WW3D_FORMAT_DXT3);
      WWASSERT(texture_format != WW3D_FORMAT_DXT4);
      WWASSERT(texture_format != WW3D_FORMAT_DXT5);
    }
    if (texture_format == WW3D_FORMAT_DXT1 || texture_format == WW3D_FORMAT_DXT2 ||
        texture_format == WW3D_FORMAT_DXT3 || texture_format == WW3D_FORMAT_DXT4 ||
        texture_format == WW3D_FORMAT_DXT5) {
      compressed = true;
    }
  }

  // If hardware supports DXTC compression, load a compressed texture. Proceed only if the texture format hasn't been
  // defined as non-compressed.
  compressed |=
      (texture_format == WW3D_FORMAT_UNKNOWN && DX8Wrapper::Get_Current_Caps()->Support_DXTC() && allow_compression);

  return compressed;
}

////////////////////////////////////////////////////////////////////////////////
//
// TextureLoader implementation
//
////////////////////////////////////////////////////////////////////////////////

void TextureLoader::Init() {
  WWASSERT(!_TextureLoadThread.Is_Running());

  ThumbnailManagerClass::Init();

  _TextureLoadThread.Execute();
  _TextureLoadThread.Set_Priority(-4);
}

void TextureLoader::Deinit() {
  std::lock_guard lock(_BackgroundCriticalSection);
  _TextureLoadThread.Stop();

  ThumbnailManagerClass::Deinit();
  TextureLoadTaskClass::Delete_Free_Pool();
}

bool TextureLoader::Is_DX8_Thread(void) {
  return (ThreadClass::_Get_Current_Thread_ID() == DX8Wrapper::_Get_Main_Thread_ID());
}

// ----------------------------------------------------------------------------
//
// Modify given texture size to nearest valid size on current hardware.
//
// ----------------------------------------------------------------------------

void TextureLoader::Validate_Texture_Size(unsigned &width, unsigned &height) {
  const DX_D3DCAPS &dx8caps = DX8Wrapper::Get_Current_Caps()->Get_DX8_Caps();

  unsigned poweroftwowidth = 1;
  while (poweroftwowidth < width) {
    poweroftwowidth <<= 1;
  }

  unsigned poweroftwoheight = 1;
  while (poweroftwoheight < height) {
    poweroftwoheight <<= 1;
  }

  if (poweroftwowidth > dx8caps.MaxTextureWidth) {
    poweroftwowidth = dx8caps.MaxTextureWidth;
  }
  if (poweroftwoheight > dx8caps.MaxTextureHeight) {
    poweroftwoheight = dx8caps.MaxTextureHeight;
  }

  if (poweroftwowidth > poweroftwoheight) {
    while (poweroftwowidth / poweroftwoheight > 8) {
      poweroftwoheight *= 2;
    }
  } else {
    while (poweroftwoheight / poweroftwowidth > 8) {
      poweroftwowidth *= 2;
    }
  }

  width = poweroftwowidth;
  height = poweroftwoheight;
}

DX_IDirect3DTexture *TextureLoader::Load_Thumbnail(const StringClass &filename) //,WW3DFormat texture_format)
{
  WWASSERT(Is_DX8_Thread());

  ThumbnailClass *thumb = NULL;
  ThumbnailManagerClass *thumb_man = ThumbnailManagerClass::Peek_List().Head();
  while (thumb_man) {
    thumb = thumb_man->Peek_Thumbnail_Instance(filename);
    if (thumb)
      break;
    thumb_man = thumb_man->Succ();
  }

  // If no thumb is found return a missing texture
  if (!thumb) {
    return MissingTexture::_Get_Missing_Texture();
  }

  WWASSERT(thumb->Get_Format() == WW3D_FORMAT_A4R4G4B4);
  unsigned src_pitch = thumb->Get_Width() * 2; // Thumbs are always 16 bits
  WW3DFormat dest_format;
  WW3DFormat texture_format = WW3D_FORMAT_UNKNOWN;
  if (texture_format == WW3D_FORMAT_UNKNOWN) {
    dest_format = Get_Valid_Texture_Format(WW3D_FORMAT_A4R4G4B4, false); // no compressed formats please
  } else {
    dest_format = Get_Valid_Texture_Format(texture_format, false); // no compressed formats please
    WWASSERT(dest_format == texture_format);
  }

  DX_IDirect3DTexture *sysmem_texture = DX8Wrapper::_Create_DX8_Texture(thumb->Get_Width(), thumb->Get_Height(),
                                                                        dest_format, TextureClass::MIP_LEVELS_ALL,
#ifdef USE_MANAGED_TEXTURES
                                                                        D3DPOOL_MANAGED);
#else
                                                                        D3DPOOL_SYSTEMMEM);
#endif

  unsigned level = 0;
  D3DLOCKED_RECT locked_rects[12];
  WWASSERT(sysmem_texture->GetLevelCount() <= 12);

  // Lock all surfaces
  for (level = 0; level < sysmem_texture->GetLevelCount(); ++level) {
    DX8_ErrorCode(sysmem_texture->LockRect(level, &locked_rects[level], NULL, 0));
  }

  unsigned char *src_surface = thumb->Peek_Bitmap();
  WW3DFormat src_format = thumb->Get_Format();
  unsigned width = thumb->Get_Width();
  unsigned height = thumb->Get_Height();

  for (level = 0; level < sysmem_texture->GetLevelCount() - 1; ++level) {
    BitmapHandlerClass::Copy_Image_Generate_Mipmap(width, height, (unsigned char *)locked_rects[level].pBits,
                                                   locked_rects[level].Pitch, dest_format, src_surface, src_pitch,
                                                   src_format,
                                                   (unsigned char *)locked_rects[level + 1].pBits, // mipmap
                                                   locked_rects[level + 1].Pitch);                 // mipmap

    src_format = dest_format;
    src_surface = (unsigned char *)locked_rects[level].pBits;
    src_pitch = locked_rects[level].Pitch;
    width >>= 1;
    height >>= 1;
  }

  // Unlock all surfaces
  for (level = 0; level < sysmem_texture->GetLevelCount(); ++level) {
    DX8_ErrorCode(sysmem_texture->UnlockRect(level));
  }
#ifdef USE_MANAGED_TEXTURES
  return sysmem_texture;
#else
  DX_IDirect3DTexture *d3d_texture = DX8Wrapper::_Create_DX8_Texture(
      thumb->Get_Width(), thumb->Get_Height(), dest_format, TextureClass::MIP_LEVELS_ALL, D3DPOOL_DEFAULT);
  DX8CALL(UpdateTexture(sysmem_texture, d3d_texture));
  sysmem_texture->Release();

  WWDEBUG_SAY(("Created non-managed texture (%s)\n", filename));
  return d3d_texture;
#endif
}

// ----------------------------------------------------------------------------
//
// Load image to a surface. The function tries to create texture that matches
// targa format. If suitable format is not available, it selects closest matching
// format and performs color space conversion.
//
// ----------------------------------------------------------------------------
DX_IDirect3DSurface *TextureLoader::Load_Surface_Immediate(const StringClass &filename, WW3DFormat texture_format,
                                                           bool allow_compression) {
  WWASSERT(Is_DX8_Thread());

  bool compressed = Is_Format_Compressed(texture_format, allow_compression);

  if (compressed) {
    DX_IDirect3DTexture *comp_tex =
        Load_Compressed_Texture(filename, 0, TextureClass::MIP_LEVELS_1, WW3D_FORMAT_UNKNOWN);
    if (comp_tex) {
      DX_IDirect3DSurface *d3d_surface = NULL;
      DX8_ErrorCode(comp_tex->GetSurfaceLevel(0, &d3d_surface));
      comp_tex->Release();
      return d3d_surface;
    }
  }

  // Make sure the file can be opened. If not, return missing texture.
  Targa targa;
  if (TARGA_ERROR_HANDLER(targa.Open(filename, TGA_READMODE), filename))
    return MissingTexture::_Create_Missing_Surface();

  // DX8 uses image upside down compared to TGA
  targa.Header.ImageDescriptor ^= TGAIDF_YORIGIN;

  WW3DFormat src_format, dest_format;
  unsigned src_bpp = 0;
  Get_WW3D_Format(dest_format, src_format, src_bpp, targa);

  if (texture_format != WW3D_FORMAT_UNKNOWN) {
    dest_format = texture_format;
  }

  // Destination size will be the next power of two square from the larger width and height...
  unsigned width, height;
  width = targa.Header.Width;
  height = targa.Header.Height;
  unsigned src_width = targa.Header.Width;
  unsigned src_height = targa.Header.Height;

  // NOTE: We load the palette but we do not yet support paletted textures!
  char palette[256 * 4];
  targa.SetPalette(palette);
  if (TARGA_ERROR_HANDLER(targa.Load(filename, TGAF_IMAGE, false), filename))
    return MissingTexture::_Create_Missing_Surface();

  unsigned char *src_surface = (unsigned char *)targa.GetImage();

  // No paletted destination format allowed
  unsigned char *converted_surface = NULL;
  if (src_format == WW3D_FORMAT_A1R5G5B5 || src_format == WW3D_FORMAT_R5G6B5 || src_format == WW3D_FORMAT_A4R4G4B4 ||
      src_format == WW3D_FORMAT_P8 || src_format == WW3D_FORMAT_L8 || src_width != width || src_height != height) {
    converted_surface = new unsigned char[width * height * 4];
    dest_format = Get_Valid_Texture_Format(WW3D_FORMAT_A8R8G8B8, false);
    BitmapHandlerClass::Copy_Image(converted_surface, width, height, width * 4,
                                   WW3D_FORMAT_A8R8G8B8, // dest_format,
                                   src_surface, src_width, src_height, src_width * src_bpp, src_format,
                                   (unsigned char *)targa.GetPalette(), targa.Header.CMapDepth >> 3, false);
    src_surface = converted_surface;
    src_format = WW3D_FORMAT_A8R8G8B8; // dest_format;
    src_width = width;
    src_height = height;
    src_bpp = Get_Bytes_Per_Pixel(src_format);
  }

  unsigned src_pitch = src_width * src_bpp;

  DX_IDirect3DSurface *d3d_surface = DX8Wrapper::_Create_DX8_Surface(width, height, dest_format);
  WWASSERT(d3d_surface);
  D3DLOCKED_RECT locked_rect;
  DX8_ErrorCode(d3d_surface->LockRect(&locked_rect, NULL, 0));

  BitmapHandlerClass::Copy_Image((unsigned char *)locked_rect.pBits, width, height, locked_rect.Pitch, dest_format,
                                 src_surface, src_width, src_height, src_pitch, src_format,
                                 (unsigned char *)targa.GetPalette(), targa.Header.CMapDepth >> 3,
                                 false); // No mipmap

  DX8_ErrorCode(d3d_surface->UnlockRect());

  if (converted_surface)
    delete[] converted_surface;

  return d3d_surface;
}

void TextureLoader::Request_Thumbnail(TextureClass *tc) {
  // Grab the foreground lock. This prevents the foreground thread
  // from retiring any tasks related to this texture. It also
  // serializes calls to Request_Thumbnail from multiple threads.
  std::lock_guard lock(_ForegroundCriticalSection);

  // Has a Direct3D texture already been loaded?
  if (tc->Peek_DX8_Texture()) {
    return;
  }

  TextureLoadTaskClass *task = tc->ThumbnailLoadTask;

  if (Is_DX8_Thread()) {
    // load the thumbnail immediately
    TextureLoader::Load_Thumbnail(tc);

    // clear any pending thumbnail load
    if (task) {
      _ForegroundQueue.Remove(task);
      task->Destroy();
    }

  } else {
    TextureLoadTaskClass *load_task = tc->TextureLoadTask;

    // if texture is not already loading a thumbnail and there is no
    // background load near completion. (a background load waiting
    // to be applied will be ready at the same time as a queued thumbnail.
    // Why do the extra work?)
    if (!task && (!load_task || load_task->Get_State() < TextureLoadTaskClass::STATE_LOAD_MIPMAP)) {

      // create a thumbnail load task and add to foreground queue.
      task = TextureLoadTaskClass::Create(tc, TextureLoadTaskClass::TASK_THUMBNAIL, TextureLoadTaskClass::PRIORITY_LOW);
      _ForegroundQueue.Push_Back(task);
    }
  }
}

void TextureLoader::Request_Background_Loading(TextureClass *tc) {
  // Grab the foreground lock. This prevents the foreground thread
  // from retiring any tasks related to this texture. It also
  // serializes calls to Request_Background_Loading from other
  // threads.
  std::lock_guard foreground_lock(_ForegroundCriticalSection);

  // Has the texture already been loaded?
  if (tc->Is_Initialized()) {
    return;
  }

  TextureLoadTaskClass *task = tc->TextureLoadTask;

  // if texture already has a load task, we don't need to create another one.
  if (task) {
    return;
  }

  task = TextureLoadTaskClass::Create(tc, TextureLoadTaskClass::TASK_LOAD, TextureLoadTaskClass::PRIORITY_LOW);

  if (Is_DX8_Thread()) {
    Begin_Load_And_Queue(task);
  } else {
    _ForegroundQueue.Push_Back(task);
  }
}

void TextureLoader::Request_Foreground_Loading(TextureClass *tc) {
  // Grab the foreground lock. This prevents the foreground thread
  // from retiring the load tasks for this texture. It also
  // serializes calls to Request_Foreground_Loading from other
  // threads.
  std::lock_guard foreground_lock(_ForegroundCriticalSection);

  // Has the texture already been loaded?
  if (tc->Is_Initialized()) {
    return;
  }

  TextureLoadTaskClass *task = tc->TextureLoadTask;
  TextureLoadTaskClass *task_thumb = tc->ThumbnailLoadTask;

  if (Is_DX8_Thread()) {

    // since we're in the DX8 thread, we can load the entire
    // texture right now.

    // if we have a thumbnail task waiting, kill it.
    if (task_thumb) {
      _ForegroundQueue.Remove(task_thumb);
      task_thumb->Destroy();
    }

    if (task) {
      // we need to remove the task from any queue, since we're going
      // to finish it up right now.

      // halt background thread. After we're holding this lock,
      // we know the background thread cannot begin loading
      // mipmap levels for this texture.
      std::lock_guard background_lock(_BackgroundCriticalSection);
      _ForegroundQueue.Remove(task);
      _BackgroundQueue.Remove(task);
    } else {
      // Since the task manages all the state associated with loading
      // a texture, we temporarily create one.
      task = TextureLoadTaskClass::Create(tc, TextureLoadTaskClass::TASK_LOAD, TextureLoadTaskClass::PRIORITY_HIGH);
    }

    // finish loading the task and destroy it.
    task->Finish_Load();
    task->Destroy();

  } else {
    // we are not in the DX8 thread. We need to add a high-priority loading
    // task to the foreground queue.

    // Grab the background lock. After we're holding this lock, we
    // know the background thread cannot begin loading mipmap levels
    // for this texture.
    std::lock_guard background_lock(_BackgroundCriticalSection);

    // if we have a thumbnail task, we should cancel it. Since we are not
    // the foreground thread, we are not allowed to call Destroy(). Instead,
    // leave it queued in the completed state so it will be destroyed by Update().
    if (task_thumb) {
      task_thumb->Set_State(TextureLoadTaskClass::STATE_COMPLETE);
    }

    if (task) {
      // if a load task is waiting on the background queue, we need to
      // move it to the foreground queue.
      if (task->Get_List() == &_BackgroundQueue) {

        // remove task from list
        _BackgroundQueue.Remove(task);

        // add to foreground queue.
        _ForegroundQueue.Push_Back(task);
      }

      // upgrade the task priority
      task->Set_Priority(TextureLoadTaskClass::PRIORITY_HIGH);

    } else {
      // allocate high priority load task
      task = TextureLoadTaskClass::Create(tc, TextureLoadTaskClass::TASK_LOAD, TextureLoadTaskClass::PRIORITY_HIGH);

      // add to back of foreground queue.
      _ForegroundQueue.Push_Back(task);
    }
  }
}

void TextureLoader::Flush_Pending_Load_Tasks(void) {
  // This function can only be called from the main thread.
  // (Only the main thread can make the DX8 calls necessary
  // to complete texture loading. If we wanted to flush
  // the pending tasks from another thread, we'd probably
  // want to set a bool that is checked by Update().
  WWASSERT(Is_DX8_Thread());

  for (;;) {
    bool done = false;

    {
      // we have no pending load tasks when both queues are empty
      // and the background thread is not processing a texture.

      // Grab the background lock. Once we're holding it, we
      // know that the background thread is not processing any
      // textures.

      // NOTE: It's important that we do only hold on to the background
      // lock while we check for completion. Otherwise, we will either
      // violate the lock order when we call Update() (which grabs
      // the foreground lock) or never give the background thread
      // a chance to empty its queue.
      std::lock_guard background_lock(_BackgroundCriticalSection);
      done = _BackgroundQueue.Is_Empty() && _ForegroundQueue.Is_Empty();
    }

    // exit loop if no entries in list
    if (done) {
      break;
    }

    Update();
    ThreadClass::Switch_Thread();
  }
}

// Nework update macro for texture loader.
#pragma warning(disable : 4201) // warning C4201: nonstandard extension used : nameless struct/union
#include <mmsystem.h>
#define UPDATE_NETWORK                                                                                                 \
  if (network_callback) {                                                                                              \
    unsigned long time2 = timeGetTime();                                                                               \
    if (time2 - time > 20) {                                                                                           \
      network_callback();                                                                                              \
      time = time2;                                                                                                    \
    }                                                                                                                  \
  }

void TextureLoader::Update(void (*network_callback)(void)) {
  WWASSERT_PRINT(Is_DX8_Thread(), "TextureLoader::Update must be called from the main thread!");

  if (TextureLoadSuspended) {
    return;
  }

  // grab foreground lock to prevent any other thread from
  // modifying texture tasks.
  std::lock_guard lock(_ForegroundCriticalSection);

  unsigned long time = timeGetTime();

  // while we have tasks on the foreground queue
  while (TextureLoadTaskClass *task = _ForegroundQueue.Pop_Front()) {
    UPDATE_NETWORK;
    // dispatch to proper task handler
    switch (task->Get_Type()) {
    case TextureLoadTaskClass::TASK_THUMBNAIL:
      Process_Foreground_Thumbnail(task);
      break;

    case TextureLoadTaskClass::TASK_LOAD:
      Process_Foreground_Load(task);
      break;
    }
  }

  TextureClass::Invalidate_Old_Unused_Textures(0);
}

void TextureLoader::Suspend_Texture_Load() {
  WWASSERT_PRINT(Is_DX8_Thread(), "TextureLoader::Suspend_Texture_Load must be called from the main thread!");
  TextureLoadSuspended = true;
}

void TextureLoader::Continue_Texture_Load() {
  WWASSERT_PRINT(Is_DX8_Thread(), "TextureLoader::Continue_Texture_Load must be called from the main thread!");
  TextureLoadSuspended = false;
}

void TextureLoader::Process_Foreground_Thumbnail(TextureLoadTaskClass *task) {
  switch (task->Get_State()) {
  case TextureLoadTaskClass::STATE_NONE:
    Load_Thumbnail(task->Peek_Texture());
    // NOTE: fall-through is intentional

  case TextureLoadTaskClass::STATE_COMPLETE:
    task->Destroy();
    break;
  }
}

void TextureLoader::Process_Foreground_Load(TextureLoadTaskClass *task) {
  // Is high-priority task?
  if (task->Get_Priority() == TextureLoadTaskClass::PRIORITY_HIGH) {
    task->Finish_Load();
    task->Destroy();
    return;
  }

  // otherwise, must be a low-priority task.

  switch (task->Get_State()) {
  case TextureLoadTaskClass::STATE_NONE:
    Begin_Load_And_Queue(task);
    break;

  case TextureLoadTaskClass::STATE_LOAD_MIPMAP:
    task->End_Load();
    task->Destroy();
    break;
  }
}

void TextureLoader::Begin_Load_And_Queue(TextureLoadTaskClass *task) {
  // should only be called from the DX8 thread.
  WWASSERT(Is_DX8_Thread());

  if (task->Begin_Load()) {
    // add to front of background queue. This means the
    // background load thread will service tasks in LIFO
    // (last in, first out) order.

    // NOTE: this was how the old code did it, with a
    // comment that mentioned good reasons for doing so,
    // without actually listing the reasons. I suspect
    // it has something to do with visually important textures,
    // like those in the foreground, starting their load last.
    _BackgroundQueue.Push_Front(task);
  } else {
    // unable to load.
    task->Apply_Missing_Texture();
    task->Destroy();
  }
}

void TextureLoader::Load_Thumbnail(TextureClass *tc) {
  // All D3D operations must run from main thread
  WWASSERT(Is_DX8_Thread());

  // load thumbnail texture
  DX_IDirect3DTexture *d3d_texture = Load_Thumbnail(tc->Get_Full_Path());

  // apply thumbnail to texture
  tc->Apply_New_Surface(d3d_texture, false);

  // release our reference to thumbnail texture
  d3d_texture->Release();
  d3d_texture = 0;
}

void LoaderThreadClass::Thread_Function(void) {
  while (running) {
    // if there are no tasks on the background queue, no need to grab background lock.
    if (!_BackgroundQueue.Is_Empty()) {
      // Grab background load so other threads know we could be
      // loading a texture.
      std::lock_guard lock(_BackgroundCriticalSection);

      // try to remove a task from the background queue. This could fail
      // if another thread modified the queue between our test above and
      // grabbing the lock.
      TextureLoadTaskClass *task = _BackgroundQueue.Pop_Front();
      if (task) {
        // verify task is in proper state for background processing.
        WWASSERT(task->Get_Type() == TextureLoadTaskClass::TASK_LOAD);
        WWASSERT(task->Get_State() == TextureLoadTaskClass::STATE_LOAD_BEGUN);

        // load mip map levels and return to foreground queue for final step.
        task->Load();
        _ForegroundQueue.Push_Back(task);
      }
    }

    Switch_Thread();
  }
}

////////////////////////////////////////////////////////////////////////////////
//
// TextureLoaderTaskClass implementation
//
////////////////////////////////////////////////////////////////////////////////

TextureLoadTaskClass::TextureLoadTaskClass()
    : Texture(0), D3DTexture(0), Format(WW3D_FORMAT_UNKNOWN), Width(0), Height(0), MipLevelCount(0), Reduction(0),
      Type(TASK_NONE), Priority(PRIORITY_LOW), State(STATE_NONE) {
  // because texture load tasks are pooled, the constructor and destructor
  // don't need to do much. The work of attaching a task to a texture is
  // is done by Init() and Deinit().

  for (int i = 0; i < TextureClass::MIP_LEVELS_MAX; ++i) {
    LockedSurfacePtr[i] = NULL;
    LockedSurfacePitch[i] = 0;
  }
}

TextureLoadTaskClass::~TextureLoadTaskClass(void) { Deinit(); }

TextureLoadTaskClass *TextureLoadTaskClass::Create(TextureClass *tc, TaskType type, PriorityType priority) {
  // recycle or create a new texture load task with the given type
  // and priority, then associate the texture with the task.

  // pull a load task from front of free list
  TextureLoadTaskClass *task = _FreeList.Pop_Front();

  // if no tasks on free list, allocate a new task
  if (!task) {
    task = new TextureLoadTaskClass;
  }

  task->Init(tc, type, priority);
  return task;
}

void TextureLoadTaskClass::Destroy(void) {
  // detach the task from its texture, and return to free pool.
  Deinit();
  _FreeList.Push_Front(this);
}

void TextureLoadTaskClass::Delete_Free_Pool(void) {
  // free memory for every task in the free pool.
  while (TextureLoadTaskClass *task = _FreeList.Pop_Front()) {
    delete task;
  }
}

void TextureLoadTaskClass::Init(TextureClass *tc, TaskType type, PriorityType priority) {
  WWASSERT(tc);

  // NOTE: we must be in the main thread to avoid corrupting the texture's refcount.
  WWASSERT(TextureLoader::Is_DX8_Thread());
  REF_PTR_SET(Texture, tc);

  // Make sure texture has a filename.
  WWASSERT(Texture->Get_Full_Path() != "");

  Type = type;
  Priority = priority;
  State = STATE_NONE;

  D3DTexture = 0;

  Format = Texture->Get_Texture_Format();
  Width = 0;
  Height = 0;
  MipLevelCount = Texture->MipLevelCount;
  Reduction = Texture->Get_Reduction();

  for (int i = 0; i < TextureClass::MIP_LEVELS_MAX; ++i) {
    LockedSurfacePtr[i] = NULL;
    LockedSurfacePitch[i] = 0;
  }

  switch (Type) {
  case TASK_THUMBNAIL:
    WWASSERT(Texture->ThumbnailLoadTask == NULL);
    Texture->ThumbnailLoadTask = this;
    break;

  case TASK_LOAD:
    WWASSERT(Texture->TextureLoadTask == NULL);
    Texture->TextureLoadTask = this;
    break;
  }
}

void TextureLoadTaskClass::Deinit() {
  // task should not be on any list when it is being detached from texture.
  WWASSERT(Next == NULL);
  WWASSERT(Prev == NULL);

  WWASSERT(D3DTexture == NULL);

  for (int i = 0; i < TextureClass::MIP_LEVELS_MAX; ++i) {
    WWASSERT(LockedSurfacePtr[i] == NULL);
  }

  if (Texture) {
    switch (Type) {
    case TASK_THUMBNAIL:
      WWASSERT(Texture->ThumbnailLoadTask == this);
      Texture->ThumbnailLoadTask = NULL;
      break;

    case TASK_LOAD:
      WWASSERT(Texture->TextureLoadTask == this);
      Texture->TextureLoadTask = NULL;
      break;
    }

    // NOTE: we must be in main thread to avoid corrupting Texture's refcount.
    WWASSERT(TextureLoader::Is_DX8_Thread());
    REF_PTR_RELEASE(Texture);
  }
}

bool TextureLoadTaskClass::Begin_Load(void) {
  WWASSERT(TextureLoader::Is_DX8_Thread());

  bool loaded = false;

  // if allowed, begin a compressed load
  if (Texture->Is_Compression_Allowed()) {
    loaded = Begin_Compressed_Load();
  }

  // otherwise, begin an uncompressed load
  if (!loaded) {
    loaded = Begin_Uncompressed_Load();
  }

  // if not loaded, abort.
  if (!loaded) {
    return false;
  }

  // lock surfaces in preparation for copy
  Lock_Surfaces();

  State = STATE_LOAD_BEGUN;

  return true;
}

// ----------------------------------------------------------------------------
//
// Load mipmap levels to a pre-generated and locked texture object based on
// information in load task object. Try loading from a DDS file first and if
// that fails try a TGA.
//
// ----------------------------------------------------------------------------
bool TextureLoadTaskClass::Load(void) {
  WWMEMLOG(MEM_TEXTURE);
  WWASSERT(Peek_D3D_Texture());

  bool loaded = false;

  // if allowed, try to load compressed mipmaps
  if (Texture->Is_Compression_Allowed()) {
    loaded = Load_Compressed_Mipmap();
  }

  // otherwise, load uncompressed mipmaps
  if (!loaded) {
    loaded = Load_Uncompressed_Mipmap();
  }

  State = STATE_LOAD_MIPMAP;

  return loaded;
}

void TextureLoadTaskClass::End_Load(void) {
  WWASSERT(TextureLoader::Is_DX8_Thread());

  Unlock_Surfaces();
  Apply(true);

  State = STATE_LOAD_COMPLETE;
}

void TextureLoadTaskClass::Finish_Load(void) {
  switch (State) {
    // NOTE: fall-through below is intentional.

  case STATE_NONE:
    if (!Begin_Load()) {
      Apply_Missing_Texture();
      break;
    }

  case STATE_LOAD_BEGUN:
    Load();

  case STATE_LOAD_MIPMAP:
    End_Load();

  default:
    break;
  }
}

void TextureLoadTaskClass::Apply_Missing_Texture(void) {
  WWASSERT(TextureLoader::Is_DX8_Thread());
  WWASSERT(!D3DTexture);

  D3DTexture = MissingTexture::_Get_Missing_Texture();
  Apply(true);
}

void TextureLoadTaskClass::Apply(bool initialize) {
  WWASSERT(D3DTexture);

  // Verify that none of the mip levels are locked
  for (unsigned i = 0; i < MipLevelCount; ++i) {
    WWASSERT(LockedSurfacePtr[i] == NULL);
  }

  Texture->Apply_New_Surface(D3DTexture, initialize);

  D3DTexture->Release();
  D3DTexture = NULL;
}

static bool Get_Texture_Information(const char *filename, unsigned reduction, unsigned &w, unsigned &h,
                                    WW3DFormat &format, unsigned &mip_count, bool compressed) {
  ThumbnailClass *thumb = NULL;
  ThumbnailManagerClass *thumb_man = ThumbnailManagerClass::Peek_List().Head();
  while (thumb_man) {
    thumb = thumb_man->Peek_Thumbnail_Instance(filename);
    if (thumb)
      break;
    thumb_man = thumb_man->Succ();
  }
  if (!thumb) {
    if (compressed) {
      DDSFileClass dds_file(filename, reduction);
      if (!dds_file.Is_Available())
        return false;

      // Destination size will be the next power of two square from the larger width and height...
      w = dds_file.Get_Width(0);
      h = dds_file.Get_Height(0);
      format = dds_file.Get_Format();
      mip_count = dds_file.Get_Mip_Level_Count();
      return true;
    }

    Targa targa;
    if (TARGA_ERROR_HANDLER(targa.Open(filename, TGA_READMODE), filename)) {
      return false;
    }

    unsigned int bpp;
    WW3DFormat dest_format;
    Get_WW3D_Format(dest_format, format, bpp, targa);

    // Destination size will be the next power of two square from the larger width and height...
    w = targa.Header.Width >> reduction;
    h = targa.Header.Height >> reduction;
    mip_count = 0;
    return true;
  }

  if (compressed && thumb->Get_Original_Texture_Format() != WW3D_FORMAT_DXT1 &&
      thumb->Get_Original_Texture_Format() != WW3D_FORMAT_DXT2 &&
      thumb->Get_Original_Texture_Format() != WW3D_FORMAT_DXT3 &&
      thumb->Get_Original_Texture_Format() != WW3D_FORMAT_DXT4 &&
      thumb->Get_Original_Texture_Format() != WW3D_FORMAT_DXT5) {
    return false;
  }

  w = thumb->Get_Original_Texture_Width() >> reduction;
  h = thumb->Get_Original_Texture_Height() >> reduction;
  mip_count = thumb->Get_Original_Texture_Mip_Level_Count();
  format = thumb->Get_Original_Texture_Format();
  return true;
}

bool TextureLoadTaskClass::Begin_Compressed_Load(void) {
  unsigned orig_w, orig_h, orig_mip_count;
  WW3DFormat orig_format;
  if (!Get_Texture_Information(Texture->Get_Full_Path(), Get_Reduction(), orig_w, orig_h, orig_format, orig_mip_count,
                               true)) {
    return false;
  }

  // Destination size will be the next power of two square from the larger width and height...
  unsigned int width = orig_w;
  unsigned int height = orig_h;
  TextureLoader::Validate_Texture_Size(width, height);

  // If the size doesn't match, try and see if texture reduction would help... (mainly for
  // cases where loaded texture is larger than hardware limit)
  if (width != orig_w || height != orig_h) {
    for (unsigned int i = 1; i < orig_mip_count; ++i) {
      unsigned w = orig_w >> i;
      if (w < 4)
        w = 4;
      unsigned h = orig_h >> i;
      if (h < 4)
        h = 4;
      unsigned tmp_w = w;
      unsigned tmp_h = h;

      TextureLoader::Validate_Texture_Size(w, h);

      if (w == tmp_w && h == tmp_h) {
        Reduction += i;
        width = w;
        height = h;
        break;
      }
    }
  }

  Width = width;
  Height = height;
  Format = Get_Valid_Texture_Format(orig_format, Texture->Is_Compression_Allowed());

  unsigned int mip_level_count = Get_Mip_Level_Count();

  // If texture wants all mip levels, take as many as the file contains (not necessarily all)
  // Otherwise take as many mip levels as the texture wants, not to exceed the count in file...
  if (!mip_level_count) {
    mip_level_count = orig_mip_count;            // dds_file.Get_Mip_Level_Count();
  } else if (mip_level_count > orig_mip_count) { // dds_file.Get_Mip_Level_Count()) {
    mip_level_count = orig_mip_count;            // dds_file.Get_Mip_Level_Count();
  }

  // Once more, verify that the mip level count is correct (in case it was changed here it might not
  // match the size...well actually it doesn't have to match but it can't be bigger than the size)
  unsigned int max_mip_level_count = 1;
  unsigned int w = 4;
  unsigned int h = 4;

  while (w < Width && h < Height) {
    w += w;
    h += h;
    max_mip_level_count++;
  }

  if (mip_level_count > max_mip_level_count) {
    mip_level_count = max_mip_level_count;
  }

  D3DTexture = DX8Wrapper::_Create_DX8_Texture(Width, Height, Format, (TextureClass::MipCountType)mip_level_count,
#ifdef USE_MANAGED_TEXTURES
                                               D3DPOOL_MANAGED);
#else
                                               D3DPOOL_SYSTEMMEM);
#endif
  MipLevelCount = mip_level_count;
  return true;
}

bool TextureLoadTaskClass::Begin_Uncompressed_Load(void) {
  unsigned width, height, orig_mip_count;
  WW3DFormat orig_format;
  if (!Get_Texture_Information(Texture->Get_Full_Path(), Get_Reduction(), width, height, orig_format, orig_mip_count,
                               false)) {
    return false;
  }

  WW3DFormat src_format = orig_format;
  WW3DFormat dest_format = src_format;
  dest_format =
      Get_Valid_Texture_Format(dest_format, false); // No compressed destination format if reading from targa...

  if (src_format != WW3D_FORMAT_A8R8G8B8 && src_format != WW3D_FORMAT_R8G8B8 && src_format != WW3D_FORMAT_X8R8G8B8) {
    WWDEBUG_SAY(("Invalid TGA format used in %s - only 24 and 32 bit formats should be used!\n",
      Texture->Get_Full_Path().Peek_Buffer()));
  }

  // Destination size will be the next power of two square from the larger width and height...
  unsigned ow = width;
  unsigned oh = height;
  TextureLoader::Validate_Texture_Size(width, height);
  if (width != ow || height != oh) {
    WWDEBUG_SAY(("Invalid texture size, scaling required. Texture: %s, size: %d x %d -> %d x %d\n",
      Texture->Get_Full_Path().Peek_Buffer(), ow, oh, width, height));
  }

  Width = width;
  Height = height;

  if (Format == WW3D_FORMAT_UNKNOWN) {
    Format = Get_Valid_Texture_Format(dest_format, false);
  } else {
    Format = Get_Valid_Texture_Format(Format, false);
  }

  D3DTexture = DX8Wrapper::_Create_DX8_Texture(Width, Height, Format, Texture->MipLevelCount,
#ifdef USE_MANAGED_TEXTURES
                                               D3DPOOL_MANAGED);
#else
                                               D3DPOOL_SYSTEMMEM);
#endif
  return true;
}

void TextureLoadTaskClass::Lock_Surfaces(void) {
  MipLevelCount = D3DTexture->GetLevelCount();
  for (unsigned int i = 0; i < MipLevelCount; ++i) {
    D3DLOCKED_RECT locked_rect;
    DX8_ErrorCode(D3DTexture->LockRect(i, &locked_rect, NULL, 0));
    LockedSurfacePtr[i] = (unsigned char *)locked_rect.pBits;
    LockedSurfacePitch[i] = locked_rect.Pitch;
  }
}

void TextureLoadTaskClass::Unlock_Surfaces(void) {
  for (unsigned int i = 0; i < MipLevelCount; ++i) {
    if (LockedSurfacePtr[i]) {
      WWASSERT(ThreadClass::_Get_Current_Thread_ID() == DX8Wrapper::_Get_Main_Thread_ID());
      DX8_ErrorCode(D3DTexture->UnlockRect(i));
    }
    LockedSurfacePtr[i] = NULL;
  }

#ifndef USE_MANAGED_TEXTURES
  DX_IDirect3DTexture *tex =
      DX8Wrapper::_Create_DX8_Texture(Width, Height, Format, Texture->MipLevelCount, D3DPOOL_DEFAULT);
  DX8CALL(UpdateTexture(D3DTexture, tex));
  D3DTexture->Release();
  D3DTexture = tex;
  WWDEBUG_SAY(("Created non-managed texture (%s)\n", Texture->Get_Full_Path()));
#endif
}

bool TextureLoadTaskClass::Load_Compressed_Mipmap(void) {
  DDSFileClass dds_file(Texture->Get_Full_Path(), Get_Reduction());

  // if we can't load from file, indicate rror.
  if (!dds_file.Is_Available() || !dds_file.Load()) {
    return false;
  }

  unsigned int width = Get_Width();
  unsigned int height = Get_Height();

  for (unsigned int level = 0; level < Get_Mip_Level_Count(); ++level) {
    WWASSERT(width && height);
    dds_file.Copy_Level_To_Surface(level, Get_Format(), width, height, Get_Locked_Surface_Ptr(level),
                                   Get_Locked_Surface_Pitch(level));

    width >>= 1;
    height >>= 1;
  }

  return true;
}

bool TextureLoadTaskClass::Load_Uncompressed_Mipmap(void) {
  if (!Get_Mip_Level_Count()) {
    return false;
  }

  Targa targa;
  if (TARGA_ERROR_HANDLER(targa.Open(Texture->Get_Full_Path(), TGA_READMODE), Texture->Get_Full_Path())) {
    return false;
  }

  // DX8 uses image upside down compared to TGA
  targa.Header.ImageDescriptor ^= TGAIDF_YORIGIN;

  WW3DFormat src_format;
  WW3DFormat dest_format;
  unsigned int src_bpp = 0;
  Get_WW3D_Format(dest_format, src_format, src_bpp, targa);
  if (src_format == WW3D_FORMAT_UNKNOWN)
    return false;

  dest_format = Get_Format(); // Texture can be requested in different format than the most obvious from the TGA

  char palette[256 * 4];
  targa.SetPalette(palette);

  unsigned int src_width = targa.Header.Width;
  unsigned int src_height = targa.Header.Height;
  unsigned int width = Get_Width();
  unsigned int height = Get_Height();

  // NOTE: We load the palette but we do not yet support paletted textures!
  if (TARGA_ERROR_HANDLER(targa.Load(Texture->Get_Full_Path(), TGAF_IMAGE, false), Texture->Get_Full_Path())) {
    return false;
  }

  unsigned char *src_surface = (unsigned char *)targa.GetImage();
  unsigned char *converted_surface = NULL;

  // No paletted format allowed when generating mipmaps
  if (src_format == WW3D_FORMAT_A1R5G5B5 || src_format == WW3D_FORMAT_R5G6B5 || src_format == WW3D_FORMAT_A4R4G4B4 ||
      src_format == WW3D_FORMAT_P8 || src_format == WW3D_FORMAT_L8 || src_width != width || src_height != height) {

    converted_surface = new unsigned char[width * height * 4];
    dest_format = Get_Valid_Texture_Format(WW3D_FORMAT_A8R8G8B8, false);

    BitmapHandlerClass::Copy_Image(converted_surface, width, height, width * 4,
                                   WW3D_FORMAT_A8R8G8B8, // dest_format,
                                   src_surface, src_width, src_height, src_width * src_bpp, src_format,
                                   (unsigned char *)targa.GetPalette(), targa.Header.CMapDepth >> 3, false);

    src_surface = converted_surface;
    src_format = WW3D_FORMAT_A8R8G8B8; // dest_format;
    src_width = width;
    src_height = height;
    src_bpp = Get_Bytes_Per_Pixel(src_format);
  }

  unsigned src_pitch = src_width * src_bpp;

  for (unsigned int level = 0; level < Get_Mip_Level_Count(); ++level) {
    WWASSERT(Get_Locked_Surface_Ptr(level));
    BitmapHandlerClass::Copy_Image(Get_Locked_Surface_Ptr(level), width, height, Get_Locked_Surface_Pitch(level),
                                   Get_Format(), src_surface, src_width, src_height, src_pitch, src_format, NULL, 0,
                                   true);

    width >>= 1;
    height >>= 1;
    src_width >>= 1;
    src_height >>= 1;

    if (!width || !height || !src_width || !src_height) {
      break;
    }
  }

  if (converted_surface) {
    delete[] converted_surface;
  }

  return true;
}

unsigned char *TextureLoadTaskClass::Get_Locked_Surface_Ptr(unsigned int level) {
  WWASSERT(level < MipLevelCount);
  WWASSERT(LockedSurfacePtr[level]);
  return LockedSurfacePtr[level];
}

// ----------------------------------------------------------------------------
//
// Return locked surface pitch (in bytes) at a specific level. The call will
// assert if level is greater or equal to the number of mip levels or if the
// requested level has not been locked.
//
// ----------------------------------------------------------------------------

unsigned int TextureLoadTaskClass::Get_Locked_Surface_Pitch(unsigned int level) const {
  WWASSERT(level < MipLevelCount);
  WWASSERT(LockedSurfacePtr[level]);
  return LockedSurfacePitch[level];
}
