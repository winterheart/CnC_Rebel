/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**	Copyright 2025 CnC Rebel Developers.
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
 *                 Project Name : WWAudio                                                      *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/WWAudio/Listener.cpp         $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 8/13/01 3:05p                                               $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "Listener.h"
#include "utils.h"
#include "SoundHandle.h"

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Listener3DClass
//
////////////////////////////////////////////////////////////////////////////////////////////////
Listener3DClass::Listener3DClass() {}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	~Listener3DClass
//
////////////////////////////////////////////////////////////////////////////////////////////////
Listener3DClass::~Listener3DClass() { Free_Miles_Handle(); }

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Initialize_Miles_Handle
//
////////////////////////////////////////////////////////////////////////////////////////////////
void Listener3DClass::Initialize_Miles_Handle() {
  MMSLockClass lock;

  // Do we have a valid sample handle from miles?
  if (m_SoundHandle != nullptr) {

    ::AIL_set_3D_position(m_SoundHandle->Get_H3DSAMPLE(), 0.0F, 0.0F, 0.0F);
    ::AIL_set_3D_orientation(m_SoundHandle->Get_H3DSAMPLE(), 0.0F, 0.0F, 1.0F, 0.0F, 1.0F, 0.0F);

    // Associate this object instance with the handle
    m_SoundHandle->Set_Sample_User_Data(INFO_OBJECT_PTR, (S32)this);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Allocate_Miles_Handle
//
////////////////////////////////////////////////////////////////////////////////////////////////
void Listener3DClass::Allocate_Miles_Handle() {}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Free_Miles_Handle
//
////////////////////////////////////////////////////////////////////////////////////////////////
void Listener3DClass::Free_Miles_Handle() {}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	On_Added_To_Scene
//
////////////////////////////////////////////////////////////////////////////////////////////////
void Listener3DClass::On_Added_To_Scene() { Allocate_Miles_Handle(); }

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	On_Removed_From_Scene
//
////////////////////////////////////////////////////////////////////////////////////////////////
void Listener3DClass::On_Removed_From_Scene() { Free_Miles_Handle(); }
