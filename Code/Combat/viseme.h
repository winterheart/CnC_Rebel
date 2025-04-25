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

#ifndef __VISEME_H_
#define __VISEME_H_

/*typedef enum VISEME_ID
{
        VISEME_CAT			= 1,		// 0  "cAt"
        VISEME_EAT			= 2,		// 1  "EAt"
        VISEME_IF			= 1, 		// 2  "If"
        VISEME_OX			= 4,		// 3  "Ox"
        VISEME_WET			= 5,		// 4  "Wet", "bOOt"
        VISEME_UP			= 5,		// 5  "Up"
        VISEME_ROAR			= 7,		// 6  "Roar"
        VISEME_FAVE			= 3,		// 7  "Fart", "Van"
        VISEME_CHURCH		= 6,		// 8  "CHurch", "SHoot"
        VISEME_BUMP			= 0,		// 9  "Bump", "p", "m"
        VISEME_THOUGH		= 6,		// 10 "THough", "THen"
        VISEME_TOLD			= 7,		// 11 'Told'
        VISEME_CAGE			= 7,		// 12 'K', 'ck'
        VISEME_NEW			= 7,		// 13 "New"
        VISEME_SIZE			= 7,		// 14 "Size", "Zip"
        VISEME_EARTH		= 2,		// 15 "buttER"
        VISEME_COUNT		= 8,
} VISEME_ID;*/

typedef enum VISEME_ID {
  VISEME_CAT = 0, // 0  "cAt"
  VISEME_EAT,     // 1  "EAt"
  VISEME_IF,      // 2  "If"
  VISEME_OX,      // 3  "Ox"
  VISEME_WET,     // 4  "Wet", "bOOt"
  VISEME_UP,      // 5  "Up"
  VISEME_ROAR,    // 6  "Roar"
  VISEME_FAVE,    // 7  "Fart", "Van"
  VISEME_CHURCH,  // 8  "CHurch", "SHoot"
  VISEME_BUMP,    // 9  "Bump", "p", "m"
  VISEME_THOUGH,  // 10 "THough", "THen"
  VISEME_TOLD,    // 11 'Told'
  VISEME_CAGE,    // 12 'K', 'ck'
  VISEME_NEW,     // 13 "New"
  VISEME_SIZE,    // 14 "Size", "Zip"
  VISEME_EARTH,   // 15 "buttER"
  VISEME_COUNT,
} VISEME_ID;

class VisemeManager {
public:
  VisemeManager(void);

  int Get_Visemes(const char *pword, int *visemelist, int maxvisemes = 255) const;

private:
  int Lookup(const char *pchar, const char *pword, int viseme[]) const;
  int Do_Letter_a(const char *pchar, char prevchar, int *viseme) const;
  int Do_Letter_e(const char *pchar, char prevchar, int *viseme) const;
  int Do_Letter_i(const char *pchar, char prevchar, int *viseme) const;
  int Do_Letter_o(const char *pchar, char prevchar, int *viseme) const;
  int Do_Letter_u(const char *pchar, char prevchar, int *viseme) const;
  int Do_Letter_s(const char *pchar, char prevchar, int *viseme) const;
  int Do_Letter_t(const char *pchar, char prevchar, int *viseme) const;
};

#endif
