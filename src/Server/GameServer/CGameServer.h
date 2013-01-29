/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameServer.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/24 */
#ifndef _CGAMESERVER_H_
#define _CGAMESERVER_H_
#include "CScene.h"
/*#include "CNetPlayer.h"
#include "CPacketSceneServerLogin.h"
#include "CPacketPlayerData.h"
#include "CPacketChangeSceneLogin.h"
#include "CPacketPlayerInit.h"*/

#include <network\gp_socket.h>

typedef enum tagSCENESERVER_STATE {
   STATE_WORLDSERVER_LOGIN,  // 對World Server做login
   STATE_SCENESERVER_WORK    // work
} SCENESERVER_STATE;  // 遊戲狀態

class CGameServer : public CScene
{
   public:
      CGameServer();
      ~CGameServer();

      /** @brief 初始化
        * @param port 此台伺服器的listen port */
      void init(int port);

      /** @brief 邏輯更新
        * @param hWnd 主視窗 */
      void work(HWND hWnd);

#ifdef _GAMEENGINE_2D_
      /** @brief 2D繪圖
        * @param hDC 繪圖區 */
      void draw(HDC hdc);
#endif  // #ifdef _GAMEENGINE_2D_

   private:
      /** @brief 處理對WorldServer的Login */
      void workWorldServerLogin();

      /** @brief 處理玩遊戲的邏輯 */
      void workPlay();

      /** @brief 處理與WorldServer之間的網路連線 */
      void procWorldServer();

      /** @brief 處理與Client之間的網路連線 */
      void procAccept();

      /** @brief 處理與Client之間的封包 */
      //void procNetPlayer(CNetPlayer *pNetPlayer);

      /** @brief 接收玩家資料
        * @param pNetStream WorldServer的網路連線
        * @param pPacket    封包 */
      //void onRecvPlayerData(GP::NetStream *pNetStream, CPacketPlayerData *pPacket);

      /** @brief 接收更換場景登入
        * @param pNetStream Client的網路連線
        * @param pPacket    封包 */
      //void onRecvChangeSceneLogin(GP::NetStream *pNetStream, CPacketChangeSceneLogin *pPacket);

      GP::NetListener             m_listener;
      GP::NetStream              *m_pWorldStream;   // World Server的網路連線
      SCENESERVER_STATE           m_gameState;      // 此台伺服器的遊戲狀態
      bool                        m_bSendWSLogin;   // 是否送出login封包給world server
      std::list<GP::NetStream *> *m_pNetStreamList; // 所有的網路連線
      //std::list<CNetPlayer *>    *m_pPlayerList;    // 此場景的所有網路玩家
};

#endif  // #ifndef _CGAMESERVER_H_