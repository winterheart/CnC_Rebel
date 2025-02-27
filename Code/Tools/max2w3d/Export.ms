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
-- Export.ms - This file contains two batch exporting scripts. The first
-- "exportDependants" will export the current scene, and any others in
-- the current directory that depend on it for their skeletons. The
-- second, "exportDirectoryTree" will export and and all Max files in
-- a given directory tree. Both of these scripts have equivalent macro
-- definitions, making it simple to add them as buttons to a toolbar.
--
------------------------------------------------------------------------


-- EXP_replace_extension is a utility function used by the scripts in this
-- file to replace the ".max" or ".w3d" of the given filename with a given
-- extension (including the dot, ie. ".w3d")
function EXP_replace_extension
	max_filename	-- x:\abc\blah.max or blah.max
	extension		-- .w3d
= (
	-- Find the ".max" extension in the filename.
	local dot_index = findString max_filename ".MAX"
	if dot_index == undefined then
	(
		dot_index = findString max_filename ".W3D"
		if dot_index == undefined then
			return max_filename
	)
	
	return (replace max_filename dot_index 4 extension)
)


-- USER-CALLABLE: exportW3D exports the current scene as a W3D file.
-- It takes a flag to determine whether it should display any dialogs
-- during the export. This makes the function suitable for batch exports.
function exportW3D
	show_dialogs:true
	w3d_name:undefined
= (
	if w3d_name == undefined then
	(
		-- Get the name of the current scene as a W3D file.
		w3d_name = EXP_replace_extension (maxFilePath + maxFileName) ".w3d"
		if show_dialogs == true then
		(
			-- Allow the user to possibly choose a different name.
			w3d_name = getSaveFileName caption:"Select File to Export" \
				filename:w3d_name types:"w3d (*.W3D)|*.w3d|"
			
			-- The dialog above will prompt the user to overwrite an
			-- existing file. If the user chooses yes, the exportFile
			-- call below will prompt him once again to overwrite the
			-- file. The solution to this is to delete the w3d file.
			if w3d_name != undefined then
				deleteFile w3d_name
		)
		-- If the user canceled the name selection, or there was some
		-- sort of error, return false.
		if w3d_name == undefined then
			return false
	)
	
	-- Print an exporting message.
	local short_name = filenameFromPath w3d_name
	print("Exporting " + short_name + "...")
	
	-- Export the scene, showing the export options if appropriate.
	if show_dialogs == true then
		exportFile w3d_name
	else
		exportFile w3d_name #noPrompt
	
	return true
)

-- The macro script definition for the "Export as W3D" toolbar button.
macroScript Export_As_W3D
	category:"Westwood Scripts"
	buttonText:"OLD - Export as W3D - OLD"
	toolTip:"This button should not be used anymore"
	icon:#("SchematicView", 1)
(
	messageBox "This button is being phased out. Please use Export_As instead."
)

-- The macro script definition for the "Export" toolbar button.
macroScript Export
	category:"Westwood Scripts"
	buttonText:"Export"
	toolTip:"Export the current scene as a W3D file without prompting"
	icon:#("GameTools", 2)
(
	exportW3D show_dialogs:false
)

-- The macro script definition for the "Export As..." toolbar button
macroScript Export_As
	category:"Westwood Scripts"
	buttonText:"Export As..."
	toolTip:"Export the current scene as a W3D file"
	icon:#("GameTools", 3)
(
	exportW3D()
)


-- USER-CALLABLE: exportDependants will export the current scene, and
-- and other scenes in the same directory that depend on the current
-- one for their hierarchy.
function exportDependants
= (
	local current_scene = undefined
	
	-- Export the current scene.
	if checkForSave() == false then
	(
		-- User aborted the save.
		return ok
	)
	else
	(
		-- The user saved changes (or the scene was unchanged).
		-- Grab the name of the scene file.
		current_scene = maxFilePath + maxFileName
	)
	if current_scene == "" then
	(
		-- This is an empty scene, don't export.
		return ok
	)
	
	-- Export the current scene as a W3D file.
	local export_file = EXP_replace_extension current_scene ".w3d"
	local short_name = filenameFromPath export_file
	exportW3D w3d_name:export_file
	
	-- Get (and sort) the list of all other MAX files
	-- in the same directory as the current scene.
	local pattern = maxFilePath
	pattern = pattern + "*.max"
	local files = getFiles pattern
	sort files
	
	-- Open and export each file in turn.
	local exported_count = 1
	for f in files do
	(
		-- Don't export the original scene again.
		if f != current_scene then
		(
			-- Load the Max scene.
			if (loadMaxFile f) != true then
			(
				print("Unable to load " + f)
			)
			else
			(
				-- Get the name of the hierarchy the scene depends on.
				-- wwGetHierarchyFile returns a relative pathname if it
				-- is available, otherwise it returns an absolute path.
				local htree_file = wwGetHierarchyFile()
				if (htree_file == undefined) or
					((htree_file as name != short_name as name) and
					(htree_file as name != current_scene as name)) then
				(
					-- The filenames don't match, or the scene doesn't
					-- depend on a hierarchy at all.
					local filename = filenameFromPath f
					print (filename + " does not depend on " + short_name)
				)
				else
				(
					-- This scene gets its hierarchy from the original.
					-- Re-export it (last export settings automatically used).
					local w3d_file = EXP_replace_extension f ".w3d"
					if (exportW3D w3d_name:w3d_file show_dialogs:false) then
						exported_count += 1
				)
			)
		)
	)
	
	-- Load up the original scene again and show how many files were re-exported.
	loadMaxFile current_scene
	print ("Export process finished! " + exported_count as string + " files exported.")
	return ok
)


-- The macro script definition for the "Export Dependants" toolbar button.
macroScript Export_Dependants
	category:"Westwood Scripts"
	buttonText:"Export Dependants"
	toolTip:"Export all dependant scenes"
	icon:#("Maxscript", 3)
(
	exportDependants()
)


-- USER-CALLABLE: exportDirectoryTree exports all MAX scenes in a directory
-- and all it's subdirectories. All scenes are exported with their last
-- export settings. Scenes that have never been exported are done so with
-- default settings as defined in max2w3d (currently exports: hierarchy,
-- animation, geometry).
global EXP_exported = #()		-- array of exported scenes
function exportDirectoryTree
	dir:undefined
= (
	-- If no directory was given, get it from the user using a directory
	-- selection dialog.
	local recursive = true
	if dir == undefined then
	(
		local ar = #(maxFilePath, true)
		local res = wwExportTreeSettings ar
		if res == undefined then
			return 0
		dir = res[1]
		recursive = res[2]
		EXP_exported = #()
	)
	
	-- Append a trailing backslash if the path doesn't have one.
	if dir[dir.count] != "\\" then
		dir = dir + "\\"
	
	-- Export all max files in the current directory.
	local exported_count = 0
	local files = getFiles(dir + "*.max")
	sort files
	for f in files do
	(
		-- Load 'er up.
		if (loadMaxFile f) != true then
		(
			print("Unable to load " + f)
			continue
		)

		-- Check if this scene requires another to be exported first.
		local htree_file = wwGetHierarchyFile()
		if htree_file != undefined then
		(
			-- Convert the relative path to an absolute one.
			local htree_abs = wwGetAbsolutePath htree_file dir
			local max_file = EXP_replace_extension htree_abs ".max"
			
			-- Has the scene been exported yet?
			if (findItem EXP_exported (max_file as Name)) == 0 then
			(
				-- It hasn't been exported. Do so now.
				
				-- Load the max file.
				if (loadMaxFile max_file) != true then
				(
					print("WARNING: " + max_file + " could not be opened, but " + \
						f + " depends on " + htree_abs + "!")
					
					-- Proceed with the export only if a previous W3D file exists.
					if (getFiles htree_abs).count == 0 then
						continue
				)
				else
				(
					-- Export the w3d file
					if (exportW3D w3d_name:w3d_file show_dialogs:false) == true then
					(
						-- Add the scene to the array of exported scenes.
						append EXP_exported (max_file as Name)
					)
					else
					(
						-- Show an error message
						print("ERROR: " + htree_abs + " not exported, but " + \
							f + " depends on it!")
						continue
					)
					
					-- Load the previous scene up again so we can export it.
					loadMaxFile f
				)
			)
		)
		
		-- Export it as a W3D file, if it hasn't been already exported.
		if (findItem EXP_exported (f as Name)) == 0 then
		(
			local w3d_file = EXP_replace_extension f ".w3d"
			if (exportW3D w3d_name:w3d_file show_dialogs:false) then
			(
				-- Add the scene to the array of exported scenes.
				append EXP_exported (f as Name)
			)
		)
	)
	
	-- Recurse through all subdirectories.
	if recursive == true then
	(
		local folders = getDirectories(dir + "*")
		sort folders
		for d in folders do
		(
			print ("Entering " + d)
			exportDirectoryTree dir:d
		)
	)
	
	return EXP_exported.count
)

-- The macro script definition for the "Export Directory Tree" toolbar button.
macroScript Export_Directory_Tree
	category:"Westwood Scripts"
	buttonText:"Export Directory Tree"
	toolTip:"Export all MAX files in a folder and all its sub-folders"
	icon:#("SchematicView", 2)
(
	local count = exportDirectoryTree()
	print (count as string + " files exported")
	if count > 0 then
		resetMaxFile #noPrompt
)

