/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CTargetInfoWnd.h
  * @author 林有良
  * @date   2012/12/21
  * @version
  *         2013/01/14 Darren Chen - 整合與修正 */
#ifndef _CTARGETINFOWND_H_
#define _CTARGETINFOWND_H_
#include "CWindow.h"
#include "CScene.h"
#include "IModelEventListener.h"

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CTargetInfoWnd : public CWindow,
                       public IModelEventListener
{
   public:
      void init(int _x, int _y, CScene *pScene, CPlayer *pPlayer);

      // CWindow
	   /* virtual */ bool canDrag(int tx, int ty);
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

      void setTarget(long long uid);
      CUnitObject* getTarget();

   private:
      CScene    *m_pScene;
      CPlayer   *m_pPlayer;
      long long  m_targetUID;

#ifdef _GAMEENGINE_3D_	
	   CImageButton   *m_pBtn;
      CTextAreaOgre  *m_pText;
      COverlayUI      m_overlay;  //管理overlay
#elif _GAMEENGINE_2D_
	   CTextButton    *m_pBtn;
      CTextArea      *m_pText;
#endif
};

#endif  // #ifndef _CTARGETINFOWND_H_