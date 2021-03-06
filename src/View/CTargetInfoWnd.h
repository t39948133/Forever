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
#include "IAdvAttrEventListener.h"

#include <network\gp_socket.h>

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CTargetInfoWnd : public CWindow,
                       public IAdvAttrEventListener
{
   public:
#ifdef _GAMEENGINE_3D_
      enum {BUTTON_AI, BUTTON_HP, BUTTON_COUNT};
      enum {TEXT_LEVEL, TEXT_NAME, TEXT_COUNT};
#endif
      CTargetInfoWnd();
      ~CTargetInfoWnd();

      void init(int _x, int _y, CScene *pScene, CPlayer *pPlayer, GP::NetStream *pNetStream);

      // CWindow
	   /* virtual */ bool canDrag(int tx, int ty);
      /* virtual */ WindowClassType getClassType();
      /* virtual */ void show(bool bShow);

      // IAdvAttrEventListener
      /* virtual */ void updateAdvAttr(CUnitObject *pUnitObject);

      void setTarget(long long uid);
      CUnitObject* getTarget();
      long long getTargetUID();

   private:
      CScene        *m_pScene;
      CPlayer       *m_pPlayer;
      long long      m_targetUID;
      GP::NetStream *m_pNetStream;      // 對Game Server的網路連線

#ifdef _GAMEENGINE_3D_	
	   CImageButton   *m_pBtn[BUTTON_COUNT];
      CTextAreaOgre  *m_pText[TEXT_COUNT];
      COverlayUI      m_overlay;  //管理overlay
#elif _GAMEENGINE_2D_
	   CTextButton    *m_pBtn;
      CTextArea      *m_pText;
#endif
};

#endif  // #ifndef _CTARGETINFOWND_H_