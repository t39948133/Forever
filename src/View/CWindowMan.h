/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWindowMan.h
  * @author 林有良
  * @date   2012/12/21
  *         2013/01/05 整合與修正 by Darren Chen */
#ifndef _CWINDOWMAN_H_
#define _CWINDOWMAN_H_
#include "CWindow.h"
#include "CKeyMan.h"

//視窗管理者(manager)
class CWindowMan
{
   protected:
	   typedef std::list <CWindow*> VP_WINDOW ;
	   VP_WINDOW vpWindow ;
	   CWindow* pDragWnd ;//拖曳中的視窗

	   bool bInDrag ;//代表視窗是否在拖曳中
	   int dragX, dragY ;

	   int screenX, screenY ;

	   int clientX, clientY ;

   public:
	   CWindowMan () ;

	   void addWnd (CWindow* pw) ;

   private:
	   void doDrag (HWND hWnd, CKeyMan&) ;

   public:
	   bool work (HWND hWnd, CKeyMan&) ;

#ifdef _GAMEENGINE_2D_
	   void draw(HDC hdc) ;
#endif

	   void deleteAllWindow () ;
};

#endif  // #ifndef _CWINDOWMAN_H_