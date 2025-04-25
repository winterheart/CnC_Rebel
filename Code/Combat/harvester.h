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
 *                 Project Name : Combat
 **
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Combat/harvester.h          $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 11/29/01 11:03a                                             $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __HARVESTER_H
#define __HARVESTER_H

#include "gameobjobserver.h"
#include "vector3.h"
#include "obbox.h"
#include "wwstring.h"

////////////////////////////////////////////////////////////////
//	Forward declarations
////////////////////////////////////////////////////////////////
class RefineryGameObj;
class VehicleGameObj;

////////////////////////////////////////////////////////////////
//
//	HarvesterClass
//
////////////////////////////////////////////////////////////////
class HarvesterClass : public GameObjObserverClass {
public:
  ////////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  ////////////////////////////////////////////////////////////////////
  HarvesterClass(void);
  ~HarvesterClass(void);

  ////////////////////////////////////////////////////////////////////
  //	Public methods
  ////////////////////////////////////////////////////////////////////

  //
  //	Initialization
  //
  void Initialize(void);

  //
  //	Timestep
  //
  void Think(void);

  //
  //	Action control
  //
  void Go_Harvest(void);
  void Go_Unload_Tiberium(void);
  void Unload_Tiberium(void);
  void Harvest_Tiberium(void);
  void Stop(void);

  //
  //	Accessors
  //
  void Set_Refinery(RefineryGameObj *refinery) { Refinery = refinery; }
  void Set_Dock_Location(const Vector3 &pos) { DockLocation = pos; }
  void Set_Dock_Entrance(const Vector3 &pos) { DockEntrance = pos; }
  void Set_Tiberium_Region(const OBBoxClass &box) { TiberiumRegion = box; }
  void Set_Harvest_Anim(const char *name) { HarvestAnimationName = name; }
  VehicleGameObj *Get_Vehicle(void) { return Vehicle; }

  //
  //	From GameObjObeserverClass
  //
  const char *Get_Name(void) { return "HarvesterClass"; }
  void Action_Complete(GameObject *obj, int action_id, ActionCompleteReason complete_reason);
  void Animation_Complete(GameObject *obj, const char *animation_name);
  void Custom(GameObject *game_obj, int type, int param, GameObject *sender);
  void Attach(GameObject *game_obj);
  void Detach(GameObject *game_obj);

  //
  //	Unused methods from the base class
  //
  void Killed(GameObject *, GameObject *) {}
  void Damaged(GameObject *, GameObject *, float amount);
  void Created(GameObject *) {}
  void Destroyed(GameObject *);
  void Sound_Heard(GameObject *, const CombatSound &) {}
  void Enemy_Seen(GameObject *, GameObject *) {}
  void Timer_Expired(GameObject *, int) {}
  void Poked(GameObject *, GameObject *) {}
  void Entered(GameObject *, GameObject *) {}
  void Exited(GameObject *, GameObject *) {}

private:
  ////////////////////////////////////////////////////////////////////
  //	Private constants
  ////////////////////////////////////////////////////////////////////
  typedef enum {
    STATE_UNINITIALIZED = 0,
    STATE_GOING_TO_HARVEST,
    STATE_HARVESTING,
    STATE_GOING_TO_UNLOAD,
    STATE_UNLOADING
  } HarvesterState;

  ////////////////////////////////////////////////////////////////////
  //	Private methods
  ////////////////////////////////////////////////////////////////////
  void Play_Harvest_Animation(bool onoff);

  ////////////////////////////////////////////////////////////////////
  //	Private member data
  ////////////////////////////////////////////////////////////////////
  RefineryGameObj *Refinery;
  Vector3 DockLocation;
  Vector3 DockEntrance;
  HarvesterState State;
  OBBoxClass TiberiumRegion;
  VehicleGameObj *Vehicle;
  StringClass HarvestAnimationName;
  float StateTimer;
  float HarvestTimer;
  bool IsHarvesting;
};

#endif //__HARVESTER_H
