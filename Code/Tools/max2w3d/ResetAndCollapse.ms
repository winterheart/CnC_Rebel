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
-- ResetAndCollapse.ms - Effectively applies the "Reset XForm" utility
-- to each selected object and collapses their stacks.
--
------------------------------------------------------------------------



-- A scripted function that does the same as the Reset Transform
-- Utility.
--									John Wainwright
--
-- Andre Arsenault: Maintain the pivot point so that it is not reset
-- to the origin.
function RAC_reset_transform obj =
(
	-- grab current transform, reset it, add a new xform
	-- modifier & set the xform's tm to the object's original tm
	local ftm = obj.transform
	local p = obj.pivot
	obj.transform = matrix3 1
	obj.pivot = p
	local xf = xform ()
	addModifier obj xf
	xf.gizmo.transform = ftm
)


function resetAndCollapse
= (
	for obj in selection do
	(
		RAC_reset_transform obj
		collapseStack obj
	)
)

macroScript Reset_XForm_And_Collapse
	category:"Westwood Scripts"
	buttonText:"Reset XForm And Collapse Stack"
	toolTip:"Apply a Reset XForm and Collapse Stack to all selected objects"
	icon:#("PolyTools",16)
(
	resetAndCollapse()
)