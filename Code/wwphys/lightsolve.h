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
 *                 Project Name : wwphys                                                       *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwphys/lightsolve.h                          $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 2/28/02 11:37a                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef LIGHTSOLVE_H
#define LIGHTSOLVE_H

#include "always.h"
#include "physlist.h"

class PhysClass;
class StaticPhysClass;
class RenderObjClass;
class LightSolveContextClass;
class LightSolveProgressClass;

/**
** LightSolveClass
** This class is a collection of static functions which are used to generate static lighting
** solves for the scene or a subset of the scene.
*/

class LightSolveClass
{
public:

static void		Generate_Static_Light_Solve(LightSolveContextClass & context);
static void		Generate_Static_Light_Solve(LightSolveContextClass & context,RefPhysListClass & obj_list);

private:

static void		Compute_Solve(LightSolveContextClass & context,RefPhysListClass & obj_list);
static void		Compute_Solve(LightSolveContextClass & context,StaticPhysClass * phys_obj);
static void		Compute_Solve(LightSolveContextClass & context,RenderObjClass * model,NonRefPhysListClass & light_list);
static bool		Does_Obj_Get_Static_Light_Solve(StaticPhysClass * obj);
static bool		Does_Model_Get_Static_Light_Solve(RenderObjClass * model);

};


#endif //LIGHTSOLVE_H

