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

#ifndef __IMECANDIDATECTRL_H__
#define __IMECANDIDATECTRL_H__

#include "DialogControl.h"
#include "ScrollBarCtrl.h"
#include "Render2D.h"
#include "Render2DSentence.h"
#include "Vector.h"

namespace IME {
class IMECandidate;
}

class IMECandidateCtrl : public DialogControlClass {
public:
  IMECandidateCtrl();
  virtual ~IMECandidateCtrl();

  void Init(IME::IMECandidate *candidate);
  void Changed(IME::IMECandidate *candidate);
  void Reset(void);

protected:
  void CreateControlRenderer(void);
  void CreateTextRenderer(void);

  void SetCurrSel(int index);
  int EntryFromPos(const Vector2 &mousePos);
  void UpdateScrollPos(void);

  void CalculateCandidatePageExtent(Vector2 &outExtent, Vector2 &outCellSize);

  // DialogControlClass methods
public:
  const RectClass &Get_Window_Rect(void) const { return mFullRect; }

protected:
  void Render(void);
  void Update_Client_Rect(void);

  void On_Set_Cursor(const Vector2 &mousePos);
  void On_LButton_Down(const Vector2 &mousePos);
  void On_LButton_Up(const Vector2 &mousePos);
  void On_Add_To_Dialog(void);
  void On_Remove_From_Dialog(void);

  // ControlAdviseSinkClass methods
protected:
  void On_VScroll(ScrollBarCtrlClass *, int, int);

  // Data members
protected:
  RectClass mFullRect;
  Vector2 mCellSize;

  int mCurrSel;
  unsigned int mScrollPos;
  unsigned int mCellsPerPage;

  ScrollBarCtrlClass mScrollBarCtrl;
  RectClass mScrollBarRect;

  Render2DClass mControlRenderer;
  Render2DClass mHilightRenderer;
  Render2DSentenceClass mTextRenderer;

  IME::IMECandidate *mCandidate;
};

#endif // __IMECANDIDATECTRL_H__
