--
--	Command & Conquer Renegade(tm)
--	Copyright 2025 Electronic Arts Inc.
--
--	This program is free software: you can redistribute it and/or modify
--	it under the terms of the GNU General Public License as published by
--	the Free Software Foundation, either version 3 of the License, or
--	(at your option) any later version.
--
--	This program is distributed in the hope that it will be useful,
--	but WITHOUT ANY WARRANTY; without even the implied warranty of
--	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--	GNU General Public License for more details.
--
--	You should have received a copy of the GNU General Public License
--	along with this program.  If not, see <http://www.gnu.org/licenses/>.
--

------------------------------------------------------------------------
--
-- SceneSetup.ms - This script allows an artist to set up their MAX
-- scene to contain multiple LOD and damage models. It contains various
-- functions that the artist can invoke manually if they wish. Those
-- functions are named in "studlyCaps". Functions intended to be used
-- internally have lowercase names with underscores.
--
------------------------------------------------------------------------


struct SS_bounding_box ( _min = [0,0,0], _max = [0,0,0] )


-- SS_replace_extension provides the same functionality as the "Assign
-- Extensions" button on the W3D tools panel, except in script.
function SS_replace_extension
	name_str
	new_extension
= (
	-- If there's no extension, return the given name.
	if new_extension == undefined then
		return name_str

	-- Find the "." in the name. If there is none, just tack the
	-- extension on then end and return it.
	local dot_index = findString name_str "."
	if dot_index == undefined then
	(
		if new_extension.count == 1 then
			return name_str + ".0" + new_extension
		else
			return name_str + "." + new_extension
	)

	-- Replace the two characters after the dot with the new extension.
	local replace_str
	if new_extension.count == 1 then
		replace_str = "0" + new_extension
	else
		replace_str = new_extension
	return (replace name_str (dot_index+1) 2 replace_str)
)


-- SS_clone_tree is used to clone a whole hierarchy of objects. The cloning
-- procedure to be used is passed in as an argument, making this a very
-- flexible function. It operates recursively, cloning each object and
-- maintaining each object's place in the hierarchy and its W3D AppData.
function SS_clone_tree
	tree_root
	offset:[-100,0,0]
	parent:undefined
	clone_proc:reference
	extension:undefined
= (
	-- Create a new object that is a clone of the given one.
	local new_object = clone_proc tree_root
	
	-- Change the extension of this node's name if we were given one.
	if extension != undefined then
	(
		local new_name = SS_replace_extension new_object.name extension
		if new_name != undefined then
			new_object.name = new_name
 	)
	
	-- Copy the AppData attached to the tree_root to the new node.
	wwCopyAppData new_object tree_root
	
	-- Move the new object by the given offset.
	move new_object offset
	
	-- Attach the object to its parent in the new tree (if it's not undefined).
	if parent != undefined then
		attachObjects parent new_object move:false
	
	-- Dupe all the children of the current root.
	for child in tree_root.children do
	(
		SS_clone_tree child offset:offset parent:new_object \
			clone_proc:clone_proc extension:extension
	)
	
	-- Return the new root.
	return new_object
)

function SS_duplicate_skin_info
	source_root
	target_root
	new_wsm:undefined	-- WWSkin WSM to attach target objects to
	tree:undefined		-- root node of the target tree
= (
	if tree == undefined then tree = target_root
	if source_root.modifiers["WWSkin Binding"] != undefined then
	(
		-- Copy the skin info for this object into the target object.
		-- If we haven't copied the WSM yet, it will be copied.
		local retval = wwCopySkinInfo source_root target_root new_wsm tree
		if retval == undefined then
		(
			print("Error copying skin info from " + source_root.name + \
				" to " + target_root.name)
		)
		else new_wsm = retval
	)
	
	-- Duplicate the skin info for all of our children
	local i
	for i = 1 to source_root.children.count do
	(
		local source_child = source_root.children[i]
		local target_child = target_root.children[i]
		new_wsm = SS_duplicate_skin_info source_child target_child \
			new_wsm:new_wsm tree:tree
	)
	
	return new_wsm
)

-- SS_create_lod_models creates a number of LOD models based on the given
-- hierarchy root. Each LOD is cloned from the previous one (as opposed
-- to them all being clones of the root).
function SS_create_lod_models
	number
	tree_root
	offset:[-100,0,0]
	clone_proc:reference
= (
	local lod_roots = #()
	local previous_lod = tree_root
	for i = 1 to number do
	(
		local ext = i as string
		lod_roots[i] = SS_clone_tree previous_lod offset:offset \
					   parent:previous_lod.parent clone_proc:clone_proc \
					   extension:ext
		
		local original_wsm = wwFindSkinNode previous_lod
		if original_wsm != undefined then
		(
			-- Find the WSM we cloned.
			local cloned_wsm = wwFindSkinNode lod_roots[i]
			if cloned_wsm == undefined then
				print "Warning: A WWSkin object was found but it wasn't linked to the base object!"
			else
			(
				-- Duplicate the WWSkin WSM (but meshes will not be bound to it).
				-- ie. The duplicated WSM will contain the correct bone names.
				local wsm = wwDuplicateSkinWSM original_wsm lod_roots[i]
				if wsm == undefined then
					messageBox("Error: Unable to duplicate the skin object for LOD " + ext)
				else
				(
					-- Copy position, name, etc.
					wsm.name = cloned_wsm.name
					wsm.transform = cloned_wsm.transform
					wsm.parent = cloned_wsm.parent
					delete cloned_wsm

					-- Create a new WWSkin WSM for this LOD with no bindings at all.
					--local wsm = WWSkinSpaceWarp()
					--wsm.name = SS_replace_extension original_wsm.name ext
					--wsm.transform = original_wsm.transform
					--move wsm offset			
					--wsm.parent = lod_roots[i]
				)
			)
		)

		print ("Built model: " + lod_roots[i].name)
		previous_lod = lod_roots[i]
	)
	
	-- Return the array of LOD root nodes in the order they were created.
	return lod_roots
)


-- SS_create_damage_models creates a number of LOD models based on the
-- given hierarchy root. Each damage model is cloned from the root.
function SS_create_damage_models
	number
	tree_root
	offset:[0,-100,0]
	clone_proc:reference
= (
	local apply_offset = offset
	local damage_roots = #()
	for i = 1 to number do
	(
		local ext = i as string
		damage_roots[i] = SS_clone_tree tree_root offset:apply_offset \
						parent:tree_root.parent clone_proc:clone_proc \
						extension:ext
		
		-- Rename the damage root from "Origin.xx" to "Damage.%02d",i
		if i < 10 then
			damage_roots[i].name = "Damage.0" + ext
		else
			damage_roots[i].name = "Damage." + ext
		
		-- If there is an object bound to a WWSkin WSM, duplicate the
		-- WSM and copy the skin information over to the new object.
		local wsm = SS_duplicate_skin_info tree_root damage_roots[i]
		
		-- Skin information has been duplicated, now replace the cloned
		-- skin WSM with the one we just created with the correct data.
		if wsm != undefined then
		(
			local cloned_wsm = wwFindSkinNode damage_roots[i]
			if cloned_wsm != undefined then
			(
				wsm.name = cloned_wsm.name
				wsm.transform = cloned_wsm.transform
				wsm.parent = cloned_wsm.parent
				delete cloned_wsm
			)
			else
				print "Warning: A WWSkin object was found but it wasn't linked to the base object!"
		)

		print ("Built model: " + damage_roots[i].name)
			
		-- Shift the next model by offset again.
		apply_offset = apply_offset + offset
	)
	
	-- Return the array of damage root nodes in the order they were created.
	return damage_roots
)

-- SS_query_integer prompts the user to input an integer value. This
-- interaction takes place in the pink/white window in the bottom left
-- of the MAX interface, making it a fallback UI.
function SS_query_integer
	prompt:
= (
	local number = getKBValue prompt:prompt
	if classOf number != integer then
		throw "The number must be an integer!"
	return number	
)


-- SS_get_tree_bbox figures out the bounding box of a hierarchical model.
-- Returns a SS_bounding_box struct containing the min and max points of the
-- node and its children.
function SS_get_tree_bbox
	root
	bbox:undefined
= (
	if root == undefined then return undefined
	
	if bbox == undefined then
	(
		bbox = SS_bounding_box _min:root.min _max:root.max
	)
	else
	(
		if root.min.x < bbox._min.x then
			bbox._min.x = root.min.x
		if root.min.y < bbox._min.y then
			bbox._min.y = root.min.y
		if root.min.z < bbox._min.z then
			bbox._min.z = root.min.z
		
		if root.max.x > bbox._max.x then
			bbox._max.x = root.max.x
		if root.max.y > bbox._max.y then
			bbox._max.y = root.max.y
		if root.max.z > bbox._max.z then
			bbox._max.z = root.max.z
	)
	
	for child in root.children do
		bbox = SS_get_tree_bbox child bbox:bbox
	
	return bbox
)


-- SS_get_set_bbox figures out the bounding box of an ObjectSet.
function SS_get_set_bbox
	object_set
	bbox:undefined
= (
	if object_set == undefined then return undefined
	
	bbox = SS_bounding_box _min:object_set.min _max:object_set.max
	return bbox
)


-- SS_get_origin_size figures out how big to make the origin cube based
-- on the size of the bounding box of the given object (including it's
-- children in the bbox calculation).
function SS_get_origin_size
	object_set
= (
	bbox = SS_get_set_bbox object_set
	if bbox == undefined then
	(
		print "Bounding box calculation error for new origin, defaulting" \
			" to origin of size 5"
		return 5.0
	)
	
	-- Figure out the smallest bounding box dimension.
	local min_size = bbox._max.x - bbox._min.x
	if (bbox._max.y - bbox._min.y) < min_size then
		min_size = bbox._max.y - bbox._min.y
	if (bbox._max.z - bbox._min.z) < min_size then
		min_size = bbox._max.z - bbox._min.z
	
	-- Origin size will be 1/6 of the smallest bounding box dimension.
	return min_size / 6
)


-- SS_create_origin creates a box to serve as the origin of a model. This is used
-- by sceneSetup if there is no Origin.00 node present in the scene.
function SS_create_origin
	name:"Origin.00"
= (
		
	-- Figure out how big our origin should be. Its size will be based
	-- on the bounding box of the objects in the scene.
	local origin_size = SS_get_origin_size geometry
	
	-- Create a new box, and rename it to the given name.
	-- The origin is created very small so that it doesn't interfere with
	-- the bounding box calculations later on when we figure out exactly
	-- how big the origin should be!
	local origin = Box width:origin_size height:origin_size length:origin_size
	origin.name = name
	origin.pos.z -= origin_size / 2
	origin.pivot.z = 0

	-- Set the box's AppData to the appropriate values for an origin node.
	wwSetOriginAppData origin

	return origin
)


-- SS_build_hierarchy attaches all top-level objects to the given root node.
-- It then assigns ALL OBJECTS IN THE SCENE an extension of ".00"
function SS_build_hierarchy
	root
= (
	-- Attach all top-level objects to the given root.
	local top_level = $/*
	for obj in top_level do
	(
		if obj == root then continue
		print ("Attaching " + obj.name + " to " + root.name)
		attachObjects root obj move:false
	)

	-- Append a ".00" extension to ALL objects in the scene.
	for obj in objects do
	(
		local new_name = SS_replace_extension obj.name "00"
		if new_name != undefined then
			obj.name = new_name
	)
)

-- USER-CALLABLE: Set up LODs based on the Origin.00 hierarchy (by default).
-- The user can specify the number of LODs to create, how much to offset
-- each model by, the method of cloning (copy, instance, reference), and
-- the root of the hierarchy the LODs should be based on.
--
-- Sample call:
--	createLOD count:2 offset:[-2,0,0] clone_by:copy root:$'Origin.02'
function createLOD
	count:-1				-- default of -1 means prompt the user
	offset:[-100,0,0]		-- offset by -100 on X axis by default
	clone_by:reference		-- default to cloning by reference
	root:undefined			-- clone Origin.00 if not specified
= (
	if root == undefined then
		root = $'Origin.00'
	if root == undefined then
	(
		-- Create the origin node and link up a hierarchy.
		root = SS_create_origin()
		SS_build_hierarchy root
	)

	-- Query the user for the number of LODs to create if she didn't supply one.
	local num_lods = count
	if num_lods == -1 then
		num_lods = SS_query_integer prompt:"Number of LODs to create:"
		
	-- Create LODs by cloning the hierarchy 'count' times.
	local lod_roots = SS_create_lod_models num_lods root offset:offset \
					clone_proc:clone_by
)

-- USER-CALLABLE: Set up Damage models based on the Origin.00 hierarchy
-- (by default). The user can specify the number of damage models to
-- create, how much to offset each model by, the method of cloning
-- (copy, instance, reference), and the root of the hierarchy the models
-- should be based on.
--
-- Sample call:
--	createDamage count:3 offset:[0,-2,0] clone_by:instance root:$'Origin.00'
function createDamage
	count:-1				-- default of -1 means prompt the user
	offset:[0,-100,0]		-- offset each model by -100 on the Y axis
	clone_by:reference		-- default to cloning by reference
	root:undefined			-- default to Origin.00 if not supplied
= (
	if root == undefined then
		root = $'Origin.00'
	if root == undefined then
	(
		-- Create the origin node and link up a hierarchy.
		root = SS_create_origin()
		SS_build_hierarchy root
	)
	
	-- Query the user for the number of Damage models to create if she didn't supply one.
	local num_damage = count
	if num_damage == -1 then
		num_damage = SS_query_integer prompt:"Number of Damage models:"
		
	-- Create the damage models by cloning the hierarchy 'count' times.
	local damage_roots = SS_create_damage_models num_damage root offset:offset \
						clone_proc:clone_by
)


-- USER-CALLABLE: Displays a friendly dialog where the user can choose a number
-- of settings for how the scene should be set up. This function has no arguments
-- and will be displayed as a button on the MAX UI.
--
-- Sample call:
--	sceneSetup()
function sceneSetup
= (
	-- Figure out some reasonable values for the lod and damage offsets.
	-- These values will be plugged into the dialog that prompts the user
	-- for values.
	local bbox
	if $'Origin.00' != undefined then
		bbox = SS_get_tree_bbox $'Origin.00'
	else
		bbox = SS_get_set_bbox geometry
	
	local x_offset = (bbox._max.x - bbox._min.x) * -1.5
	local y_offset = (bbox._max.y - bbox._min.y) * -1.5

	-- Create an array of default values that will be displayed in the dialog.
	-- (lod_count, lod_offset, lod_clone_proc, damage_count, damage_offset,
	--  damage_clone_proc)
	-- for procs: 1==copy 2==instance 3==reference
	--local default_args = #(2, -2, 3, 3, -3, 3)
	local default_args = #(2, x_offset, 3, 3, y_offset, 3)
	
	-- Show the dialog to get the parameters from the user.
	-- The user's choices will override the above default values.
	local chosen_args = wwSceneSetup default_args
	if chosen_args != undefined then
	(
		-- Pick the user's choices out of the array returned from wwSceneSetup.
		local lod_count = chosen_args[1]
		local lod_offset = chosen_args[2]
		local lod_clone_proc = chosen_args[3]
		local damage_count = chosen_args[4]
		local damage_offset = chosen_args[5]
		local damage_clone_proc = chosen_args[6]
		local lod_proc
		local damage_proc
		
		-- Choose the clone procs
		case lod_clone_proc of
		(
			1: lod_proc = copy
			2: lod_proc = instance
			3: lod_proc = reference
			default: throw "Invalid selection for LOD cloning procedure" lod_clone_proc
		)
		case damage_clone_proc of
		(
			1: damage_proc = copy
			2: damage_proc = instance
			3: damage_proc = reference
			default: throw "Invalid selection for Damage cloning procedure" damage_clone_proc
		)
		
		-- Create the LOD models
		createLOD count:lod_count offset:[lod_offset,0,0] clone_by:lod_proc
		
		-- Create the Damage models
		createDamage count:damage_count offset:[0,damage_offset,0] clone_by:damage_proc
	)
	
	return OK
)

-- The macro script definition for the toolbar button.
macroScript LOD_And_Damage_Setup
	category:"Westwood Scripts"
	buttonText:"LOD and Damage Setup"
	toolTip:"LOD and Damage Setup"
	icon:#("GameTools", 1)
(
	if objects.count == 0 then
	(
		messageBox("There are no objects in the current scene. Load " + \
			"a scene first.")
	)
	else
	(
		sceneSetup()
	)
)


-- The macro script definition for the "create origin" toolbar
-- button. This will create a new origin object centered at 0,0,0
-- assign all objects a ".00" extension, and link all top-level
-- objects to the new origin.
macroScript Create_Origin
	category:"Westwood Scripts"
	buttonText:"Create Origin"
	toolTip:"Create Origin"
	icon:#("Helpers", 2)
(
	if objects.count == 0 then
	(
		messageBox "An origin is not useful in an empty scene."
		return OK
	)
	if $'Origin.00' == undefined then
	(
		local origin = SS_create_origin()
		SS_build_hierarchy origin
		print(origin.name + " created.")
	)
	else
	(
		messageBox "Origin.00 already exists"
	)
)