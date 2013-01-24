/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWindowMan.h
  * @author 林有良
  * @date   2012/12/21
  * @version
  *         2013/01/05 Darren Chen - 整合與修正 */
#ifndef _CWINDOWMAN_H_
#define _CWINDOWMAN_H_
#include "CWindow.h"

#ifdef _GAMEENGINE_2D_
#include "CKeyMan.h"
#endif

//視窗管理者(manager)
class CWindowMan
{
   public:
	   CWindowMan();
      virtual ~CWindowMan();

	   virtual void addWnd(CWindow *pWnd);
      void deleteAllWindow();

#ifdef _GAMEENGINE_2D_
      bool work(HWND hWnd, CKeyMan &keyMan);
	   void draw(HDC hdc);
#endif

   protected:
#ifdef _GAMEENGINE_2D_
	   void doDrag(HWND hWnd, CKeyMan &keyMan);
#endif

	   std::list<CWindow *> *m_pWindowList;  // 視窗列表
	   CWindow *m_pDragWnd;     // 拖曳中的視窗
      CWindow *m_pBackpackWnd; // 背包視窗
	   bool     m_bInDrag;      // 視窗是否在拖曳中
	   int      m_iDragX;       // 拖曳的座標X
      int      m_iDragY;       // 拖曳的座標Y 
      int      m_iClientX;     // 滑鼠點擊的座標X
      int      m_iClientY;     // 滑鼠點擊的座標Y
};

#endif  // #ifndef _CWINDOWMAN_H_