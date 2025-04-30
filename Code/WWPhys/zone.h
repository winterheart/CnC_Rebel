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
 *                     $Archive:: /Commando/Code/wwphys/zone.h                                $*
 *                                                                                             *
 *                       Author:: Greg_h                                                       *
 *                                                                                             *
 *                     $Modtime:: 9/09/99 2:19p                                               $*
 *                                                                                             *
 *                    $Revision:: 6                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if 0 // TODO: implement zones one day???

#ifndef ZONE_H
#define ZONE_H

#ifndef ALWAYS_H
#include "always.h"
#endif

#ifndef REFCOUNT_H
#include "refcount.h"
#endif

#ifndef OBBOX_H
#include "obbox.h"
#endif

/*

  - Physobjs cache a list of the zones they are in
  - PhysScene maintains an aabtree of zones
  - Zones are PhysObjs only so I can re-use the AABTree
  - Zones contain a bit field of "type" attributes.
  - When a new ZoneList is built, it contains the union of all of the attributes
  - Some zones never need to be actually added to the list, only their bits OR'd in (lava)
  - Zones never MOVE or they only move out

  - Zones DO/CAN move
  - don't cache zone lists for now
  - motion parenting?
  - maybe do cache zone lists but invalidate the ones that could be affected by a moving zone
  - Dynamic objects can store a dynamic vector of "attached zone nodes".  Each node
    has a pointer to a zone and the relative transform.  Whenever the object moves, pull
	 the zone out, transform it, put it back in.

*/




/*
** ZoneClass!
**
** Zones are basically rectangular regions of space.  This is the abstract base class
** for all zones.  Zones will perform functions such as:
** "Trigger Zone" - inform the game whenever a physical object enters it.
** "Water Zone" - apply a boyancy force to physical objects penetrating the zone.
*/
class ZoneClass : public RefCountClass
{
public:

	ZoneClass(void) {}
	virtual ~ZoneClass(void) {}

private:

	// bounding box which defines the space enclosed by this zone
	OBBoxClass	Box;

};

#endif

#endif // 0
