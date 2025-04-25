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
 *                     $Archive:: /Commando/Code/Combat/characterclasssettings.cpp     $*
 *                                                                                             *
 *                      $Author:: Patrick                                                     $*
 *                                                                                             *
 *                     $Modtime:: 3/21/01 9:38a                                               $*
 *                                                                                             *
 *                    $Revision:: 4                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "characterclasssettings.h"
#include "combatchunkid.h"
#include "wwhack.h"
#include "persistfactory.h"
#include "definitionfactory.h"
#include "simpledefinitionfactory.h"
#include "debug.h"
#include "objectives.h"

DECLARE_FORCE_LINK(CharClassSettings)

///////////////////////////////////////////////////////////////////////////////////////////
//	Static member initialization
///////////////////////////////////////////////////////////////////////////////////////////
CharacterClassSettingsDefClass *CharacterClassSettingsDefClass::GlobalInstance = NULL;

///////////////////////////////////////////////////////////////////////////////////////////
//	Factories
///////////////////////////////////////////////////////////////////////////////////////////
SimplePersistFactoryClass<CharacterClassSettingsDefClass, CHUNKID_GLOBAL_SETTINGS_DEF_CHAR_CLASS>
    _CharClassDefPersistFactory;
DECLARE_DEFINITION_FACTORY(CharacterClassSettingsDefClass, CLASSID_GLOBAL_SETTINGS_DEF_CHAR_CLASS, "Character Classes")
_CharClassDefDefFactory;

///////////////////////////////////////////////////////////////////////////////////////////
//	Constants
///////////////////////////////////////////////////////////////////////////////////////////

static const char *CHAR_CLASS_NAMES[CharacterClassSettingsDefClass::CLASS_COUNT] = {
    "Minigunner", "Rocket Soldier", "Grenadier", "Engineer", "Flame Thrower", "Mutant"};

static const char *CHAR_RANK_NAMES[CharacterClassSettingsDefClass::RANK_COUNT] = {"Enlisted", "Officer",
                                                                                  "Special-Forces", "Boss"};

static const char *CHAR_TEAM_NAMES[CharacterClassSettingsDefClass::TEAM_COUNT] = {
    "GDI",
    "NOD",
};

///////////////////////////////////////////////////////////////////////////////////////////
//	Save/load constants
///////////////////////////////////////////////////////////////////////////////////////////
enum {
  CHUNKID_PARENT = 0x12021027,
  CHUNKID_VARIABLES,

  VARID_COST_GDI_MINIGUNNER_ENLISTED = 1,
  VARID_COST_GDI_MINIGUNNER_OFFICER,
  VARID_COST_GDI_MINIGUNNER_SPECIAL_FORCES,
  VARID_COST_GDI_MINIGUNNER_BOSS,
  VARID_COST_GDI_ROCKET_SOLDIER_ENLISTED,
  VARID_COST_GDI_ROCKET_SOLDIER_OFFICER,
  VARID_COST_GDI_ROCKET_SOLDIER_SPECIAL_FORCES,
  VARID_COST_GDI_ROCKET_SOLDIER_BOSS,
  VARID_COST_GDI_GRENADIER_ENLISTED,
  VARID_COST_GDI_GRENADIER_OFFICER,
  VARID_COST_GDI_GRENADIER_SPECIAL_FORCES,
  VARID_COST_GDI_GRENADIER_BOSS,
  VARID_COST_GDI_ENGINEER_ENLISTED,
  VARID_COST_GDI_ENGINEER_OFFICER,
  VARID_COST_GDI_ENGINEER_SPECIAL_FORCES,
  VARID_COST_GDI_ENGINEER_BOSS,
  VARID_COST_GDI_FLAME_THROWER_ENLISTED,
  VARID_COST_GDI_FLAME_THROWER_OFFICER,
  VARID_COST_GDI_FLAME_THROWER_SPECIAL_FORCES,
  VARID_COST_GDI_FLAME_THROWER_BOSS,
  VARID_COST_GDI_MUTANT_ENLISTED,
  VARID_COST_GDI_MUTANT_OFFICER,
  VARID_COST_GDI_MUTANT_SPECIAL_FORCES,
  VARID_COST_GDI_MUTANT_BOSS,

  VARID_COST_NOD_MINIGUNNER_ENLISTED,
  VARID_COST_NOD_MINIGUNNER_OFFICER,
  VARID_COST_NOD_MINIGUNNER_SPECIAL_FORCES,
  VARID_COST_NOD_MINIGUNNER_BOSS,
  VARID_COST_NOD_ROCKET_SOLDIER_ENLISTED,
  VARID_COST_NOD_ROCKET_SOLDIER_OFFICER,
  VARID_COST_NOD_ROCKET_SOLDIER_SPECIAL_FORCES,
  VARID_COST_NOD_ROCKET_SOLDIER_BOSS,
  VARID_COST_NOD_GRENADIER_ENLISTED,
  VARID_COST_NOD_GRENADIER_OFFICER,
  VARID_COST_NOD_GRENADIER_SPECIAL_FORCES,
  VARID_COST_NOD_GRENADIER_BOSS,
  VARID_COST_NOD_ENGINEER_ENLISTED,
  VARID_COST_NOD_ENGINEER_OFFICER,
  VARID_COST_NOD_ENGINEER_SPECIAL_FORCES,
  VARID_COST_NOD_ENGINEER_BOSS,
  VARID_COST_NOD_FLAME_THROWER_ENLISTED,
  VARID_COST_NOD_FLAME_THROWER_OFFICER,
  VARID_COST_NOD_FLAME_THROWER_SPECIAL_FORCES,
  VARID_COST_NOD_FLAME_THROWER_BOSS,
  VARID_COST_NOD_MUTANT_ENLISTED,
  VARID_COST_NOD_MUTANT_OFFICER,
  VARID_COST_NOD_MUTANT_SPECIAL_FORCES,
  VARID_COST_NOD_MUTANT_BOSS,

  VARID_DEFID_GDI_MINIGUNNER_ENLISTED,
  VARID_DEFID_GDI_MINIGUNNER_OFFICER,
  VARID_DEFID_GDI_MINIGUNNER_SPECIAL_FORCES,
  VARID_DEFID_GDI_MINIGUNNER_BOSS,
  VARID_DEFID_GDI_ROCKET_SOLDIER_ENLISTED,
  VARID_DEFID_GDI_ROCKET_SOLDIER_OFFICER,
  VARID_DEFID_GDI_ROCKET_SOLDIER_SPECIAL_FORCES,
  VARID_DEFID_GDI_ROCKET_SOLDIER_BOSS,
  VARID_DEFID_GDI_GRENADIER_ENLISTED,
  VARID_DEFID_GDI_GRENADIER_OFFICER,
  VARID_DEFID_GDI_GRENADIER_SPECIAL_FORCES,
  VARID_DEFID_GDI_GRENADIER_BOSS,
  VARID_DEFID_GDI_ENGINEER_ENLISTED,
  VARID_DEFID_GDI_ENGINEER_OFFICER,
  VARID_DEFID_GDI_ENGINEER_SPECIAL_FORCES,
  VARID_DEFID_GDI_ENGINEER_BOSS,
  VARID_DEFID_GDI_FLAME_THROWER_ENLISTED,
  VARID_DEFID_GDI_FLAME_THROWER_OFFICER,
  VARID_DEFID_GDI_FLAME_THROWER_SPECIAL_FORCES,
  VARID_DEFID_GDI_FLAME_THROWER_BOSS,
  VARID_DEFID_GDI_MUTANT_ENLISTED,
  VARID_DEFID_GDI_MUTANT_OFFICER,
  VARID_DEFID_GDI_MUTANT_SPECIAL_FORCES,
  VARID_DEFID_GDI_MUTANT_BOSS,

  VARID_DEFID_NOD_MINIGUNNER_ENLISTED,
  VARID_DEFID_NOD_MINIGUNNER_OFFICER,
  VARID_DEFID_NOD_MINIGUNNER_SPECIAL_FORCES,
  VARID_DEFID_NOD_MINIGUNNER_BOSS,
  VARID_DEFID_NOD_ROCKET_SOLDIER_ENLISTED,
  VARID_DEFID_NOD_ROCKET_SOLDIER_OFFICER,
  VARID_DEFID_NOD_ROCKET_SOLDIER_SPECIAL_FORCES,
  VARID_DEFID_NOD_ROCKET_SOLDIER_BOSS,
  VARID_DEFID_NOD_GRENADIER_ENLISTED,
  VARID_DEFID_NOD_GRENADIER_OFFICER,
  VARID_DEFID_NOD_GRENADIER_SPECIAL_FORCES,
  VARID_DEFID_NOD_GRENADIER_BOSS,
  VARID_DEFID_NOD_ENGINEER_ENLISTED,
  VARID_DEFID_NOD_ENGINEER_OFFICER,
  VARID_DEFID_NOD_ENGINEER_SPECIAL_FORCES,
  VARID_DEFID_NOD_ENGINEER_BOSS,
  VARID_DEFID_NOD_FLAME_THROWER_ENLISTED,
  VARID_DEFID_NOD_FLAME_THROWER_OFFICER,
  VARID_DEFID_NOD_FLAME_THROWER_SPECIAL_FORCES,
  VARID_DEFID_NOD_FLAME_THROWER_BOSS,
  VARID_DEFID_NOD_MUTANT_ENLISTED,
  VARID_DEFID_NOD_MUTANT_OFFICER,
  VARID_DEFID_NOD_MUTANT_SPECIAL_FORCES,
  VARID_DEFID_NOD_MUTANT_BOSS,
};

///////////////////////////////////////////////////////////////////////////////////////////
//
//	CharacterClassSettingsDefClass
//
///////////////////////////////////////////////////////////////////////////////////////////
CharacterClassSettingsDefClass::CharacterClassSettingsDefClass(void) {
  //
  //	Initialize the cost and definition tables
  //
  ::memset(CostTable, 0, sizeof(CostTable));
  ::memset(DefinitionTable, 0, sizeof(DefinitionTable));

  //
  //	Configure the editable system
  //
  for (int class_index = 0; class_index < CLASS_COUNT; class_index++) {
    for (int team_index = 0; team_index < TEAM_COUNT; team_index++) {

      //
      //	Add a separator for this character class
      //
      StringClass name;
      name.Format("Class %s (%s)", CHAR_CLASS_NAMES[class_index], CHAR_TEAM_NAMES[team_index]);
      PARAM_SEPARATOR(CharacterClassSettingsDefClass, (const char *)name);

      //
      // Add a pair of parameters for each rank
      //
      for (int rank_index = 0; rank_index < RANK_COUNT; rank_index++) {

        name.Format("%s Cost", CHAR_RANK_NAMES[rank_index]);
        NAMED_EDITABLE_PARAM(CharacterClassSettingsDefClass, ParameterClass::TYPE_INT,
                             CostTable[class_index][rank_index][team_index], (const char *)name);

        name.Format("%s Object", CHAR_RANK_NAMES[rank_index]);

#ifdef PARAM_EDITING_ON
        GenericDefParameterClass *param =
            new GenericDefParameterClass(&(DefinitionTable[class_index][rank_index][team_index]));
        param->Set_Class_ID(CLASSID_GAME_OBJECT_DEF_SOLDIER);
        param->Set_Name(name);
        GENERIC_EDITABLE_PARAM(CharacterClassSettingsDefClass, param)
#endif // PARAM_EDITING_ON
      }
    }
  }

  GlobalInstance = this;
  return;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//	~CharacterClassSettingsDefClass
//
///////////////////////////////////////////////////////////////////////////////////////////
CharacterClassSettingsDefClass::~CharacterClassSettingsDefClass(void) {
  GlobalInstance = NULL;
  return;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Class_ID
//
///////////////////////////////////////////////////////////////////////////////////////////
uint32 CharacterClassSettingsDefClass::Get_Class_ID(void) const { return CLASSID_GLOBAL_SETTINGS_DEF_CHAR_CLASS; }

///////////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Factory
//
///////////////////////////////////////////////////////////////////////////////////////////
const PersistFactoryClass &CharacterClassSettingsDefClass::Get_Factory(void) const {
  return _CharClassDefPersistFactory;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//	Create
//
///////////////////////////////////////////////////////////////////////////////////////////
PersistClass *CharacterClassSettingsDefClass::Create(void) const {
  WWASSERT(0);
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//	Save
//
///////////////////////////////////////////////////////////////////////////////////////////
bool CharacterClassSettingsDefClass::Save(ChunkSaveClass &csave) {
  csave.Begin_Chunk(CHUNKID_PARENT);
  DefinitionClass::Save(csave);
  csave.End_Chunk();

  //
  //	Save the cost and definition tables...
  // Note:  We save each with its own specific ID because the format (rows/cols)
  // of this table is likely to change...
  //
  csave.Begin_Chunk(CHUNKID_VARIABLES);

  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_MINIGUNNER_ENLISTED, CostTable[CLASS_MINIGUNNER][RANK_ENLISTED][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_MINIGUNNER_OFFICER, CostTable[CLASS_MINIGUNNER][RANK_OFFICER][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_MINIGUNNER_SPECIAL_FORCES,
                    CostTable[CLASS_MINIGUNNER][RANK_SPECIAL_FORCES][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_MINIGUNNER_BOSS, CostTable[CLASS_MINIGUNNER][RANK_BOSS][TEAM_GDI]);

  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_ROCKET_SOLDIER_ENLISTED,
                    CostTable[CLASS_ROCKET_SOLDIER][RANK_ENLISTED][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_ROCKET_SOLDIER_OFFICER,
                    CostTable[CLASS_ROCKET_SOLDIER][RANK_OFFICER][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_ROCKET_SOLDIER_SPECIAL_FORCES,
                    CostTable[CLASS_ROCKET_SOLDIER][RANK_SPECIAL_FORCES][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_ROCKET_SOLDIER_BOSS, CostTable[CLASS_ROCKET_SOLDIER][RANK_BOSS][TEAM_GDI]);

  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_GRENADIER_ENLISTED, CostTable[CLASS_GRENADIER][RANK_ENLISTED][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_GRENADIER_OFFICER, CostTable[CLASS_GRENADIER][RANK_OFFICER][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_GRENADIER_SPECIAL_FORCES,
                    CostTable[CLASS_GRENADIER][RANK_SPECIAL_FORCES][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_GRENADIER_BOSS, CostTable[CLASS_GRENADIER][RANK_BOSS][TEAM_GDI]);

  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_ENGINEER_ENLISTED, CostTable[CLASS_ENGINEER][RANK_ENLISTED][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_ENGINEER_OFFICER, CostTable[CLASS_ENGINEER][RANK_OFFICER][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_ENGINEER_SPECIAL_FORCES,
                    CostTable[CLASS_ENGINEER][RANK_SPECIAL_FORCES][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_ENGINEER_BOSS, CostTable[CLASS_ENGINEER][RANK_BOSS][TEAM_GDI]);

  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_FLAME_THROWER_ENLISTED,
                    CostTable[CLASS_FLAME_THROWER][RANK_ENLISTED][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_FLAME_THROWER_OFFICER,
                    CostTable[CLASS_FLAME_THROWER][RANK_OFFICER][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_FLAME_THROWER_SPECIAL_FORCES,
                    CostTable[CLASS_FLAME_THROWER][RANK_SPECIAL_FORCES][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_FLAME_THROWER_BOSS, CostTable[CLASS_FLAME_THROWER][RANK_BOSS][TEAM_GDI]);

  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_MUTANT_ENLISTED, CostTable[CLASS_MUTANT][RANK_ENLISTED][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_MUTANT_OFFICER, CostTable[CLASS_MUTANT][RANK_OFFICER][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_MUTANT_SPECIAL_FORCES,
                    CostTable[CLASS_MUTANT][RANK_SPECIAL_FORCES][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_GDI_MUTANT_BOSS, CostTable[CLASS_MUTANT][RANK_BOSS][TEAM_GDI]);

  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_MINIGUNNER_ENLISTED,
                    DefinitionTable[CLASS_MINIGUNNER][RANK_ENLISTED][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_MINIGUNNER_OFFICER,
                    DefinitionTable[CLASS_MINIGUNNER][RANK_OFFICER][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_MINIGUNNER_SPECIAL_FORCES,
                    DefinitionTable[CLASS_MINIGUNNER][RANK_SPECIAL_FORCES][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_MINIGUNNER_BOSS, DefinitionTable[CLASS_MINIGUNNER][RANK_BOSS][TEAM_GDI]);

  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_ROCKET_SOLDIER_ENLISTED,
                    DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_ENLISTED][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_ROCKET_SOLDIER_OFFICER,
                    DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_OFFICER][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_ROCKET_SOLDIER_SPECIAL_FORCES,
                    DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_SPECIAL_FORCES][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_ROCKET_SOLDIER_BOSS,
                    DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_BOSS][TEAM_GDI]);

  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_GRENADIER_ENLISTED,
                    DefinitionTable[CLASS_GRENADIER][RANK_ENLISTED][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_GRENADIER_OFFICER, DefinitionTable[CLASS_GRENADIER][RANK_OFFICER][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_GRENADIER_SPECIAL_FORCES,
                    DefinitionTable[CLASS_GRENADIER][RANK_SPECIAL_FORCES][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_GRENADIER_BOSS, DefinitionTable[CLASS_GRENADIER][RANK_BOSS][TEAM_GDI]);

  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_ENGINEER_ENLISTED, DefinitionTable[CLASS_ENGINEER][RANK_ENLISTED][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_ENGINEER_OFFICER, DefinitionTable[CLASS_ENGINEER][RANK_OFFICER][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_ENGINEER_SPECIAL_FORCES,
                    DefinitionTable[CLASS_ENGINEER][RANK_SPECIAL_FORCES][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_ENGINEER_BOSS, DefinitionTable[CLASS_ENGINEER][RANK_BOSS][TEAM_GDI]);

  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_FLAME_THROWER_ENLISTED,
                    DefinitionTable[CLASS_FLAME_THROWER][RANK_ENLISTED][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_FLAME_THROWER_OFFICER,
                    DefinitionTable[CLASS_FLAME_THROWER][RANK_OFFICER][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_FLAME_THROWER_SPECIAL_FORCES,
                    DefinitionTable[CLASS_FLAME_THROWER][RANK_SPECIAL_FORCES][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_FLAME_THROWER_BOSS,
                    DefinitionTable[CLASS_FLAME_THROWER][RANK_BOSS][TEAM_GDI]);

  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_MUTANT_ENLISTED, DefinitionTable[CLASS_MUTANT][RANK_ENLISTED][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_MUTANT_OFFICER, DefinitionTable[CLASS_MUTANT][RANK_OFFICER][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_MUTANT_SPECIAL_FORCES,
                    DefinitionTable[CLASS_MUTANT][RANK_SPECIAL_FORCES][TEAM_GDI]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_GDI_MUTANT_BOSS, DefinitionTable[CLASS_MUTANT][RANK_BOSS][TEAM_GDI]);

  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_MINIGUNNER_ENLISTED, CostTable[CLASS_MINIGUNNER][RANK_ENLISTED][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_MINIGUNNER_OFFICER, CostTable[CLASS_MINIGUNNER][RANK_OFFICER][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_MINIGUNNER_SPECIAL_FORCES,
                    CostTable[CLASS_MINIGUNNER][RANK_SPECIAL_FORCES][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_MINIGUNNER_BOSS, CostTable[CLASS_MINIGUNNER][RANK_BOSS][TEAM_NOD]);

  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_ROCKET_SOLDIER_ENLISTED,
                    CostTable[CLASS_ROCKET_SOLDIER][RANK_ENLISTED][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_ROCKET_SOLDIER_OFFICER,
                    CostTable[CLASS_ROCKET_SOLDIER][RANK_OFFICER][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_ROCKET_SOLDIER_SPECIAL_FORCES,
                    CostTable[CLASS_ROCKET_SOLDIER][RANK_SPECIAL_FORCES][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_ROCKET_SOLDIER_BOSS, CostTable[CLASS_ROCKET_SOLDIER][RANK_BOSS][TEAM_NOD]);

  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_GRENADIER_ENLISTED, CostTable[CLASS_GRENADIER][RANK_ENLISTED][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_GRENADIER_OFFICER, CostTable[CLASS_GRENADIER][RANK_OFFICER][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_GRENADIER_SPECIAL_FORCES,
                    CostTable[CLASS_GRENADIER][RANK_SPECIAL_FORCES][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_GRENADIER_BOSS, CostTable[CLASS_GRENADIER][RANK_BOSS][TEAM_NOD]);

  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_ENGINEER_ENLISTED, CostTable[CLASS_ENGINEER][RANK_ENLISTED][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_ENGINEER_OFFICER, CostTable[CLASS_ENGINEER][RANK_OFFICER][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_ENGINEER_SPECIAL_FORCES,
                    CostTable[CLASS_ENGINEER][RANK_SPECIAL_FORCES][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_ENGINEER_BOSS, CostTable[CLASS_ENGINEER][RANK_BOSS][TEAM_NOD]);

  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_FLAME_THROWER_ENLISTED,
                    CostTable[CLASS_FLAME_THROWER][RANK_ENLISTED][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_FLAME_THROWER_OFFICER,
                    CostTable[CLASS_FLAME_THROWER][RANK_OFFICER][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_FLAME_THROWER_SPECIAL_FORCES,
                    CostTable[CLASS_FLAME_THROWER][RANK_SPECIAL_FORCES][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_FLAME_THROWER_BOSS, CostTable[CLASS_FLAME_THROWER][RANK_BOSS][TEAM_NOD]);

  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_MUTANT_ENLISTED, CostTable[CLASS_MUTANT][RANK_ENLISTED][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_MUTANT_OFFICER, CostTable[CLASS_MUTANT][RANK_OFFICER][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_MUTANT_SPECIAL_FORCES,
                    CostTable[CLASS_MUTANT][RANK_SPECIAL_FORCES][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_COST_NOD_MUTANT_BOSS, CostTable[CLASS_MUTANT][RANK_BOSS][TEAM_NOD]);

  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_MINIGUNNER_ENLISTED,
                    DefinitionTable[CLASS_MINIGUNNER][RANK_ENLISTED][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_MINIGUNNER_OFFICER,
                    DefinitionTable[CLASS_MINIGUNNER][RANK_OFFICER][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_MINIGUNNER_SPECIAL_FORCES,
                    DefinitionTable[CLASS_MINIGUNNER][RANK_SPECIAL_FORCES][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_MINIGUNNER_BOSS, DefinitionTable[CLASS_MINIGUNNER][RANK_BOSS][TEAM_NOD]);

  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_ROCKET_SOLDIER_ENLISTED,
                    DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_ENLISTED][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_ROCKET_SOLDIER_OFFICER,
                    DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_OFFICER][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_ROCKET_SOLDIER_SPECIAL_FORCES,
                    DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_SPECIAL_FORCES][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_ROCKET_SOLDIER_BOSS,
                    DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_BOSS][TEAM_NOD]);

  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_GRENADIER_ENLISTED,
                    DefinitionTable[CLASS_GRENADIER][RANK_ENLISTED][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_GRENADIER_OFFICER, DefinitionTable[CLASS_GRENADIER][RANK_OFFICER][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_GRENADIER_SPECIAL_FORCES,
                    DefinitionTable[CLASS_GRENADIER][RANK_SPECIAL_FORCES][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_GRENADIER_BOSS, DefinitionTable[CLASS_GRENADIER][RANK_BOSS][TEAM_NOD]);

  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_ENGINEER_ENLISTED, DefinitionTable[CLASS_ENGINEER][RANK_ENLISTED][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_ENGINEER_OFFICER, DefinitionTable[CLASS_ENGINEER][RANK_OFFICER][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_ENGINEER_SPECIAL_FORCES,
                    DefinitionTable[CLASS_ENGINEER][RANK_SPECIAL_FORCES][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_ENGINEER_BOSS, DefinitionTable[CLASS_ENGINEER][RANK_BOSS][TEAM_NOD]);

  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_FLAME_THROWER_ENLISTED,
                    DefinitionTable[CLASS_FLAME_THROWER][RANK_ENLISTED][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_FLAME_THROWER_OFFICER,
                    DefinitionTable[CLASS_FLAME_THROWER][RANK_OFFICER][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_FLAME_THROWER_SPECIAL_FORCES,
                    DefinitionTable[CLASS_FLAME_THROWER][RANK_SPECIAL_FORCES][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_FLAME_THROWER_BOSS,
                    DefinitionTable[CLASS_FLAME_THROWER][RANK_BOSS][TEAM_NOD]);

  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_MUTANT_ENLISTED, DefinitionTable[CLASS_MUTANT][RANK_ENLISTED][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_MUTANT_OFFICER, DefinitionTable[CLASS_MUTANT][RANK_OFFICER][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_MUTANT_SPECIAL_FORCES,
                    DefinitionTable[CLASS_MUTANT][RANK_SPECIAL_FORCES][TEAM_NOD]);
  WRITE_MICRO_CHUNK(csave, VARID_DEFID_NOD_MUTANT_BOSS, DefinitionTable[CLASS_MUTANT][RANK_BOSS][TEAM_NOD]);

  csave.End_Chunk();

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//	Load
//
///////////////////////////////////////////////////////////////////////////////////////////
bool CharacterClassSettingsDefClass::Load(ChunkLoadClass &cload) {
  while (cload.Open_Chunk()) {
    switch (cload.Cur_Chunk_ID()) {

    case CHUNKID_PARENT:
      DefinitionClass::Load(cload);
      break;

    case CHUNKID_VARIABLES:
      while (cload.Open_Micro_Chunk()) {
        switch (cload.Cur_Micro_Chunk_ID()) {

          READ_MICRO_CHUNK(cload, VARID_COST_GDI_MINIGUNNER_ENLISTED,
                           CostTable[CLASS_MINIGUNNER][RANK_ENLISTED][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_MINIGUNNER_OFFICER,
                           CostTable[CLASS_MINIGUNNER][RANK_OFFICER][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_MINIGUNNER_SPECIAL_FORCES,
                           CostTable[CLASS_MINIGUNNER][RANK_SPECIAL_FORCES][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_MINIGUNNER_BOSS, CostTable[CLASS_MINIGUNNER][RANK_BOSS][TEAM_GDI]);

          READ_MICRO_CHUNK(cload, VARID_COST_GDI_ROCKET_SOLDIER_ENLISTED,
                           CostTable[CLASS_ROCKET_SOLDIER][RANK_ENLISTED][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_ROCKET_SOLDIER_OFFICER,
                           CostTable[CLASS_ROCKET_SOLDIER][RANK_OFFICER][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_ROCKET_SOLDIER_SPECIAL_FORCES,
                           CostTable[CLASS_ROCKET_SOLDIER][RANK_SPECIAL_FORCES][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_ROCKET_SOLDIER_BOSS,
                           CostTable[CLASS_ROCKET_SOLDIER][RANK_BOSS][TEAM_GDI]);

          READ_MICRO_CHUNK(cload, VARID_COST_GDI_GRENADIER_ENLISTED,
                           CostTable[CLASS_GRENADIER][RANK_ENLISTED][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_GRENADIER_OFFICER, CostTable[CLASS_GRENADIER][RANK_OFFICER][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_GRENADIER_SPECIAL_FORCES,
                           CostTable[CLASS_GRENADIER][RANK_SPECIAL_FORCES][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_GRENADIER_BOSS, CostTable[CLASS_GRENADIER][RANK_BOSS][TEAM_GDI]);

          READ_MICRO_CHUNK(cload, VARID_COST_GDI_ENGINEER_ENLISTED, CostTable[CLASS_ENGINEER][RANK_ENLISTED][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_ENGINEER_OFFICER, CostTable[CLASS_ENGINEER][RANK_OFFICER][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_ENGINEER_SPECIAL_FORCES,
                           CostTable[CLASS_ENGINEER][RANK_SPECIAL_FORCES][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_ENGINEER_BOSS, CostTable[CLASS_ENGINEER][RANK_BOSS][TEAM_GDI]);

          READ_MICRO_CHUNK(cload, VARID_COST_GDI_FLAME_THROWER_ENLISTED,
                           CostTable[CLASS_FLAME_THROWER][RANK_ENLISTED][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_FLAME_THROWER_OFFICER,
                           CostTable[CLASS_FLAME_THROWER][RANK_OFFICER][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_FLAME_THROWER_SPECIAL_FORCES,
                           CostTable[CLASS_FLAME_THROWER][RANK_SPECIAL_FORCES][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_FLAME_THROWER_BOSS,
                           CostTable[CLASS_FLAME_THROWER][RANK_BOSS][TEAM_GDI]);

          READ_MICRO_CHUNK(cload, VARID_COST_GDI_MUTANT_ENLISTED, CostTable[CLASS_MUTANT][RANK_ENLISTED][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_MUTANT_OFFICER, CostTable[CLASS_MUTANT][RANK_OFFICER][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_MUTANT_SPECIAL_FORCES,
                           CostTable[CLASS_MUTANT][RANK_SPECIAL_FORCES][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_COST_GDI_MUTANT_BOSS, CostTable[CLASS_MUTANT][RANK_BOSS][TEAM_GDI]);

          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_MINIGUNNER_ENLISTED,
                           DefinitionTable[CLASS_MINIGUNNER][RANK_ENLISTED][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_MINIGUNNER_OFFICER,
                           DefinitionTable[CLASS_MINIGUNNER][RANK_OFFICER][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_MINIGUNNER_SPECIAL_FORCES,
                           DefinitionTable[CLASS_MINIGUNNER][RANK_SPECIAL_FORCES][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_MINIGUNNER_BOSS,
                           DefinitionTable[CLASS_MINIGUNNER][RANK_BOSS][TEAM_GDI]);

          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_ROCKET_SOLDIER_ENLISTED,
                           DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_ENLISTED][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_ROCKET_SOLDIER_OFFICER,
                           DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_OFFICER][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_ROCKET_SOLDIER_SPECIAL_FORCES,
                           DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_SPECIAL_FORCES][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_ROCKET_SOLDIER_BOSS,
                           DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_BOSS][TEAM_GDI]);

          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_GRENADIER_ENLISTED,
                           DefinitionTable[CLASS_GRENADIER][RANK_ENLISTED][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_GRENADIER_OFFICER,
                           DefinitionTable[CLASS_GRENADIER][RANK_OFFICER][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_GRENADIER_SPECIAL_FORCES,
                           DefinitionTable[CLASS_GRENADIER][RANK_SPECIAL_FORCES][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_GRENADIER_BOSS,
                           DefinitionTable[CLASS_GRENADIER][RANK_BOSS][TEAM_GDI]);

          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_ENGINEER_ENLISTED,
                           DefinitionTable[CLASS_ENGINEER][RANK_ENLISTED][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_ENGINEER_OFFICER,
                           DefinitionTable[CLASS_ENGINEER][RANK_OFFICER][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_ENGINEER_SPECIAL_FORCES,
                           DefinitionTable[CLASS_ENGINEER][RANK_SPECIAL_FORCES][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_ENGINEER_BOSS, DefinitionTable[CLASS_ENGINEER][RANK_BOSS][TEAM_GDI]);

          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_FLAME_THROWER_ENLISTED,
                           DefinitionTable[CLASS_FLAME_THROWER][RANK_ENLISTED][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_FLAME_THROWER_OFFICER,
                           DefinitionTable[CLASS_FLAME_THROWER][RANK_OFFICER][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_FLAME_THROWER_SPECIAL_FORCES,
                           DefinitionTable[CLASS_FLAME_THROWER][RANK_SPECIAL_FORCES][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_FLAME_THROWER_BOSS,
                           DefinitionTable[CLASS_FLAME_THROWER][RANK_BOSS][TEAM_GDI]);

          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_MUTANT_ENLISTED,
                           DefinitionTable[CLASS_MUTANT][RANK_ENLISTED][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_MUTANT_OFFICER,
                           DefinitionTable[CLASS_MUTANT][RANK_OFFICER][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_MUTANT_SPECIAL_FORCES,
                           DefinitionTable[CLASS_MUTANT][RANK_SPECIAL_FORCES][TEAM_GDI]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_GDI_MUTANT_BOSS, DefinitionTable[CLASS_MUTANT][RANK_BOSS][TEAM_GDI]);

          READ_MICRO_CHUNK(cload, VARID_COST_NOD_MINIGUNNER_ENLISTED,
                           CostTable[CLASS_MINIGUNNER][RANK_ENLISTED][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_MINIGUNNER_OFFICER,
                           CostTable[CLASS_MINIGUNNER][RANK_OFFICER][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_MINIGUNNER_SPECIAL_FORCES,
                           CostTable[CLASS_MINIGUNNER][RANK_SPECIAL_FORCES][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_MINIGUNNER_BOSS, CostTable[CLASS_MINIGUNNER][RANK_BOSS][TEAM_NOD]);

          READ_MICRO_CHUNK(cload, VARID_COST_NOD_ROCKET_SOLDIER_ENLISTED,
                           CostTable[CLASS_ROCKET_SOLDIER][RANK_ENLISTED][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_ROCKET_SOLDIER_OFFICER,
                           CostTable[CLASS_ROCKET_SOLDIER][RANK_OFFICER][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_ROCKET_SOLDIER_SPECIAL_FORCES,
                           CostTable[CLASS_ROCKET_SOLDIER][RANK_SPECIAL_FORCES][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_ROCKET_SOLDIER_BOSS,
                           CostTable[CLASS_ROCKET_SOLDIER][RANK_BOSS][TEAM_NOD]);

          READ_MICRO_CHUNK(cload, VARID_COST_NOD_GRENADIER_ENLISTED,
                           CostTable[CLASS_GRENADIER][RANK_ENLISTED][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_GRENADIER_OFFICER, CostTable[CLASS_GRENADIER][RANK_OFFICER][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_GRENADIER_SPECIAL_FORCES,
                           CostTable[CLASS_GRENADIER][RANK_SPECIAL_FORCES][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_GRENADIER_BOSS, CostTable[CLASS_GRENADIER][RANK_BOSS][TEAM_NOD]);

          READ_MICRO_CHUNK(cload, VARID_COST_NOD_ENGINEER_ENLISTED, CostTable[CLASS_ENGINEER][RANK_ENLISTED][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_ENGINEER_OFFICER, CostTable[CLASS_ENGINEER][RANK_OFFICER][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_ENGINEER_SPECIAL_FORCES,
                           CostTable[CLASS_ENGINEER][RANK_SPECIAL_FORCES][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_ENGINEER_BOSS, CostTable[CLASS_ENGINEER][RANK_BOSS][TEAM_NOD]);

          READ_MICRO_CHUNK(cload, VARID_COST_NOD_FLAME_THROWER_ENLISTED,
                           CostTable[CLASS_FLAME_THROWER][RANK_ENLISTED][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_FLAME_THROWER_OFFICER,
                           CostTable[CLASS_FLAME_THROWER][RANK_OFFICER][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_FLAME_THROWER_SPECIAL_FORCES,
                           CostTable[CLASS_FLAME_THROWER][RANK_SPECIAL_FORCES][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_FLAME_THROWER_BOSS,
                           CostTable[CLASS_FLAME_THROWER][RANK_BOSS][TEAM_NOD]);

          READ_MICRO_CHUNK(cload, VARID_COST_NOD_MUTANT_ENLISTED, CostTable[CLASS_MUTANT][RANK_ENLISTED][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_MUTANT_OFFICER, CostTable[CLASS_MUTANT][RANK_OFFICER][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_MUTANT_SPECIAL_FORCES,
                           CostTable[CLASS_MUTANT][RANK_SPECIAL_FORCES][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_COST_NOD_MUTANT_BOSS, CostTable[CLASS_MUTANT][RANK_BOSS][TEAM_NOD]);

          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_MINIGUNNER_ENLISTED,
                           DefinitionTable[CLASS_MINIGUNNER][RANK_ENLISTED][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_MINIGUNNER_OFFICER,
                           DefinitionTable[CLASS_MINIGUNNER][RANK_OFFICER][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_MINIGUNNER_SPECIAL_FORCES,
                           DefinitionTable[CLASS_MINIGUNNER][RANK_SPECIAL_FORCES][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_MINIGUNNER_BOSS,
                           DefinitionTable[CLASS_MINIGUNNER][RANK_BOSS][TEAM_NOD]);

          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_ROCKET_SOLDIER_ENLISTED,
                           DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_ENLISTED][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_ROCKET_SOLDIER_OFFICER,
                           DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_OFFICER][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_ROCKET_SOLDIER_SPECIAL_FORCES,
                           DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_SPECIAL_FORCES][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_ROCKET_SOLDIER_BOSS,
                           DefinitionTable[CLASS_ROCKET_SOLDIER][RANK_BOSS][TEAM_NOD]);

          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_GRENADIER_ENLISTED,
                           DefinitionTable[CLASS_GRENADIER][RANK_ENLISTED][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_GRENADIER_OFFICER,
                           DefinitionTable[CLASS_GRENADIER][RANK_OFFICER][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_GRENADIER_SPECIAL_FORCES,
                           DefinitionTable[CLASS_GRENADIER][RANK_SPECIAL_FORCES][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_GRENADIER_BOSS,
                           DefinitionTable[CLASS_GRENADIER][RANK_BOSS][TEAM_NOD]);

          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_ENGINEER_ENLISTED,
                           DefinitionTable[CLASS_ENGINEER][RANK_ENLISTED][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_ENGINEER_OFFICER,
                           DefinitionTable[CLASS_ENGINEER][RANK_OFFICER][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_ENGINEER_SPECIAL_FORCES,
                           DefinitionTable[CLASS_ENGINEER][RANK_SPECIAL_FORCES][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_ENGINEER_BOSS, DefinitionTable[CLASS_ENGINEER][RANK_BOSS][TEAM_NOD]);

          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_FLAME_THROWER_ENLISTED,
                           DefinitionTable[CLASS_FLAME_THROWER][RANK_ENLISTED][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_FLAME_THROWER_OFFICER,
                           DefinitionTable[CLASS_FLAME_THROWER][RANK_OFFICER][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_FLAME_THROWER_SPECIAL_FORCES,
                           DefinitionTable[CLASS_FLAME_THROWER][RANK_SPECIAL_FORCES][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_FLAME_THROWER_BOSS,
                           DefinitionTable[CLASS_FLAME_THROWER][RANK_BOSS][TEAM_NOD]);

          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_MUTANT_ENLISTED,
                           DefinitionTable[CLASS_MUTANT][RANK_ENLISTED][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_MUTANT_OFFICER,
                           DefinitionTable[CLASS_MUTANT][RANK_OFFICER][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_MUTANT_SPECIAL_FORCES,
                           DefinitionTable[CLASS_MUTANT][RANK_SPECIAL_FORCES][TEAM_NOD]);
          READ_MICRO_CHUNK(cload, VARID_DEFID_NOD_MUTANT_BOSS, DefinitionTable[CLASS_MUTANT][RANK_BOSS][TEAM_NOD]);

        default:
          Debug_Say(("Unhandled Micro Chunk:%d File:%s Line:%d\r\n", cload.Cur_Micro_Chunk_ID(), __FILE__, __LINE__));
          break;
        }
        cload.Close_Micro_Chunk();
      }
      break;

    default:
      Debug_Say(("Unhandled Chunk:%d File:%s Line:%d\r\n", cload.Cur_Chunk_ID(), __FILE__, __LINE__));
      break;
    }

    cload.Close_Chunk();
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Cost
//
///////////////////////////////////////////////////////////////////////////////////////////
int CharacterClassSettingsDefClass::Get_Cost(CLASS char_class, RANK char_rank, TEAM char_team) {
  int cost = -1;

  //
  //	Lookup the cost if we have an entry for the given coords
  //
  if (char_class >= 0 && char_class < CLASS_COUNT && char_rank >= 0 && char_rank < RANK_COUNT && char_team >= 0 &&
      char_team < TEAM_COUNT) {
    cost = CostTable[char_class][char_rank][char_team];
  }

  return cost;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Definition
//
///////////////////////////////////////////////////////////////////////////////////////////
int CharacterClassSettingsDefClass::Get_Definition(CLASS char_class, RANK char_rank, TEAM char_team) {
  int definition_id = -1;

  //
  //	Lookup the definition if we have an entry for the given coords
  //
  if (char_class >= 0 && char_class < CLASS_COUNT && char_rank >= 0 && char_rank < RANK_COUNT && char_team >= 0 &&
      char_team < TEAM_COUNT) {
    definition_id = DefinitionTable[char_class][char_rank][char_team];
  }

  return definition_id;
}
