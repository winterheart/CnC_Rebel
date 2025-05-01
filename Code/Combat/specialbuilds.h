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
 ***                            Confidential - Westwood Studios                              ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Commando                                                     *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Combat/specialbuilds.h                           $*
 *                                                                                             *
 *                      $Author:: Bhayes                                                      $*
 *                                                                                             *
 *                     $Modtime:: 3/18/02 11:54a                                              $*
 *                                                                                             *
 *                    $Revision:: 5                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#if defined(_MSV_VER)
#pragma once
#endif

#ifndef SPECIALBUILDS_H
#define SPECIALBUILDS_H

//
// N.B. Any file that references any of the following special build defines
// must include this file.
//

//-----------------------------------------------------------------------------
// DEFINES
//-----------------------------------------------------------------------------

//
// Uncomment the FREEDEDICATEDSERVER define to permit only dedicated
// hosting.
//
// #define FREEDEDICATEDSERVER

//
// Uncomment the MULTIPLAYERDEMO define to build the MP demo.
//
// #define MULTIPLAYERDEMO

//-----------------------------------------------------------------------------
// COMPILE-TIME WARNINGS
//-----------------------------------------------------------------------------

#ifdef FREEDEDICATEDSERVER
#pragma message("*** FREEDEDICATEDSERVER is defined ***")
#endif // FREEDEDICATEDSERVER

#ifdef MULTIPLAYERDEMO
#pragma message("*** MULTIPLAYERDEMO is defined ***")
#endif // MULTIPLAYERDEMO

//
// Disallow specialbuild defines to be used together.
//
#if defined(FREEDEDICATEDSERVER)
#error "*** ERROR: specialbuild defines should be mutually exclusive.***"
#endif

#if defined(MULTIPLAYERDEMO)
#error "*** ERROR: specialbuild defines should be mutually exclusive.***"
#endif

#if defined(FREEDEDICATEDSERVER) && defined(MULTIPLAYERDEMO)
#error "*** ERROR: specialbuild defines should be mutually exclusive.***"
#endif
//-----------------------------------------------------------------------------

#endif // SPECIALBUILDS_H
