/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CHotKeyWnd.h
  * @author 林有良
  * @date   2012/12/21
  * @version
  *         2013/01/12 Darren Chen - 整合與修正 */
#ifndef _CHOTKEYWND_H_
#define _CHOTKEYWND_H_
#include "CWindow.h"
#include "CPlayer.h"
#include "IModelEventListener.h"

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CHotKeyWnd : public CWindow,
                   public IModelEventListener
{
   public:
      enum {BUTTON_COUNT = 10, CELL_SIZE = 40, TEXT_COUNT = 20};

      ~CHotKeyWnd();

      void init(int _x, int _y, CPlayer *pPlr);

      // CWindow
	   /* virtual */ bool canDrag(int tx, int ty);
      /* virtual */ void onLCommand(int btnID);
      /* virtual */ void onRCommand(int btnID);
      /* virtual */ WindowClassType getClassType();
      /* virtual */ void show(bool bShow);
#ifdef _GAMEENGINE_3D_
	   /* virtual */ void setZOrder(int order);
#endif

      // IModelEventListener
      /* virtual */ void updateAdvAttr(CUnitObject *pUnitObject);
      /* virtual */ void updateBackpack(CUnitObject *pUnitObject);
      /* virtual */ void updateSkill(CUnitObject *pUnitObject);
      /* virtual */ void updateHotKeyItem(int field, HotKeyItem *pHotKeyItem);
      /* virtual */ void updateCoolDown(CSkill *pSkill);

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

#endif  // #ifndef _CHOTKEYWND_H_