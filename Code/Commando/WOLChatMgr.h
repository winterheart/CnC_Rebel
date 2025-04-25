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
 *     $Archive: /Commando/Code/Commando/WOLChatMgr.h $
 *
 * DESCRIPTION
 *
 * PROGRAMMER
 *     Denzil E. Long, Jr.
 *     $Author: Denzil_l $
 *
 * VERSION INFO
 *     $Revision: 18 $
 *     $Modtime: 11/08/01 2:31p $
 *
 ******************************************************************************/

#ifndef __WOLCHATMGR_H__
#define __WOLCHATMGR_H__

#include <WWLib\RefCount.h>
#include <WWLib\Notify.h>
#include <WWLib\WideString.h>
#include <WWOnline\RefPtr.h>
#include <WWOnline\WOLSession.h>
#include <WWOnline\WOLChatMsg.h>

typedef std::vector<RefPtr<WWOnline::ChannelData>> LobbyList;

enum WOLChatMgrEvent {
  LobbyListChanged = 1,
  LobbyChanged,
  UserInListChanged,
  UserOutListChanged,
  MessageListChanged,
  KickedFromChannel,
  BannedFromChannel
};

class WOLChatMgr : public RefCountClass,
                   public Notifier<WOLChatMgrEvent>,
                   public Observer<WWOnline::ServerError>,
                   public Observer<WWOnline::ChannelListEvent>,
                   public Observer<WWOnline::ChannelEvent>,
                   public Observer<WWOnline::UserEvent>,
                   public Observer<WWOnline::UserList>,
                   public Observer<WWOnline::ChatMessage> {
public:
  static WOLChatMgr *GetInstance(bool createOK);

  void Start(void);
  void Stop(void);

  // Lobby Methods
  void RefreshLobbyList(void);
  const LobbyList &GetLobbyList(void);

  const RefPtr<WWOnline::ChannelData> &GetCurrentLobby(void);
  const RefPtr<WWOnline::ChannelData> FindLobby(const wchar_t *name);

  void CreateLobby(const wchar_t *name, const wchar_t *password);
  void JoinLobby(const RefPtr<WWOnline::ChannelData> &channel);
  void LeaveLobby(void);
  void GetLobbyDisplayName(const RefPtr<WWOnline::ChannelData> &lobby, WideStringClass &outName);

  // User Methods
  const RefPtr<WWOnline::UserData> FindUser(const wchar_t *name);

  inline const WWOnline::UserList &GetUserInList(void) { return mUserInList; }

  void ClearUserInList(void);

  inline const WWOnline::UserList &GetUserOutList(void) { return mUserOutList; }

  void ClearUserOutList(void);

  bool SquelchUser(const RefPtr<WWOnline::UserData> &user, bool onoff);
  void LocateUser(const wchar_t *name);

  // Message Methods
  inline const WWOnline::ChatMessageList &GetMessageList(void) { return mMessageList; }

  void ClearMessageList(void);

  void SendPublicMessage(const wchar_t *message, bool isAction);
  void SendPrivateMessage(const RefPtr<WWOnline::UserData> &user, const wchar_t *message, bool isAction);
  void SendPrivateMessage(WWOnline::UserList &users, const wchar_t *message, bool isAction);

protected:
  WOLChatMgr();
  ~WOLChatMgr();

  // Delcare here to prevent copy and assignment
  WOLChatMgr(const WOLChatMgr &);
  const WOLChatMgr &operator=(const WOLChatMgr &);

  bool FinalizeCreate(void);

  bool IsLobbyValid(const RefPtr<WWOnline::ChannelData> &lobby);

  void AddMessage(const wchar_t *sender, const wchar_t *message, bool isPrivate, bool isAction);
  bool PassesFilters(const WWOnline::ChatMessage &msg);

  void HandleNotification(WWOnline::ServerError &);
  void HandleNotification(WWOnline::ChannelListEvent &);
  void HandleNotification(WWOnline::ChannelEvent &);
  void HandleNotification(WWOnline::UserEvent &);
  void HandleNotification(WWOnline::UserList &);
  void HandleNotification(WWOnline::ChatMessage &);

  bool ProcessCommand(const wchar_t *message);

private:
  static WOLChatMgr *_mInstance;
  RefPtr<WWOnline::Session> mWOLSession;

  WideStringClass mLobbyPrefix;
  LobbyList mLobbyList;

  WWOnline::UserList mUserInList;
  WWOnline::UserList mUserOutList;
  WideStringClass mLocatingUserName;

  WWOnline::ChatMessageList mMessageList;
};

#endif __WOLCHATMGR_H__
