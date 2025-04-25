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
 *                     $Archive:: /Commando/Code/ww3d2/proto.cpp                              $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 1/08/01 10:04a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   MeshLoaderClass::Load -- reads in a mesh and creates a prototype for it                   *
 *   HModelLoaderClass::Load -- reads in an hmodel definition and creates a prototype for it   *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "proto.h"
#include "mesh.h"
#include "hmdldef.h"
#include "hlod.h"
#include "w3derr.h"

/*
** Global instances of the default loaders for the asset manager to install
*/
MeshLoaderClass _MeshLoader;
HModelLoaderClass _HModelLoader;

/*
** Prototype Classes
** These prototypes are the "built-in" ones for the W3D library.
*/
PrimitivePrototypeClass::PrimitivePrototypeClass(RenderObjClass *proto) {
  Proto = proto;
  assert(Proto);
  Proto->Add_Ref();
}
PrimitivePrototypeClass::~PrimitivePrototypeClass(void) {
  if (Proto) {
    Proto->Release_Ref();
  }
}

const char *PrimitivePrototypeClass::Get_Name(void) const { return Proto->Get_Name(); }

int PrimitivePrototypeClass::Get_Class_ID(void) const { return Proto->Class_ID(); }

RenderObjClass *PrimitivePrototypeClass::Create(void) { return (RenderObjClass *)(SET_REF_OWNER(Proto->Clone())); }

class HModelPrototypeClass : public PrototypeClass {
public:
  HModelPrototypeClass(HModelDefClass *def) {
    HModelDef = def;
    assert(HModelDef);
  }
  virtual ~HModelPrototypeClass(void) {
    if (HModelDef)
      delete HModelDef;
  }

  virtual const char *Get_Name(void) const { return HModelDef->Get_Name(); }
  virtual int Get_Class_ID(void) const { return RenderObjClass::CLASSID_HLOD; }
  virtual RenderObjClass *Create(void) { return NEW_REF(HLodClass, (*HModelDef)); }
  HModelDefClass *HModelDef;
};

/***********************************************************************************************
 * MeshLoaderClass::Load -- reads in a mesh and creates a prototype for it                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   7/28/98    GTH : Created.                                                                 *
 *=============================================================================================*/
PrototypeClass *MeshLoaderClass::Load_W3D(ChunkLoadClass &cload) {
  MeshClass *mesh = NEW_REF(MeshClass, ());

  if (mesh == NULL) {
    return NULL;
  }

  if (mesh->Load_W3D(cload) != WW3D_ERROR_OK) {

    // if the load failed, delete the mesh
    assert(mesh->Num_Refs() == 1);
    mesh->Release_Ref();
    return NULL;

  } else {

    // create the prototype and add it to the lists
    PrimitivePrototypeClass *newproto = new PrimitivePrototypeClass(mesh);
    mesh->Release_Ref();
    return newproto;
  }
}

/***********************************************************************************************
 * HModelLoaderClass::Load -- reads in an hmodel and creates a prototype for it                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   7/28/98    GTH : Created.                                                                 *
 *=============================================================================================*/
PrototypeClass *HModelLoaderClass::Load_W3D(ChunkLoadClass &cload) {
  HModelDefClass *hdef = new HModelDefClass;

  if (hdef == NULL) {
    return NULL;
  }

  if (hdef->Load_W3D(cload) != HModelDefClass::OK) {

    // load failed, delete the model and return an error
    delete hdef;
    return NULL;

  } else {

    // ok, accept this model!
    HModelPrototypeClass *hproto = new HModelPrototypeClass(hdef);
    return hproto;
  }
}
