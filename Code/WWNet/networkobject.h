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
 ***                            Confidential - Westwood Studios                              ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Commando                                                     *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwnet/networkobject.h                        $*
 *                                                                                             *
 *                      $Author:: Jani_p                                                      $*
 *                                                                                             *
 *                     $Modtime:: 1/15/02 2:03p                                               $*
 *                                                                                             *
 *                    $Revision:: 34                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "wwpacket.h"

enum PACKET_TIER_ENUM {
  PACKET_TIER_CREATION,
  PACKET_TIER_RARE,
  PACKET_TIER_OCCASIONAL,
  PACKET_TIER_FREQUENT,

  PACKET_TIER_COUNT
};

////////////////////////////////////////////////////////////////
//	Forward delcarations
////////////////////////////////////////////////////////////////
class BitStreamClass;

////////////////////////////////////////////////////////////////
//
//	NetworkObjectClass
//
//	Base class that all objects which need to transmit state
//	updates across the network are derived from.
//
////////////////////////////////////////////////////////////////
class NetworkObjectClass {
public:
  ////////////////////////////////////////////////////////////////
  //	Public constants
  ////////////////////////////////////////////////////////////////
  typedef enum {
    BIT_FREQUENT = 0x01,
    BIT_OCCASIONAL = 0x02 | BIT_FREQUENT,
    BIT_RARE = 0x04 | BIT_OCCASIONAL,
    BIT_CREATION = 0x08 | BIT_RARE,
  } DIRTY_BIT;

  enum { MAX_CLIENT_COUNT = 128 };

  ////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  ////////////////////////////////////////////////////////////////
  NetworkObjectClass();
  virtual ~NetworkObjectClass();

  ////////////////////////////////////////////////////////////////
  //	Public methods
  ////////////////////////////////////////////////////////////////

  //
  //	ID support
  //
  int Get_Network_ID() const { return NetworkID; }
  void Set_Network_ID(int id);

#ifdef WWDEBUG
  int Get_Created_By_Packet_ID() const { return CreatedByPacketID; }
  void Set_Created_By_Packet_ID(int id);
#endif // WWDEBUG

  //
  //	Class ID support
  //
  virtual uint32 Get_Network_Class_ID() const { return 0; }

  //
  //	Server-to-client data importing/exporting
  //
  virtual void Import_Creation(BitStreamClass &packet) {}
  virtual void Import_Rare(BitStreamClass &packet) {}
  virtual void Import_Occasional(BitStreamClass &packet) {}
  virtual void Import_Frequent(BitStreamClass &packet) {}

  virtual void Export_Creation(BitStreamClass &packet) {}
  virtual void Export_Rare(BitStreamClass &packet) {}
  virtual void Export_Occasional(BitStreamClass &packet) {}
  virtual void Export_Frequent(BitStreamClass &packet) {}

  //
  //	Timestep support
  //
  virtual void Network_Think() {}

  //
  //	Delete support.
  // Override Delete in the subclass if you have a destructor there.
  //
  bool Is_Delete_Pending() const { return IsDeletePending; }
  virtual void Set_Delete_Pending();
  virtual void Delete() = 0;

  //
  // Record application packet type
  //
  void Set_App_Packet_Type(BYTE type) { AppPacketType = type; }
  BYTE Get_App_Packet_Type() const { return AppPacketType; }

  //
  //	Dirty bit support
  //
  virtual void Set_Object_Dirty_Bit(DIRTY_BIT dirty_bit, bool onoff);
  virtual void Set_Object_Dirty_Bit(int client_id, DIRTY_BIT dirty_bit, bool onoff);
  virtual void Clear_Object_Dirty_Bits();
  virtual bool Get_Object_Dirty_Bit(int client_id, DIRTY_BIT dirty_bit);
  virtual BYTE Get_Object_Dirty_Bits(int client_id);
  virtual void Set_Object_Dirty_Bits(int client_id, BYTE bits);
  virtual bool Is_Client_Dirty(int client_id);

  inline bool Get_Object_Dirty_Bit_2(int client_id, DIRTY_BIT dirty_bit) const;
  inline BYTE Get_Object_Dirty_Bits_2(int client_id) const;

  //
  //	Filtering support
  //
  virtual int Get_Vis_ID() { return -1; }
  virtual bool Get_World_Position(Vector3 &pos) const { return false; }
  virtual float Get_Filter_Distance() const { return 10000.0f; }

  //
  // Client-side update tracking
  //
  void Reset_Client_Hint_Count(int client_id);
  void Increment_Client_Hint_Count(int client_id);
  void Hint_To_All_Clients();
  BYTE Get_Client_Hint_Count(int client_id) const;
  inline BYTE Get_Client_Hint_Count_2(int client_id) const;
  void Reset_Import_State_Count() { ImportStateCount = 0; }
  void Increment_Import_State_Count() { ImportStateCount++; }
  int Get_Import_State_Count() const { return ImportStateCount; }
  void Reset_Last_Clientside_Update_Time();
  void Set_Last_Clientside_Update_Time(ULONG time);
  ULONG Get_Last_Clientside_Update_Time() const { return LastClientsideUpdateTime; }
  int Get_Clientside_Update_Frequency();

  //
  // Ownership
  //
  bool Belongs_To_Client(int client_id) const;

  //
  // Per client update functions.
  //
  unsigned char Get_Frequent_Update_Export_Size() const { return (FrequentExportPacketSize); }
  void Set_Frequent_Update_Export_Size(unsigned char size) { FrequentExportPacketSize = size; }
  unsigned long Get_Last_Update_Time(int client_id) const;
  unsigned short Get_Update_Rate(int client_id) const;
  void Set_Last_Update_Time(int client_id, unsigned long time);
  void Set_Update_Rate(int client_id, unsigned short rate);

  //
  //	Diagnostics
  //
  virtual bool Is_Tagged() { return false; }
  virtual void Get_Description(StringClass &description) {}

  void Set_Unreliable_Override(bool flag) { UnreliableOverride = flag; }
  bool Get_Unreliable_Override() const { return UnreliableOverride; }

  //
  //	Static methods
  //
  static void Set_Is_Server(bool flag) { IsServer = flag; }

  void Set_Cached_Priority(float priority);
  virtual float Get_Cached_Priority() const { return CachedPriority; }
  inline void Set_Cached_Priority_2(int client_id, float priority);
  inline float Get_Cached_Priority_2(int client_id) const;

  void Set_Last_Object_Id_I_Damaged(int id) { LastObjectIdIDamaged = id; }
  int Get_Last_Object_Id_I_Damaged() const { return LastObjectIdIDamaged; }

  void Set_Last_Object_Id_I_Got_Damaged_By(int id) { LastObjectIdIGotDamagedBy = id; }
  int Get_Last_Object_Id_I_Got_Damaged_By() const { return LastObjectIdIGotDamagedBy; }

private:
  ////////////////////////////////////////////////////////////////
  //	Private constants
  ////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////
  //	Private member data
  ////////////////////////////////////////////////////////////////
  int NetworkID;

#ifdef WWDEBUG
  int CreatedByPacketID;
#endif // WWDEBUG

  //
  // Per client update information. Bandwidth will be allocated per object, per client.
  //
  struct PerClientUpdateInfoStruct {
    unsigned long LastUpdateTime;
    unsigned short UpdateRate;
    BYTE ClientHintCount;
  } UpdateInfo[MAX_CLIENT_COUNT];

  BYTE ClientStatus[MAX_CLIENT_COUNT];
  int ImportStateCount;
  ULONG LastClientsideUpdateTime;
  ULONG ClientsideUpdateFrequencySampleStartTime;
  int ClientsideUpdateFrequencySampleCount;
  int ClientsideUpdateRate;
  bool IsDeletePending;
  BYTE AppPacketType;

  int LastObjectIdIDamaged;
  int LastObjectIdIGotDamagedBy;

  //
  // The size of this objects FREQUENT tier export. Used as a starting point for bandwidth calculation.
  // It better not be exporting more than 255 bytes!
  //
  unsigned char FrequentExportPacketSize;

  float CachedPriority;
  float CachedPriority_2[MAX_CLIENT_COUNT];

  bool UnreliableOverride;

  static bool IsServer;
};

////////////////////////////////////////////////////////////////
//
//	Set_Cached_Priority
//
////////////////////////////////////////////////////////////////
inline void NetworkObjectClass::Set_Cached_Priority_2(int client_id, float priority) {
  CachedPriority_2[client_id] = priority;
}

////////////////////////////////////////////////////////////////
//
//	Set_Cached_Priority
//
////////////////////////////////////////////////////////////////
inline float NetworkObjectClass::Get_Cached_Priority_2(int client_id) const { return (CachedPriority_2[client_id]); }

////////////////////////////////////////////////////////////////
//
//	Get_Object_Dirty_Bit
//
////////////////////////////////////////////////////////////////
inline bool NetworkObjectClass::Get_Object_Dirty_Bit_2(int client_id, DIRTY_BIT dirty_bit) const {
  return ((ClientStatus[client_id] & dirty_bit) == dirty_bit);
}

////////////////////////////////////////////////////////////////
//
//	Get_Object_Dirty_Bits
//
////////////////////////////////////////////////////////////////
inline BYTE NetworkObjectClass::Get_Object_Dirty_Bits_2(int client_id) const { return ClientStatus[client_id]; }

////////////////////////////////////////////////////////////////
//
//	Get_Client_Hint_Count
//
////////////////////////////////////////////////////////////////
inline BYTE NetworkObjectClass::Get_Client_Hint_Count_2(int client_id) const { return UpdateInfo[client_id].ClientHintCount; }

// virtual void		Clear_Object_Dirty_Bits (int client_id);
// static void			Set_Random_Float (float random_float);
// static float		RandomFloat;
// float					CachedPriority;

// static float		MaxDistance;

// virtual float		Compute_Object_Priority (int client_id, const Vector3 &client_pos);
// void					Set_Cached_Priority (float priority);
// virtual float		Get_Object_Distance (const Vector3 &client_pos);
// virtual float		Get_Cached_Priority () const
// { return CachedPriority; } static void			Set_Max_Distance (float distance)
// { MaxDistance = distance; } static float		MaxDistance;