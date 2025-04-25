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
 *                     $Archive:: /Commando/Code/ww3d2/projector.h                            $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 2/07/01 2:07p                                               $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef PROJECTOR_H
#define PROJECTOR_H

#include "always.h"
#include "matrix3d.h"
#include "matrix4.h"
#include "aabox.h"
#include "obbox.h"

class MatrixMapperClass;

/**
** ProjectorClass
** This is a class which encapsulates the data needed to describe a projection.  It isn't
** really useful by itself but it is a common base class between TexProjectClass and DecalGeneratorClass.
*/
class ProjectorClass {
public:
  ProjectorClass(void);
  virtual ~ProjectorClass(void);

  virtual void Set_Transform(const Matrix3D &tm);
  virtual const Matrix3D &Get_Transform(void) const;

  virtual void Set_Perspective_Projection(float hfov, float vfov, float znear, float zfar);
  virtual void Set_Ortho_Projection(float xmin, float xmax, float ymin, float ymax, float znear, float zfar);

  const OBBoxClass &Get_Bounding_Volume(void) const { return WorldBoundingVolume; }
  void Compute_Texture_Coordinate(const Vector3 &point, Vector3 *set_stq);

protected:
  virtual void Update_WS_Bounding_Volume(void);

  Matrix3D Transform;
  Matrix4 Projection;

  AABoxClass LocalBoundingVolume;
  OBBoxClass WorldBoundingVolume;

  MatrixMapperClass *Mapper;
};

#endif
