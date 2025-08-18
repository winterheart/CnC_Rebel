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
 *                     $Archive:: /Commando/Code/wwlib/wwstring.h              $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 12/13/01 5:11p                                              $*
 *                                                                                             *
 *                    $Revision:: 37                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include <mutex>

#include "always.h"
#include "win.h"
#include <tchar.h>
#include "trim.h"
#include "wwdebug.h"

//////////////////////////////////////////////////////////////////////
//
//	StringClass
//
//	Note:  This class is UNICODE friendly.  That means it can be
// compiled using either single-byte or double-byte strings.  There
// are no assumptions made as to the size of a character.
//
//	Any method that takes a parameter with the word 'len' or 'length'
//	in it refers to a count of characters.  If the name contains 'byte'
// it is talking about the memory size.
//
//////////////////////////////////////////////////////////////////////
class StringClass {
public:
  ////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  ////////////////////////////////////////////////////////////
  StringClass(bool hint_temporary);
  StringClass(size_t initial_len = 0, bool hint_temporary = false);
  StringClass(const StringClass &string, bool hint_temporary = false);
  StringClass(const TCHAR *string, bool hint_temporary = false);
  StringClass(TCHAR ch, bool hint_temporary = false);
  StringClass(const WCHAR *string, bool hint_temporary = false);
  ~StringClass();

  ////////////////////////////////////////////////////////////
  //	Public operators
  ////////////////////////////////////////////////////////////
  bool operator==(const TCHAR *rvalue) const;
  bool operator!=(const TCHAR *rvalue) const;

  inline const StringClass &operator=(const StringClass &string);
  inline const StringClass &operator=(const TCHAR *string);
  inline const StringClass &operator=(TCHAR ch);
  inline const StringClass &operator=(const WCHAR *string);

  const StringClass &operator+=(const StringClass &string);
  const StringClass &operator+=(const TCHAR *string);
  const StringClass &operator+=(TCHAR ch);

  friend StringClass operator+(const StringClass &string1, const StringClass &string2);
  friend StringClass operator+(const TCHAR *string1, const StringClass &string2);
  friend StringClass operator+(const StringClass &string1, const TCHAR *string2);

  bool operator<(const TCHAR *string) const;
  bool operator<=(const TCHAR *string) const;
  bool operator>(const TCHAR *string) const;
  bool operator>=(const TCHAR *string) const;

  const TCHAR &operator[](unsigned int index) const;
  TCHAR &operator[](unsigned int index);
  inline operator const TCHAR *() const;

  ////////////////////////////////////////////////////////////
  //	Public methods
  ////////////////////////////////////////////////////////////
  int Compare(const TCHAR *string) const;
  int Compare_No_Case(const TCHAR *string) const;

  inline size_t Get_Length() const;
  bool Is_Empty() const;

  void Erase(unsigned int start_index, size_t char_count) const;
  int _cdecl Format(const TCHAR *format, ...);
  int _cdecl Format_Args(const TCHAR *format, const va_list &arg_list);

  // Trim leading and trailing whitespace characters (values <= 32)
  void Trim() const;

  TCHAR *Get_Buffer(size_t new_length);
  TCHAR *Peek_Buffer();
  const TCHAR *Peek_Buffer() const;

  bool Copy_Wide(const WCHAR *source);

  ////////////////////////////////////////////////////////////
  //	Static methods
  ////////////////////////////////////////////////////////////
  static void Release_Resources();

private:
  ////////////////////////////////////////////////////////////
  //	Private structures
  ////////////////////////////////////////////////////////////
  typedef struct HEADER {
    size_t allocated_length;
    size_t length;
  } HEADER;

  ////////////////////////////////////////////////////////////
  //	Private constants
  ////////////////////////////////////////////////////////////
  // Note: Don't change these enums without withs checking the Get_String() and Free_String() function!
  enum {
    MAX_TEMP_STRING = 8,
    MAX_TEMP_LEN = 256 - sizeof(HEADER),
    MAX_TEMP_BYTES = (MAX_TEMP_LEN * sizeof(TCHAR)) + sizeof(HEADER),
    ALL_TEMP_STRINGS_USED_MASK = 0xff
  };

  ////////////////////////////////////////////////////////////
  //	Private methods
  ////////////////////////////////////////////////////////////
  void Get_String(size_t length, bool is_temp);
  TCHAR *Allocate_Buffer(size_t length);
  void Resize(size_t size);
  void Uninitialised_Grow(size_t length);
  void Free_String();

  inline void Store_Length(size_t length) const;
  inline void Store_Allocated_Length(size_t allocated_length) const;
  inline HEADER *Get_Header() const;
  size_t Get_Allocated_Length() const;

  void Set_Buffer_And_Allocated_Length(TCHAR *buffer, size_t length);

  ////////////////////////////////////////////////////////////
  //	Private member data
  ////////////////////////////////////////////////////////////
  TCHAR *m_Buffer;

  ////////////////////////////////////////////////////////////
  //	Static member data
  ////////////////////////////////////////////////////////////
  static unsigned ReservedMask;
  static char m_TempStrings[];

  static std::recursive_mutex m_Mutex;

  static TCHAR m_NullChar;
  static TCHAR *m_EmptyString;
};

///////////////////////////////////////////////////////////////////
//	operator=
///////////////////////////////////////////////////////////////////
inline const StringClass &StringClass::operator=(const StringClass &string) {
  size_t len = string.Get_Length();
  Uninitialised_Grow(len + 1);
  Store_Length(len);

  ::memcpy(m_Buffer, string.m_Buffer, (len + 1) * sizeof(TCHAR));
  return (*this);
}

///////////////////////////////////////////////////////////////////
//	operator=
///////////////////////////////////////////////////////////////////
inline const StringClass &StringClass::operator=(const TCHAR *string) {
  if (string != nullptr) {

    size_t len = _tcslen(string);
    Uninitialised_Grow(len + 1);
    Store_Length(len);

    ::memcpy(m_Buffer, string, (len + 1) * sizeof(TCHAR));
  }

  return (*this);
}

///////////////////////////////////////////////////////////////////
//	operator=
///////////////////////////////////////////////////////////////////
inline const StringClass &StringClass::operator=(const WCHAR *string) {
  if (string != nullptr) {
    Copy_Wide(string);
  }

  return (*this);
}

///////////////////////////////////////////////////////////////////
//	operator=
///////////////////////////////////////////////////////////////////
inline const StringClass &StringClass::operator=(const TCHAR ch) {
  Uninitialised_Grow(2);

  m_Buffer[0] = ch;
  m_Buffer[1] = m_NullChar;
  Store_Length(1);

  return (*this);
}

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
inline StringClass::StringClass(const bool hint_temporary) : m_Buffer(m_EmptyString) {
  Get_String(MAX_TEMP_LEN, hint_temporary);
  m_Buffer[0] = m_NullChar;

}

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
inline StringClass::StringClass(const size_t initial_len, const bool hint_temporary) : m_Buffer(m_EmptyString) {
  Get_String(initial_len, hint_temporary);
  m_Buffer[0] = m_NullChar;

}

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
inline StringClass::StringClass(const TCHAR ch, const bool hint_temporary) : m_Buffer(m_EmptyString) {
  Get_String(2, hint_temporary);
  (*this) = ch;
}

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
inline StringClass::StringClass(const StringClass &string, const bool hint_temporary) : m_Buffer(m_EmptyString) {
  if (hint_temporary || (string.Get_Length() > 0)) {
    Get_String(string.Get_Length() + 1, hint_temporary);
  }

  (*this) = string;
}

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
inline StringClass::StringClass(const TCHAR *string, const bool hint_temporary) : m_Buffer(m_EmptyString) {
  size_t len = string ? _tcsclen(string) : 0;
  if (hint_temporary || len > 0) {
    Get_String(len + 1, hint_temporary);
  }

  (*this) = string;
}

///////////////////////////////////////////////////////////////////
//	StringClass
///////////////////////////////////////////////////////////////////
inline StringClass::StringClass(const WCHAR *string, const bool hint_temporary) : m_Buffer(m_EmptyString) {
  size_t len = string ? wcslen(string) : 0;
  if (hint_temporary || len > 0) {
    Get_String(len + 1, hint_temporary);
  }

  (*this) = string;
}

///////////////////////////////////////////////////////////////////
//	~StringClass
///////////////////////////////////////////////////////////////////
inline StringClass::~StringClass() {
  Free_String();
}

///////////////////////////////////////////////////////////////////
//	Is_Empty
///////////////////////////////////////////////////////////////////
inline bool StringClass::Is_Empty() const { return (m_Buffer[0] == m_NullChar); }

///////////////////////////////////////////////////////////////////
//	Compare
///////////////////////////////////////////////////////////////////
inline int StringClass::Compare(const TCHAR *string) const { return _tcscmp(m_Buffer, string); }

///////////////////////////////////////////////////////////////////
//	Compare_No_Case
///////////////////////////////////////////////////////////////////
inline int StringClass::Compare_No_Case(const TCHAR *string) const { return _tcsicmp(m_Buffer, string); }

///////////////////////////////////////////////////////////////////
//	operator[]
///////////////////////////////////////////////////////////////////
inline const TCHAR &StringClass::operator[](const unsigned int index) const {
  WWASSERT(index < Get_Length());
  return m_Buffer[index];
}

///////////////////////////////////////////////////////////////////
//	operator[]
///////////////////////////////////////////////////////////////////
inline TCHAR &StringClass::operator[](const unsigned int index) {
  WWASSERT(index < Get_Length());
  return m_Buffer[index];
}

///////////////////////////////////////////////////////////////////
//	operator const TCHAR *
///////////////////////////////////////////////////////////////////
inline StringClass::operator const TCHAR *() const { return m_Buffer; }

///////////////////////////////////////////////////////////////////
//	operator==
///////////////////////////////////////////////////////////////////
inline bool StringClass::operator==(const TCHAR *rvalue) const { return (Compare(rvalue) == 0); }

///////////////////////////////////////////////////////////////////
//	operator!=
///////////////////////////////////////////////////////////////////
inline bool StringClass::operator!=(const TCHAR *rvalue) const { return (Compare(rvalue) != 0); }

///////////////////////////////////////////////////////////////////
//	operator <
///////////////////////////////////////////////////////////////////
inline bool StringClass::operator<(const TCHAR *string) const { return (_tcscmp(m_Buffer, string) < 0); }

///////////////////////////////////////////////////////////////////
//	operator <=
///////////////////////////////////////////////////////////////////
inline bool StringClass::operator<=(const TCHAR *string) const { return (_tcscmp(m_Buffer, string) <= 0); }

///////////////////////////////////////////////////////////////////
//	operator >
///////////////////////////////////////////////////////////////////
inline bool StringClass::operator>(const TCHAR *string) const { return (_tcscmp(m_Buffer, string) > 0); }

///////////////////////////////////////////////////////////////////
//	operator >=
///////////////////////////////////////////////////////////////////
inline bool StringClass::operator>=(const TCHAR *string) const { return (_tcscmp(m_Buffer, string) >= 0); }

///////////////////////////////////////////////////////////////////
//	Erase
///////////////////////////////////////////////////////////////////
inline void StringClass::Erase(const unsigned int start_index, size_t char_count) const {
  size_t len = Get_Length();

  if (start_index < len) {

    if (start_index + char_count > len) {
      char_count = len - start_index;
    }

    ::memmove(&m_Buffer[start_index], &m_Buffer[start_index + char_count],
              (len - (start_index + char_count) + 1) * sizeof(TCHAR));

    Store_Length(len - char_count);
  }

}

///////////////////////////////////////////////////////////////////
// Trim leading and trailing whitespace characters (values <= 32)
///////////////////////////////////////////////////////////////////
inline void StringClass::Trim() const { strtrim(m_Buffer); }

///////////////////////////////////////////////////////////////////
//	operator+=
///////////////////////////////////////////////////////////////////
inline const StringClass &StringClass::operator+=(const TCHAR *string) {
  WWASSERT(string != nullptr);

  size_t cur_len = Get_Length();
  size_t src_len = _tcslen(string);
  size_t new_len = cur_len + src_len;

  //
  //	Make sure our buffer is large enough to hold the new string
  //
  Resize(new_len + 1);
  Store_Length(new_len);

  //
  //	Copy the new string onto our the end of our existing buffer
  //
  ::memcpy(&m_Buffer[cur_len], string, (src_len + 1) * sizeof(TCHAR));
  return (*this);
}

///////////////////////////////////////////////////////////////////
//	operator+=
///////////////////////////////////////////////////////////////////
inline const StringClass &StringClass::operator+=(TCHAR ch) {
  size_t cur_len = Get_Length();
  Resize(cur_len + 2);

  m_Buffer[cur_len] = ch;
  m_Buffer[cur_len + 1] = m_NullChar;

  if (ch != m_NullChar) {
    Store_Length(cur_len + 1);
  }

  return (*this);
}

///////////////////////////////////////////////////////////////////
//	Get_Buffer
///////////////////////////////////////////////////////////////////
inline TCHAR *StringClass::Get_Buffer(size_t new_length) {
  Uninitialised_Grow(new_length);

  return m_Buffer;
}

///////////////////////////////////////////////////////////////////
//	Peek_Buffer
///////////////////////////////////////////////////////////////////
inline TCHAR *StringClass::Peek_Buffer() { return m_Buffer; }

///////////////////////////////////////////////////////////////////
//	Peek_Buffer
///////////////////////////////////////////////////////////////////
inline const TCHAR *StringClass::Peek_Buffer() const { return m_Buffer; }

///////////////////////////////////////////////////////////////////
//	operator+=
///////////////////////////////////////////////////////////////////
inline const StringClass &StringClass::operator+=(const StringClass &string) {
  size_t src_len = string.Get_Length();
  if (src_len > 0) {
    size_t cur_len = Get_Length();
    size_t new_len = cur_len + src_len;

    //
    //	Make sure our buffer is large enough to hold the new string
    //
    Resize(new_len + 1);
    Store_Length(new_len);

    //
    //	Copy the new string onto our the end of our existing buffer
    //
    ::memcpy(&m_Buffer[cur_len], (const TCHAR *)string, (src_len + 1) * sizeof(TCHAR));
  }

  return (*this);
}

///////////////////////////////////////////////////////////////////
//	operator+=
///////////////////////////////////////////////////////////////////
inline StringClass operator+(const StringClass &string1, const StringClass &string2) {
  StringClass new_string(string1, true);
  new_string += string2;
  return new_string;
}

///////////////////////////////////////////////////////////////////
//	operator+=
///////////////////////////////////////////////////////////////////
inline StringClass operator+(const TCHAR *string1, const StringClass &string2) {
  StringClass new_string(string1, true);
  new_string += string2;
  return new_string;
}

///////////////////////////////////////////////////////////////////
//	operator+=
///////////////////////////////////////////////////////////////////
inline StringClass operator+(const StringClass &string1, const TCHAR *string2) {
  StringClass new_string(string1, true);
  StringClass new_string2(string2, true);
  new_string += new_string2;
  return new_string;
}

///////////////////////////////////////////////////////////////////
//	Get_Allocated_Length
//
//	Return allocated size of the string buffer
///////////////////////////////////////////////////////////////////
inline size_t StringClass::Get_Allocated_Length() const {
  size_t allocated_length = 0;

  //
  //	Read the allocated length from the header
  //
  if (m_Buffer != m_EmptyString) {
    HEADER *header = Get_Header();
    allocated_length = header->allocated_length;
  }

  return allocated_length;
}

///////////////////////////////////////////////////////////////////
//	Get_Length
//
//	Return text legth. If length is not known calculate it, otherwise
// just return the previously stored value (strlen tends to take
// quite a lot cpu time if a lot of string combining operations are
// performed.
///////////////////////////////////////////////////////////////////
inline size_t StringClass::Get_Length() const {
  size_t length = 0;

  if (m_Buffer != m_EmptyString) {

    //
    //	Read the length from the header
    //
    HEADER *header = Get_Header();
    length = header->length;

    //
    //	Hmmm, a zero length was stored in the header,
    // we better manually get the string length.
    //
    if (length == 0) {
      length = _tcslen(m_Buffer);
      ((StringClass *)this)->Store_Length(length);
    }
  }

  return length;
}

///////////////////////////////////////////////////////////////////
//	Set_Buffer_And_Allocated_Length
//
// Set buffer pointer and init size variable. Length is set to 0
// as the contents of the new buffer are not necessarily defined.
///////////////////////////////////////////////////////////////////
inline void StringClass::Set_Buffer_And_Allocated_Length(TCHAR *buffer, const size_t length) {
  Free_String();
  m_Buffer = buffer;

  //
  //	Update the header (if necessary)
  //
  if (m_Buffer != m_EmptyString) {
    Store_Allocated_Length(length);
    Store_Length(0);
  } else {
    WWASSERT(length == 0);
  }

}

///////////////////////////////////////////////////////////////////
// Allocate_Buffer
///////////////////////////////////////////////////////////////////
inline TCHAR *StringClass::Allocate_Buffer(const size_t length) {
  //
  //	Allocate a buffer that is 'length' characters long, plus the
  // bytes required to hold the header.
  //
  char *buffer = new char[(sizeof(TCHAR) * length) + sizeof(StringClass::HEADER)];

  //
  //	Fill in the fields of the header
  //
  HEADER *header = reinterpret_cast<HEADER *>(buffer);
  header->length = 0;
  header->allocated_length = length;

  //
  //	Return the buffer as if it was a TCHAR pointer
  //
  return reinterpret_cast<TCHAR *>(buffer + sizeof(StringClass::HEADER));
}

///////////////////////////////////////////////////////////////////
// Get_Header
///////////////////////////////////////////////////////////////////
inline StringClass::HEADER *StringClass::Get_Header() const {
  return reinterpret_cast<HEADER *>(((char *)m_Buffer) - sizeof(StringClass::HEADER));
}

///////////////////////////////////////////////////////////////////
// Store_Allocated_Length
///////////////////////////////////////////////////////////////////
inline void StringClass::Store_Allocated_Length(const size_t allocated_length) const {
  if (m_Buffer != m_EmptyString) {
    HEADER *header = Get_Header();
    header->allocated_length = allocated_length;
  } else {
    WWASSERT(allocated_length == 0);
  }

}

///////////////////////////////////////////////////////////////////
// Store_Length
//
// Set length... The caller of this (private) function better
// be sure that the len is correct.
///////////////////////////////////////////////////////////////////
inline void StringClass::Store_Length(const size_t length) const {
  if (m_Buffer != m_EmptyString) {
    HEADER *header = Get_Header();
    header->length = length;
  } else {
    WWASSERT(length == 0);
  }

}
