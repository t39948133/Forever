/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameServer.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/24 */
#include "CGameServer.h"
#include "CPacketPasswordGW.h"
#include "CPacketPlayerInit.h"
#include "CPacketPlayerData.h"

#ifdef _DEBUGLOG
#include "LogWindow.h"
extern CLogWindow glog;
#endif  // #ifdef _DEBUG

CGameServer::CGameServer(std::string machineName) : CScene(machineName)
{
   m_machineName = machineName;
   m_pWorldStream = new GP::NetStream();
   m_pNetPlayerList = new std::list<CNetPlayer *>();
}

CGameServer::~CGameServer()
{
   if(m_pWorldStream != NULL) {
      m_pWorldStream->stopConnection();
      delete m_pWorldStream;
      m_pWorldStream = NULL;
   }

   std::list<CNetPlayer *>::iterator itNetPlayer = m_pNetPlayerList->begin();
   while(itNetPlayer != m_pNetPlayerList->end()) {
      delete (*itNetPlayer);
      itNetPlayer++;
   }
   m_pNetPlayerList->clear();
   delete m_pNetPlayerList;
   m_pNetPlayerList = NULL;
}

void CGameServer::init(int port)
{
   m_curUID = 3000;  // 要避開World Server給的UID, 這裡的m_curUID只有怪物用的到
   m_curNetID = 0;
   m_listener.startListen(port);

   GP::NetAddress addr;
   addr.setIPPort("127.0.0.1:2000");
   m_pWorldStream->startConnect(addr);

   if(port == 2200) {  // 第一個場景
      // 產生怪物
      //for(int i = 0; i < 4; i++)
      //   this->addMonster(m_curUID++, 0, float(300 + i * 50), (float)300);
	   m_MonsterArea.create(0);
      
      // Todo: 產生NPC
   }
}

void CGameServer::work(HWND hWnd, float timePass)
{
   CScene::work(timePass);

   procWorldServer();
   procAccept();
   
   // Todo: 種怪物物件.work()
   m_MonsterArea.work(*this, *this);

   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      procNetPlayer((*it));  // 收client的封包

      if((*it)->m_pNetStream->isConnected() == false) {  // 網路斷線
         if((*it)->m_pPlayer != NULL)
            this->removePlayer((*it)->m_pPlayer->getUID());
         it = m_pNetPlayerList->erase(it);
      }
      else
         it++;
   }
}

long long CGameServer::generateUID()
{
	return m_curUID++;
}

#ifdef _GAMEENGINE_2D_
void CGameServer::draw(HDC hdc)
{
   CScene::draw(hdc);
}
#endif  // #ifdef _GAMEENGINE_2D_

void CGameServer::procAccept()
{
   if(m_listener.isAccepted()) {
      CNetPlayer *pNetPlayer = new CNetPlayer();
      pNetPlayer->m_state = CNetPlayer::STATE_WAIT_LOGIN_DATA;
      pNetPlayer->m_netID = m_curNetID++;
      m_pNetPlayerList->push_back(pNetPlayer);

      m_listener.transferAcceptStream(*(pNetPlayer->m_pNetStream));
   }
}

void CGameServer::procWorldServer()
{
   m_pWorldStream->procPackage();
   GP::NetBuffer netBuff;
   if(m_pWorldStream->getFullPackage(netBuff)) {
      CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
      if(pPacket->m_id == PACKET_PLAYER_DATA_WG)
         onRecvPlayerDataWG((CPacketPlayerDataWG *)pPacket);
   }
}

void CGameServer::procNetPlayer(CNetPlayer *pNetPlayer)
{
   pNetPlayer->m_pNetStream->procPackage();

   if(pNetPlayer->m_pNetStream->isConnected() == true) {
      GP::NetBuffer netBuff;
      if(pNetPlayer->m_state == CNetPlayer::STATE_WAIT_LOGIN_DATA) {
         if(pNetPlayer->m_pNetStream->getFullPackage(netBuff)) {
            CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
            if(pPacket->m_id == PACKET_FIRST_LOGIN)
               onRecvFirstLogin(pNetPlayer, (CPacketFirstLogin *)pPacket);
         }
      }
      else if(pNetPlayer->m_state == CNetPlayer::STATE_PLAY) {
         if(pNetPlayer->m_pNetStream->getFullPackage(netBuff)) {
            CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
            if(pPacket->m_id == PACKET_TARGET_POS)
               onRecvTargetPos(pNetPlayer, (CPacketTargetPos *)pPacket);
         }
      }
   }
}

CNetPlayer* CGameServer::getNetPlayer(long long netID)
{
   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      if((*it)->m_netID == netID)
         return (*it);

      it++;
   }

   return NULL;
}

void CGameServer::sendPlayerDataToOtherClient(CNetPlayer *pNetPlayer)
{
   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      if((*it) != pNetPlayer) {
         CPacketPlayerData packet;
         packet.pack(pNetPlayer->m_pPlayer);
         (*it)->m_pNetStream->send(&packet, sizeof(packet));
      }

      it++;
   }
}

void CGameServer::sendNearPlayerToClient(CNetPlayer *pNetPlayer)
{
   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      if((*it)->m_state == CNetPlayer::STATE_PLAY) {
         if((*it) != pNetPlayer) {
            CPacketPlayerData packet;
            packet.pack((*it)->m_pPlayer);
            pNetPlayer->m_pNetStream->send(&packet, sizeof(packet));
         }
      }

      it++;
   }
}

void CGameServer::sendPacket(CNetPlayer *pNetPlayer, void *pPacket, int packetSize)
{
   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      if((*it) != pNetPlayer)
         (*it)->m_pNetStream->send(pPacket, packetSize);
      it++;
   }
}

void CGameServer::onRecvFirstLogin(CNetPlayer *pNetPlayer, CPacketFirstLogin *pPacket)
{
   CPacketPasswordGW packetPasswordGW;
   packetPasswordGW.m_netID = pNetPlayer->m_netID;
   pNetPlayer->m_state = CNetPlayer::STATE_WAIT_PLAYER_DATA;
   m_pWorldStream->send(&packetPasswordGW, sizeof(packetPasswordGW));
}

void CGameServer::onRecvPlayerDataWG(CPacketPlayerDataWG *pPacket)
{
   // 產生一個玩家 (資料未定)
   CPlayer *pNewPlayer = CScene::addPlayer(pPacket->m_uid);
   pPacket->unpack(pNewPlayer);  // 取得封包內的玩家資料
   
   CNetPlayer *pNetPlayer = getNetPlayer(pPacket->m_netID);
   pNetPlayer->m_pPlayer = pNewPlayer;
   pNetPlayer->m_state = CNetPlayer::STATE_PLAY;

   // 送資料給Client
   CPacketPlayerInit packetPlayerInit;
   packetPlayerInit.pack(pNewPlayer);
   pNetPlayer->m_pNetStream->send(&packetPlayerInit, sizeof(packetPlayerInit));

   // 送自己的資料給其他client
   sendPlayerDataToOtherClient(pNetPlayer);

   // 送其他玩家的資料給自己
   sendNearPlayerToClient(pNetPlayer);

   // Todo: 還沒處理完畢
}

void CGameServer::onRecvTargetPos(CNetPlayer *pNetPlayer, CPacketTargetPos *pPacket)
{
   pPacket->unpack(pNetPlayer->m_pPlayer);
   sendPacket(pNetPlayer, pPacket, sizeof(*pPacket));
}