/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/******************************************************************************
 *
 * FILE
 *     $Archive: /Commando/Code/WWOnline/WOLDownload.h $
 *
 * DESCRIPTION
 *     This class specifies patch files to be downloaded from the server.
 *
 * PROGRAMMER
 *     $Author: Denzil_l $
 *
 * VERSION INFO
 *     $Revision: 5 $
 *     $Modtime: 1/11/02 5:17p $
 *
 ******************************************************************************/

#ifndef __WOLDOWNLOAD_H__
#define __WOLDOWNLOAD_H__

#include <atlbase.h>
#include "RefCounted.h"
#include "RefPtr.h"
#include "WaitCondition.h"

namespace WOL {
#include <WOLAPI\wolapi.h>
}

namespace WWOnline {

class Session;
class DownloadEvent;

class Download : public RefCounted, public WOL::IDownloadEvent, public Notifier<DownloadEvent> {
public:
  static RefPtr<Download> Create(const WOL::Update &patch);

  bool Start(void);
  void Stop(void);
  bool IsDone(void) const;
  void Process(void);

  unsigned long GetSKU(void) const { return mWOLUpdate.SKU; }

  unsigned long GetVersion(void) const { return mWOLUpdate.version; }

  bool IsRequired(void) const { return (mWOLUpdate.required != 0); }

  const char *GetServerName(void) const { return (const char *)mWOLUpdate.server; }

  const char *GetLoginName(void) const { return (const char *)mWOLUpdate.login; }

  const char *GetPassword(void) const { return (const char *)mWOLUpdate.password; }

  const char *GetDownloadPath(void) const { return (const char *)mWOLUpdate.patchpath; }

  const char *GetFilename(void) const { return (const char *)mWOLUpdate.patchfile; }

  const char *GetLocalPath(void) const { return (const char *)mWOLUpdate.localpath; }

  int GetStatusCode(void) const { return mStatusCode; }

  const wchar_t *GetStatusText(void) const;

  int GetErrorCode(void) const { return mErrorCode; }

  const wchar_t *GetErrorText(void) const;

  void GetProgress(int &bytesRead, int &totalSize, int &timeElapsed, int &timeRemaining) const;

  DECLARE_NOTIFIER(DownloadEvent)

protected:
  typedef enum { DLError = 0, DLPending, DLDownloading, DLAborted, DLComplete } DLState;

  Download(const WOL::Update &patch);
  ~Download();

  bool CreateDownloadObject(void);
  void ReleaseDownloadObject(void);

  void SetError(int errorCode, const char *errorText);
  const char *GetOnErrorText(int onErrorCode) const;

  // Prevent copy and assignment.
  Download(const Download &);
  const Download &operator=(const Download &);

  WOL::Update mWOLUpdate;

  CComPtr<WOL::IDownload> mDownloadObject;
  unsigned long mDownloadCookie;

  DLState mState;

  // Status / Error
  int mStatusCode;
  int mErrorCode;
  const char *mErrorText;

  // Progress
  int mBytesRead;
  int mTotalSize;
  int mTimeElapsed;
  int mTimeRemaining;

  //---------------------------------------------------------------------------
  // IUnknown methods
  //---------------------------------------------------------------------------
protected:
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(const IID &iid, void **ppv);
  virtual ULONG STDMETHODCALLTYPE AddRef(void);
  virtual ULONG STDMETHODCALLTYPE Release(void);

  //---------------------------------------------------------------------------
  // IDownloadEvent Methods
  //---------------------------------------------------------------------------
protected:
  STDMETHOD(OnEnd)(void);
  STDMETHOD(OnError)(int error);
  STDMETHOD(OnProgressUpdate)(int bytesRead, int totalSize, int timeElapsed, int timeRemaining);
  STDMETHOD(OnQueryResume)(void);
  STDMETHOD(OnStatusUpdate)(int status);
};

typedef std::vector<RefPtr<Download>> DownloadList;

class DownloadEvent {
public:
  enum Event {
    DOWNLOAD_ERROR = -1,
    DOWNLOAD_STATUS,
    DOWNLOAD_BEGIN,
    DOWNLOAD_PROGRESS,
    DOWNLOAD_END,
    DOWNLOAD_STOPPED,
    DOWNLOAD_RESUME
  };

  Event GetEvent(void) const { return mEvent; }

  const RefPtr<Download> &GetDownload(void) const { return mDownload; }

  DownloadEvent(Event event, const RefPtr<Download> &download) : mEvent(event), mDownload(download) {}

  ~DownloadEvent() {}

protected:
  // Prevent copy and assignment.
  DownloadEvent(const DownloadEvent &);
  const DownloadEvent &operator=(const DownloadEvent &);

  Event mEvent;
  const RefPtr<Download> mDownload;
};

typedef void (*DownloadWaitCallback)(DownloadEvent &event, unsigned long userdata);

class DownloadWait : public SingleWait, public Observer<DownloadEvent> {
public:
  static RefPtr<DownloadWait> Create(const DownloadList &files);

  void WaitBeginning(void);

  WaitResult GetResult(void);

  void EndWait(WaitResult, const wchar_t *);

  void SetCallback(DownloadWaitCallback callback, unsigned long userdata);

  unsigned int GetDownloadCount(void) const { return mFiles.size(); }

  const RefPtr<Download> &GetCurrentDownload(void) const { return mCurrentDownload; }

protected:
  DownloadWait(const DownloadList &files);
  virtual ~DownloadWait();

  // Prevent copy and assignment
  DownloadWait(const DownloadWait &);
  const DownloadWait &operator=(const DownloadWait &);

  void DoCallback(DownloadEvent &event);

  void HandleNotification(DownloadEvent &);

protected:
  const DownloadList &mFiles;

  int mFileIndex;
  RefPtr<Download> mCurrentDownload;

  DownloadWaitCallback mCallback;
  unsigned long mUserdata;
};

} // namespace WWOnline

#endif // __WOLDOWNLOAD_H__
