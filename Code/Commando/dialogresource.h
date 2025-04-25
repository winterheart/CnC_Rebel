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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Combat
 **
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Commando/dialogresource.h      $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 11/09/01 4:45p                                              $*
 *                                                                                             *
 *                    $Revision:: 18                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __DIALOG_RESOURCE_H
#define __DIALOG_RESOURCE_H

//
//	These button IDs are used for "simple" buttons
// that's only purpose is to start a new dialog.
//
//	Note:  These IDs are coded using defines instead of an enumeration
// because the resource compiler ignores enumerations.
//
#define DIALOG_LINK_FIRST 11000

#define IDC_MENU_START_SP_GAME_BUTTON DIALOG_LINK_FIRST
#define IDC_MENU_START_MP_GAME_BUTTON IDC_MENU_START_SP_GAME_BUTTON + 1
#define IDC_MENU_VIEW_SCORES_BUTTON IDC_MENU_START_MP_GAME_BUTTON + 1
#define IDC_MENU_OPTIONS_BUTTON IDC_MENU_VIEW_SCORES_BUTTON + 1
#define IDC_MENU_START_CAMPAIGN_BUTTON IDC_MENU_OPTIONS_BUTTON + 1
#define IDC_MENU_START_TUTORIAL_BUTTON IDC_MENU_START_CAMPAIGN_BUTTON + 1
#define IDC_MENU_LOAD_SP_GAME_BUTTON IDC_MENU_START_TUTORIAL_BUTTON + 1
#define IDC_MENU_DIFFCULTY01_BUTTON (IDC_MENU_LOAD_SP_GAME_BUTTON + 1)
#define IDC_MENU_DIFFCULTY02_BUTTON IDC_MENU_DIFFCULTY01_BUTTON + 1
#define IDC_MENU_DIFFCULTY03_BUTTON IDC_MENU_DIFFCULTY02_BUTTON + 1
#define IDC_MENU_DIFFCULTY04_BUTTON IDC_MENU_DIFFCULTY03_BUTTON + 1
#define IDC_MENU_CONTROLS_BUTTON IDC_MENU_DIFFCULTY04_BUTTON + 1
#define IDC_MENU_CHARACTER_BUTTON IDC_MENU_CONTROLS_BUTTON + 1
#define IDC_MENU_CHEATS_BUTTON IDC_MENU_CHARACTER_BUTTON + 1
#define IDC_MENU_TECH_BUTTON IDC_MENU_CHEATS_BUTTON + 1
#define IDC_MENU_MOVIES_BUTTON IDC_MENU_TECH_BUTTON + 1
#define IDC_MENU_PREVIEWS_BUTTON IDC_MENU_MOVIES_BUTTON + 1
#define IDC_MENU_CREDITS_BUTTON IDC_MENU_PREVIEWS_BUTTON + 1
#define IDC_MENU_QUIT_BUTTON IDC_MENU_CREDITS_BUTTON + 1
#define IDC_MENU_INGAME_MENU_BUTTON IDC_MENU_QUIT_BUTTON + 1
#define IDC_MENU_MAIN_MENU_BUTTON IDC_MENU_INGAME_MENU_BUTTON + 1
#define IDC_MENU_SAVE_SP_GAME_BUTTON IDC_MENU_MAIN_MENU_BUTTON + 1
#define IDC_MENU_MP_LAN_BUTTON IDC_MENU_SAVE_SP_GAME_BUTTON + 1
#define IDC_MENU_MP_INTERNET_BUTTON IDC_MENU_MP_LAN_BUTTON + 1
#define IDC_MENU_MP_START_SERVER_BUTTON IDC_MENU_MP_INTERNET_BUTTON + 1
#define IDC_MENU_MP_JOIN_GAME_BUTTON IDC_MENU_MP_START_SERVER_BUTTON + 1
#define IDC_MENU_MP_START_GAME_BUTTON IDC_MENU_MP_JOIN_GAME_BUTTON + 1

#define IDC_MENU_MULTIPLAY_OPTS_BUTTON IDC_MENU_MP_START_GAME_BUTTON + 1

#define IDC_MENU_MP_MENU_BUTTON IDC_MENU_MULTIPLAY_OPTS_BUTTON + 1
#define IDC_MENU_MP_INTERNET_GAME_BUTTON IDC_MENU_MP_MENU_BUTTON + 1
// efine IDC_MENU_START_SKIRMISH_GAME_BUTTON	IDC_MENU_MP_MENU_BUTTON + 1
// efine IDC_MENU_MP_INTERNET_GAME_BUTTON	IDC_MENU_START_SKIRMISH_GAME_BUTTON + 1
#define IDC_MENU_MP_LAN_GAME_BUTTON IDC_MENU_MP_INTERNET_GAME_BUTTON + 1
#define IDC_MENU_MP_LAN_JOIN_BUTTON IDC_MENU_MP_LAN_GAME_BUTTON + 1
#define IDC_MENU_MP_LAN_START_BUTTON IDC_MENU_MP_LAN_JOIN_BUTTON + 1

#define DIALOG_LINK_LAST IDC_MENU_MP_LAN_START_BUTTON + 1

//
//	These IDs are for non-link controls that reside
// inside a dialog.
//
#define IDC_MENU_BACK_BUTTON DIALOG_LINK_LAST + 1
#define IDC_LOAD_GAME_LIST_CTRL IDC_MENU_BACK_BUTTON + 1
#define IDC_DELETE_GAME_BUTTON IDC_LOAD_GAME_LIST_CTRL + 1
#define IDC_LOAD_GAME_BUTTON IDC_DELETE_GAME_BUTTON + 1
#define IDC_MENU_MP_START_BUTTON IDC_LOAD_GAME_BUTTON + 1
#define IDC_MENU_MP_JOING_BUTTON IDC_MENU_MP_START_BUTTON + 1
#define IDC_MP_NICKNAME_EDIT IDC_LOAD_GAME_BUTTON + 1
#define IDC_MP_CONNECTING_OK_BUTTON IDC_MP_NICKNAME_EDIT + 1
#define IDC_MP_PASSWORD_VALID_COMMAND IDC_MP_CONNECTING_OK_BUTTON + 1

#define IDC_MP_SHORTCUT_NEWS IDC_MP_PASSWORD_VALID_COMMAND + 1
#define IDC_MP_SHORTCUT_CLANS IDC_MP_SHORTCUT_NEWS + 1
#define IDC_MP_SHORTCUT_RANKINGS IDC_MP_SHORTCUT_CLANS + 1
#define IDC_MP_SHORTCUT_BUDDIES IDC_MP_SHORTCUT_RANKINGS + 1
#define IDC_MP_SHORTCUT_ACCOUNT IDC_MP_SHORTCUT_BUDDIES + 1
#define IDC_MP_SHORTCUT_NET_STATUS IDC_MP_SHORTCUT_ACCOUNT + 1
#define IDC_MP_SHORTCUT_PAGE_BUDDY IDC_MP_SHORTCUT_NET_STATUS + 1
#define IDC_MP_SHORTCUT_CHAT IDC_MP_SHORTCUT_PAGE_BUDDY + 1
#define IDC_MP_SHORTCUT_GAMELIST IDC_MP_SHORTCUT_CHAT + 1
#define IDC_MP_SHORTCUT_QUICKMATCH_OPTIONS IDC_MP_SHORTCUT_GAMELIST + 1
#define IDC_MP_SHORTCUT_INTERNET_OPTIONS IDC_MP_SHORTCUT_QUICKMATCH_OPTIONS + 1
#define IDC_MENU_MP_LAN_HOST_BUTTON IDC_MP_SHORTCUT_INTERNET_OPTIONS + 1

#define IDC_CNC_PURCHASE_VEHICLE_BUTTON 12000
#define IDC_CNC_PURCHASE_POWERUP_BUTTON 12001
#define IDC_CNC_PURCHASE_CHARACTER_BUTTON 12002

#define IDC_BUY_GDI_VEHICLE01_BUTTON 2000
#define IDC_BUY_GDI_VEHICLE02_BUTTON 2001
#define IDC_BUY_GDI_VEHICLE03_BUTTON 2002
#define IDC_BUY_GDI_VEHICLE04_BUTTON 2003
#define IDC_BUY_NOD_VEHICLE01_BUTTON 2004
#define IDC_BUY_NOD_VEHICLE02_BUTTON 2005
#define IDC_BUY_NOD_VEHICLE03_BUTTON 2006
#define IDC_BUY_NOD_VEHICLE04_BUTTON 2007
#define IDC_BUY_NOD_VEHICLE05_BUTTON 2008
#define IDC_BUY_NOD_VEHICLE06_BUTTON 2009
#define IDC_BUY_NOD_VEHICLE07_BUTTON 2010

#define IDC_BUY_POWERUP01_BUTTON 3000
#define IDC_BUY_POWERUP02_BUTTON 3001
#define IDC_BUY_POWERUP03_BUTTON 3002
#define IDC_BUY_POWERUP04_BUTTON 3003
#define IDC_BUY_POWERUP05_BUTTON 3004
#define IDC_BUY_POWERUP06_BUTTON 3005
#define IDC_BUY_POWERUP07_BUTTON 3006
#define IDC_BUY_POWERUP08_BUTTON 3007
#define IDC_BUY_POWERUP09_BUTTON 3008
#define IDC_BUY_POWERUP10_BUTTON 3009
#define IDC_BUY_POWERUP11_BUTTON 3010
#define IDC_BUY_POWERUP12_BUTTON 3011
#define IDC_BUY_POWERUP13_BUTTON 3012
#define IDC_BUY_POWERUP14_BUTTON 3013

#define IDC_BUY_CHARACTER01_BUTTON 4000
#define IDC_BUY_CHARACTER02_BUTTON 4001
#define IDC_BUY_CHARACTER03_BUTTON 4002
#define IDC_BUY_CHARACTER04_BUTTON 4003
#define IDC_BUY_CHARACTER05_BUTTON 4004
#define IDC_BUY_CHARACTER06_BUTTON 4005
#define IDC_BUY_CHARACTER07_BUTTON 4006
#define IDC_BUY_CHARACTER08_BUTTON 4007
#define IDC_BUY_CHARACTER09_BUTTON 4008
#define IDC_BUY_CHARACTER10_BUTTON 4009
#define IDC_BUY_CHARACTER11_BUTTON 4010
#define IDC_BUY_CHARACTER12_BUTTON 4011
#define IDC_BUY_CHARACTER13_BUTTON 4012

#define IDC_SCORE_TABCTRL 40001
#define IDC_GENERIC_TABCTRL 40002

#endif //__DIALOG_RESOURCE_H
