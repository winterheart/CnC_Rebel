/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**  Copyright 2025 CnC Rebel Developers.
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
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwlib/Except.h                               $*
 *                                                                                             *
 *                      $Author:: Steve_t                                                     $*
 *                                                                                             *
 *                     $Modtime:: 2/07/02 12:28p                                              $*
 *                                                                                             *
 *                    $Revision:: 6                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#ifndef EXCEPT_H
#define EXCEPT_H

#ifdef _MSC_VER

#include "win.h"
/*
** Forward Declarations
*/
using EXCEPTION_POINTERS = _EXCEPTION_POINTERS;
using CONTEXT = _CONTEXT;

int Exception_Handler(int exception_code, EXCEPTION_POINTERS *e_info);
int Stack_Walk(unsigned long *return_addresses, int num_addresses, CONTEXT *context = nullptr);
bool Lookup_Symbol(void *code_ptr, char *symbol, int &displacement);
void Load_Image_Helper();
void Register_Thread_ID(unsigned long thread_id, const char *thread_name, bool main = false);
void Unregister_Thread_ID(unsigned long thread_id, const char *thread_name);
void Register_Application_Exception_Callback(void (*app_callback)());
void Register_Application_Version_Callback(char *(*app_version_callback)());
void Set_Exit_On_Exception(bool set);
bool Is_Trying_To_Exit();
unsigned long Get_Main_Thread_ID();
#if (0)
bool Register_Thread_Handle(unsigned long thread_id, HANDLE thread_handle);
int Get_Num_Thread(void);
HANDLE Get_Thread_Handle(int thread_index);
#endif //(0)

/*
** Register dump variables. These are used to allow the game to restart from an arbitrary
** position after an exception occurs.
*/
extern unsigned long ExceptionReturnStack;
extern unsigned long ExceptionReturnAddress;
extern unsigned long ExceptionReturnFrame;


using ThreadInfoType = struct tThreadInfoType {
	char				ThreadName[128];
	unsigned long	ThreadID;
	HANDLE			ThreadHandle;
	bool				Main;
};

#endif	//_MSC_VER

#endif	//EXCEPT_H