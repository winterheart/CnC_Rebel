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
 *                 Project Name : LevelEdit                                                    *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/ZoneNode.h       $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 10/09/00 1:11p                                              $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __ZONE_NODE_H
#define __ZONE_NODE_H

#include "objectnode.h"
#include "icons.h"
#include "spawn.h"
#include "GrabHandles.h"

// Forward declarations
class PresetClass;
class ScriptZoneGameObj;

////////////////////////////////////////////////////////////////////////////
//
//	ZoneNodeClass
//
////////////////////////////////////////////////////////////////////////////
class ZoneNodeClass : public ObjectNodeClass {
public:
  //////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  //////////////////////////////////////////////////////////////////
  ZoneNodeClass(PresetClass *preset = NULL);
  ZoneNodeClass(const ZoneNodeClass &src);
  ~ZoneNodeClass(void);

  //////////////////////////////////////////////////////////////
  //	Public operators
  //////////////////////////////////////////////////////////////
  const ZoneNodeClass &operator=(const ZoneNodeClass &src);

  //////////////////////////////////////////////////////////////////
  //	Public methods
  //////////////////////////////////////////////////////////////////

  //
  //	From PersistClass
  //
  virtual const PersistFactoryClass &Get_Factory(void) const;
  virtual bool Save(ChunkSaveClass &csave);
  virtual bool Load(ChunkLoadClass &cload);

  // From NodeClass
  NodeClass *Clone(void) { return new ZoneNodeClass(*this); }
  void Initialize(void);
  NODE_TYPE Get_Type(void) const { return NODE_TYPE_ZONE; }
  int Get_Icon_Index(void) const { return ZONE_ICON; }
  PhysClass *Peek_Physics_Obj(void) const;
  bool Is_Static(void) const { return false; }
  void Hide(bool hide);

  //
  //	Scene methods
  //
  void Add_To_Scene(void);
  void Remove_From_Scene(void);

  //
  //	Notifications
  //
  void On_Rotate(void);
  void On_Translate(void);
  void On_Transform(void);

  //
  //	Export methods
  //
  void Pre_Export(void);
  void Post_Export(void);

  //
  //	Zone edit methods
  //
  void On_Vertex_Drag_Begin(int vertex_index);
  void On_Vertex_Drag(int vertex_index, POINT point);

  //
  //	ZoneNodeClass specific
  //
  Box3DClass *Get_Box(void);
  ScriptZoneGameObj *Get_Zone_Obj(void) const { return (ScriptZoneGameObj *)m_GameObj; }

protected:
  //////////////////////////////////////////////////////////////////
  //	Protected methods
  //////////////////////////////////////////////////////////////////
  void Update_Zone_Obj(void);

private:
  //////////////////////////////////////////////////////////////////
  //	Private member data
  //////////////////////////////////////////////////////////////////
  Box3DPhysClass *m_PhysObj;
  GrabHandlesClass m_GrabHandles;
  Vector3 m_FirstPoint;
  Vector3 m_CachedSize;
};

//////////////////////////////////////////////////////////////////
//	Peek_Physics_Obj
//////////////////////////////////////////////////////////////////
inline PhysClass *ZoneNodeClass::Peek_Physics_Obj(void) const { return m_PhysObj; }

//////////////////////////////////////////////////////////////////
//	On_Rotate
//////////////////////////////////////////////////////////////////
inline void ZoneNodeClass::On_Rotate(void) {
  if (m_IsInScene) {
    m_GrabHandles.Position_Around_Node(this);
  }

  Update_Zone_Obj();
  NodeClass::On_Rotate();
  return;
}

//////////////////////////////////////////////////////////////////
//	On_Translate
//////////////////////////////////////////////////////////////////
inline void ZoneNodeClass::On_Translate(void) {
  if (m_IsInScene) {
    m_GrabHandles.Position_Around_Node(this);
  }

  Update_Zone_Obj();
  NodeClass::On_Translate();
  return;
}

//////////////////////////////////////////////////////////////////
//	On_Transform
//////////////////////////////////////////////////////////////////
inline void ZoneNodeClass::On_Transform(void) {
  if (m_IsInScene) {
    m_GrabHandles.Position_Around_Node(this);
  }

  Update_Zone_Obj();
  NodeClass::On_Transform();
  return;
}

//////////////////////////////////////////////////////////////////
//	Get_Box
//////////////////////////////////////////////////////////////////
inline Box3DClass *ZoneNodeClass::Get_Box(void) {
  Box3DClass *box = NULL;
  if (m_PhysObj != NULL) {
    box = m_PhysObj->Get_Box();
  }

  return box;
}

#endif //__ZONE_NODE_H
