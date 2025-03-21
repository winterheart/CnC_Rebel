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
 *                     $Archive:: /Commando/Code/ww3d2/sphereobj.cpp                          $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 11/24/01 6:17p                                              $*
 *                                                                                             *
 *                    $Revision:: 23                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   SphereRenderObjClass::SphereRenderObjClass -- Constructor                                 *
 *   SphereRenderObjClass::SphereRenderObjClass -- Constructor - init from a definition        *
 *   SphereRenderObjClass::SphereRenderObjClass -- Copy constructor                            *
 *   SphereRenderObjClass::operator -- assignment operator                                     *
 *   SphereRenderObjClass::Get_Num_Polys -- returns number of polygons                         *
 *   SphereRenderObjClass::Get_Name -- returns name                                            *
 *   SphereRenderObjClass::Set_Name -- sets the name                                           *
 *   SphereRenderObjClass::render_Sphere -- submits the Sphere to the GERD                     *
 *   SphereRenderObjClass::vis_render_Sphere -- submits Sphere to the GERD for VIS             *
 *   SphereRenderObjClass::SphereRenderObjClass -- constructor                                 *
 *   SphereRenderObjClass::SphereRenderObjClass -- Constructor - init from a definition        *
 *   SphereRenderObjClass::SphereRenderObjClass -- copy constructor                            *
 *   SphereRenderObjClass::SphereRenderObjClass -- Constructor from a wwmath aaSphere          *
 *   SphereRenderObjClass::operator -- assignment operator                                     *
 *   SphereRenderObjClass::Clone -- clones the Sphere                                          *
 *   SphereRenderObjClass::Class_ID -- returns the class-id for AASphere's                     *
 *   SphereRenderObjClass::Render -- render this Sphere                                        *
 *   SphereRenderObjClass::Special_Render -- special render this Sphere (vis)                  *
 *   SphereRenderObjClass::Set_Transform -- set the transform for this Sphere                  *
 *   SphereRenderObjClass::Set_Position -- Set the position of this Sphere                     *
 *   SphereRenderObjClass::update_cached_Sphere -- update the world-space version of this Spher*
 *   SphereRenderObjClass::Cast_Ray -- cast a ray against this Sphere                          *
 *   SphereRenderObjClass::Cast_AASphere -- cast an AASphere against this Sphere               *
 *   SphereRenderObjClass::Cast_OBSphere -- cast an OBSphere against this Sphere               *
 *   SphereRenderObjClass::Intersect_AASphere -- intersect this Sphere with an AASphere        *
 *   SphereRenderObjClass::Intersect_OBSphere -- Intersect this Sphere with an OBSphere        *
 *   SphereRenderObjClass::Get_Obj_Space_Bounding_Sphere -- return the object-space bounding sp*
 *   SphereRenderObjClass::Get_Obj_Space_Bounding_Sphere -- returns the obj-space bounding Sphe*
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "sphereobj.h"
#include "w3d_util.h"
#include "wwdebug.h"
#include "vertmaterial.h"
#include "ww3d.h"
#include "chunkio.h"
#include "rinfo.h"
#include "coltest.h"
#include "inttest.h"
#include "matrix3.h"
#include "wwmath.h"
#include "assetmgr.h"
#include "wwstring.h"
#include "camera.h"
#include "statistics.h"
#include "dx8wrapper.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "sortingrenderer.h"
#include "visrasterizer.h"


#define SPHERE_NUM_LOD		(6)
#define SPHERE_LOWEST_LOD	(4)
#define SPHERE_HIGHEST_LOD (16)

#define STATIC_SORT_SPHERES	1
#define SPHERE_SORT_LEVEL		1

static bool Sphere_Array_Valid = false;

SphereMeshClass SphereMeshArray[SPHERE_NUM_LOD];


/*
** SphereRenderObjClass Implementation
*/

/***********************************************************************************************
 * SphereRenderObjClass::SphereRenderObjClass -- Constructor                                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
SphereRenderObjClass::SphereRenderObjClass(void)
	:	anim_time (0.0F),
		IsAnimating (true),
		AnimDuration (0.0F),
		SphereMaterial (NULL),
		SphereTexture (NULL),
		Color (0.75F,0.75F,0.75F),
		Scale (1, 1, 1),
		Alpha (1.0F),
		Flags(USE_ALPHA_VECTOR),
		ObjSpaceCenter (0, 0, 0),
		ObjSpaceExtent (1, 1, 1),
		CurrentLOD (SPHERE_NUM_LOD - 1)
{
	Generate_Shared_Mesh_Arrays ( Vector );

	Orientation.Make_Identity();
	memset(Name,0,sizeof(Name));

	Init_Material ();

#if (STATIC_SORT_SPHERES)
	//	(gth) testing whether we can get away without poly-sorting rings and spheres
	Set_Sort_Level(SPHERE_SORT_LEVEL);
#endif
}


/***********************************************************************************************
 * SphereRenderObjClass::SphereRenderObjClass -- Constructor - init from a definition          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
SphereRenderObjClass::SphereRenderObjClass(const W3dSphereStruct & def)
	:	anim_time (0.0F),
		IsAnimating (true),
		AnimDuration (0.0F),
		SphereMaterial (NULL),
		SphereTexture (NULL),
		Color (0.75F,0.75F,0.75F),
		Scale (1, 1, 1),
		Alpha (1.0F),
		Flags(USE_ALPHA_VECTOR),
		ObjSpaceCenter (0, 0, 0),
		ObjSpaceExtent (1, 1, 1),
		CurrentLOD (SPHERE_NUM_LOD - 1)
{
	Generate_Shared_Mesh_Arrays ( Vector );
	Init_Material ();
	Orientation.Make_Identity();
	
	//
	//	Initialize from the defintion
	//
	Set_Name(def.Name);
	Set_Local_Center_Extent (	Vector3 (def.Center.X, def.Center.Y, def.Center.Z),
										Vector3 (def.Extent.X, def.Extent.Y, def.Extent.Z));	

	if (def.TextureName[0] != 0) {
		SphereTexture = WW3DAssetManager::Get_Instance ()->Get_Texture (def.TextureName);
	}

#if (STATIC_SORT_SPHERES)
	//	(gth) testing whether we can get away without poly-sorting rings and spheres
	Set_Sort_Level(SPHERE_SORT_LEVEL);
#endif
}


/***********************************************************************************************
 * SphereRenderObjClass::SphereRenderObjClass -- Copy constructor                              *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
SphereRenderObjClass::SphereRenderObjClass(const SphereRenderObjClass & src)
	:	anim_time (0.0F),
		IsAnimating (true),
		AnimDuration (0.0F),
		SphereMaterial (NULL),
		SphereTexture (NULL),
		Color (0.75F,0.75F,0.75F),
		Scale (1, 1, 1),
		Alpha (1.0F),
		Flags(USE_ALPHA_VECTOR),
		ObjSpaceCenter (0, 0, 0),
		ObjSpaceExtent (1, 1, 1),
		CurrentLOD (SPHERE_NUM_LOD - 1)
{
	Generate_Shared_Mesh_Arrays ( Vector );	
	Init_Material ();
	Orientation.Make_Identity();

	*this = src;

#if (STATIC_SORT_SPHERES)
	//	(gth) testing whether we can get away without poly-sorting rings and spheres
	Set_Sort_Level(SPHERE_SORT_LEVEL);
#endif
}

SphereRenderObjClass::~SphereRenderObjClass()
{
	REF_PTR_RELEASE(SphereMaterial);
} // destructor

/***********************************************************************************************
 * SphereRenderObjClass::operator -- assignment operator                                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
SphereRenderObjClass & SphereRenderObjClass::operator = (const SphereRenderObjClass & that)
{
	if (this != &that) {
		RenderObjClass::operator = (that);
		Set_Name(that.Get_Name());
		Color					= that.Color;
		Alpha					= that.Alpha;
		Scale					= that.Scale;
		Vector				= that.Vector;
		Flags					= that.Flags;
		Orientation			= that.Orientation;
		SphereShader		= that.SphereShader;
		CachedBox			= that.CachedBox;
		anim_time			= that.anim_time;
		AnimDuration		= that.AnimDuration;
		ObjSpaceCenter		= that.ObjSpaceCenter;
		ObjSpaceExtent		= that.ObjSpaceExtent;
		ColorChannel		= that.ColorChannel;
		AlphaChannel		= that.AlphaChannel;
		ScaleChannel		= that.ScaleChannel;
		VectorChannel		= that.VectorChannel;
		
		Set_Texture (that.SphereTexture);
	}

	return *this;
}


/***********************************************************************************************
 * SphereRenderObjClass::Generate_Shared_Mesh_Arrays  -- Generates mesh LOD arrays.				  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/08/00    pds : Created.                                                                *
 *=============================================================================================*/
void SphereRenderObjClass::Generate_Shared_Mesh_Arrays (const AlphaVectorStruct &alphavector)
{
	// Generate shared Mesh Arrays
	if (!Sphere_Array_Valid) {

		float size = SPHERE_LOWEST_LOD;
		float step = (SPHERE_HIGHEST_LOD - SPHERE_LOWEST_LOD);
		step /= SPHERE_NUM_LOD;

		for(int i=0; i < SPHERE_NUM_LOD; i++) {

			SphereMeshArray[i].Generate(1.0f, size, size);

			size+=step;

			SphereMeshArray[i].Set_Alpha_Vector( alphavector, false, false );

		}

		Sphere_Array_Valid = true;
	}

	return ;
}

/***********************************************************************************************
 * SphereRenderObjClass::Init_Material -- Sets up the material and default shader for the sphere.*
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/08/00    pds : Created.                                                                *
 *=============================================================================================*/
void SphereRenderObjClass::Init_Material (void)
{
	REF_PTR_RELEASE (SphereMaterial);

	SphereMaterial = NEW_REF(VertexMaterialClass,());
	SphereMaterial->Set_Ambient(0,0,0);
	SphereMaterial->Set_Diffuse(0,0,0);
	SphereMaterial->Set_Specular(0,0,0);
	SphereMaterial->Set_Emissive(1,1,1);
	SphereMaterial->Set_Opacity(0.25f);	
	SphereMaterial->Set_Shininess(0.0f);
	SphereMaterial->Set_Lighting(true);

	// Texturing, zbuffer, primary gradient, alpha blending
	SphereShader = ShaderClass::_PresetAlphaShader;

}	// Init_Material


/***********************************************************************************************
 * SphereRenderObjClass::Get_Num_Polys -- returns number of polygons                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
int SphereRenderObjClass::Get_Num_Polys(void) const
{
	return SphereMeshArray[ CurrentLOD ].Get_Num_Polys();
}


/***********************************************************************************************
 * SphereRenderObjClass::Set_Texture					                                            *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void SphereRenderObjClass::Set_Texture(TextureClass *tf)
{
	REF_PTR_SET(SphereTexture,tf);
}


/***********************************************************************************************
 * SphereRenderObjClass::Get_Name -- returns name                                              *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
const char * SphereRenderObjClass::Get_Name(void) const
{
	return Name;
}


/***********************************************************************************************
 * SphereRenderObjClass::Set_Name -- sets the name                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void SphereRenderObjClass::Set_Name(const char * name)
{
	WWASSERT(name != NULL);
	WWASSERT(strlen(name) < 2*W3D_NAME_LEN);
	strcpy(Name,name);
}


/***********************************************************************************************
 * SphereRenderObjClass::render_sphere                                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/01/00    jga : Created.                                                                 *
 *   2/19/01    HY  : upgraded to DX8                                                          *
 *=============================================================================================*/
void SphereRenderObjClass::render_sphere()
{
	SphereMeshClass & mesh = SphereMeshArray[ CurrentLOD ];

	if (SphereTexture) {
		SphereShader.Set_Texturing (ShaderClass::TEXTURING_ENABLE);
	} else {
		SphereShader.Set_Texturing (ShaderClass::TEXTURING_DISABLE);
	}
	DX8Wrapper::Set_Shader(SphereShader);
	DX8Wrapper::Set_Texture(0,SphereTexture);
	DX8Wrapper::Set_Material(SphereMaterial);	

	DynamicVBAccessClass vb(BUFFER_TYPE_DYNAMIC_SORTING,dynamic_fvf_type,mesh.Vertex_ct);
	{
		DynamicVBAccessClass::WriteLockClass Lock(&vb);
		VertexFormatXYZNDUV2 *vb = Lock.Get_Formatted_Vertex_Array();

		for (int i=0; i<mesh.Vertex_ct; i++)
		{			
			vb->x = mesh.vtx[i].X;
			vb->y = mesh.vtx[i].Y;
			vb->z = mesh.vtx[i].Z;
			
			vb->nx = mesh.vtx_normal[i].X;		// may not need this!
			vb->ny = mesh.vtx_normal[i].Y;
			vb->nz = mesh.vtx_normal[i].Z;

			if (Flags & USE_ALPHA_VECTOR) {
				vb->diffuse = DX8Wrapper::Convert_Color(mesh.dcg[i]);
			} else {
				vb->diffuse = 0xFFFFFFFF;		// TODO could combine the material color with this and turn off lighting
			}
			
			if (SphereTexture) {
				vb->u1 = mesh.vtx_uv[i].X;
				vb->v1 = mesh.vtx_uv[i].Y;
			}
			vb++;
		}		
	}

	DynamicIBAccessClass ib(BUFFER_TYPE_DYNAMIC_SORTING,mesh.face_ct*3);
	{
		DynamicIBAccessClass::WriteLockClass Lock(&ib);
		unsigned short *mem=Lock.Get_Index_Array();
		for (int i=0; i<mesh.face_ct; i++)
		{
			mem[3*i]=mesh.tri_poly[i].I;
			mem[3*i+1]=mesh.tri_poly[i].J;
			mem[3*i+2]=mesh.tri_poly[i].K;
		}
	}	

	DX8Wrapper::Set_Vertex_Buffer(vb);
	DX8Wrapper::Set_Index_Buffer(ib,0);

#if (STATIC_SORT_SPHERES)
	DX8Wrapper::Draw_Triangles(0,mesh.face_ct,0,mesh.Vertex_ct);
#else
	SortingRendererClass::Insert_Triangles(
		Get_Bounding_Sphere(),
		0,
		mesh.face_ct,
		0,
		mesh.Vertex_ct);
#endif

} // render_sphere


/***********************************************************************************************
 * SphereRenderObjClass::vis_render_sphere -- submits box to the GERD for VIS                  *
 *                                                                                             *
 * this renders the sphere with the specified VIS-ID.                                          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void SphereRenderObjClass::vis_render_sphere(SpecialRenderInfoClass & rinfo,const Vector3 & center,const Vector3 & extent)
{
}	// vis_render_sphere


/***********************************************************************************************
 * SphereRenderObjClass::Clone -- clones the box                                                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
RenderObjClass * SphereRenderObjClass::Clone(void) const
{
	return new SphereRenderObjClass(*this);
}


/***********************************************************************************************
 * SphereRenderObjClass::Class_ID -- returns the class-id for sphere's                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
int SphereRenderObjClass::Class_ID(void) const
{
	return RenderObjClass::CLASSID_SPHERE;
}


/***********************************************************************************************
 * SphereRenderObjClass::Render -- render this box                                              *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void SphereRenderObjClass::Render(RenderInfoClass & rinfo)
{
	if (Is_Not_Hidden_At_All() == false) {
		return;
	}
	
	// If static sort lists are enabled and this mesh has a sort level, put it on the list instead
	// of rendering it.
	unsigned int sort_level = (unsigned int)Get_Sort_Level();

	if (WW3D::Are_Static_Sort_Lists_Enabled() && sort_level != SORT_LEVEL_NONE) {

		WW3D::Add_To_Static_Sort_List(this, sort_level);

	} else {

		// Process texture reductions:
//		if (SphereTexture) SphereTexture->Process_Reduction();

		// Determine LOD

		float screen_size = Get_Screen_Size(rinfo.Camera);
		
		// This code assumes that screen_size returns back the percentage of the screen, 0.0 = 0%, 1.0f = 100%

		// Currently it will use Linear interpolation over 0.0 to 1.0, with the SPHERE_NUM_LOD
		// to set the CurrentLOD

		screen_size = sqrtf(screen_size);

		float lod     = screen_size * ((float) SPHERE_NUM_LOD);
		int	lod_int = lod;
		lod-=lod_int;

		if (lod >= 0.5f) lod_int++;

		if (lod_int < 0) lod_int = 0;
		if (lod_int >= SPHERE_NUM_LOD) lod_int = SPHERE_NUM_LOD-1;

		CurrentLOD = lod_int;


		// End LOD Determination

		Matrix3D temp = Transform;

		// Do Time Based Animation
		animate();

		// Scale

		Vector3 real_scale;
		real_scale.X = ObjSpaceExtent.X * Scale.X;
		real_scale.Y = ObjSpaceExtent.Y * Scale.Y;
		real_scale.Z = ObjSpaceExtent.Z * Scale.Z;
		temp.Scale(real_scale);

		//
		// Configure the alpha
		//
		bool is_additive = (SphereShader.Get_Dst_Blend_Func () == ShaderClass::DSTBLEND_ONE);
		if (is_additive) {
			SphereMaterial->Set_Emissive (Alpha * Color);
		} else {
			SphereMaterial->Set_Opacity (Alpha);
			SphereMaterial->Set_Emissive (Color);
		}

		// If using Alpha Vector, check to see if it needs updated
		if (Flags & USE_ALPHA_VECTOR) {

			bool use_inverse = false;

			if (Flags & USE_INVERSE_ALPHA) {
				use_inverse = true;
			}

			SphereMeshArray[CurrentLOD].Set_Alpha_Vector( Vector, use_inverse, is_additive );
		}

		// Camera Align
		if (Flags & USE_CAMERA_ALIGN) {
			Matrix4 view,ident(true);
			DX8Wrapper::Get_Transform(D3DTS_VIEW,view);

			Vector4 wpos(Transform[0][3],Transform[1][3],Transform[2][3],1);
			Vector4 cpos;

			Matrix4::Transform_Vector(view,wpos,&cpos);
			Matrix3D tm(0.0f, 1.0f, 0.0f, cpos.X,
							0.0f, 0.0f, 1.0f, cpos.Y,
							1.0f, 0.0f, 0.0f, cpos.Z);

			tm.Scale(real_scale);
			DX8Wrapper::Set_Transform(D3DTS_WORLD,ident);
			DX8Wrapper::Set_Transform(D3DTS_VIEW,tm); 
			render_sphere();
			DX8Wrapper::Set_Transform(D3DTS_VIEW,view);
		} else {
			DX8Wrapper::Set_Transform(D3DTS_WORLD,temp);	
			render_sphere();
		}		
	}
}


/***********************************************************************************************
 * SphereRenderObjClass::Special_Render -- special render this box (vis)                        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void SphereRenderObjClass::Special_Render(SpecialRenderInfoClass & rinfo)
{
	Matrix3D temp(1);
	temp.Translate(Transform.Get_Translation());
	
	if (rinfo.RenderType == SpecialRenderInfoClass::RENDER_VIS) {
		WWASSERT(rinfo.VisRasterizer != NULL);
		rinfo.VisRasterizer->Set_Model_Transform(temp);
		vis_render_sphere(rinfo,ObjSpaceCenter,ObjSpaceExtent);
	}
}


/***********************************************************************************************
 * SphereRenderObjClass::Set_Transform -- set the transform for this box                        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void SphereRenderObjClass::Set_Transform(const Matrix3D &m)
{
	RenderObjClass::Set_Transform(m);
	update_cached_box();
}


/***********************************************************************************************
 * SphereRenderObjClass::Set_Position -- Set the position of this box                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void SphereRenderObjClass::Set_Position(const Vector3 &v)
{
	RenderObjClass::Set_Position(v);
	update_cached_box();
}


/***********************************************************************************************
 * SphereRenderObjClass::update_cached_box -- update the world-space version of this box        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void SphereRenderObjClass::update_cached_box(void)
{
	CachedBox.Center = Transform.Get_Translation() + ObjSpaceCenter;
	CachedBox.Extent = ObjSpaceExtent;
}




/***********************************************************************************************
 * SphereRenderObjClass::Get_Obj_Space_Bounding_Sphere -- return the object-space bounding sphe *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void SphereRenderObjClass::Get_Obj_Space_Bounding_Sphere(SphereClass & sphere) const
{
	sphere.Init(ObjSpaceCenter,ObjSpaceExtent.Length());
}


/***********************************************************************************************
 * SphereRenderObjClass::Get_Obj_Space_Bounding_Box -- returns the obj-space bounding box       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void SphereRenderObjClass::Get_Obj_Space_Bounding_Box(AABoxClass & box) const
{
	box.Init(ObjSpaceCenter,ObjSpaceExtent);
}

/***********************************************************************************************
 * SphereRenderObjClass::Update_Cached_Bounding_Volumes -- Updates world-space bounding volumes *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/00    gth : Created.                                                                 *
 *=============================================================================================*/
void SphereRenderObjClass::Update_Cached_Bounding_Volumes(void) const
{
	CachedBoundingBox.Extent.X = ObjSpaceExtent.X * Scale.X;
	CachedBoundingBox.Extent.Y = ObjSpaceExtent.Y * Scale.Y;
	CachedBoundingBox.Extent.Z = ObjSpaceExtent.Z * Scale.Z;

	CachedBoundingSphere.Center = CachedBoundingBox.Center = Get_Position() + ObjSpaceCenter;
	CachedBoundingSphere.Radius = CachedBoundingBox.Extent.Length();

	Validate_Cached_Bounding_Volumes();
}


/***********************************************************************************************
 * SphereRenderObjClass::Get_Default_Color - get the default (or first frame) value				  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/13/2000    pds : Created.                                                               *
 *=============================================================================================*/
Vector3 SphereRenderObjClass::Get_Default_Color(void) const
{
	Vector3 value;
	
	if (ColorChannel.Get_Key_Count () > 0) {
		value = ColorChannel.Get_Key (0).Get_Value ();
	} else {
		value = Color;
	}

	return value;
}


/***********************************************************************************************
 * SphereRenderObjClass::Get_Default_Alpha - get the default (or first frame) value				  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/13/2000    pds : Created.                                                               *
 *=============================================================================================*/
float SphereRenderObjClass::Get_Default_Alpha(void) const
{
	float  value;
	
	if (AlphaChannel.Get_Key_Count () > 0) {
		value = AlphaChannel.Get_Key (0).Get_Value ();
	} else {
		value = Alpha;
	}

	return value;
}


/***********************************************************************************************
 * SphereRenderObjClass::Get_Default_Scale - get the default (or first frame) value				  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/13/2000    pds : Created.                                                               *
 *=============================================================================================*/
Vector3 SphereRenderObjClass::Get_Default_Scale(void) const
{
	Vector3 value;
	
	if (ScaleChannel.Get_Key_Count () > 0) {
		value = ScaleChannel.Get_Key (0).Get_Value ();
	} else {
		value = Scale;
	}

	return value;
}


/***********************************************************************************************
 * SphereRenderObjClass::Get_Default_Vector - get the default (or first frame) value			  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/13/2000    pds : Created.                                                               *
 *=============================================================================================*/
AlphaVectorStruct SphereRenderObjClass::Get_Default_Vector(void) const
{
	AlphaVectorStruct value;
	
	if (VectorChannel.Get_Key_Count () > 0) {
		value = VectorChannel.Get_Key (0).Get_Value ();
	} else {
		value = Vector;
	}

	return value;
}


/***********************************************************************************************
 * SphereRenderObjClass::Update_On_Visibilty	-- Either starts or stops the animation based on visibility*
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   4/04/00    pds : Created.                                                                 *
 *=============================================================================================*/
void SphereRenderObjClass::Update_On_Visibilty(void)
{
	// Simply start or stop the animation based on
	// the visibility state of the primitive.
	if (Is_Not_Hidden_At_All () && Is_Animating () == false) {
		Start_Animating ();
	} else if ((Is_Not_Hidden_At_All () == false) && Is_Animating ()) {
		Stop_Animating ();
	}

	return ;
}


/***********************************************************************************************
 * SphereRenderObjClass::animate	-- Update Current Display state										  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/07/00    jga : Created.                                                                 *
 *=============================================================================================*/
void SphereRenderObjClass::animate (void)
{
	if (Is_Animating ()) {

		if (	ColorChannel.Get_Key_Count () > 0 ||
				AlphaChannel.Get_Key_Count () > 0 ||
				ScaleChannel.Get_Key_Count () > 0 ||
				VectorChannel.Get_Key_Count () > 0)
		{		
			//
			// Convert from milliseconds to seconds and normalize the time
			//
			if (AnimDuration > 0) {
				float	frametime = WW3D::Get_Frame_Time();
				frametime = (frametime * 0.001F) / AnimDuration;
				anim_time += frametime;
			} else {
				anim_time = 1.0F;
			}
			WWASSERT (anim_time >= 0.0F);

			if ((Flags & USE_ANIMATION_LOOP) && anim_time > 1.0F) {
				anim_time -= 1.0F;
			}

			if (ColorChannel.Get_Key_Count () > 0) {
				Color	= ColorChannel.Evaluate (anim_time);
			}
			
			if (AlphaChannel.Get_Key_Count () > 0) {
				Alpha	= AlphaChannel.Evaluate (anim_time);
			}
			
			if (ScaleChannel.Get_Key_Count () > 0) {
				Scale	= ScaleChannel.Evaluate (anim_time);
				Update_Cached_Bounding_Volumes ();
			}
			
			if (VectorChannel.Get_Key_Count () > 0) {
				Vector = VectorChannel.Evaluate (anim_time);
			}
		}
	}

	return ;

} // animate


/*
** SphereLoaderClass Implementation
*/
PrototypeClass * SphereLoaderClass::Load_W3D(ChunkLoadClass & cload)
{
	SpherePrototypeClass *prototype = new SpherePrototypeClass;
	prototype->Load (cload);
	return prototype;
}

/*
** SpherePrototypeClass Implementation
*/
SpherePrototypeClass::SpherePrototypeClass (void)
{
	::memset (&Definition, 0, sizeof (Definition));
	return ;
}

SpherePrototypeClass::SpherePrototypeClass(SphereRenderObjClass *sphere)
{
	::memset (&Definition, 0, sizeof (Definition));	
	::strcpy (Definition.Name, sphere->Get_Name ());

	Definition.DefaultAlpha = sphere->Get_Default_Alpha ();
	Definition.AnimDuration = sphere->AnimDuration;
	Definition.Attributes	= sphere->Get_Flags ();
	Definition.DefaultVector = sphere->Get_Default_Vector ();
	
	Vector3 def_color = sphere->Get_Default_Color ();
	Vector3 def_scale = sphere->Get_Default_Scale ();
	W3dUtilityClass::Convert_Vector (def_color, &Definition.DefaultColor);
	W3dUtilityClass::Convert_Vector (def_scale, &Definition.DefaultScale);
	
	W3dUtilityClass::Convert_Vector (sphere->Get_Box ().Center, &Definition.Center);
	W3dUtilityClass::Convert_Vector (sphere->Get_Box ().Extent, &Definition.Extent);	
	W3dUtilityClass::Convert_Shader (sphere->SphereShader, &Definition.Shader);	

	//
	//	Determine the texture name for this sphere
	//
	if (sphere->SphereTexture != NULL) {
		StringClass name = sphere->SphereTexture->Get_Full_Path();
		const char *filename = ::strrchr (name, '\\');
		if (filename != NULL) {
			filename ++;
		} else {
			filename = name;
		}

		::strcpy (Definition.TextureName, filename);

	}

	//
	//	Save the animateable channels
	//
	ColorChannel	= sphere->Peek_Color_Channel ();
	AlphaChannel	= sphere->Peek_Alpha_Channel ();
	ScaleChannel	= sphere->Peek_Scale_Channel ();
	VectorChannel	= sphere->Peek_Vector_Channel ();
	return ;
}

SpherePrototypeClass::~SpherePrototypeClass (void)
{
	return ;
}

enum
{
	CHUNKID_SPHERE_DEF			= 1,
	CHUNKID_COLOR_CHANNEL,
	CHUNKID_ALPHA_CHANNEL,
	CHUNKID_SCALE_CHANNEL,
	CHUNKID_VECTOR_CHANNEL
};

bool SpherePrototypeClass::Load (ChunkLoadClass &cload)
{
	ColorChannel.Reset ();
	AlphaChannel.Reset ();
	ScaleChannel.Reset ();
	VectorChannel.Reset ();

	while (cload.Open_Chunk ()) {
		switch (cload.Cur_Chunk_ID ()) {
			
			case CHUNKID_SPHERE_DEF:
				cload.Read (&Definition, sizeof (Definition));
				break;

			case CHUNKID_COLOR_CHANNEL:
				ColorChannel.Load (cload);
				break;

			case CHUNKID_ALPHA_CHANNEL:
				AlphaChannel.Load (cload);
				break;

			case CHUNKID_SCALE_CHANNEL:
				ScaleChannel.Load (cload);
				break;

			case CHUNKID_VECTOR_CHANNEL:
				VectorChannel.Load (cload);
				break;
		}

		cload.Close_Chunk ();
	}

	return true;
}

bool SpherePrototypeClass::Save (ChunkSaveClass &csave)
{	
	csave.Begin_Chunk (W3D_CHUNK_SPHERE);

		csave.Begin_Chunk (CHUNKID_SPHERE_DEF);
			csave.Write (&Definition, sizeof (Definition));
		csave.End_Chunk ();

		if (ColorChannel.Get_Key_Count () > 0) {
			csave.Begin_Chunk (CHUNKID_COLOR_CHANNEL);
			ColorChannel.Save (csave);
			csave.End_Chunk ();
		}

		if (AlphaChannel.Get_Key_Count () > 0) {
			csave.Begin_Chunk (CHUNKID_ALPHA_CHANNEL);
			AlphaChannel.Save (csave);
			csave.End_Chunk ();
		}


		if (ScaleChannel.Get_Key_Count () > 0) {
			csave.Begin_Chunk (CHUNKID_SCALE_CHANNEL);
			ScaleChannel.Save (csave);
			csave.End_Chunk ();
		}

		if (VectorChannel.Get_Key_Count () > 0) {
			csave.Begin_Chunk (CHUNKID_VECTOR_CHANNEL);
			VectorChannel.Save (csave);
			csave.End_Chunk ();
		}

	csave.End_Chunk ();
	return true;
}

const char * SpherePrototypeClass::Get_Name(void) const
{
	return Definition.Name;
}

int SpherePrototypeClass::Get_Class_ID(void) const
{
	return RenderObjClass::CLASSID_SPHERE;
}
	
RenderObjClass * SpherePrototypeClass::Create(void)
{
	//
	//	Create the new render object
	//
	SphereRenderObjClass *sphere = new SphereRenderObjClass (Definition);
	
	//
	//	Configure the sphere
	//
	W3dUtilityClass::Convert_Shader (Definition.Shader, &sphere->SphereShader);		
	if (WW3DAssetManager::Get_Instance()->Get_Activate_Fog_On_Load()) {
		sphere->SphereShader.Enable_Fog ("SpherePrototypeClass");
	}
	W3dUtilityClass::Convert_Vector (Definition.DefaultColor, &sphere->Color);
	W3dUtilityClass::Convert_Vector (Definition.DefaultScale, &sphere->Scale);
	sphere->Vector = Definition.DefaultVector;
	sphere->Set_Animation_Duration (Definition.AnimDuration);	
	sphere->Alpha = Definition.DefaultAlpha;
	sphere->Set_Flags (Definition.Attributes);
	
	//
	//	Initialize the render object with the keyframe arrays
	//
	sphere->Set_Color_Channel (ColorChannel);
	sphere->Set_Alpha_Channel (AlphaChannel);
	sphere->Set_Scale_Channel (ScaleChannel);
	sphere->Set_Vector_Channel (VectorChannel);
	return sphere;
}

/*
** Global instance of the box loader
*/
SphereLoaderClass _SphereLoader;


//
// Vertices are ordered as such
//  North Pole, stack 1, stack 2, stack x..., SouthPole
//
/***********************************************************************************************
 * SphereMeshClass::SphereMeshClass -- Constructor for SphereMesh Geometry							  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/07/00    jga : Created.                                                                 *
 *=============================================================================================*/
SphereMeshClass::SphereMeshClass(float radius, int slices, int stacks):
Radius(radius),
Slices(slices),
Stacks(stacks),
Vertex_ct(0),	
vtx(NULL),
vtx_normal(NULL),
vtx_uv(NULL),
strip_ct(0),
strip_size(0),
strips(NULL),
fan_ct(0),
fan_size(0),
fans(NULL),
face_ct(0),
tri_poly(NULL),
inverse_alpha(false)
{
	// compute # of vertices
	// 1st 2 vertices, represent, north, and south pole (Y - axis)
	
	Generate(radius, slices, stacks);

} // SphereMesh Constructor

/***********************************************************************************************
 * SphereMeshClass::SphereMeshClass -- Constructor for SphereMesh Geometry							  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/07/00    jga : Created.                                                                 *
 *=============================================================================================*/
SphereMeshClass::SphereMeshClass(void):
Radius(0.0f),
Slices(0),
Stacks(0),
Vertex_ct(0),	
vtx(NULL),
vtx_normal(NULL),
vtx_uv(NULL),
strip_ct(0),
strip_size(0),
strips(NULL),
fan_ct(0),
fan_size(0),
fans(NULL),
face_ct(0),
tri_poly(NULL),
inverse_alpha(false)
{

} // Empty SphereMesh Constructor



/***********************************************************************************************
 * SphereMeshClass::Set_Alpha_Vector -- Unit Direction Vector, for Alpha hole effects			  *
 *                                                                                             *
 * INPUT: vector4 v   ; Unit Vector pointing into the sphere in object space                   *
 *        .W =  Intensity  ; Percent Effect                                                    *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/07/00    jga : Created.                                                                 *
 *=============================================================================================*/
void	SphereMeshClass::Set_Alpha_Vector (const AlphaVectorStruct &v, bool inverse, bool is_additive, bool force)
{
	//
	//	Exit if there is nothing to do...
	//
	if (	alpha_vector == v &&
			inverse == inverse_alpha &&
			is_additive == IsAdditive &&
			!force)
	{
		return ;
	}

	inverse_alpha = inverse;
	alpha_vector = v;

	float Intensity = v.intensity;
	assert(Intensity >= 0.0f);

	Vector3 vec = alpha_vector.angle.Rotate_Vector (Vector3 (1, 0, 0));

	if (inverse_alpha) {
		for (int idx=0; idx < Vertex_ct; idx++) {

			float temp;
			temp = vec * vtx_normal[idx];
			temp*= Intensity;
			
			temp = fabs(temp);
			
			if (temp > 1.0f) temp = 1.0f;

			Set_DCG (is_additive, idx, temp);
		}

	} else {

		for (int idx=0; idx < Vertex_ct; idx++) {

			float temp;
			temp = vec * vtx_normal[idx];
			temp*= Intensity;
			
			temp = fabs(temp);
			
			if (temp > 1.0f) temp = 1.0f;

			Set_DCG (is_additive, idx, 1.0F - temp);
		}
	}

	return ;
} // Set_Alpha_Vector


/***********************************************************************************************
 * SphereMeshClass::Generate -- Alloc Memory, and Generate Geometry, for the SphereMesh		  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/07/00    jga : Created.                                                                 *
 *=============================================================================================*/
void SphereMeshClass::Generate(float radius, int slices, int stacks)
{
	// compute # of vertices
	// 1st 2 vertices, represent, north, and south pole (Y - axis)

	Free();
	
	Slices = slices;
	Stacks = stacks;
	Radius = radius;

	face_ct = (Slices * Stacks * 2);

	Vertex_ct = ((Slices+1) * Stacks) + 2;

	vtx			= new Vector3[Vertex_ct];
	vtx_normal	= new Vector3[Vertex_ct];
	vtx_uv		= new Vector2[Vertex_ct];
	dcg			= new Vector4[Vertex_ct];

	Matrix3 mat;
	Vector3 vec(0.0f, 0.0f, radius);

	Vector3 *veclist = vtx;
	Vector2 *uv      = vtx_uv;

	*veclist = vec;	// assign north pole
	veclist++;

	// Generate Vertex UV coordinates
	//
	//															   0,0 _____ 1,0
	//  Texture maps UV's look something like this 		|_____|
	//																0,1		 1,1
	//
	//

	uv->U = 0.5f; uv->V = 0.0f;		// assign uv for north pole
	uv++;

	for (stacks = 0; stacks < Stacks; stacks++) {
		
		float stackstep  = ((float)stacks + 1) / ((float) Stacks+1);
		float XAxisAngle = WWMATH_PI * stackstep;

		for (slices = 0; slices <= Slices; slices++) {

			float slicestep  = ((float)slices) / ((float)Slices);
			float YAxisAngle = (WWMATH_PI * 2.0f) * slicestep;


			mat.Make_Identity();
			mat.Rotate_Z( YAxisAngle );
			mat.Rotate_X( XAxisAngle );
			*veclist = mat * vec;

			veclist++;

			// update UV

			uv->U = slicestep;
			uv->V = stackstep;
			uv++;

		} // for slices
	} // for stacks

	// Assign vertex for south pole;
	*veclist = -1.0f * vec;
	uv->U = 0.5f; uv->V = 1.0f;	// uv for south pole

	// Generate Vertex Normals

	Vector3 *src = vtx;
	Vector3 *dst = vtx_normal;

	for(int idx = 0; idx < Vertex_ct; idx++) {
		
		Vector3 temp;

		temp = src[idx];
		temp.Normalize();
		dst[idx] = temp;
	}


	// Generate Fans for North + south pole
	fan_ct = 2;
	fan_size = Slices+2;
	fans = new int[fan_size * fan_ct];
	
	// Do Fan #1
	for (int ct = 0; ct < fan_size; ct++) {
		fans[ct] = ct;
	}
	//fans[ct] = 1;

	// Do Fan #2
	int vtx_idx = Vertex_ct - 1;
	for (int ct = fan_size; ct < (fan_size * 2); ct++) {
		fans[ct] = vtx_idx;
		vtx_idx--;
	}
	//fans[ct]	= Vertex_ct - 2;

	// Generate Strips, for the inbetween stacks

	strip_size = ((Slices+1) * 2);
	strip_ct = Stacks - 1;
	if (strip_ct) {
		strips = new int[strip_size * strip_ct];
		for (stacks = 0; stacks < strip_ct; stacks++) {
			// outer loop for each stack
			int store_idx = stacks * strip_size;
			int base_vtx  = 1 + (stacks * (Slices+1));
			int cur_vtx = base_vtx;

			for(int ct = 0; ct <= Slices; ct++) {

				strips[store_idx]   = cur_vtx + (Slices+1);
				strips[store_idx+1] = cur_vtx;

				cur_vtx++;
				store_idx+=2;

			}

			// Last, special case +2
			//strips[store_idx]   = base_vtx + Slices;
			//strips[store_idx+1] = base_vtx;
		}
	}

	// Generate Tri-Poly Indices

	tri_poly		= new TriIndex[face_ct];	// 3 indices per triangle

	TriIndex *out = tri_poly;
	int	   *in;

	for (stacks = 0; stacks < strip_ct; stacks++) {

		in  = &strips[strip_size * stacks];

		// Strip to Poly Function
		// IJK
		for(int fidx=0; fidx < (strip_size - 2); fidx++) {

			out->I = in[0];
			out->J = in[1];
			out->K = in[2];

			out++;
			in++;
			
			fidx++;
			if (fidx >= (strip_size-2)) break;

			out->I = in[0];
			out->J = in[2];
			out->K = in[1];
			out++;
			in++;

		}

		// End Strip to Poly Function
	}


	// Fans to Poly Function

	for(slices = 0; slices < fan_ct; slices++) {

		in = &fans[fan_size * slices];
		int *base_idx = in;

		for (int fidx=0; fidx < (fan_size - 2); fidx++) {

			out->I = base_idx[0];
			out->J = in[2];
			out->K = in[1];

			in++;
			out++;
		}

	}

	// Make Sure ptr is where I expect it to be
	WWASSERT(((int)out) == ((int)(tri_poly + face_ct)));

	//
	//	Fill in the DCG array
	//
	Set_Alpha_Vector (alpha_vector, inverse_alpha, IsAdditive, true);
	return ;

} // Generate



/***********************************************************************************************
 * SphereMeshClass::~SphereMeshClass -- Destructor                                             *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/07/00    jga : Created.                                                                 *
 *=============================================================================================*/
SphereMeshClass::~SphereMeshClass(void)
{

	Free();

} // Destructor


/***********************************************************************************************
 * SphereMeshClass::Free Memory used by geometry for the SphereMesh                            *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/07/00    jga : Created.                                                                 *
 *=============================================================================================*/
void SphereMeshClass::Free(void)
{
	if (vtx)				delete [] vtx;
	if (vtx_normal)	delete [] vtx_normal;
	if (vtx_uv)			delete [] vtx_uv;
	if (dcg)				delete [] dcg;
	if (strips)			delete [] strips;
	if (fans)			delete [] fans;
	if (tri_poly)		delete [] tri_poly;

	vtx			= NULL;
	vtx_normal	= NULL;
	vtx_uv		= NULL;
 	dcg			= NULL;
	strips		= NULL;
	fans			= NULL;
	tri_poly		= NULL;

}

// EOF - sphereobj.cpp

