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
 *                     $Archive:: /Commando/Code/Combat/c4.h                                  $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 1/08/02 3:05p                                               $*
 *                                                                                             *
 *                    $Revision:: 33                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef C4_H
#define C4_H

#ifndef ALWAYS_H
#include "always.h"
#endif

#ifndef SIMPLEGAMEOBJ_H
#include "simplegameobj.h"
#endif

#ifndef TIMEMGR_H
#include "timemgr.h"
#endif

class AmmoDefinitionClass;
class StaticAnimPhysClass;

/*
** C4GameObjDef - Defintion class for a C4GameObj
*/
class C4GameObjDef : public SimpleGameObjDef {
public:
  C4GameObjDef(void);

  virtual uint32 Get_Class_ID(void) const;
  virtual PersistClass *Create(void) const;
  virtual bool Save(ChunkSaveClass &csave);
  virtual bool Load(ChunkLoadClass &cload);
  virtual const PersistFactoryClass &Get_Factory(void) const;

  DECLARE_EDITABLE(C4GameObjDef, SimpleGameObjDef);

  float ThrowVelocity;

protected:
  friend class C4GameObj;
};

/*
**
*/
class C4GameObj : public SimpleGameObj {

public:
  C4GameObj();
  virtual ~C4GameObj();

  // Definitions
  virtual void Init(void);
  void Init(const C4GameObjDef &definition);
  const C4GameObjDef &Get_Definition(void) const;

  // Save / Load / Construction Factory
  virtual bool Save(ChunkSaveClass &csave);
  virtual bool Load(ChunkLoadClass &cload);
  virtual const PersistFactoryClass &Get_Factory(void) const;

  virtual C4GameObj *As_C4GameObj(void) { return this; }

  void Init_C4(const AmmoDefinitionClass *def, SoldierGameObj *owner, int detonation_mode, const Matrix3D &tm);
  virtual CollisionReactionType Collision_Occurred(const CollisionEventClass &event);

  virtual void Think();
  virtual void Post_Think();

  virtual void Get_Information(StringClass &string);

  virtual void Export_Rare(BitStreamClass &packet);
  virtual void Import_Rare(BitStreamClass &packet);

  ScriptableGameObj *Get_Stuck_Object(void) { return StuckObject.Get_Ptr(); }

  virtual void Completely_Damaged(const OffenseObjectClass &damager);

  SoldierGameObj *Get_Owner(void) const { return (SoldierGameObj *)Owner.Get_Ptr(); }
  void Defuse(void);

  static void Maintain_C4_Limit(int player_type);

private:
  float Timer;
  GameObjReference Owner;
  void *OwnerBackup;
  const AmmoDefinitionClass *AmmoDefinition;
  int DetonationMode;

  bool Stuck;

  bool StuckToObject;
  GameObjReference StuckObject;
  Vector3 StuckOffset;
  int StuckBone;

  StaticAnimPhysClass *StuckStaticAnimObj;
  bool StuckMCT;

  float Age;

  void Detonate(void);
  void Restore_Owner(void);
};

#endif // C4_H
