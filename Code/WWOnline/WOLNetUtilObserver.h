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
 *     $Archive: /Commando/Code/WWOnline/WOLNetUtilObserver.h $
 *
 * DESCRIPTION
 *
 * PROGRAMMER
 *     $Author: Denzil_l $
 *
 * VERSION INFO
 *     $Revision: 4 $
 *     $Modtime: 1/22/02 5:53p $
 *
 ******************************************************************************/

#ifndef __WOLNETUTILOBSERVER_H__
#define __WOLNETUTILOBSERVER_H__

#include <windows.h>
#include "WOLUser.h"

namespace WOL {
#include <WOLAPI\wolapi.h>
}

template <typename T> class RefPtr;

namespace WWOnline {

class Session;
class SquadData;

class NetUtilObserver : public WOL::INetUtilEvent {
public:
  NetUtilObserver();

  void Init(Session &outer);

  //---------------------------------------------------------------------------
  // IUnknown methods
  //---------------------------------------------------------------------------
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(const IID &iid, void **ppv);
  virtual ULONG STDMETHODCALLTYPE AddRef(void);
  virtual ULONG STDMETHODCALLTYPE Release(void);

  //---------------------------------------------------------------------------
  // INetUtilEvent Methods
  //---------------------------------------------------------------------------
  STDMETHOD(OnPing)(HRESULT hr, int time, unsigned long ip, int handle);

  STDMETHOD(OnLadderList)(HRESULT hr, WOL::Ladder *list, int count, long time, int keyRung);

  STDMETHOD(OnGameresSent)(HRESULT hr);

  STDMETHOD(OnNewNick)(HRESULT hr, LPCSTR message, LPCSTR nick, LPCSTR pass);

  STDMETHOD(OnAgeCheck)(HRESULT hr, int years, int consent);

  STDMETHOD(OnWDTState)(HRESULT hr, unsigned char *state, int length);

  STDMETHOD(OnHighscore)(HRESULT hr, WOL::Highscore *list, int count, long time, int keyRung);

protected:
  virtual ~NetUtilObserver();

  NetUtilObserver(const NetUtilObserver &);
  const NetUtilObserver &operator=(const NetUtilObserver &);

  void ProcessLadderListResults(WOL::Ladder *list, long timeStamp);
  void NotifyClanLadderUpdate(const UserList &users, const RefPtr<SquadData> &squad);

private:
  ULONG mRefCount;
  Session *mOuter;
};

} // namespace WWOnline

#endif // _WOLNETUTILOBSERVER_H__