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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/animobj.cpp                            $*
 *                                                                                             *
 *                       Author:: Greg_h                                                       *
 *                                                                                             *
 *                     $Modtime:: 12/13/01 6:56p                                              $*
 *                                                                                             *
 *                    $Revision:: 10                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Animatable3DObjClass::Animatable3DObjClass -- constructor                                 *
 *   Animatable3DObjClass::Animatable3DObjClass -- copy constructor                            *
 *   Animatable3DObjClass::~Animatable3DObjClass -- destructor                                 *
 *   Animatable3DObjClass::operator = -- assignment operator                                   *
 *   Animatable3DObjClass::Release -- Releases any anims being held by this object             *
 *   Animatable3DObjClass::Render -- Update this object for rendering                          *
 *   Animatable3DObjClass::Special_Render -- "special render" function for animatables         *
 *   Animatable3DObjClass::Set_Transform -- sets the transform and marks sub-objects as dirty  *
 *   Animatable3DObjClass::Set_Position -- Sets the position and marks sub-objects as dirty    *
 *   Animatable3DObjClass::Get_Num_Bones -- returns number of bones in this object             *
 *   Animatable3DObjClass::Get_Bone_Name -- returns the name of the given bone                 *
 *   Animatable3DObjClass::Get_Bone_Index -- returns the index of the given bone               *
 *   Animatable3DObjClass::Set_Animation -- set the animation state to "none" (base pose)      *
 *   Animatable3DObjClass::Set_Animation -- Set the animation state to the given anim/frame    *
 *   Animatable3DObjClass::Set_Animation -- set the animation state to a blend of two anims    *
 *   Animatable3DObjClass::Set_Animation -- Set animation state with an anim combo             *
 *   Animatable3DObjClass::Get_Bone_Transform -- return the transform for the given bone       *
 *   Animatable3DObjClass::Get_Bone_Transform -- return the transform for the given bone       *
 *   Animatable3DObjClass::Capture_Bone -- capture the specified bone (override animation)     *
 *   Animatable3DObjClass::Release_Bone -- release the specified bone (allow animation)        *
 *   Animatable3DObjClass::Is_Bone_Captured -- returns whether the specified bone is captured  *
 *   Animatable3DObjClass::Control_Bone -- sets the transform for the bone                     *
 *   Animatable3DObjClass::Update_Sub_Object_Transforms -- recalculate the transforms for our  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "animobj.h"
#include "htree.h"
#include "assetmgr.h"
#include "hanim.h"
#include "hcanim.h"
#include "ww3d.h"
#include "wwmemlog.h"
#include "animatedsoundmgr.h"

/***********************************************************************************************
 * Animatable3DObjClass::Animatable3DObjClass -- constructor                                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 * htree_name -- name of the hierarchy tree which defines the "bone" structure for this object *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
Animatable3DObjClass::Animatable3DObjClass(const char *htree_name) : IsTreeValid(0), CurMotionMode(BASE_POSE) {
  // Inline struct members can't be initialized in init list for some reason...
  ModeAnim.Motion = NULL;
  ModeAnim.Frame = 0.0f;
  ModeAnim.PrevFrame = 0.0f;
  ModeAnim.LastSyncTime = WW3D::Get_Sync_Time();
  ModeInterp.Motion0 = NULL;
  ModeInterp.Motion1 = NULL;
  ModeInterp.Frame0 = 0.0f;
  ModeInterp.PrevFrame0 = 0.0f;
  ModeInterp.PrevFrame1 = 0.0f;
  ModeInterp.Frame1 = 0.0f;
  ModeInterp.Percentage = 0.0f;
  ModeCombo.AnimCombo = NULL;

  /*
  ** Store a pointer to the htree
  */
  if (htree_name == NULL) {
    HTree = NULL;
  } else if (htree_name[0] == 0) {
    HTree = new HTreeClass;
    HTree->Init_Default();
  } else {
    HTreeClass *source = WW3DAssetManager::Get_Instance()->Get_HTree(htree_name);
    if (source != NULL) {
      HTree = new HTreeClass(*source);
    } else {
      WWDEBUG_SAY(("Unable to find HTree: %s\r\n", htree_name));
      HTree = new HTreeClass;
      HTree->Init_Default();
    }
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Animatable3DObjClass -- copy constructor                              *
 *                                                                                             *
 * INPUT:                                                                                      *
 * src -- animatable object to copy.                                                           *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
Animatable3DObjClass::Animatable3DObjClass(const Animatable3DObjClass &src)
    : CompositeRenderObjClass(src), IsTreeValid(0), CurMotionMode(BASE_POSE), HTree(NULL) {
  // Inline struct members can't be initialized in init list for some reason...
  ModeAnim.Motion = NULL;
  ModeAnim.Frame = 0.0f;
  ModeAnim.PrevFrame = 0.0f;
  ModeAnim.LastSyncTime = WW3D::Get_Sync_Time();
  ModeInterp.Motion0 = NULL;
  ModeInterp.Motion1 = NULL;
  ModeInterp.Frame0 = 0.0f;
  ModeInterp.PrevFrame0 = 0.0f;
  ModeInterp.PrevFrame1 = 0.0f;
  ModeInterp.Frame1 = 0.0f;
  ModeInterp.Percentage = 0.0f;
  ModeCombo.AnimCombo = NULL;

  *this = src;
}

/***********************************************************************************************
 * Animatable3DObjClass::~Animatable3DObjClass -- destructor                                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
Animatable3DObjClass::~Animatable3DObjClass(void) {
  Release();

  if (HTree) {
    delete HTree;
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::operator = -- assignment operator                                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
Animatable3DObjClass &Animatable3DObjClass::operator=(const Animatable3DObjClass &that) {
  if (&that != this) {
    Release();
    if (HTree) {
      delete HTree;
    }

    CompositeRenderObjClass::operator=(that);

    IsTreeValid = 0;
    CurMotionMode = BASE_POSE;
    ModeAnim.Motion = NULL;
    ModeAnim.Frame = 0.0f;
    ModeAnim.PrevFrame = 0.0f;
    ModeAnim.LastSyncTime = WW3D::Get_Sync_Time();
    ModeInterp.Motion0 = NULL;
    ModeInterp.Motion1 = NULL;
    ModeInterp.Frame0 = 0.0f;
    ModeInterp.PrevFrame0 = 0.0f;
    ModeInterp.PrevFrame1 = 0.0f;
    ModeInterp.Frame1 = 0.0f;
    ModeInterp.Percentage = 0.0f;
    ModeCombo.AnimCombo = NULL;

    HTree = new HTreeClass(*that.HTree);
  }
  return *this;
}

/***********************************************************************************************
 * Animatable3DObjClass::Release -- Releases any anims being held by this object               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Release(void) {
  switch (CurMotionMode) {

  case BASE_POSE:
    break;

  case SINGLE_ANIM:
    if (ModeAnim.Motion != NULL) {
      ModeAnim.Motion->Release_Ref();
      ModeAnim.Motion = NULL;
    }
    break;

  case DOUBLE_ANIM:
    if (ModeInterp.Motion0 != NULL) {
      ModeInterp.Motion0->Release_Ref();
      ModeInterp.Motion0 = NULL;
    }

    if (ModeInterp.Motion1 != NULL) {
      ModeInterp.Motion1->Release_Ref();
      ModeInterp.Motion1 = NULL;
    }
    break;

  case MULTIPLE_ANIM:
    break;

  default:
    break;
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Render -- Update this object for rendering                            *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Render(RenderInfoClass &rinfo) {
  if (HTree == NULL)
    return;

  if (Is_Not_Hidden_At_All() == false) {
    return;
  }

  if (CurMotionMode == SINGLE_ANIM) {
    if (ModeAnim.AnimMode != ANIM_MODE_MANUAL) {
      Single_Anim_Progress();
    }
  }

  if (!Is_Hierarchy_Valid() || Are_Sub_Object_Transforms_Dirty()) {
    Update_Sub_Object_Transforms();
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Special_Render -- "special render" function for animatables           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/10/98   GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Special_Render(SpecialRenderInfoClass &rinfo) {
  if (HTree == NULL)
    return;

  if (CurMotionMode == SINGLE_ANIM) {
    if (ModeAnim.AnimMode != ANIM_MODE_MANUAL) {
      Single_Anim_Progress();
    }
  }

  if (!Is_Hierarchy_Valid()) {
    Update_Sub_Object_Transforms();
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Set_Transform -- sets the transform and marks sub-objects as dirty    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Set_Transform(const Matrix3D &m) {
  CompositeRenderObjClass::Set_Transform(m);
  Set_Hierarchy_Valid(false);
}

/***********************************************************************************************
 * Animatable3DObjClass::Set_Position -- Sets the position and marks sub-objects as dirty      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Set_Position(const Vector3 &v) {
  CompositeRenderObjClass::Set_Position(v);
  Set_Hierarchy_Valid(false);
}

/***********************************************************************************************
 * Animatable3DObjClass::Get_Num_Bones -- returns number of bones in this object               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
int Animatable3DObjClass::Get_Num_Bones(void) {
  if (HTree) {
    return HTree->Num_Pivots();
  } else {
    return 1;
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Get_Bone_Name -- returns the name of the given bone                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
const char *Animatable3DObjClass::Get_Bone_Name(int bone_index) {
  if (HTree) {
    return HTree->Get_Bone_Name(bone_index);
  } else {
    return "RootTransform";
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Get_Bone_Index -- returns the index of the given bone                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
int Animatable3DObjClass::Get_Bone_Index(const char *bonename) {
  if (HTree) {
    return HTree->Get_Bone_Index(bonename);
  } else {
    return 0;
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Set_Animation -- set the animation state to "none" (base pose)        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Set_Animation(void) {
  Release();
  CurMotionMode = BASE_POSE;
  Set_Hierarchy_Valid(false);
}

/***********************************************************************************************
 * Animatable3DObjClass::Set_Animation -- Set the animation state to the given anim/frame      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Set_Animation(HAnimClass *motion, float frame, int mode) {

  if (motion) {
    // Add_Ref before we remove, in case it is the same one.
    motion->Add_Ref();
    Release();
    CurMotionMode = SINGLE_ANIM;
    ModeAnim.Motion = motion;
    ModeAnim.PrevFrame = ModeAnim.Frame;
    ModeAnim.Frame = frame;
    ModeAnim.LastSyncTime = WW3D::Get_Sync_Time();
    ModeAnim.AnimMode = mode;
  } else {
    CurMotionMode = BASE_POSE;
    Release();
  }

  Set_Hierarchy_Valid(false);
}

/***********************************************************************************************
 * Animatable3DObjClass::Set_Animation -- set the animation state to a blend of two anims      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Set_Animation(HAnimClass *motion0, float frame0, HAnimClass *motion1, float frame1,
                                         float percentage) {
  Release();

  CurMotionMode = DOUBLE_ANIM;
  ModeInterp.Motion0 = motion0;
  ModeInterp.Motion1 = motion1;
  ModeInterp.PrevFrame0 = ModeInterp.Frame0;
  ModeInterp.PrevFrame1 = ModeInterp.Frame1;
  ModeInterp.Frame0 = frame0;
  ModeInterp.Frame1 = frame1;
  ModeInterp.Percentage = percentage;
  Set_Hierarchy_Valid(false);

  if (ModeInterp.Motion0 != NULL) {
    ModeInterp.Motion0->Add_Ref();
  }

  if (ModeInterp.Motion1 != NULL) {
    ModeInterp.Motion1->Add_Ref();
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Set_Animation -- Set animation state with an anim combo               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Set_Animation(HAnimComboClass *anim_combo) {
  Release();

  CurMotionMode = MULTIPLE_ANIM;
  ModeCombo.AnimCombo = anim_combo;
  Set_Hierarchy_Valid(false);
}

/***********************************************************************************************
 * Animatable3DObjClass::Peek_Animation
 **
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
HAnimClass *Animatable3DObjClass::Peek_Animation(void) {
  if (CurMotionMode == SINGLE_ANIM) {
    return ModeAnim.Motion;
  } else {
    return NULL;
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Get_Bone_Transform -- return the transform for the given bone         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
const Matrix3D &Animatable3DObjClass::Get_Bone_Transform(const char *bonename) {
  if (HTree) {
    WWASSERT(HTree);
    WWASSERT(bonename);

    int idx = HTree->Get_Bone_Index(bonename);
    return Get_Bone_Transform(idx);
  } else {
    return Get_Transform();
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Get_Bone_Transform -- return the transform for the given bone         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
const Matrix3D &Animatable3DObjClass::Get_Bone_Transform(int boneindex) {
  Validate_Transform();

  if (HTree) {
    /*
    ** If our hierarchy isn't valid, we just need to evaluate our animation
    ** state.
    */
    if (!Is_Hierarchy_Valid()) {
      Update_Sub_Object_Transforms();
    }

    return HTree->Get_Transform(boneindex);
  } else {
    return Transform;
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Capture_Bone -- capture the specified bone (override animation)       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Capture_Bone(int boneindex) {
  if (HTree) {
    HTree->Capture_Bone(boneindex);
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Release_Bone -- release the specified bone (allow animation)          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Release_Bone(int boneindex) {
  if (HTree) {
    HTree->Release_Bone(boneindex);
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Is_Bone_Captured -- returns whether the specified bone is captured    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
bool Animatable3DObjClass::Is_Bone_Captured(int boneindex) const {
  if (HTree) {
    return HTree->Is_Bone_Captured(boneindex);
  } else {
    return false;
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Control_Bone -- sets the transform for the bone                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/99     GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Control_Bone(int bindex, const Matrix3D &objtm, bool world_space_translation) {
#ifdef WWDEBUG
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 4; i++) {
      WWASSERT(WWMath::Is_Valid_Float(objtm[j][i]));
    }
  }
#endif

  if (HTree) {
    HTree->Control_Bone(bindex, objtm, world_space_translation);
    Set_Hierarchy_Valid(false);
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Update_Sub_Object_Transforms -- recalculate the transforms for our su *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/8/98    GTH : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Update_Sub_Object_Transforms(void) {
  /*
  ** The RenderObj impementation will cause our 'container'
  ** to update if we are not valid yet
  */
  CompositeRenderObjClass::Update_Sub_Object_Transforms();

  /*
  ** Update the transforms
  */
  switch (CurMotionMode) {

  case BASE_POSE:
    Base_Update(Transform);
    break;

  case SINGLE_ANIM:
    if (ModeAnim.AnimMode != ANIM_MODE_MANUAL) {
      Single_Anim_Progress();
    }
    Anim_Update(Transform, ModeAnim.Motion, ModeAnim.Frame);

    /*
    **	Play any sounds that are triggered by this frame of animation
    */
    if (ModeAnim.Motion->Has_Embedded_Sounds()) {
      ModeAnim.PrevFrame =
          AnimatedSoundMgrClass::Trigger_Sound(ModeAnim.Motion, ModeAnim.PrevFrame, ModeAnim.Frame, Get_Transform());
    }
    break;

  case DOUBLE_ANIM:
    Blend_Update(Transform, ModeInterp.Motion0, ModeInterp.Frame0, ModeInterp.Motion1, ModeInterp.Frame1,
                 ModeInterp.Percentage);

    /*
    **	Play any sounds that are triggered by this frame of animation
    */
    if (ModeInterp.Motion0->Has_Embedded_Sounds()) {
      ModeInterp.PrevFrame0 = AnimatedSoundMgrClass::Trigger_Sound(ModeInterp.Motion0, ModeInterp.PrevFrame0,
                                                                   ModeInterp.Frame0, Get_Transform());
    }

    if (ModeInterp.Motion1->Has_Embedded_Sounds()) {
      ModeInterp.PrevFrame1 = AnimatedSoundMgrClass::Trigger_Sound(ModeInterp.Motion1, ModeInterp.PrevFrame1,
                                                                   ModeInterp.Frame1, Get_Transform());
    }

    break;

  case MULTIPLE_ANIM: {
    Combo_Update(Transform, ModeCombo.AnimCombo);

    /*
    **	Play any sounds that are triggered by this frame of animation
    */
    int count = ModeCombo.AnimCombo->Get_Num_Anims();
    for (int index = 0; index < count; index++) {
      HAnimClass *motion = ModeCombo.AnimCombo->Peek_Motion(index);

      if (motion != NULL && motion->Has_Embedded_Sounds()) {
        float prev_frame = AnimatedSoundMgrClass::Trigger_Sound(motion, ModeCombo.AnimCombo->Get_Prev_Frame(index),
                                                                ModeCombo.AnimCombo->Get_Frame(index), Get_Transform());
        ModeCombo.AnimCombo->Set_Prev_Frame(index, prev_frame);
      }
    }
    break;
  }

  default:
    break;
  }
  Set_Hierarchy_Valid(true);
}

/***********************************************************************************************
 * Animatable3DObjClass::Simple_Evaluate_Bone -- If the animation is 'single', evaluate the    *
 *																	given
 *pivot and return its transform.		  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   04/13/2000    PDS : Created.                                                              *
 *=============================================================================================*/
bool Animatable3DObjClass::Simple_Evaluate_Bone(int boneindex, Matrix3D *tm) const {
  bool retval = false;

  //
  //	Only do this for simple animations
  //
  if (CurMotionMode == NONE || CurMotionMode == BASE_POSE || CurMotionMode == SINGLE_ANIM) {
    //
    //	Determine which frame we should be on, then use this
    // information to determine the bone's transform.
    //
    float curr_frame = Compute_Current_Frame();
    retval = Simple_Evaluate_Bone(boneindex, curr_frame, tm);

  } else {

    const_cast<Animatable3DObjClass *>(this)->Update_Sub_Object_Transforms();
    *tm = HTree->Get_Transform(boneindex);
  }

  return retval;
}

/***********************************************************************************************
 * Animatable3DObjClass::Simple_Evaluate_Bone -- If the animation is 'single', evaluate the    *
 *																	given
 *pivot and return its transform.		  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   04/13/2000    PDS : Created.                                                                *
 *=============================================================================================*/
bool Animatable3DObjClass::Simple_Evaluate_Bone(int boneindex, float frame, Matrix3D *tm) const {
  bool retval = false;

  //
  //	Only do this for simple animations
  //
  if (HTree != NULL) {

    if (CurMotionMode == SINGLE_ANIM) {
      retval = HTree->Simple_Evaluate_Pivot(ModeAnim.Motion, boneindex, frame, Get_Transform(), tm);
    } else if (CurMotionMode == NONE || CurMotionMode == BASE_POSE) {
      retval = HTree->Simple_Evaluate_Pivot(boneindex, Get_Transform(), tm);
    } else {
      *tm = Transform;
    }

  } else {
    *tm = Transform;
  }

  return retval;
}

/***********************************************************************************************
 * Animatable3DObjClass::Compute_Current_Frame -- Returns the animation frame for the next rend*
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS: Only works for Single and CSingle!                                                *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   04/13/2000    PDS : Created.                                                              *
 *=============================================================================================*/
float Animatable3DObjClass::Compute_Current_Frame() const {
  float frame = 0;

  switch (CurMotionMode) {
  case SINGLE_ANIM: {
    frame = ModeAnim.Frame;

    //
    //	Compute the current frame based on elapsed time.
    //
    if (ModeAnim.AnimMode != ANIM_MODE_MANUAL) {
      float sync_time_diff = WW3D::Get_Sync_Time() - ModeAnim.LastSyncTime;
      frame += ModeAnim.Motion->Get_Frame_Rate() * sync_time_diff * 0.001f;

      //
      //	Wrap the frame
      //
      switch (ModeAnim.AnimMode) {
      case ANIM_MODE_ONCE:
        if (frame >= ModeAnim.Motion->Get_Num_Frames() - 1) {
          frame = ModeAnim.Motion->Get_Num_Frames() - 1;
        }
        break;

      case ANIM_MODE_LOOP:
        if (frame >= ModeAnim.Motion->Get_Num_Frames() - 1) {
          frame -= ModeAnim.Motion->Get_Num_Frames() - 1;
        }
        // If it is still too far out, reset
        if (frame >= ModeAnim.Motion->Get_Num_Frames() - 1) {
          frame = 0;
        }
        break;
      }
    }
  } break;
  }

  return frame;
}

/***********************************************************************************************
 * Animatable3DObjClass::Single_Anim_Progress -- progess anims for loop and once               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:  Only works for Single and CSingle                                                *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/26/99    BMG : Created.                                                                 *
 *=============================================================================================*/
void Animatable3DObjClass::Single_Anim_Progress(void) {
  //
  //	Update the current frame (only works in "SINGLE_ANIM" mode!)
  //
  if (CurMotionMode == SINGLE_ANIM) {

    //
    // Update the frame number and sync time
    //
    ModeAnim.PrevFrame = ModeAnim.Frame;
    ModeAnim.Frame = Compute_Current_Frame();
    ModeAnim.LastSyncTime = WW3D::Get_Sync_Time();

    //
    // Force the heirarchy to be recalculated
    //
    Set_Hierarchy_Valid(false);
  }
}

/***********************************************************************************************
 * Animatable3DObjClass::Is_Animation_Complete -- is the current animation on the last frame?  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS: Only works for Single, ONCE anims                                                 *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/13/99    BMG : Created.                                                                 *
 *=============================================================================================*/
bool Animatable3DObjClass::Is_Animation_Complete(void) const {
  if (CurMotionMode == SINGLE_ANIM) {

    if (ModeAnim.AnimMode == ANIM_MODE_ONCE) {
      return (ModeAnim.Frame == ModeAnim.Motion->Get_Num_Frames() - 1);
    }
  }
  return false;
}

// (gth) TESTING DYNAMICALLY SWAPPING SKELETONS!

void Animatable3DObjClass::Set_HTree(HTreeClass *new_htree) {
  WWMEMLOG(MEM_ANIMATION);
  // try to ensure that the htree we're using has the same structure...
  WWASSERT(new_htree->Num_Pivots() == HTree->Num_Pivots());

  // just assign it...
  if (HTree != NULL) {
    delete HTree;
  }
  HTree = new HTreeClass(*new_htree);
}

// EOF - animobj.cpp