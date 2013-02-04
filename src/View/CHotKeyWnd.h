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
#include "IPlayerHotKeyEventListener.h"
#include "IItemEventListener.h"
#include "ISkillEventListener.h"

#ifdef _GAMEENGINE_3D_
#include "CHotKeyButton.h"
#include "COverlayUI.h"
#include "IKeyEventListener.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CHotKeyWnd : public CWindow,
                   public IPlayerHotKeyEventListener,
                   public IItemEventListener,
#ifdef _GAMEENGINE_3D_
                   public IKeyEventListener,
#endif
                   public ISkillEventListener

                   
{
   public:
#ifdef _GAMEENGINE_3D_
      enum {BUTTON_COUNT = 10, ICON_SIZE = 40};
#elif _GAMEENGINE_2D_
      enum {BUTTON_COUNT = 10, CELL_SIZE = 40, TEXT_COUNT = 20};
#endif

      CHotKeyWnd();
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

      // IPlayerHotKeyEventListener
      /* virtual */ void updatePlayerHotKey(HotKeyItem *pHotKeyItem);

      // IItemEventListener
      /* virtual */ void updateItemData(CItem *pItem);

      // ISkillEventListener
      /* virtual */ void updateSkill(CUnitObject *pUnitObject);
      /* virtual */ void updateSkillCoolDown(CSkill *pSkill);

#ifdef _GAMEENGINE_3D_
      // IKeyEventListener
      /* virtual */ void keyDown(const OIS::KeyEvent &evt);
      /* virtual */ void keyUp(const OIS::KeyEvent &evt);
#endif

   private:
	   CPlayer *m_pPlayer;
      std::map<void *, int> m_table;
   	
#ifdef _GAMEENGINE_3D_	
	   CHotKeyButton  *m_vpBtn[BUTTON_COUNT];
      COverlayUI      m_overlay;  //管理overlay
      bool            m_bvCoolDown[BUTTON_COUNT];
#elif _GAMEENGINE_2D_
	   CTextButton    *m_vpBtn[BUTTON_COUNT];
      CTextArea      *m_vpText[TEXT_COUNT];
#endif
};

#endif  // #ifndef _CHOTKEYWND_H_