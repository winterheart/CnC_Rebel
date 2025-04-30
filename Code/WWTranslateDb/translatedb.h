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
 *                 Project Name : LevelEdit                                                    *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwtranslatedb/translatedb.h                  $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 11/12/01 11:43a                                             $*
 *                                                                                             *
 *                    $Revision:: 23                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "saveloadsubsystem.h"
#include "vector.h"
#include "bittype.h"
#include "translateobj.h"
#include "tdbcategory.h"
#include "hashtemplate.h"

//////////////////////////////////////////////////////////////////////////
// Singleton instance
//////////////////////////////////////////////////////////////////////////
extern class TranslateDBClass _TheTranslateDB;

//////////////////////////////////////////////////////////////////////////
// Typedefs
//////////////////////////////////////////////////////////////////////////
typedef DynamicVectorClass<TDBObjClass *> TDB_OBJ_LIST;
typedef DynamicVectorClass<TDBCategoryClass *> TDB_CATEGORY_LIST;

extern const WCHAR *STRING_NOT_FOUND;
extern const char *ENGLISH_STRING_NOT_FOUND;

//////////////////////////////////////////////////////////////////////////
// Useful macros
//////////////////////////////////////////////////////////////////////////
#define TRANSLATION TranslateDBClass::Get_String
#define TRANSLATE TranslateDBClass::Get_String
#define TRANSLATE_BY_DESC(desc) TranslateDBClass::Get_String(desc);

//////////////////////////////////////////////////////////////////////////
//
//	TranslateDBClass
//
//////////////////////////////////////////////////////////////////////////
class TranslateDBClass : public SaveLoadSubSystemClass {
public:
  //////////////////////////////////////////////////////////////
  //	Public constants
  //////////////////////////////////////////////////////////////
  enum {
    LANGID_ENGLISH = 0,
    LANGID_FRENCH,
    LANGID_GERMAN,
    LANGID_SPANISH,
    LANGID_CHINESE,
    LANGID_JAPANESE,
    LANGID_KOREAN
  };

  typedef enum {
    FILTER_DISABLED = 0,
    FILTER_IF_EQUAL,
    FILTER_IF_NOT_EQUAL,
  } FILTER_OPT;

  //////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  //////////////////////////////////////////////////////////////
  TranslateDBClass() = default;
  virtual ~TranslateDBClass() = default;

  //////////////////////////////////////////////////////////////
  //	Public methods
  //////////////////////////////////////////////////////////////

  //
  //	Initialization
  //
  static void Initialize();
  static void Shutdown();
  static uint32 Get_Version_Number();
  static void Update_Version();
  static bool Is_Loaded() { return (m_ObjectList.Count() > 0); }

  //
  // From SaveLoadSubSystemClass
  //
  virtual uint32 Chunk_ID() const;
  virtual const char *Name() const { return "TranslateDBClass"; }

  //
  //	C style header file support
  //
  static void Import_Strings(const char *filename);
  static void Import_C_Header(const char *filename);
  static void Export_C_Header(const char *filename);
  static void Export_Table(const char *filename);

  //
  //	Data access
  //
  static const WCHAR *Get_String(uint32 id);
  static const WCHAR *Get_String(const char *id_desc);
  static const char *Get_English_String(uint32 id);
  WWINLINE static TDBObjClass *Find_Object(uint32 id);
  WWINLINE static TDBObjClass *Find_Object(const char *id_desc);

  //
  //	Content management
  //
  static bool Add_Object(TDBObjClass *new_obj);
  static bool Remove_Object(int index);
  static void Remove_All();

  //
  //	Enumeration
  //
  static int Get_Object_Count();
  static TDBObjClass *Get_Object(int index);
  static TDBObjClass *Get_First_Object(uint32 category_id);
  static TDBObjClass *Get_Next_Object(uint32 category_id, TDBObjClass *curr_obj);

  //
  //	Category support
  //
  static int Get_Category_Count();
  static TDBCategoryClass *Get_Category(int index);
  static TDBCategoryClass *Find_Category(uint32 id);
  static TDBCategoryClass *Find_Category(const char *name);
  static TDBCategoryClass *Add_Category(const char *name);
  static bool Add_Category(TDBCategoryClass *new_category, bool assign_id = true);
  static bool Remove_Category(int index);

  //
  //	Language support
  //
  static void Set_Current_Language(int lang_id) { m_LanguageID = lang_id; }
  static uint32 Get_Current_Language() { return m_LanguageID; }

  //
  //	Save/load options
  //
  static bool Is_Single_Language_Export_Enabled() { return IsSingleLanguageExport; }
  static void Enable_Single_Language_Export(bool onoff) { IsSingleLanguageExport = onoff; }

  static void Set_Export_Filter(FILTER_OPT filter, uint32 category_id);

protected:
  //////////////////////////////////////////////////////////////
  //	Protected methods
  //////////////////////////////////////////////////////////////

  //
  //	Save/load stuff
  //
  virtual bool Contains_Data() const;
  virtual bool Save(ChunkSaveClass &csave);
  virtual bool Load(ChunkLoadClass &cload);

  bool Load_Variables(ChunkLoadClass &cload);
  bool Load_Objects(ChunkLoadClass &cload);
  bool Load_Categories(ChunkLoadClass &cload);

  static void Validate_Data();

  static void Free_Objects();
  static void Free_Categories();

  //
  //	ID managment
  //
  static uint32 Find_Unique_ID();

  //////////////////////////////////////////////////////////////
  //	Protected data types
  //////////////////////////////////////////////////////////////
  enum { ID_MIN = 1000, ID_MAX = 999999 };

private:
  //////////////////////////////////////////////////////////////
  //	Private member data
  //////////////////////////////////////////////////////////////
  static TDB_OBJ_LIST m_ObjectList;
  static HashTemplateClass<StringClass, TDBObjClass *> m_ObjectHash;
  static TDB_CATEGORY_LIST m_CategoryList;
  static uint32 m_VersionNumber;
  static uint32 m_LanguageID;
  static bool IsSingleLanguageExport;
  static uint32 CategoryExportFilter;
  static FILTER_OPT FilterType;
  static uint32 FilterCategoryID;
};

//////////////////////////////////////////////////////////////
//	Get_String
//////////////////////////////////////////////////////////////
inline const WCHAR *TranslateDBClass::Get_String(uint32 id) {
  // ID of 0 (zero) is a special case NULL string.
  if (id == 0) {
    return nullptr;
  }

  const WCHAR *string = STRING_NOT_FOUND;

  //
  //	Check to make sure the database is loaded
  //
  WWASSERT(Is_Loaded());

  //
  //	Calculate which index this ID refers to
  //
  int index = (id - ID_MIN);

  //
  //	Check to see if the requested ID is in the range
  // of loaded string objects.
  //
  WWASSERT(index >= 0 && index < m_ObjectList.Count());
  if (index >= 0 && index < m_ObjectList.Count()) {

    //
    //	Get the translation object
    //
    TDBObjClass *trans_obj = m_ObjectList[index];
    WWASSERT(trans_obj != nullptr);
    if (trans_obj != nullptr) {

      //
      //	Get the string from the object and return it to the caller
      //
      string = trans_obj->Get_String();
    }
  }

  return string;
}

//////////////////////////////////////////////////////////////
//	Get_String
//////////////////////////////////////////////////////////////
inline const WCHAR *TranslateDBClass::Get_String(const char *id_desc) {
  // NULL description is a special case NULL string.
  if (id_desc == nullptr) {
    return nullptr;
  }

  const WCHAR *string = STRING_NOT_FOUND;

  //
  //	Lookup the object based on its ID
  //
  TDBObjClass *translate_obj = Find_Object(id_desc);
  if (translate_obj != nullptr) {

    //
    //	Get the string from the object and return it to the caller
    //
    string = translate_obj->Get_String();
  }

  return string;
}

//////////////////////////////////////////////////////////////
//	Get_English_String
//////////////////////////////////////////////////////////////
inline const char *TranslateDBClass::Get_English_String(uint32 id) {
  // ID of 0 (zero) is a special case nullptr string.
  if (id == 0) {
    return nullptr;
  }

  const char *string = ENGLISH_STRING_NOT_FOUND;

  //
  //	Check to make sure the database is loaded
  //
  WWASSERT(m_ObjectList.Count() > 0);

  //
  //	Calculate which index this ID refers to
  //
  int index = (id - ID_MIN);

  //
  //	Check to see if the requested ID is in the range
  // of loaded string objects.
  //
  WWASSERT(index >= 0 && index < m_ObjectList.Count());
  if (index >= 0 && index < m_ObjectList.Count()) {

    //
    //	Get the translation object
    //
    TDBObjClass *trans_obj = m_ObjectList[index];
    WWASSERT(trans_obj != nullptr);
    if (trans_obj != nullptr) {

      //
      //	Get the string from the object and return it to the caller
      //
      string = trans_obj->Get_English_String();
    }
  }

  return string;
}

//////////////////////////////////////////////////////////////
//
//	Find_Object
//
//////////////////////////////////////////////////////////////
WWINLINE TDBObjClass *TranslateDBClass::Find_Object(const char *id_desc) {
  StringClass lower_case_name(id_desc, true);
  _strlwr(lower_case_name.Peek_Buffer());
  return m_ObjectHash.Get(lower_case_name);
}

//////////////////////////////////////////////////////////////
//	Find_Object
//////////////////////////////////////////////////////////////
WWINLINE TDBObjClass *TranslateDBClass::Find_Object(uint32 id) {
  TDBObjClass *object = nullptr;

  //
  //	Calculate which index this ID refers to
  //
  int index = (id - ID_MIN);
  if (index >= 0 && index < m_ObjectList.Count()) {

    //
    //	Get the translation object
    //
    object = m_ObjectList[index];

    //
    //	Make sure this is the object the caller requested
    //
    WWASSERT(object != nullptr && object->Get_ID() == id);
    if (object != nullptr && object->Get_ID() != id) {
      object = nullptr;
    }
  }

  return object;
}
