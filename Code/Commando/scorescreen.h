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
 *                     $Archive:: /Commando/Code/Commando/scorescreen.h                       $*
 *                                                                                             *
 *                      $Author:: Byon_g                                                      $*
 *                                                                                             *
 *                     $Modtime:: 10/22/01 7:32p                                              $*
 *                                                                                             *
 *                    $Revision:: 7                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef SCORESCREEN_H
#define SCORESCREEN_H

#ifndef ALWAYS_H
#include "always.h"
#endif

#ifndef GAMEMODE_H
#include "gamemode.h"
#endif

#ifndef __MENU_DIALOG_H
#include "menudialog.h"
#endif

/*
** Game (Sub) Mode to display ScoreScreen view
*/
class ScoreScreenGameModeClass : public GameModeClass {
public:
  virtual const char *Name() { return "ScoreScreen"; } // the name of this mode
  virtual void Init();                                 // called when the mode is activated
  virtual void Shutdown() {}                           // called when the mode is deactivated
  virtual void Think() {}                              // called each time through the main loop
  virtual void Render() {}                             // called each time through the main loop

  void Save_Stats(void);
};

////////////////////////////////////////////////////////////////
//
//	StartSPGameDialogClass
//
////////////////////////////////////////////////////////////////
class ScoreScreenDialogClass : public MenuDialogClass {
public:
  ////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  ////////////////////////////////////////////////////////////////
  ScoreScreenDialogClass(void);

  void On_Init_Dialog(void);
  void On_Destroy(void);
  void On_Command(int ctrl_id, int mesage_id, DWORD param);

private:
  bool ScoreScreenActive;

  int Get_Time_To_Finish_Stars(void);
  int Get_Level_Of_Play_Stars(void);
  int Get_Saves_Loaded_Stars(void);
  int Get_Secondary_Missions_Stars(void);
};

#endif
