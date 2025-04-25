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
 *                 Project Name : WWPhys                                                       *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/lightenvironment.h                     $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Naty_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 4/01/01 12:01a                                              $*
 *                                                                                             *
 *                    $Revision:: 4                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef LIGHTENVIRONMENT_H
#define LIGHTENVIRONMENT_H

#include "always.h"
#include "vector3.h"

class Matrix3D;
class LightClass;

/**
** LightEnvironmentClass
** This class represents an approximation of the local lighting for a given point.  The idea
** is to collect all of the point light sources affecting an object at any given time and
** create temporary directional light sources representing them.  Any distance or directional
** attenuation will be precalculated into the overall intensity of the light and a vector from
** the light source to the center of the bounding sphere of the model will be used as the
** directional component.
** In addition, the engine will provide the ambient component which will be determined by
** a combination of the ambient setting for the level and sampling the light maps in the area.
**
** Notes:
** - will need fast collection of the lights affecting any one given object
** - intensity of these lights should take into account attenuation of the original light
** - intensity should also take into account spot attenuation (no-per vertex atten...)
** - we need the direction of the lights in eye-space
** - the ambient light from all lights should be added into the ambient light (not just scene)
*/
class LightEnvironmentClass {
public:
  LightEnvironmentClass(void);
  ~LightEnvironmentClass(void);

  /*
  ** Usage (starting from scratch each frame):
  ** - Reset the object
  ** - Set the scene ambient light (will be derived from lightmap sampling probably)
  ** - Add in all overlapping lights, this object will keep the most important ones
  ** - When ready to render, call Pre_Render_Update and push into the gerd.
  **
  ** Usage (caching the lights, only done if the object and the lights are not moving)
  ** - Reset and collect the lights once and keep this object around
  ** - When ready to render, call Pre_Render_Update and push into the gerd.
  */
  void Reset(const Vector3 &object_center, const Vector3 &scene_ambient);
  void Add_Light(const LightClass &light);
  void Pre_Render_Update(const Matrix3D &camera_tm);

  /*
  ** Accessors
  */
  const Vector3 &Get_Equivalent_Ambient(void) const { return OutputAmbient; }
  int Get_Light_Count(void) const { return LightCount; }
  const Vector3 &Get_Light_Direction(int i) const { return InputLights[i].Direction; }
  const Vector3 &Get_Light_Diffuse(int i) const { return InputLights[i].Diffuse; }

  /*
  ** Lighting LOD.  This is a static setting that is used to convert weak diffuse lights
  ** into pure ambient lights.
  */
  static void Set_Lighting_LOD_Cutoff(float inten);
  static float Get_Lighting_LOD_Cutoff(void);

protected:
  enum { MAX_LIGHTS = 4 };

  struct InputLightStruct {
    void Init(const LightClass &light, const Vector3 &object_center);
    void Init_From_Point_Or_Spot_Light(const LightClass &light, const Vector3 &object_center);
    void Init_From_Directional_Light(const LightClass &light, const Vector3 &object_center);
    float Contribution(void);

    Vector3 Direction;
    Vector3 Ambient;
    Vector3 Diffuse;
    bool DiffuseRejected;
  };

  struct OutputLightStruct {
    void Init(const InputLightStruct &input, const Matrix3D &camera_tm);

    Vector3 Direction; // direction to the light.
    Vector3 Diffuse;   // diffuse color * attenuation
  };

  /*
  ** Member variables
  */
  int LightCount;
  Vector3 ObjectCenter;                     // center of the object to be lit
  InputLightStruct InputLights[MAX_LIGHTS]; // input lights

  Vector3 OutputAmbient;                      // scene ambient + lights' ambients
  OutputLightStruct OutputLights[MAX_LIGHTS]; // ouput lights
};

#endif // LIGHTENVIRONMENT_H
