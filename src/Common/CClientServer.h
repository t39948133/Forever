/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CClientServer.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/07 */
#ifndef _CCLIENTSERVER_H_
#define _CCLIENTSERVER_H_
#include "CGameServer.h"
#include "CWorldServer.h"

#ifdef _GAMEENGINE_3D_
#include "CGraphicsRender.h"
#include "CRenderLoader.h"
#include "CGameClient3D.h"
#elif _GAMEENGINE_2D_
#include "CGameClient.h"
#include "CFPS.h"
#endif

#ifdef _GAMEENGINE_3D_
class CClientServer : public IGameFlowListener
#elif _GAMEENGINE_2D_
class CClientServer
#endif
{
   public:
      CClientServer();
      ~CClientServer();

#ifdef _GAMEENGINE_3D_
      void run();
#elif _GAMEENGINE_2D_
      void init();
      void work(HWND hWnd);
      void draw(HDC hdc);
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

   private:
#ifdef _GAMEENGINE_3D_
      // IGameFlowListener
      /* virtual */ void createScene();
      /* virtual */ bool frameRenderingQueued(float timeSinceLastFrame);
      /* virtual */ void destoryScene();
#endif

      bool m_bShowClient;
      int  m_curClient;
      int  m_curServer;

      enum {MAX_SERVER = 1};
      std::vector<CGameServer *>    m_gameServer;

      enum {MAX_WORLDSERVER = 1};
      std::vector<CWorldServer *>   m_worldServer;

#ifdef _GAMEENGINE_3D_
      enum {MAX_CLIENT = 1};
      std::vector<CGameClient3D *>  m_gameClient;

      CGraphicsRender              *m_pRenderCore;    // 繪圖引擎
#elif _GAMEENGINE_2D_
      enum {MAX_CLIENT = 2};
      std::vector<CGameClient *>    m_gameClient;

      CFPS                          m_fps;            // FPS產生器
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_
};

#endif  // #ifndef _CCLIENTSERVER_H_