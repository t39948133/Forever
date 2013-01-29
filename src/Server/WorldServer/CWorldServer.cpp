/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWorldServer.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/24 */
#include "CWorldServer.h"
#include "LogWindow.h"
extern CLogWindow glog;

CWorldServer::CWorldServer()
{
   //m_pPlayerList = new std::list<CNetPlayer *>();
   m_pNetStreamList = new std::list<GP::NetStream *>();
   m_pSceneStreamList = new std::list<GP::NetStream *>();
   m_pSceneTable = new std::map<SCENE_TYPE, GP::NetStream *>();
}

CWorldServer::~CWorldServer()
{
   /*std::list<CNetPlayer *>::iterator itPlayer = m_pPlayerList->begin();
   while(itPlayer != m_pPlayerList->end()) {
      delete (*itPlayer);
      itPlayer++;
   }
   m_pPlayerList->clear();
   delete m_pPlayerList;
   m_pPlayerList = NULL;*/

   std::list<GP::NetStream *>::iterator itNet = m_pNetStreamList->begin();
   while(itNet != m_pNetStreamList->end()) {
      (*itNet)->stopConnection();
      delete (*itNet);
      itNet++;
   }
   m_pNetStreamList->clear();
   delete m_pNetStreamList;
   m_pNetStreamList = NULL;

   std::list<GP::NetStream *>::iterator itScene = m_pSceneStreamList->begin();
   while(itScene != m_pSceneStreamList->end()) {
      (*itScene)->stopConnection();
      delete (*itScene);
      itScene++;
   }
   m_pSceneStreamList->clear();
   delete m_pSceneStreamList;
   m_pSceneStreamList = NULL;

   std::map<SCENE_TYPE, GP::NetStream *>::iterator itTable = m_pSceneTable->begin();
   while(itTable != m_pSceneTable->end()) {
      itTable->second->stopConnection();
      delete itTable->second;
      itTable++;
   }
   m_pSceneTable->clear();
   delete m_pSceneTable;
   m_pSceneTable = NULL;
}

void CWorldServer::init(int port)
{
   m_curUID = 0;
   m_curNetID = 0;
   m_listener.startListen(port);

   glog("%s [WS] : Init. listen port = %d", getCurDateTime().c_str(), port);
   glog("%s [WS] : Server is ready.", getCurDateTime().c_str());
}

void CWorldServer::work(HWND hWnd)
{
   procAccept();
   procSceneServer();
}

void CWorldServer::procAccept()
{
   if(m_listener.isAccepted()) {
      GP::NetStream *pNetStream = new GP::NetStream();
      
      m_listener.transferAcceptStream(*pNetStream);
      m_pNetStreamList->push_back(pNetStream);
   }

   std::list<GP::NetStream *>::iterator it = m_pNetStreamList->begin();
   while(it != m_pNetStreamList->end()) {
      (*it)->procPackage();

      if((*it)->isConnected()) {
         GP::NetBuffer netBuff;
         if((*it)->getFullPackage(netBuff)) {
            /*CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
            if(pPacket->getPacketType() == PACKET_SCENESERVER_LOGIN) {
               // Scene Server login
               onRecvSceneServerLogin((*it), (CPacketSceneServerLogin *)pPacket);
               m_pNetStreamList->erase(it);
               break;
            }
            else if(pPacket->getPacketType() == PACKET_FIRST_LOGIN) {
               // Client login
               onRecvFirstLogin((*it), (CPacketFirstLogin *)pPacket);
            }*/
         }
      }

      it++;
   }
}

void CWorldServer::procSceneServer()
{
   std::list<GP::NetStream *>::iterator it = m_pSceneStreamList->begin();
   while(it != m_pSceneStreamList->end()) {
      (*it)->procPackage();

      if((*it)->isConnected()) {
         GP::NetBuffer netBuff;
         if((*it)->getFullPackage(netBuff)) {
            //CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
            // Todo: 未完成
         }
      }

      it++;
   }
}

/*void CWorldServer::onRecvSceneServerLogin(GP::NetStream *pNetStream, CPacketSceneServerLogin *pPacket)
{
   if(pNetStream->isConnected()) {
      // 把Scene Server的網路連線註冊於Scene Table中
      std::map<SCENE_TYPE, GP::NetStream *>::iterator it = m_pSceneTable->find(pPacket->getScene());
      if(it != m_pSceneTable->end()) {
         it->second->stopConnection();
         delete it->second;
         it->second = pNetStream;
      }
      else
         m_pSceneTable->insert(std::make_pair(pPacket->getScene(), pNetStream));

      // 把Scene Server的網路連線獨立於另一個list中(方便管理)
      m_pSceneStreamList->push_back(pNetStream);

      if(pPacket->getScene() == SCENE_POETA)
         log("%s [WS] [Recv 0x%X] : 接收CPacketSceneServerLogin封包. 波伊塔場景伺服器登入", getCurDateTime().c_str(), pNetStream);

      // 回傳OK訊息給Scene Server
      CPacketOK packetOK;
      pNetStream->send(&packetOK, sizeof(packetOK));
      log("%s [WS] [Send 0x%X] : 場景伺服器註冊完畢, 發送CPacketOK封包", getCurDateTime().c_str(), pNetStream);
   }
}*/

/*void CWorldServer::onRecvFirstLogin(GP::NetStream *pNetStream, CPacketFirstLogin *pPacket)
{
   if(pNetStream->isConnected()) {
      // 產生玩家資料

      log("%s [WS] [Recv 0x%X] : 接收CPacketFirstLogin封包", getCurDateTime().c_str(), pNetStream);

      static int id = 0;
      char name[256];
      sprintf_s(name, sizeof(name), "玩家_%d", id++);
      CPlayer *pNewPlayer = new CPlayer(name, m_curUID++);
      pNewPlayer->setPosition(0, 0);
      pNewPlayer->setTargetPosition(0, 0);
      //pNewPlayer->setAdvAttr(); 要設定,暫時不細寫

      NETPLAYER_DATA netPlayerData;
      netPlayerData.netID         = m_curNetID++;
      //netPlayerData.playerState   = STATE_WAIT_LOGIN_DATA;
      netPlayerData.pClientStream = (*m_pSceneTable)[SCENE_POETA];  // 玩家出生場景(波伊塔)
      netPlayerData.pPlayer       = pNewPlayer;

      CNetPlayer *pNetPlayer = new CNetPlayer();
      pNetPlayer->init(netPlayerData);
      m_pPlayerList->push_back(pNetPlayer);

      log("%s [WS] : 產生玩家資料", getCurDateTime().c_str());

      // 玩家資料送給Scene Server
      CPacketPlayerData packetPlayerData;
      packetPlayerData.pack(pNetPlayer->getNetID(), pNetPlayer->getPlayer());
      pNetPlayer->getClientStream()->send(&packetPlayerData, sizeof(packetPlayerData));
      log("%s [WS] [Send 0x%X] : 發送CPacketPlayerData封包給場景伺服器", getCurDateTime().c_str(), pNetPlayer->getClientStream());

      // 告知Client端更換Scene
      CPacketChangeScene packetChangeScene;
      packetChangeScene.pack(pNetPlayer->getNetID(), "127.0.0.1:2200", SCENE_POETA);
      pNetStream->send(&packetChangeScene, sizeof(packetChangeScene));
      log("%s [WS] [Send 0x%X] : 發送CPacketChangeScene封包給Client", getCurDateTime().c_str(), pNetStream);
   }
}*/