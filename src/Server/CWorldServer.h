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
#include "CPlayerServerID.h"
#include "CPacketPasswordGW.h"

#include <network\gp_socket.h>

class CWorldServer
{
   public:
      CWorldServer(std::string machineName);
      ~CWorldServer();

      /** @brief 初始化 */
      void init(int port);

      /** @brief 邏輯更新
        * @param hWnd window視窗
        * @param timePass 一個frame幾秒 */
      void work(HWND hWnd, float timePass);

   private:
      CPlayerServerID* addPlayerServerID(GP::NetStream *pNetStream);

      /** @brief 處理GameServer的封包 
        * @param pNetStream GameServer的網路連線 */
      void procGameServer(GP::NetStream *pNetStream);

      void onRecvPasswordGW(GP::NetStream *pNetStream, CPacketPasswordGW *pPacket);

      std::string                    m_machineName;     // 機器名稱 (用來識別是不同機器, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      std::vector<std::string>       m_nameVector;       // 玩家名稱列表
      GP::NetListener                m_listener;
      long long                      m_curUID;           // 目前的UID
      std::list<GP::NetStream *>    *m_pNetStreamList;   // 與GameServer網路連線
      std::list<CPlayerServerID *>  *m_pPlayerList;      // 所有玩家
};

#endif  // #ifndef _CWORLDSERVER_H_