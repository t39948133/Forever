/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWindow.h
  * @author 林有良
  * @date   2012/12/21
  * @version
  *         2013/01/05 Darren Chen - 整合與修正 */
#ifndef _CWINDOW_H_
#define _CWINDOW_H_
#include "Common.h"

typedef enum WINDOW_CLASS_TYPE {
   WND_NULL,
   WND_PLAYERINFO,  // 人物資訊視窗
   WND_BACKPACK,    // 背包視窗
   WND_SKILL,       // 技能視窗
   WND_HUD,         // Hud視窗
   WND_HOTKEY,      // 快捷鍵視窗
   WND_TARGETINFO,  // 目標視窗
   WND_PLAYERSTATE, // 人物狀態視窗
} WindowClassType;

class CWindowMan;

//代表一個遊戲介面視窗
//將來可以被擴充成為背包介面,狀態介面,任務界面
class CWindow
{
   public:
      CWindow();
	   virtual ~CWindow();

	   CWindow* pParent ;//父親視窗
	   typedef std::list <CWindow*> VP_WND ;
	   VP_WND vpWnd ;//所有的子視窗

	   int x, y ;//視窗的座標,左上角的
	   int w, h ;//視窗的寬高

	   bool checkPoint(int tx, int ty);
      void addChild(CWindow *pChildWnd);
      void delChild(CWindow *pChildWnd);

	   virtual bool canDrag(int tx, int ty);   // 是否可以拖曳視窗
      virtual void onDrag();                  // 視窗拖曳過程中

	   virtual void onLClick(int tx, int ty);  // 滑鼠左鍵Click
      virtual void onRClick(int tx, int ty);  // 滑鼠右鍵Click
   	
      virtual void onLCommand(int btnID);  //子視窗,按鈕button,通知 (滑鼠左鍵按下)
      virtual void onRCommand(int btnID);  //子視窗,按鈕button,通知 (滑鼠右鍵按下)

      virtual WindowClassType getClassType();  // 取得視窗型態
      void setWindowMan(CWindowMan *pWndMan);

      bool isVisible();
      virtual void show(bool bShow);

#ifdef _GAMEENGINE_3D_
	   virtual void setZOrder(int order);
      virtual int getZOrder();
#elif _GAMEENGINE_2D_
      virtual void draw(HDC hdc, int ox, int oy);
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

   protected:
      CWindowMan* getWindowMan();

   private:
      bool        m_bVisible;
      CWindowMan *m_pWindowMan;
};

#endif  // #ifndef _CWINDOW_H_