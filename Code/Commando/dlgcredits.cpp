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
 *                     $Archive:: /Commando/Code/commando/dlgcredits.cpp        $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 1/27/02 11:33a                                              $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "dlgcredits.h"
#include "wwfile.h"
#include "ffactory.h"

////////////////////////////////////////////////////////////////
//
//	CreditsMenuClass
//
////////////////////////////////////////////////////////////////
CreditsMenuClass::CreditsMenuClass(void) : MenuDialogClass(IDD_OPTIONS_CREDITS) { return; }

////////////////////////////////////////////////////////////////
//
//	On_Init_Dialog
//
////////////////////////////////////////////////////////////////
void CreditsMenuClass::On_Init_Dialog(void) {
  const char *CREDITS_TXT_FILENAME = "credits.txt";

  //
  //	Open the text file
  //
  FileClass *credits_txt_file = _TheFileFactory->Get_File(CREDITS_TXT_FILENAME);
  if (credits_txt_file != NULL && credits_txt_file->Is_Available()) {
    if (credits_txt_file->Open()) {

      //
      //	Read the data from the file
      //
      int size = credits_txt_file->Size();
      StringClass ascii_text;
      credits_txt_file->Read(ascii_text.Get_Buffer(size + 1), size);
      ascii_text.Peek_Buffer()[size] = 0;

      //
      //	Convert the text to wide character format and
      //	strip off any carriage-returns
      //
      WideStringClass wide_text;
      WCHAR *buffer = wide_text.Get_Buffer(size + 1);
      int dest_index = 0;

      int len = ascii_text.Get_Length();
      for (int index = 0; index < len; index++) {
        if (ascii_text[index] != '\r') {
          buffer[dest_index++] = (unsigned char)ascii_text[index];
        }
      }
      buffer[dest_index] = 0;

      //
      //	Put the text into the control
      //
      Set_Dlg_Item_Text(IDC_CREDITS_EDIT, wide_text);
    }

    //
    //	Close the text file
    //
    _TheFileFactory->Return_File(credits_txt_file);
  }

  MenuDialogClass::On_Init_Dialog();
  return;
}

////////////////////////////////////////////////////////////////
//
//	On_Command
//
////////////////////////////////////////////////////////////////
void CreditsMenuClass::On_Command(int ctrl_id, int message_id, DWORD param) {
  MenuDialogClass::On_Command(ctrl_id, message_id, param);
  return;
}
