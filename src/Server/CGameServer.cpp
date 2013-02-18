/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameServer.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/24 */
#include "CGameServer.h"
#include "CSkill.h"
#include "CPacketPasswordGW.h"
#include "CPacketPlayerInit.h"
#include "CPacketPlayerData.h"
#include "CPacketMonsterData.h"
#include "CPacketTargetObject.h"
#include "CPacketActionEvent.h"
#include "CPacketUseSkill.h"

#ifdef _DEBUGLOG
#include "LogWindow.h"
extern CLogWindow glog;
#endif  // #ifdef _DEBUG

const int idelRandRange = 500;

CGameServer::CGameServer(std::string machineName) : CScene(machineName)
{
   m_machineName = machineName;
   m_pWorldStream = new GP::NetStream();
   m_pNetPlayerList = new std::list<CNetPlayer *>();
   srand((unsigned int)time(NULL));
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
   CScene::addSceneMonsterEventListener(this);

   m_port = port;
   m_curUID = 3000;  // 要避開World Server給的UID, 這裡的m_curUID只有怪物用的到
   m_curNetID = 0;
   m_listener.startListen(port);

   GP::NetAddress addr;
   addr.setIPPort("127.0.0.1:2000");
   m_pWorldStream->startConnect(addr);

   if(m_port == 2200) {  // 第一個場景
      // 產生怪物
      for(int i = 0; i < MONSTERAREA_INFO::getInfoCount(); i++) {
         CMonsterArea *pMonsterArea = m_monsterMap.addArea();
         pMonsterArea->create(i);
      }

      // Todo: 產生NPC
   }
}

void CGameServer::work(HWND hWnd, float timePass)
{
   CScene::work(timePass);

   procWorldServer();
   procAccept();
   
   m_monsterMap.work(this, this);

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
   m_monsterMap.draw(hdc);
   CScene::draw(hdc);
}
#endif  // #ifdef _GAMEENGINE_2D_

void CGameServer::updateAddMonster(CMonster *pMonster)
{
   CPacketMonsterData packet;
   packet.pack(pMonster);
   sendPacket(NULL, &packet, sizeof(packet));  // 送給所有玩家
}

void CGameServer::updateMonsterTargetObject(CMonster *pMonster, long long newTargetObjectUID)
{
   CUnitObject *pNewTargetObject = this->getUnitObject(newTargetObjectUID);
   pMonster->setTargetObject(pNewTargetObject);

   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      CPacketTargetObject packet;
      packet.pack(pMonster);
      (*it)->m_pNetStream->send(&packet, sizeof(packet));
      it++;
   }
}

void CGameServer::updateMonsterAI(CMonster *pMonster)
{
   CMonsterInfo* pMonsterInfo = pMonster->getInfo();
   if(pMonsterInfo == NULL)
      return;

   if(pMonster->getState() == IDLE)
      doMonsterAIIdle(pMonster);
   else if(pMonster->getState() == GOALS)
      doMonsterAIGoals(pMonster);
   else if(pMonster->getState() == DOLLY)
      doMonsterAIDolly(pMonster);
   else if(pMonster->getState() == RETURN)  //回歸原位 檢查到了沒 到了開始idle
      doMonsterAIReturn(pMonster);
   else if(pMonster->getState() == ATTACK)
      doMonsterAIAttack(pMonster);
}

void CGameServer::doMonsterAIIdle(CMonster *pMonster)
{
   CMonsterInfo* pMonsterInfo = pMonster->getInfo();
   if(pMonsterInfo == NULL)
      return;

   if(pMonsterInfo->getATKtype() == MONSTER_ACTIVE) {
      std::list<CPlayer*>* playerList = this->getAllPlayer();
      std::list<CPlayer*>::iterator it = playerList->begin();
      float distance = pMonsterInfo->getAlert();
      long long playerID = -1;
      while(it != playerList->end()) {
         float dis = getDistance(pMonster->getPosition().fX, pMonster->getPosition().fY,
                                 (*it)->getPosition().fX, (*it)->getPosition().fY);
         if(dis < pMonsterInfo->getAlert()) {
            if(dis < distance) {
               distance = dis;
               playerID = (*it)->getUID();
            }
         }
         it++;
      }

      if(playerID > -1) {
         pMonster->addHate(playerID, 0);
         return;
      }
   }

   if(pMonster->isReachTarget()) {
      int pass = rand() % idelRandRange;
      if(pass == 3) {
         float range = pMonsterInfo->getAlert();
         int fx = (rand() % (int) (range * 2)) - (int) (range);
         int fy = (rand() % (int) (range * 2)) - (int) (range);
         float ftx = pMonster->getBornPosition().fX + fx;
         float fty = pMonster->getBornPosition().fY + fy;
         moveMonster(pMonster, ftx, fty);
      }
   }
}

void CGameServer::doMonsterAIGoals(CMonster *pMonster)
{
   CUnitObject* pUnitObject = pMonster->getTargetObject();
   if(pUnitObject == NULL)
      return;

   float fx = pUnitObject->getPosition().fX;
   float fy = pUnitObject->getPosition().fY;
   moveMonster(pMonster, fx, fy);

   pMonster->setState(DOLLY);
}

void CGameServer::doMonsterAIDolly(CMonster *pMonster)
{
   CMonsterInfo* pMonsterInfo = pMonster->getInfo();
   if(pMonsterInfo == NULL)
      return;

   CUnitObject* pUnitObject = pMonster->getTargetObject();
   if(pUnitObject == NULL)
      return;

   float fx = pUnitObject->getPosition().fX;
   float fy = pUnitObject->getPosition().fY;
   moveMonster(pMonster, fx, fy);

   //目標物離開太遠怪物回歸
   if(pMonster->isMonsterTargetTooFarAway() == true) {
      moveMonster(pMonster, pMonster->getAnchorPosition().fX, pMonster->getAnchorPosition().fY);
      return;
   }

	float distance = getDistance(pMonster->getPosition().fX, pMonster->getPosition().fY, fx, fy);

   //取得怪物普通攻擊技能
   std::vector<int> vMonsterSkillID = pMonsterInfo->getSkill();
   std::vector<int>::iterator itSkillID = vMonsterSkillID.begin();
   CSkill *pSkill = pMonster->getSkill((*itSkillID));
   
   if(distance < pSkill->getInfo()->getCastRange()) {
      CActionEvent actEvent;
      actEvent.m_event = AET_REACH;
      CActionDispatch::getInstance()->sendEvnet(pMonster->getMachineName(), pMonster->getUID(), actEvent);

      CPacketActionEvent packet;
      packet.pack(pMonster, &actEvent);
      sendPacket(NULL, &packet, sizeof(packet));  // 送給所有玩家

      pMonster->setState(ATTACK);
   }
}

void CGameServer::doMonsterAIReturn(CMonster *pMonster)
{
   CMonsterInfo* pMonsterInfo = pMonster->getInfo();
   if(pMonsterInfo == NULL)
      return;

   pMonster->setAdvAttr(pMonsterInfo->getAdvAttr());
   // Todo: 要處理怪物HP,MP封包

   if(pMonster->isReachTarget())
      pMonster->setState(IDLE);
}

void CGameServer::doMonsterAIAttack(CMonster *pMonster)
{
   CMonsterInfo* pMonsterInfo = pMonster->getInfo();
   if(pMonsterInfo == NULL)
      return;

   std::vector<CSkill*> vSkill = pMonster->getSkill();
   float castRange = -1.0f;
   switch(pMonsterInfo->getWistom()) {
      case 1: {  // 只使用普通攻擊
         std::vector<CSkill *>::iterator itSkill = vSkill.begin();
         if(itSkill != vSkill.end()) {
            castRange = (*itSkill)->getInfo()->getCastRange();

            if((*itSkill)->isReady()) {
               CPacketUseSkill packet;
               packet.pack(pMonster, (*itSkill)->getID());
               sendPacket(NULL, &packet, sizeof(packet));  // 送給所有玩家

               pMonster->startCastSkill((*itSkill)->getID());
            }
         }
         break;
      }

      case 2:  
      case 3: {
         int skillIdx = 1;
         if(vSkill.size() > 2)
            skillIdx = rand() % vSkill.size();

         if(skillIdx < (int)vSkill.size()) {
            CSkill *pSkill = vSkill.at(skillIdx);
            castRange = pSkill->getInfo()->getCastRange();

            if(pSkill->isReady()) {
               CPacketUseSkill packet;
               packet.pack(pMonster, pSkill->getID());
               sendPacket(NULL, &packet, sizeof(packet));  // 送給所有玩家

               pMonster->startCastSkill(pSkill->getID());
            }
            else {
               // 改用普通攻擊
               pSkill = vSkill.at(0);
               castRange = pSkill->getInfo()->getCastRange();

               if(pSkill->isReady()) {
                  CPacketUseSkill packet;
                  packet.pack(pMonster, pSkill->getID());
                  sendPacket(NULL, &packet, sizeof(packet));  // 送給所有玩家

                  pMonster->startCastSkill(pSkill->getID());
               }
            }
         }
         break;
      }
   }

   float fx = pMonster->getTargetObject()->getPosition().fX;
   float fy = pMonster->getTargetObject()->getPosition().fY;
   float distance = getDistance(pMonster->getPosition().fX, pMonster->getPosition().fY, fx, fy);

   if(distance > castRange) {
      pMonster->setState(GOALS);
      return;
   }
}

void CGameServer::moveMonster(CMonster *pMonster, float x, float y)
{
#ifdef _GAMEENGINE_3D_
   pMonster->setTargetPosition(x, y);
#elif _GAMEENGINE_2D_
   pMonster->setTargetPosition(x, y, true);
#endif

   CPacketTargetPos packet;
#ifdef _GAMEENGINE_3D_
   packet.pack(pMonster);
#elif _GAMEENGINE_2D_
   packet.pack(pMonster, true);
#endif
   sendPacket(NULL, &packet, sizeof(packet));  // 送給所有玩家

	CActionEvent actEvent;
	actEvent.m_event = AET_NOT_REACH;
	CActionDispatch::getInstance()->sendEvnet(m_machineName, pMonster->getUID(), actEvent);
}

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
   while(m_pWorldStream->getFullPackage(netBuff)) {
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
         while(pNetPlayer->m_pNetStream->getFullPackage(netBuff)) {
            CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
            if(pPacket->m_id == PACKET_FIRST_LOGIN)
               onRecvFirstLogin(pNetPlayer, (CPacketFirstLogin *)pPacket);
         }
      }
      else if(pNetPlayer->m_state == CNetPlayer::STATE_PLAY) {
         while(pNetPlayer->m_pNetStream->getFullPackage(netBuff)) {
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

void CGameServer::sendNearMonsterToClient(CNetPlayer *pNetPlayer)
{
   std::list<CMonster *> *pMonsterList = this->getAllMonster();
   std::list<CMonster *>::iterator it = pMonsterList->begin();
   while(it != pMonsterList->end()) {
      CPacketMonsterData packet;
      packet.pack((*it));
      pNetPlayer->m_pNetStream->send(&packet, sizeof(packet));

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

   // 送怪的資料給client
	sendNearMonsterToClient(pNetPlayer);

   // Todo: 還沒處理完畢
}

void CGameServer::onRecvTargetPos(CNetPlayer *pNetPlayer, CPacketTargetPos *pPacket)
{
   pPacket->unpack(pNetPlayer->m_pPlayer);
   sendPacket(pNetPlayer, pPacket, sizeof(*pPacket));
}