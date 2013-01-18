/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPlayerInfoWnd.h
  * @author 林有良
  * @date   2012/12/21
  * @version
  *         2013/01/05 Darren Chen - 整合與修正 */
#ifndef _CPLAYERINFOWND_H_
#define _CPLAYERINFOWND_H_
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

class CPlayerInfoWnd : public CWindow,
                       public IModelEventListener
{
   public:
	   enum {BUTTON_SPAULDER, BUTTON_GLOVE, BUTTON_WEAPON, BUTTON_CLOTHES,
	   BUTTON_PANTS, BUTTON_SHIELD, BUTTON_SHOES, BUTTON_UI_NAME, BUTTON_PLAYER_NAME, 
	   BUTTON_LEVEL_EXP, BUTTON_ATTRIBUTE, BUTTON_PLAYER_IMAGE, BUTTON_COUNT};

	   enum {CELL_SIZE = 20, TEXT_COUNT = 21};

	   ~CPlayerInfoWnd();

	   void init(int _x, int _y, CPlayer *pPlr);

      // CWindow
	   /* virtual */ bool canDrag(int tx, int ty);
	   /* virtual */ void onRCommand(int btnID);
      /* virtual */ WindowClassType getClassType();
      /* virtual */ void show(bool bShow);
      /* virtual */ void onDrag();
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
	   CImageButton   *m_vpBtn[BUTTON_COUNT];
      CTextAreaOgre  *m_vpText[TEXT_COUNT];
      COverlayUI      m_overlay;  //管理overlay
#elif _GAMEENGINE_2D_
	   CTextButton    *m_vpBtn[BUTTON_COUNT];
      CTextArea      *m_vpText[TEXT_COUNT];
#endif
};

#endif  // #ifndef _CPLAYERINFOWND_H_