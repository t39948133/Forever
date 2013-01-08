/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWindow.h
  * @author 林有良
  * @date   2012/12/21
  *         2013/01/05 整合與修正 by Darren Chen */
#ifndef _CWINDOW_H_
#define _CWINDOW_H_
#include "Common.h"

typedef enum WINDOW_CLASS_TYPE {
   WND_NULL,
   WND_PLAYERINFO,  // 人物資訊視窗
   WND_BACKPACK,    // 背包視窗
   WND_SKILL,       // 技能視窗
} WindowClassType;

//代表一個遊戲介面視窗
//將來可以被擴充成為背包介面,狀態介面,任務界面
class CWindow
{
   public:
      CWindow ();
	   virtual ~CWindow ();

	   CWindow* pParent ;//父親視窗
	   typedef std::list <CWindow*> VP_WND ;
	   VP_WND vpWnd ;//所有的子視窗

	   int x, y ;//視窗的座標,左上角的
	   int w, h ;//視窗的寬高

	   bool bVisible ;

	   bool checkPoint (int tx, int ty) ;

	   virtual void onMove () {} ;

	   virtual bool canDrag (int tx, int ty) ;
	   virtual void onLClick (int tx, int ty);  // 滑鼠左鍵Click
      virtual void onRClick(int tx, int ty);   // 滑鼠右鍵Click
   	
	   virtual void setZOrder (int) {} ;

	   void addChild (CWindow*) ;

	   virtual void onLCommand (int) {} ;//子視窗,按鈕button,通知 (滑鼠左鍵按下)
      virtual void onRCommand (int) {} ;//子視窗,按鈕button,通知 (滑鼠右鍵按下)

      virtual WindowClassType getClassType();

#ifdef _GAMEENGINE_2D_
      virtual void draw (HDC hdc, int ox, int oy) ;
#endif 
};

#endif  // #ifndef _CWINDOW_H_