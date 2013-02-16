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
#include "IAdvAttrEventListener.h"
#include "IPlayerAttrEventListener.h"
#include "IPlayerEquipEventListener.h"

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CPlayerInfoWnd : public CWindow,
                       public IAdvAttrEventListener,
                       public IPlayerAttrEventListener,
                       public IPlayerEquipEventListener
{
   public:
      enum {BUTTON_MAINHAND, BUTTON_OFFHAND, BUTTON_CHEST, BUTTON_LEGS,
            BUTTON_SHOULDER, BUTTON_GLOVE, BUTTON_BOOT, BUTTON_COUNT};
   
      enum {TEXT_TITLE, TEXT_NAME, TEXT_LEVEL, TEXT_HP, TEXT_MP, TEXT_ATK,
            TEXT_DEF, TEXT_HIT, TEXT_CRI, TEXT_MATK, TEXT_MDEF, TEXT_MHIT,
            TEXT_MCRI, TEXT_SDEF, TEXT_WDEF, TEXT_FLEE, TEXT_MOVE,
            TEXT_ATKSPEED, TEXT_CASTING, TEXT_COUNT};

	   enum {ICON_SIZE = 40};

      CPlayerInfoWnd();
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

      // IAdvAttrEventListener
      /* virtual */ void updateAdvAttr(CUnitObject *pUnitObject);

      // IPlayerAttrEventListener
      /* virtual */ void updatePlayerAttr(CPlayer *pPlayer);

      // IPlayerEquipEventListener
      /* virtual */ void updatePlayerEquip(CPlayer *pPlayer, EquipSlot equipSlot, int itemId);

   private:
	   CPlayer *m_pPlayer;
   	
#ifdef _GAMEENGINE_3D_	
	   CImageButton   *m_vpBtn[BUTTON_COUNT];
      CTextAreaOgre  *m_vpTextName[TEXT_COUNT];
      CTextAreaOgre  *m_vpText[TEXT_COUNT];
      COverlayUI      m_overlay;  //管理overlay
#elif _GAMEENGINE_2D_
	   CTextButton    *m_vpBtn[BUTTON_COUNT];
      CTextArea      *m_vpTextName[TEXT_COUNT];
      CTextArea      *m_vpText[TEXT_COUNT];
#endif
};

#endif  // #ifndef _CPLAYERINFOWND_H_