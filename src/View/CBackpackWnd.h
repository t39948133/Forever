/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CBackpackWnd.h
  * @author 林有良
  * @date   2012/12/21
  * @version
  *         2013/01/05 Darren Chen - 整合與修正 */
#ifndef _CBACKPACKWND_H_
#define _CBACKPACKWND_H_
#include "CWindow.h"
#include "CPlayer.h"
#include "IPlayerBackpackEventListener.h"
#include "IPlayerAttrEventListener.h"

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CBackpackWnd : public CWindow,
                     public IPlayerBackpackEventListener,
                     public IPlayerAttrEventListener
{
   public:
      enum {BUTTON_COUNT = BACK_MAX, ICON_SIZE = 40};
      enum {TEXT_TITLE, TEXT_MONEY, TEXT_COUNT};
   	
      CBackpackWnd();
	   ~CBackpackWnd();

      void init(int _x, int _y, CPlayer *pb);

	   // CWindow
	   /* virtual */ bool canDrag(int tx, int ty);
      /* virtual */ void onLCommand(int btnID);
	   /* virtual */ void onRCommand(int btnID);
      /* virtual */ WindowClassType getClassType();
      /* virtual */ void show(bool bShow);
      /* virtual */ void onDrag();
#ifdef _GAMEENGINE_3D_
	   /* virtual */ void setZOrder(int order);
#endif

      // IPlayerBackpackEventListener
      /* virtual */ void updatePlayerBackpack(CPlayer *pPlayer);

      // IPlayerAttrEventListener
      /* virtual */ void updatePlayerAttr(CPlayer *pPlayer);

   private:
      CPlayer *m_pPlayer;

#ifdef _GAMEENGINE_3D_	
	   CImageButton   *m_vpBtn[BUTTON_COUNT];
      CTextAreaOgre  *m_vpText[TEXT_COUNT];
      COverlayUI      m_overlay;  //管理overlay
#elif _GAMEENGINE_2D_
	   CTextButton    *m_vpBtn[BUTTON_COUNT];
      CTextArea      *m_vpText[TEXT_COUNT];
      CTextArea      *m_vpStackText[BUTTON_COUNT];
#endif
};

#endif  // #ifndef _CBACKPACKWND_H_