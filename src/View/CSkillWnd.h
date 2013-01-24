/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CSkillWnd.h
  * @author 林有良
  * @date   2012/12/21
  * @version
  *         2013/01/05 Darren Chen - 整合與修正 */
#ifndef _CSKILLWND_H_
#define _CSKILLWND_H_
#include "CWindow.h"
#include "CPlayer.h"
#include "ISkillEventListener.h"

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CSkillWnd : public CWindow,
                  public ISkillEventListener
{
   public:
	   enum {BUTTON_COUNT = 7, CELL_SIZE = 60, TEXT_COUNT = 7} ;
   	 
	   ~CSkillWnd();

	   void init(int _x, int _y, CPlayer *pb);

	   // CWindow
	   /* virtual */ bool canDrag(int tx, int ty);
      /* virtual */ void onLCommand(int btnID);
      /* virtual */ WindowClassType getClassType();
      /* virtual */ void show(bool bShow);
      /* virtual */ void onDrag();
#ifdef _GAMEENGINE_3D_
	   void setZOrder(int order);
#endif

      // ISkillEventListener
      /* virtual */ void updateSkill(CUnitObject *pUnitObject);
      /* virtual */ void updateSkillCoolDown(CSkill *pSkill);

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

#endif  // #ifndef _CSKILLWND_H_