/*
 * 	Command & Conquer Renegade(tm)
 * 	Copyright 2025 Electronic Arts Inc.
 * 	Copyright 2025 CnC: Rebel Developers.
 *
 * 	This program is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 * 	This program is distributed in the hope that it will be useful,
 * 	but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 	GNU General Public License for more details.
 *
 * 	You should have received a copy of the GNU General Public License
 * 	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WWSaveLoad                                                   *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwnet/networkobjectfactorymgr.cpp            $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 5/18/01 2:35p                                               $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "networkobjectfactorymgr.h"
#include "networkobjectfactory.h"
#include "wwdebug.h"

////////////////////////////////////////////////////////////////////////////
//	Static member initialization
////////////////////////////////////////////////////////////////////////////
NetworkObjectFactoryClass *NetworkObjectFactoryMgrClass::_FactoryListHead = nullptr;

////////////////////////////////////////////////////////////////////////////
//
//	Find_Factory
//
////////////////////////////////////////////////////////////////////////////
NetworkObjectFactoryClass *NetworkObjectFactoryMgrClass::Find_Factory(uint32 class_id) {
  NetworkObjectFactoryClass *factory = nullptr;

  //
  //	Loop through all the factories and see if we can
  // find the one who owns the corresponding class-id.
  //
  for (NetworkObjectFactoryClass *curr_factory = _FactoryListHead; (factory == nullptr) && (curr_factory != nullptr);
       curr_factory = curr_factory->NextFactory) {

    //
    //	Is this the factory we were looking for?
    //
    if (curr_factory->Get_Class_ID() == class_id) {
      factory = curr_factory;
    }
  }

  return factory;
}

////////////////////////////////////////////////////////////////////////////
//
//	Get_First
//
////////////////////////////////////////////////////////////////////////////
NetworkObjectFactoryClass *NetworkObjectFactoryMgrClass::Get_First() { return _FactoryListHead; }

////////////////////////////////////////////////////////////////////////////
//
//	Get_Next
//
////////////////////////////////////////////////////////////////////////////
NetworkObjectFactoryClass *NetworkObjectFactoryMgrClass::Get_Next(const NetworkObjectFactoryClass *curr_factory) {
  NetworkObjectFactoryClass *factory = nullptr;

  //
  //	Simply return the next factory in the chain
  //
  if (curr_factory != nullptr) {
    factory = curr_factory->NextFactory;
  }

  return factory;
}

////////////////////////////////////////////////////////////////////////////
//
//	Register_Factory
//
////////////////////////////////////////////////////////////////////////////
void NetworkObjectFactoryMgrClass::Register_Factory(NetworkObjectFactoryClass *factory) {
  WWASSERT(factory->NextFactory == nullptr);
  WWASSERT(factory->PrevFactory == nullptr);
  Link_Factory(factory);
}

////////////////////////////////////////////////////////////////////////////
//
//	Unregister_Factory
//
////////////////////////////////////////////////////////////////////////////
void NetworkObjectFactoryMgrClass::Unregister_Factory(NetworkObjectFactoryClass *factory) {
  WWASSERT(factory != nullptr);
  Unlink_Factory(factory);
}

////////////////////////////////////////////////////////////////////////////
//
//	Link_Factory
//
////////////////////////////////////////////////////////////////////////////
void NetworkObjectFactoryMgrClass::Link_Factory(NetworkObjectFactoryClass *factory) {
  WWASSERT(factory->NextFactory == nullptr);
  WWASSERT(factory->PrevFactory == nullptr);

  // Adding this factory in front of the current head of the list
  factory->NextFactory = _FactoryListHead;

  // If the list wasn't empty, link the next factory back to this factory
  if (factory->NextFactory != nullptr) {
    factory->NextFactory->PrevFactory = factory;
  }

  // Point the head of the list at this factory now
  _FactoryListHead = factory;
}

////////////////////////////////////////////////////////////////////////////
//
//	Unlink_Factory
//
////////////////////////////////////////////////////////////////////////////
void NetworkObjectFactoryMgrClass::Unlink_Factory(NetworkObjectFactoryClass *factory) {
  WWASSERT(factory != nullptr);

  // Handle the factory's prev pointer:
  if (factory->PrevFactory == nullptr) {

    // this factory is the head
    WWASSERT(_FactoryListHead == factory);
    _FactoryListHead = factory->NextFactory;

  } else {

    // link it's prev with it's next
    factory->PrevFactory->NextFactory = factory->NextFactory;
  }

  // Handle the factory's next pointer if its not at the end of the list:
  if (factory->NextFactory != nullptr) {

    factory->NextFactory->PrevFactory = factory->PrevFactory;
  }

  // factory is now un-linked
  factory->NextFactory = nullptr;
  factory->PrevFactory = nullptr;
}
