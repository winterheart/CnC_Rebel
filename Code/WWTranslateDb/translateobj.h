/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**	Copyright 2025 CnC Rebel Developers.
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
 *                 Project Name : wwtranslatedb
 **
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwtranslatedb/translateobj.h       $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 9/10/01 8:43a                                               $*
 *                                                                                             *
 *                    $Revision:: 8                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "persist.h"
#include "persistfactory.h"
#include "bittype.h"
#include "wwstring.h"
#include "widestring.h"
#include "vector.h"

//////////////////////////////////////////////////////////////////////////
//	Forward declarations
//////////////////////////////////////////////////////////////////////////
class ChunkSaveClass;
class ChunkLoadClass;
class StringTwiddlerClass;

//////////////////////////////////////////////////////////////////////////
//
//	TDBObjClass
//
//////////////////////////////////////////////////////////////////////////
class TDBObjClass : public PersistClass {
public:
  //////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  //////////////////////////////////////////////////////////////
  TDBObjClass();
  TDBObjClass(const TDBObjClass &src);
  virtual ~TDBObjClass();

  //////////////////////////////////////////////////////////////
  //	Public operators
  //////////////////////////////////////////////////////////////
  const TDBObjClass &operator=(const TDBObjClass &src);

  //////////////////////////////////////////////////////////////
  //	Public methods
  //////////////////////////////////////////////////////////////

  //
  //	RTTI
  //
  virtual StringTwiddlerClass *As_StringTwiddlerClass() { return nullptr; }

  //
  // From PersistClass
  //
  const PersistFactoryClass &Get_Factory() const;
  bool Save(ChunkSaveClass &csave);
  bool Load(ChunkLoadClass &cload);

  //
  // Copy methods
  //
  virtual TDBObjClass *Clone() const { return new TDBObjClass(*this); }

  //
  // TranslateObj specific
  //
  virtual const WideStringClass &Get_String(uint32 lang_id);
  virtual const WideStringClass &Get_String();
  virtual const StringClass &Get_English_String() { return EnglishString; }
  virtual uint32 Get_ID() { return ID; }
  virtual const StringClass &Get_ID_Desc() { return IDDesc; }
  virtual uint32 Get_Sound_ID() { return SoundID; }
  virtual const StringClass &Get_Animation_Name() { return AnimationName; }
  virtual uint32 Get_Category_ID() { return CategoryID; }

  virtual void Set_String(uint32 lang_id, const WCHAR *string);
  virtual void Set_English_String(const TCHAR *string);
  virtual void Set_ID(uint32 id);
  virtual void Set_ID_Desc(const TCHAR *desc);
  virtual void Set_Animation_Name(const TCHAR *name) { AnimationName = name; }
  virtual void Set_Sound_ID(uint32 id) { SoundID = id; }
  virtual void Set_Category_ID(uint32 id) { CategoryID = id; }

  //
  //	Informational
  //
  virtual bool Contains_Translation(uint32 lang_id);

protected:
  //////////////////////////////////////////////////////////////
  //	Protected methods
  //////////////////////////////////////////////////////////////
  void Save_Variables(ChunkSaveClass &csave);
  void Load_Variables(ChunkLoadClass &cload);

  //////////////////////////////////////////////////////////////
  //	Protected member data
  //////////////////////////////////////////////////////////////
  StringClass EnglishString;
  StringClass IDDesc;
  uint32 ID;
  uint32 SoundID;
  uint32 CategoryID;
  StringClass AnimationName;
  DynamicVectorClass<WideStringClass> TranslatedStrings;
};
