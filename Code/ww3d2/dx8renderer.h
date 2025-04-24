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
 *                 Project Name : ww3d                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/dx8renderer.h                          $*
 *                                                                                             *
 *              Original Author:: Jani Penttinen                                               *
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 2/28/02 5:34p                                               $*
 *                                                                                             *
 *                    $Revision:: 30                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#if defined(_MSC_VER)
#pragma once
#endif

#ifndef DX8_RENDERER_H
#define DX8_RENDERER_H

#include "always.h"
#include "wwstring.h"
#include "simplevec.h"
#include "refcount.h"
#include "vector.h"
#include "dx8list.h"
#include "shader.h"
#include "dx8wrapper.h"
#include "hashtemplate.h"

class IndexBufferClass;
class VertexBufferClass;
class DX8RenderTypeArrayClass;
class MeshClass;
class MeshModelClass;
class DX8PolygonRendererClass;
class Vertex_Split_Table;
class DX8FVFCategoryContainer;
class DecalMeshClass;
class MaterialPassClass;
class MatPassTaskClass;
class PolyRenderTaskClass;
class TextureClass;
class VertexMaterialClass;
class CameraClass;

#define RECORD_RENDER(I,P) render_stats[I].count++; render_stats[I].polys+=P;

/**
** DX8TextureCategoryClass
** This class is used for each Material-Texture-Shader combination that is encountered during rendering.
** Each polygon_renderer that uses the same 'TextureCategory' will be linked to the 'TextureCategory' object.
** Then, all polygons will be rendered in 'TextureCategory' batches to reduce the number of stage changes
** (and most importantly, texture changes) that we cause in DX8.
*/
class DX8TextureCategoryClass : public MultiListObjectClass
{
	int												pass;
	TextureClass *									textures[MAX_TEXTURE_STAGES];
	ShaderClass										shader;
	VertexMaterialClass *						material;					
	DX8PolygonRendererList						PolygonRendererList;
	DX8FVFCategoryContainer*					container;	

	PolyRenderTaskClass *						render_task_head;			// polygon renderers queued for rendering

public:

	DX8TextureCategoryClass(DX8FVFCategoryContainer* container,TextureClass** textures, ShaderClass shd, VertexMaterialClass* mat,int pass);
	~DX8TextureCategoryClass();

	void									Add_Render_Task(DX8PolygonRendererClass * p_renderer,MeshClass * p_mesh);

	void									Render(void);
	bool									Anything_To_Render() { return (render_task_head != NULL); }
	void									Clear_Render_List() { render_task_head = NULL; }

	TextureClass *						Peek_Texture(int stage)	{ return textures[stage]; }
	const VertexMaterialClass *	Peek_Material() { return material; }	
	ShaderClass							Get_Shader() { return shader; }

	DX8PolygonRendererList&			Get_Polygon_Renderer_List() { return PolygonRendererList; }

	unsigned Add_Mesh(
		Vertex_Split_Table& split_buffer,
		unsigned vertex_offset,
		unsigned index_offset,
		IndexBufferClass* index_buffer,
		unsigned pass);
	void Log(bool only_visible);

	void Remove_Polygon_Renderer(DX8PolygonRendererClass* p_renderer);
	void Add_Polygon_Renderer(DX8PolygonRendererClass* p_renderer,DX8PolygonRendererClass* add_after_this=NULL);
	

	DX8FVFCategoryContainer * Get_Container(void) { return container; }
};

// ----------------------------------------------------------------------------

/**
** DX8FVFCategoryContainer
*/

class DX8FVFCategoryContainer : public MultiListObjectClass
{
public:
	enum {
		MAX_PASSES=4
	};
protected:

	TextureCategoryList									texture_category_list[MAX_PASSES];
	TextureCategoryList									visible_texture_category_list[MAX_PASSES];
	
	MatPassTaskClass *									visible_matpass_head;
	MatPassTaskClass *									visible_matpass_tail;
	
	IndexBufferClass *									index_buffer;
	int														used_indices;
	unsigned													FVF;
	unsigned													passes;
	unsigned													uv_coordinate_channels;
	bool														sorting;
	bool														AnythingToRender;
	bool														AnyDelayedPassesToRender;

	void Generate_Texture_Categories(Vertex_Split_Table& split_table,unsigned vertex_offset);
	void Insert_To_Texture_Category(
		Vertex_Split_Table& split_table,
		TextureClass** textures,
		VertexMaterialClass* mat,
		ShaderClass shader,
		int pass,
		unsigned vertex_offset);

	inline bool Anything_To_Render()					{ return AnythingToRender; }
	inline bool Any_Delayed_Passes_To_Render()	{ return AnyDelayedPassesToRender; }

	void Render_Procedural_Material_Passes(void);

	DX8TextureCategoryClass* Find_Matching_Texture_Category(
		TextureClass* texture,
		unsigned pass,
		unsigned stage,
		DX8TextureCategoryClass* ref_category);

	DX8TextureCategoryClass* Find_Matching_Texture_Category(
		VertexMaterialClass* vmat,
		unsigned pass,		
		DX8TextureCategoryClass* ref_category);

public:
	
	DX8FVFCategoryContainer(unsigned FVF,bool sorting);
	virtual ~DX8FVFCategoryContainer();

	static unsigned Define_FVF(MeshModelClass* mmc,unsigned int * user_lighting,bool enable_lighting);
	bool Is_Sorting() const { return sorting; }

	void Change_Polygon_Renderer_Texture(
		DX8PolygonRendererList& polygon_renderer_list,
		TextureClass* texture,
		TextureClass* new_texture,
		unsigned pass,
		unsigned stage);

	void Change_Polygon_Renderer_Material(
		DX8PolygonRendererList& polygon_renderer_list,
		VertexMaterialClass* vmat,
		VertexMaterialClass* new_vmat,
		unsigned pass);

	void Remove_Texture_Category(DX8TextureCategoryClass* tex_category);

	virtual void Render(void)=0;
	virtual void Add_Mesh(MeshClass* mmc)=0;
	virtual void Log(bool only_visible)=0;
	virtual bool Check_If_Mesh_Fits(MeshModelClass* mmc)=0;

	inline unsigned Get_FVF() const { return FVF; }
	
	inline void Add_Visible_Texture_Category(DX8TextureCategoryClass * tex_category,int pass) 
	{
		WWASSERT(pass<MAX_PASSES);
		WWASSERT(tex_category != NULL);
		WWASSERT(texture_category_list[pass].Contains(tex_category));
		visible_texture_category_list[pass].Add(tex_category);
		AnythingToRender=true;
	}

	/*
	** Material pass rendering.  The following two functions allow procedural material passes
	** to be applied to meshes in this FVF category.  In certain cases, the game will *only* render
	** the procedural pass and not the base materials for the mesh.  When this happens there can
	** be rendering errors unless these procedural passes are rendered after all of the meshes in 
	** the scene.  The virtual method Add_Delayed_Material_Pass is used in this case.  
	*/
	void Add_Visible_Material_Pass(MaterialPassClass * pass,MeshClass * mesh);
	virtual void Add_Delayed_Visible_Material_Pass(MaterialPassClass * pass, MeshClass * mesh) = 0;
	virtual void Render_Delayed_Procedural_Material_Passes(void) = 0;
};


/**
** DX8RigidFVFCategoryContainer
** This is an FVFCategoryContainer for rigid (non-skin) meshes
*/
class DX8RigidFVFCategoryContainer : public DX8FVFCategoryContainer
{
public:
	DX8RigidFVFCategoryContainer(unsigned FVF,bool sorting);
	~DX8RigidFVFCategoryContainer();

	void Add_Mesh(MeshClass* mmc);
	void Log(bool only_visible);
	bool Check_If_Mesh_Fits(MeshModelClass* mmc);

	void Render(void);	// Generic render function

	/* 
	** This method adds a material pass which must be rendered after all of the other rendering is complete. 
	** This is needed whenever a mesh turns off its base passes and renders a translucent pass on its geometry.
	*/
	virtual void Add_Delayed_Visible_Material_Pass(MaterialPassClass * pass, MeshClass * mesh);
	virtual void Render_Delayed_Procedural_Material_Passes(void);

protected:


	VertexBufferClass *	vertex_buffer;
	int						used_vertices;

	MatPassTaskClass *	delayed_matpass_head;
	MatPassTaskClass *	delayed_matpass_tail;

};


/**
** DX8SkinFVFCategoryContainer
** This is an FVFCategoryContainer for skin meshes
*/
class DX8SkinFVFCategoryContainer: public DX8FVFCategoryContainer
{
public:
	DX8SkinFVFCategoryContainer(bool sorting);
	~DX8SkinFVFCategoryContainer();

	void Render(void);
	void Add_Mesh(MeshClass* mmc);
	void Log(bool only_visible);
	bool Check_If_Mesh_Fits(MeshModelClass* mmc);

	void Add_Visible_Skin(MeshClass * mesh);

	/* 
	** Since skins are already rendered after the rigid meshes, the Add_Delayed_Material_Pass function simply
	** routes into the Add_Visible_Material_Pass method and no extra overhead is added.
	*/
	virtual void Add_Delayed_Visible_Material_Pass(MaterialPassClass * pass, MeshClass * mesh) { Add_Visible_Material_Pass(pass,mesh); }
	virtual void Render_Delayed_Procedural_Material_Passes(void) { }

private:

	void Reset();

	unsigned int								VisibleVertexCount;
	MeshClass *									VisibleSkinHead;

};


/**
** MeshRegKeyStruct, _RegisteredMeshTable
** This hash table is used to map model+lighting pointer pairs back to meshes
** which are registered with the mesh rendering system.  Whenever a mesh is using
** the same model and lighting array, it can simply clone the polygon renderers
** and re-use the vb and ib data.
*/
struct MeshRegKeyStruct
{
	MeshRegKeyStruct() : Model(nullptr), UserLighting(nullptr) {}
	MeshRegKeyStruct(MeshModelClass * mdl,unsigned int * lighting) : Model(mdl), UserLighting(lighting) {}
	bool operator == (const MeshRegKeyStruct & that) const {
		return ((Model == that.Model) && (UserLighting == that.UserLighting));
	}

	MeshModelClass *	Model;
	unsigned int *		UserLighting;
};

template <>
inline unsigned int HashTemplateKeyClass<MeshRegKeyStruct>::Get_Hash_Value(const MeshRegKeyStruct& k)
{
	unsigned int hval = (unsigned int)(k.Model) + (unsigned int)(k.UserLighting);
	hval = hval + (hval>>5) + (hval>>10) + (hval >> 20);
	return hval;
}




/**
** DX8MeshRendererClass
** This object is controller for the entire DX8 mesh rendering system.  It organizes mesh
** fragments into groups based on FVF, texture, and material.  During rendering, a list of 
** the visible mesh fragments is composed and rendered.  There is a global instance of this
** class called TheDX8MeshRenderer that should be used for all mesh rendering.
*/
class DX8MeshRendererClass
{
public:
	DX8MeshRendererClass();
	~DX8MeshRendererClass();

	void						Init();
	void						Shutdown();

	void						Flush();
	void						Clear_Pending_Delete_Lists();

	void						Log_Statistics_String(bool only_visible);
	static void				Request_Log_Statistics();

	void						Register_Mesh_Type(MeshClass* mesh);
	void						Unregister_Mesh_Type(MeshClass* mesh);
	
	void						Set_Camera(CameraClass* cam) { camera=cam; }
	CameraClass *			Peek_Camera(void)	{ return camera; }
	void						Add_To_Render_List(DecalMeshClass * decalmesh);

	// Enable or disable lighting on all objects inserted from now on. (Doesn't affect the objects that are already in the lists)
	void						Enable_Lighting(bool enable) { enable_lighting=enable; }

	// This should be called at the beginning of a game or menu or after a major modifications to the scene...
	void						Invalidate();

protected:

	void Render_Decal_Meshes(void);

	bool													enable_lighting;
	CameraClass *										camera;

	SimpleDynVecClass<FVFCategoryList *>		texture_category_container_lists_rigid;
	FVFCategoryList *									texture_category_container_list_skin;

	DecalMeshClass *									visible_decal_meshes;

	HashTemplateClass<MeshRegKeyStruct,MeshClass*> _RegisteredMeshTable;

};

extern DX8MeshRendererClass TheDX8MeshRenderer;

#endif