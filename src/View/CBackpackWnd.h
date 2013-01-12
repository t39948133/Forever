/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CBackpackWnd.h
  * @author 林有良
  * @date   2012/12/21
  *         2013/01/05 整合與修正 by Darren Chen */
#ifndef _CBACKPACKWND_H_
#define _CBACKPACKWND_H_
#include "CWindow.h"
#include "CPlayer.h"

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CBackpackWnd : public CWindow
{
   public:
	   enum {BUTTON_COUNT = BACK_MAX, CELL_SIZE = 60, TEXT_COUNT = BACK_MAX + 2} ;
   	
	   ~CBackpackWnd () {};

      void init(int _x, int _y, CPlayer *pb);

	   // CWindow
	   /* virtual */ bool canDrag(int tx, int ty);
	   /* virtual */ void onRCommand(int btnID);
      /* virtual */ WindowClassType getClassType();
      /* virtual */ void update();
      /* virtual */ void show(bool bShow);
      /* virtual */ void onDrag();

#ifdef _GAMEENGINE_3D_
	   /* virtual */ void setZOrder(int order);
#endif

   private:
      CPlayer *m_pPlayer;

#ifdef _GAMEENGINE_3D_	
	   CImageButton   *m_vpBtn[BUTTON_COUNT] ;
      CTextAreaOgre  *m_vpText[TEXT_COUNT];
      COverlayUI      m_overlay;  //管理overlay
#elif _GAMEENGINE_2D_
	   CTextButton    *m_vpBtn[BUTTON_COUNT] ;
      CTextArea      *m_vpText[TEXT_COUNT];
#endif
};

#endif  // #ifndef _CBACKPACKWND_H_