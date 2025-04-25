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
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/VisSectorSampler.h           $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 8/04/00 8:51a                                               $*
 *                                                                                             *
 *                    $Revision:: 4                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef VISSECTORSAMPLER_H
#define VISSECTORSAMPLER_H

#include "always.h"
#include "vector3.h"

class RenderObjClass;
class MeshBuilderClass;
class SceneEditorClass;
class VisGenProgressClass;
class Matrix3D;

/**
** VisSectorSamplerClass
** This class encapsulates the process of adaptively sampling a vis sector.  It will generate
** an edge table of all of the "external" edges of the vis-sector meshes contained in the
** given model and then adaptively sample along them.
*/
class VisSectorSamplerClass {
public:
  VisSectorSamplerClass(SceneEditorClass *scene, VisGenProgressClass *Stats, float min_point_distance,
                        int collision_group);
  ~VisSectorSamplerClass(void);

  void Process(RenderObjClass *model);

protected:
  void Reset(int poly_count);
  int Collect_Polygons(RenderObjClass *model);
  void Sample_Edges(void);
  void Sample_Edge(const Vector3 &p0, const Vector3 &p1);
  int Sample_Point(const Vector3 &point);
  int Sample_Vertical_Segment(const Vector3 &p0, const Vector3 &p1);
  int Update_Vis(const Vector3 &point);
  bool Check_Ceiling(const Vector3 &position, float *ceiling_dist);
  bool Is_Object_Invalid_Roof(RenderObjClass *render_obj);
  bool Do_View_Planes_Pass(const Matrix3D &vis_transform);

  SceneEditorClass *Scene;
  MeshBuilderClass *MeshBuilder;
  VisGenProgressClass *Stats;
  float MinSampleDistance;
  int CollisionGroup;

  float EdgeSkipAccum;
};

#endif // VISSECTORSAMPLER_H
