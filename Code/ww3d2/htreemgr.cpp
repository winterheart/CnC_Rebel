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

/* $Header: /Commando/Code/ww3d2/htreemgr.cpp 2     9/19/01 6:17p Jani_p $ */
/***********************************************************************************************
 ***                            Confidential - Westwood Studios                              ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Commando / G 3D Library                                      *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/htreemgr.cpp                           $*
 *                                                                                             *
 *                       Author:: Byon_g                                                       *
 *                                                                                             *
 *                     $Modtime:: 9/14/01 12:01p                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   HTreeManagerClass::HTreeManagerClass -- constructor                                       *
 *   HTreeManagerClass::~HTreeManagerClass -- destructor                                       *
 *   HTreeManagerClass::Free -- de-allocate all memory in use                                  *
 *   HTreeManagerClass::Free_All_Trees -- de-allocates all hierarchy trees currently loaded    *
 *   HTreeManagerClass::Load_Tree -- load a hierarchy tree from a file                         *
 *   HTreeManagerClass::Get_Tree_ID -- look up the ID of a named hierarchy tree                *
 *   HTreeManagerClass::Get_Tree -- get a pointer to the specified hierarchy tree              *
 *   HTreeManagerClass::Get_Tree -- get a pointer to the specified hierarchy tree              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "htreemgr.h"
#include <string.h>
#include "htree.h"
#include "chunkio.h"
#include "wwmemlog.h"

/***********************************************************************************************
 * HTreeManagerClass::HTreeManagerClass -- constructor                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/11/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
HTreeManagerClass::HTreeManagerClass(void) : NumTrees(0) {
  for (int treeidx = 0; treeidx < MAX_TREES; treeidx++) {
    TreePtr[treeidx] = NULL;
  }
}

/***********************************************************************************************
 * HTreeManagerClass::~HTreeManagerClass -- destructor                                         *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/11/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
HTreeManagerClass::~HTreeManagerClass(void) { Free(); }

/***********************************************************************************************
 * HTreeManagerClass::Free -- de-allocate all memory in use                                    *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/11/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
void HTreeManagerClass::Free(void) { Free_All_Trees(); }

/***********************************************************************************************
 * HTreeManagerClass::Free_All_Trees -- de-allocates all hierarchy trees currently loaded      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/11/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
void HTreeManagerClass::Free_All_Trees(void) {
  // Clear the hash table
  TreeHash.Remove_All();

  for (int treeidx = 0; treeidx < MAX_TREES; treeidx++) {
    if (TreePtr[treeidx] != NULL) {
      delete TreePtr[treeidx];
      TreePtr[treeidx] = NULL;
    }
  }
  NumTrees = 0;
}

/***********************************************************************************************
 * HTreeManagerClass::Load_Tree -- load a hierarchy tree from a file                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/11/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
int HTreeManagerClass::Load_Tree(ChunkLoadClass &cload) {
  WWMEMLOG(MEM_ANIMATION);
  HTreeClass *newtree = new HTreeClass;

  if (newtree == NULL) {
    goto Error;
  }

  if (newtree->Load_W3D(cload) != HTreeClass::OK) {

    // load failed, delete and return error
    delete newtree;
    goto Error;

  } else if (Get_Tree_ID(newtree->Get_Name()) != -1) {

    // tree with this name already exists, reject it!
    delete newtree;
    goto Error;

  } else {

    // ok, accept this hierarchy tree!
    TreePtr[NumTrees] = newtree;
    NumTrees++;

    // Insert to hash table for fast name based search
    StringClass lower_case_name(newtree->Get_Name(), true);
    _strlwr(lower_case_name.Peek_Buffer());
    TreeHash.Insert(lower_case_name, newtree);
  }

  return 0;

Error:

  return 1;
}

/***********************************************************************************************
 * HTreeManagerClass::Get_Tree_ID -- look up the ID of a named hierarchy tree                  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/11/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
int HTreeManagerClass::Get_Tree_ID(const char *name) {
  for (int i = 0; i < NumTrees; i++) {
    if (TreePtr[i] && (stricmp(name, TreePtr[i]->Get_Name()) == 0)) {
      return i;
    }
  }
  return -1;
}

/***********************************************************************************************
 * HTreeManagerClass::Get_Tree_Name -- look up the name of a id'd hierarchy tree                  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/11/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
char *HTreeManagerClass::Get_Tree_Name(const int idx) {
  if ((idx < NumTrees) && TreePtr[idx]) {
    if (TreePtr[idx]) {
      return (char *)TreePtr[idx]->Get_Name();
    }
  }

  return NULL;
}

/***********************************************************************************************
 * HTreeManagerClass::Get_Tree -- get a pointer to the specified hierarchy tree                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/11/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
HTreeClass *HTreeManagerClass::Get_Tree(const char *name) {
  StringClass lower_case_name(name, true);
  _strlwr(lower_case_name.Peek_Buffer());
  return TreeHash.Get(lower_case_name);

  //	for (int i=0; i<NumTrees; i++) {
  //		if (TreePtr[i] && (stricmp(name,TreePtr[i]->Get_Name()) == 0)) {
  //
  //			return TreePtr[i];
  //		}
  //	}
  //	return NULL;
}

/***********************************************************************************************
 * HTreeManagerClass::Get_Tree -- get a pointer to the specified hierarchy tree                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/11/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
HTreeClass *HTreeManagerClass::Get_Tree(int id) {
  if ((id >= 0) && (id < NumTrees)) {
    return TreePtr[id];
  } else {
    return NULL;
  }
}