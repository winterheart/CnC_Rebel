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
 ***                            Confidential - Westwood Studios                              ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Commando                                                     *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Combat/samsite.h                             $*
 *                                                                                             *
 *                      $Author:: Tom_s                                                       $*
 *                                                                                             *
 *                     $Modtime:: 9/17/01 4:18p                                               $*
 *                                                                                             *
 *                    $Revision:: 24                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef SAMSITE_H
#define SAMSITE_H

#ifndef ALWAYS_H
#include "always.h"
#endif

#ifndef SMARTGAMEOBJ_H
#include "smartgameobj.h"
#endif

/*
** SamSiteGameObjDef - Defintion class for a SamSiteGameObj
*/
class SAMSiteGameObjDef : public SmartGameObjDef {
public:
  SAMSiteGameObjDef(void);

  virtual uint32 Get_Class_ID(void) const;
  virtual PersistClass *Create(void) const;
  virtual bool Save(ChunkSaveClass &csave);
  virtual bool Load(ChunkLoadClass &cload);
  virtual const PersistFactoryClass &Get_Factory(void) const;

  DECLARE_EDITABLE(SAMSiteGameObjDef, SmartGameObjDef);

protected:
  friend class SamSiteGameObj;
};

/*
**
*/
class SAMSiteGameObj : public SmartGameObj {

public:
  SAMSiteGameObj();
  virtual ~SAMSiteGameObj();

  // Definitions
  virtual void Init(void);
  void Init(const SAMSiteGameObjDef &definition);
  const SAMSiteGameObjDef &Get_Definition(void) const;

  // Save / Load / Construction Factory
  virtual bool Save(ChunkSaveClass &csave);
  virtual bool Load(ChunkLoadClass &cload);
  virtual const PersistFactoryClass &Get_Factory(void) const;

  // Think
  virtual void Think(void);

  // Control
  virtual void Generate_Control(void);

  // Turret
  virtual bool Set_Targeting(const Vector3 &pos, bool do_tilt = true); // Set the targeting pos in world space

  // State
  virtual void Import_Frequent(BitStreamClass &packet);
  virtual void Export_Frequent(BitStreamClass &packet);

protected:
  int TurretBone;
  int BarrelBone;
  void Update_Turret(float weapon_turn, float weapon_tilt);

  int State;

  float Timer;
};

#endif //	SAMSITE_H
