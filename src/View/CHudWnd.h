/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CHudWnd.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/03 */
#ifndef _CHUDWND_H_
#define _CHUDWND_H_
#ifdef _GAMEENGINE_3D_
#include "CWindow.h"
#include "CPlayer.h"
#include "COverlayUI.h"
#include "CHotKeyWnd.h"

class CHudWnd : public CWindow
{
   public:
      CHudWnd();

      void init(int _x, int _y, CPlayer *pPlayer);

      // CWindow
	   /* virtual */ bool canDrag(int tx, int ty);
      /* virtual */ WindowClassType getClassType();
      /* virtual */ void show(bool bShow);
      /* virtual */ void setZOrder(int order);

   private:
      CPlayer    *m_pPlayer;
      COverlayUI  m_overlay;  //ºÞ²zoverlay
};

#endif  // #ifdef _GAMEENGINE_3D_
#endif  // #ifndef _CHUDWND_H_