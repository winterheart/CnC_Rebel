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

/************************************************************************************************
*   C O N F I D E N T I A L --- W E S T W O O D   A S S O C I A T E S							*
*************************************************************************************************
*
* FILE
*     $Archive: /Commando/Code/Tools/WWConfig/Locale_API.h $
*
* DESCRIPTION
*
* PROGRAMMER
*     $Author: Maria_l $
*
* VERSION INFO
*     $Modtime: 12/07/01 2:05p $
*     $Revision: 1 $
*
*************************************************************************************************/

#ifndef  LOCALE_API_H
#define  LOCALE_API_H

#include <STDLIB.H>

/****************************************************************************/
/* GLOBAL VARIABLES                                                         */
/****************************************************************************/
extern	int		CodePage;
extern	void *	LocaleFile;
extern	int		LanguageID;
extern	CHAR	LanguageFile[];

/****************************************************************************/
/* LOCALE API                                                               */
/****************************************************************************/
int				Locale_Init	( int language, const CHAR *file );
void			Locale_Restore ( void );
const CHAR	*	Locale_GetString( int StringID, CHAR *String );
const WCHAR	*	Locale_GetString( int StringID, WCHAR *String );
const WCHAR	*	Locale_GetString( int StringID );
bool			Locale_Use_Multi_Language_Files	( void );

#endif