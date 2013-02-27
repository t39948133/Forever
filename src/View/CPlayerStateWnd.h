/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPlayerStateWnd.h
  * @author 林有良
  * @date   2012/12/21
  * @version
  *         2013/01/16 Darren Chen - 整合與修正 */
#ifndef _CPLAYERSTATEWND_H_
#define _CPLAYERSTATEWND_H_
#include "CWindow.h"
#include "CPlayer.h"
#include "IAdvAttrEventListener.h"
#include "IPlayerAttrEventListener.h"

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CPlayerStateWnd : public CWindow,
                        public IAdvAttrEventListener,
                        public IPlayerAttrEventListener
{
   public:
#ifdef _GAMEENGINE_3D_
      enum {BUTTON_HP, BUTTON_MP, BUTTON_XP, BUTTON_COUNT};
      enum {TEXT_HP, TEXT_MP, TEXT_XP, TEXT_HP_VALUE, TEXT_MP_VALUE, TEXT_XP_VALUE, TEXT_LV_VALUE, TEXT_COUNT};
#elif _GAMEENGINE_2D_
      enum {BUTTON_COUNT = 3, CELL_SIZE = 20, TEXT_COUNT = 3};
#endif

      CPlayerStateWnd();
      ~CPlayerStateWnd();

#ifdef _GAMEENGINE_3D_
      void init(int _x, int _y, CPlayer *pPlr, int zOrder);
#elif _GAMEENGINE_2D_
      void init(int _x, int _y, CPlayer *pPlr);
#endif

      // CWindow
	   /* virtual */ bool canDrag(int tx, int ty);
      /* virtual */ WindowClassType getClassType();
      /* virtual */ void show(bool bShow);

      // IAdvAttrEventListener
      /* virtual */ void updateAdvAttr(CUnitObject *pUnitObject);

      // IPlayerAttrEventListener
      /* virtual */ void updatePlayerAttr(CPlayer *pPlayer, unsigned int offsetXP, long long offsetMoney);

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

#endif  // #ifndef _CPLAYERSTATEWND_H_