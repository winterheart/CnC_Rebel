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

/******************************************************************************
 *
 * FILE
 *     $Archive: /Commando/Code/WWOnline/WOLAgeCheck.h $
 *
 * DESCRIPTION
 *
 * PROGRAMMER
 *     $Author: Denzil_l $
 *
 * VERSION INFO
 *     $Revision: 1 $
 *     $Modtime: 7/09/01 6:03p $
 *
 ******************************************************************************/

#ifndef __WOLAGECHECK_H__
#define __WOLAGECHECK_H__

namespace WWOnline {

class AgeCheckEvent {
public:
  AgeCheckEvent(int age, bool consent) : mAge(age), mConsent(consent) {}

  inline int GetAge() const { return mAge; }

  inline bool HasConsent() const { return mConsent; }

private:
  int mAge;
  bool mConsent;
};

} // namespace WWOnline

#endif // __WOLAGECHECK_H__
