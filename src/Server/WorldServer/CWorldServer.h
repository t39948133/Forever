/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWorldServer.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/24 */
#ifndef _CWORLDSERVER_H_
#define _CWORLDSERVER_H_
#include "Common.h"
/*#include "CNetPlayer.h"
#include "CPacketOK.h"
#include "CPacketSceneServerLogin.h"
#include "CPacketFirstLogin.h"
#include "CPacketPlayerData.h"
#include "CPacketChangeScene.h"*/

#include <network\gp_socket.h>

class CWorldServer
{
   public:
      CWorldServer();
      ~CWorldServer();

      /** @brief 初始化
        * @param port port number */
      void init(int port);

      /** @brief 邏輯更新
        * @param hWnd window視窗 */
      void work(HWND hWnd);

   private:
      /** @brief 處理Client端連線
        *        這裡的Client會有兩種, 一種是玩家的Client, 一種是SceneServer */
      void procAccept();

      /** @brief 處理SceneServer的連線 */
      void procSceneServer();

      /** @brief SceneServer登入時的封包處理
        * @param pNetStream SceneServer的網路連線
        * @param pPacket    封包 */
      //void onRecvSceneServerLogin(GP::NetStream *pNetStream, CPacketSceneServerLogin *pPacket);

      /** @brief Client登入時的封包處理
        * @param pNetStream Client的網路連線
        * @param pPacket    封包 */
      //void onRecvFirstLogin(GP::NetStream *pNetStream, CPacketFirstLogin *pPacket);

      GP::NetListener             m_listener;
      long long                   m_curUID;           // 目前的UID
      long long                   m_curNetID;         // 目前的網路ID 唯一編號
      std::list<GP::NetStream *> *m_pNetStreamList;   // 所有的網路連線
      std::list<GP::NetStream *> *m_pSceneStreamList; // 所有場景伺服器的網路連線
      //std::list<CNetPlayer *>    *m_pPlayerList;      // 所有玩家
      std::map<SCENE_TYPE, GP::NetStream *> *m_pSceneTable;  // 場景對照表
};

#endif  // #ifndef _CWORLDSERVER_H_