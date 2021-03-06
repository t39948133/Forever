/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameClient.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#include "CGameClient.h"
#include "CPacketFirstLogin.h"
#include "CPacketCancelUseSkill.h"

#ifdef _GAMESOUND_
#include "CSoundManager.h"
#endif  // #ifdef _GAMESOUND_

#ifdef _GAMEENGINE_2D_
#include "CWASDKeyActionEvent.h"
#include "CPlayerInfoWnd.h"
#include "CBackpackWnd.h"
#include "CSkillWnd.h"
#include "CHotKeyWnd.h"
#include "CPlayerStateWnd.h"
#endif  // #ifdef _GAMEENGINE_2D_

#ifdef _DEBUGLOG
#include "LogWindow.h"
extern CLogWindow glog;
#endif  // #ifdef _DEBUGLOG

CGameClient::CGameClient(std::string machineName)
{
   m_machineName = machineName;
   m_pNetStream = NULL;
   m_pScene = new CScene(m_machineName);

#ifdef _GAMESOUND_
   CSoundManager::getInstance();
#endif  // #ifdef _GAMESOUND_

#ifdef _GAMEENGINE_2D_
   m_pWindowMan = new CWindowMan();
   m_keyMove = false;
#endif  // #ifdef _GAMEENGINE_2D_
}

CGameClient::~CGameClient()
{
   if(m_pNetStream != NULL) {
      m_pNetStream->stopConnection();
      delete m_pNetStream;
      m_pNetStream = NULL;
   }

#ifdef _GAMEENGINE_2D_
   if(m_pWindowMan != NULL) {
      delete m_pWindowMan;
      m_pWindowMan = NULL;
   }
#endif  // #ifdef _GAMEENGINE_2D_

   if(m_pScene != NULL) {
      delete m_pScene;
      m_pScene = NULL;
   }

#ifdef _GAMESOUND_
   CSoundManager::releaseInstance();
#endif  // #ifdef _GAMESOUND_
}

void CGameClient::init()
{
   FILE *pFile; 
   fopen_s(&pFile, "server_ip.txt", "rt");

   if(pFile == NULL)
      return;

   char buf[256];
   memset(buf, 0, sizeof(buf));
   fread(buf, 256, 1, pFile);
   std::string serverIP = buf;

   m_gameState = STATE_LOGIN;
   m_bSendLogin = false;

   // 場景產生一個主角, 但此主角資料沒有內容
   m_pScene->addPlayer(-1, true);

   // 連線到Game Server來取得角色資料
   GP::NetAddress addr;
   addr.setIPPort(serverIP.c_str());
   m_pNetStream = new GP::NetStream();
	m_pNetStream->startConnect(addr);

   initUI();
}

std::string CGameClient::getMachineName()
{
   return m_machineName;
}

#ifdef _GAMEENGINE_2D_
void CGameClient::work(HWND hWnd, float timePass, bool bActive)
{
   if(bActive == true) {
      m_keyMan.work();
#ifdef _GAMESOUND_
      CSoundManager::getInstance()->work();
#endif  // #ifdef _GAMESOUND_
   }

   if(m_gameState == STATE_LOGIN)
      workLogin();
   else if(m_gameState == STATE_CHANGE_LOGIN)
      ; //workChangeLogin();
   else if(m_gameState == STATE_PLAY)
      workPlay(hWnd, timePass);
}
#elif _GAMEENGINE_3D_
void CGameClient::work(HWND hWnd, float timePass)
{
   if(m_gameState == STATE_LOGIN)
      workLogin();
   else if(m_gameState == STATE_CHANGE_LOGIN)
      ; //workChangeLogin();
   else if(m_gameState == STATE_PLAY)
      workPlay(hWnd, timePass);
}
#endif  // #ifdef _GAMEENGINE_2D_ && #elif _GAMEENGINE_3D_

#ifdef _GAMEENGINE_2D_
void CGameClient::draw(HDC hdc)
{
   m_pScene->draw(hdc);
   m_pWindowMan->draw(hdc);
}
#endif  // #ifndef _GAMEENGINE_2D_

CScene* CGameClient::getScene()
{
   return m_pScene;
}

GP::NetStream* CGameClient::getNetStream()
{
   return m_pNetStream;
}

void CGameClient::initUI()
{
#ifdef _GAMEENGINE_2D_
   CPlayer *pPlayer = m_pScene->getMainPlayer();

   CPlayerInfoWnd *pPlayerInfoWnd = new CPlayerInfoWnd();
   pPlayerInfoWnd->init(10, 10, pPlayer, m_pNetStream);
   m_pWindowMan->addWnd(pPlayerInfoWnd);

   CBackpackWnd *pBackpackWnd = new CBackpackWnd();
   pBackpackWnd->init(10, 411, pPlayer, m_pNetStream);
   m_pWindowMan->addWnd(pBackpackWnd);

   CSkillWnd *pSkillWnd = new CSkillWnd();
   pSkillWnd->init(500, 10, pPlayer);
   m_pWindowMan->addWnd(pSkillWnd);

   CHotKeyWnd *pHotKeyWnd = new CHotKeyWnd();
   pHotKeyWnd->init(250, 860, pPlayer, m_pNetStream);
   m_pWindowMan->addWnd(pHotKeyWnd);

   m_pTargetInfoWnd = new CTargetInfoWnd();
   m_pTargetInfoWnd->init(300, 0, m_pScene, pPlayer, m_pNetStream);
   m_pWindowMan->addWnd(m_pTargetInfoWnd);

   CPlayerStateWnd *pPlayerStateWnd = new CPlayerStateWnd();
   pPlayerStateWnd->init(20, 900 - 78, pPlayer);
   m_pWindowMan->addWnd(pPlayerStateWnd);
#endif  // #ifdef _GAMEENGINE_2D_
}

void CGameClient::onRecvPlayerInit(CPacketPlayerInit *pPacket)
{
   CPlayer *pPlayer = m_pScene->getMainPlayer();
   pPacket->unpack(pPlayer);
}

void CGameClient::onRecvPlayerData(CPacketPlayerData *pPacket)
{
   CPlayer *pPlayer = m_pScene->getPlayer(pPacket->getUID());
   if(pPlayer == NULL)
      pPlayer = m_pScene->addPlayer(pPacket->getUID());

   pPacket->unpack(pPlayer);
}

void CGameClient::onRecvMonsterData(CPacketMonsterData *pPacket)
{
   CMonster *pMonster = m_pScene->getMonster(pPacket->getUID());
   if(pMonster == NULL)
      pMonster = m_pScene->addMonster(-1, pPacket->getKindID(), 0, 0);

   pPacket->unpack(pMonster);
}

void CGameClient::onRecvEquipData(CPacketEquipData *pPacket)
{
   CPlayer *pPlayer = m_pScene->getPlayer(pPacket->getUID());
   if(pPlayer != NULL)
      pPacket->unpack(pPlayer);
}

void CGameClient::onRecvDead(CPacketDead *pPacket)
{
   CPlayer *pPlayer = m_pScene->getPlayer(pPacket->getUID());
   if(pPlayer != NULL) {
      // 出現載入畫面, 等待Server傳送玩家資料 (2D不做事情)
   }
   else
      m_pScene->removeMonster(pPacket->getUID());
}

void CGameClient::onRecvPlayerDeadReset(CPacketPlayerDeadReset *pPacket)
{
   CPlayer *pPlayer = m_pScene->getPlayer(pPacket->getUID());
   if(pPlayer != NULL) {
      pPacket->unpack(pPlayer);

#ifdef _GAMEENGINE_2D_
      m_pTargetInfoWnd->setTarget(pPacket->getTargetUID());
#endif

      pPlayer->resetDead();   // 玩家復活
   }
}

void CGameClient::onRecvNPCData(CPacketNPCData *pPacket)
{
	CNPC *pNPC = m_pScene->getNPC(pPacket->getUID());
	if(pNPC == NULL)
		pNPC = m_pScene->addNPC(-1, pPacket->getKindID(), 0, 0);

	pPacket->unpack(pNPC);
}

void CGameClient::workLogin()
{
   m_pNetStream->procPackage();

   if(m_pNetStream->isConnected()) {
      if(m_bSendLogin == false) {
         CPacketFirstLogin packetFirstLogin;
         m_pNetStream->send(&packetFirstLogin, sizeof(packetFirstLogin));

         m_bSendLogin = true;
      }

      GP::NetBuffer netBuff;
      if(m_pNetStream->getFullPackage(netBuff)) {
         CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
         if(pPacket->m_id == PACKET_PLAYER_INIT) {
            m_gameState = STATE_PLAY;
            onRecvPlayerInit((CPacketPlayerInit *)pPacket);
         }
      }
   }
}

void CGameClient::workPlay(HWND hWnd, float timePass)
{
   m_pScene->work(timePass);

#ifdef _GAMEENGINE_2D_
   doUI(hWnd);
   doKeyControl();
#endif  // #ifdef _GAMEENGINE_2D_

   m_pNetStream->procPackage();
   if(m_pNetStream->isConnected()) {
      GP::NetBuffer netBuff;
      while(m_pNetStream->getFullPackage(netBuff)) {
         CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
         if(pPacket->m_id == PACKET_PLAYER_DATA)
            onRecvPlayerData((CPacketPlayerData *)pPacket);
         else if(pPacket->m_id == PACKET_TARGET_POS)
            onRecvTargetPos((CPacketTargetPos *)pPacket);
         else if(pPacket->m_id == PACKET_MONSTER_DATA)
            onRecvMonsterData((CPacketMonsterData *)pPacket);
         else if(pPacket->m_id == PACKET_TARGET_OBJECT)
            onRecvTargetObject((CPacketTargetObject *)pPacket);
         else if(pPacket->m_id == PACKET_ACTION_EVENT)
            onRecvActionEvent((CPacketActionEvent *)pPacket);
         else if(pPacket->m_id == PACKET_USE_SKILL)
            onRecvUseSkill((CPacketUseSkill *)pPacket);
         else if(pPacket->m_id == PACKET_BACKPACK_DATA)
            onRecvBackpackData((CPacketBackpackData *)pPacket);
         else if(pPacket->m_id == PACKET_EQUIP_DATA)
            onRecvEquipData((CPacketEquipData *)pPacket);
         else if(pPacket->m_id == PACKET_ADVATTR_DATA)
            onRecvAdvAttrData((CPacketAdvAttrData *)pPacket);
         else if(pPacket->m_id == PACKET_ADD_SKILL)
            onRecvAddSkill((CPacketAddSkill *)pPacket);
         else if(pPacket->m_id == PACKET_CAN_USE_SKILL)
            onRecvCanUseSkill((CPacketCanUseSkill *)pPacket);
         else if(pPacket->m_id == PACKET_DEAD)
            onRecvDead((CPacketDead *)pPacket);
         else if(pPacket->m_id == PACKET_PLAYER_DEAD_RESET)
            onRecvPlayerDeadReset((CPacketPlayerDeadReset *)pPacket);
         else if(pPacket->m_id == PACKET_NPC_DATA)
	         onRecvNPCData((CPacketNPCData *)pPacket);
         else if(pPacket->m_id == PACKET_MONEY)
            onRecvMoney((CPacketMoney *)pPacket);
         else if(pPacket->m_id == PACKET_XP)
            onRecvXP((CPacketXP *)pPacket);
         else if(pPacket->m_id == PACKET_CANCEL_USESKILL)
            onRecvCancelUseSkill((CPacketCancelUseSkill *)pPacket);
         else if(pPacket->m_id == PACKET_KEY_ACTION_EVENT)
            onRecvKeyActionEvent((CPacketKeyActionEvent *)pPacket);
      }
   }
}

void CGameClient::onRecvTargetPos(CPacketTargetPos *pPacket)
{
   CUnitObject *pUnitObject = m_pScene->getUnitObject(pPacket->getUID());
   if(pUnitObject != NULL)
      pPacket->unpack(pUnitObject);
}

void CGameClient::onRecvTargetObject(CPacketTargetObject *pPacket)
{
   CUnitObject *pUnitObject = m_pScene->getUnitObject(pPacket->getUID());
   if(pUnitObject != NULL) {
      CUnitObject *pNewTargetObject = m_pScene->getUnitObject(pPacket->getTargetUID());
      pUnitObject->setTargetObject(pNewTargetObject);
   }
}

void CGameClient::onRecvActionEvent(CPacketActionEvent *pPacket)
{
   CUnitObject *pUnitObject = m_pScene->getUnitObject(pPacket->getUID());
   if(pUnitObject != NULL)
      pPacket->unpack(pUnitObject);
}

void CGameClient::onRecvUseSkill(CPacketUseSkill *pPacket)
{
   CUnitObject *pUnitObject = m_pScene->getUnitObject(pPacket->getUID());
   if(pUnitObject != NULL)
      pPacket->unpack(pUnitObject);
}

void CGameClient::onRecvBackpackData(CPacketBackpackData *pPacket)
{
   CPlayer *pPlayer = m_pScene->getPlayer(pPacket->getUID());
   if(pPlayer != NULL)
      pPacket->unpack(pPlayer);
}

void CGameClient::onRecvAdvAttrData(CPacketAdvAttrData *pPacket)
{
   CUnitObject *pUnitObject = m_pScene->getUnitObject(pPacket->getUID());
   if(pUnitObject != NULL)
      pPacket->unpack(pUnitObject);
}

void CGameClient::onRecvAddSkill(CPacketAddSkill *pPacket)
{
   CPlayer *pPlayer = m_pScene->getPlayer(pPacket->getUID());
   if(pPlayer != NULL)
      pPacket->unpack(pPlayer);
}

void CGameClient::onRecvCanUseSkill(CPacketCanUseSkill *pPacket)
{
   CPlayer *pPlayer = m_pScene->getPlayer(pPacket->getUID());
   if(pPlayer != NULL) {
      if(pPacket->canUseSkill() == true)
         pPlayer->startCastSkill(pPacket->getUseSkillID());
   }
}

void CGameClient::onRecvMoney(CPacketMoney *pPacket)
{
   CPlayer *pPlayer = m_pScene->getMainPlayer();
   if(pPlayer->getUID() != pPacket->m_uid)
      return;

   pPlayer->addMoney(pPacket->m_offsetMoney);
}

void CGameClient::onRecvXP(CPacketXP *pPacket)
{
   CPlayer *pPlayer = m_pScene->getMainPlayer();
   if(pPlayer->getUID() != pPacket->m_uid)
      return;

   pPlayer->addXP(pPacket->m_offsetXP);
}

void CGameClient::onRecvCancelUseSkill(CPacketCancelUseSkill *pPacket)
{
   CPlayer *pPlayer = m_pScene->getPlayer(pPacket->getUID());
   if(pPlayer != NULL)
      pPacket->unpack(pPlayer);
}

void CGameClient::onRecvKeyActionEvent(CPacketKeyActionEvent *pPacket)
{
   CUnitObject *pUnitObject = m_pScene->getUnitObject(pPacket->getUID());
   if(pUnitObject != NULL)
      pPacket->unpack(pUnitObject);
}

// Add by Darren Chen on 2013/01/03 {
#ifdef _GAMEENGINE_2D_
void CGameClient::doKeyControl()
{
   CPlayer *pPlayer = m_pScene->getMainPlayer();
   if(pPlayer == NULL)
      return;

   bool bKeyMove = false;
   float fMoveDirection = pPlayer->getDirection();  // 移動方向
   if(m_keyMan.isDown(KEY_W) == true) {
      bKeyMove = true;
   }
   else if(m_keyMan.isDown(KEY_S) == true) {
      bKeyMove = true;
      fMoveDirection -= 3.1415926f;
   }
   else if(m_keyMan.isDown(KEY_A) == true) {
      bKeyMove = true;
      fMoveDirection += (3.1415926f / 2.0f);
   }
   else if(m_keyMan.isDown(KEY_D) == true) {
      bKeyMove = true;
      fMoveDirection -= (3.1415926f / 2.0f);
   }

   if(bKeyMove == true) {
      if(pPlayer->isCastSkill() == true) {
         pPlayer->cancelCastSkill();

         CPacketCancelUseSkill packet;
         packet.pack(pPlayer);
         m_pNetStream->send(&packet, sizeof(packet));
      }

      float moveX = pPlayer->getPosition().fX + 1.0f * sin(fmod(fMoveDirection, 2.0f * 3.1415926f));
      float moveY = pPlayer->getPosition().fY + 1.0f * cos(fmod(fMoveDirection, 2.0f * 3.1415926f));
      pPlayer->setTargetPosition(moveX, moveY, false);

      CWASDKeyActionEvent actEvent;
      actEvent.m_event = AET_KEY_WASD;
      actEvent.m_iKeyDownID = 'W';
      CActionDispatch::getInstance()->sendEvnet(m_machineName, pPlayer->getUID(), actEvent);
      m_keyMove = true;

      CPacketTargetPos packet;
      packet.pack(pPlayer, false);
      m_pNetStream->send(&packet, sizeof(packet));
   }
   else {
      if(m_keyMove == true) {
         // 停止移動
         FPOS curPos = pPlayer->getPosition();
         pPlayer->setTargetPosition(curPos.fX, curPos.fY);

         CWASDKeyActionEvent actEvent;
         actEvent.m_event = AET_KEY_WASD;
         actEvent.m_iKeyUpID = 'W';
         CActionDispatch::getInstance()->sendEvnet(m_machineName, pPlayer->getUID(), actEvent);
         m_keyMove = false;

         CPacketTargetPos packet;
         packet.pack(pPlayer, false);
         m_pNetStream->send(&packet, sizeof(packet));
      }
   }
}

void CGameClient::doUI(HWND hWnd)
{
   bool bPressWindow = m_pWindowMan->work(hWnd, m_keyMan);

   CPlayer *pPlayer = m_pScene->getMainPlayer();

   if(m_keyMan.isPress(KEY_LBUTTON)) {
      int mx, my;
      getMousePos(hWnd, mx, my);
      
      if(bPressWindow == true) {
         // 點到介面
      }
      else {
         CUnitObject *pUnitObject = m_pScene->getUnitObject((float)mx, (float)my);
         if(pUnitObject != NULL) {
            m_pTargetInfoWnd->setTarget(pUnitObject->getUID());
         }
         else {
            m_pTargetInfoWnd->setTarget(-1);

            if(pPlayer != NULL) {
               if(m_keyMove == true) {
                  FPOS curPos = pPlayer->getPosition();
                  pPlayer->setTargetPosition(curPos.fX, curPos.fY);

                  CWASDKeyActionEvent actEvent;
                  actEvent.m_event = AET_KEY_WASD;
                  actEvent.m_iKeyUpID = 'W';
                  CActionDispatch::getInstance()->sendEvnet(m_machineName, pPlayer->getUID(), actEvent);
                  m_keyMove = false;

                  CPacketTargetPos packet1;
                  packet1.pack(pPlayer, false);
                  m_pNetStream->send(&packet1, sizeof(packet1));
               }

               if(pPlayer->isCastSkill() == true) {
                  pPlayer->cancelCastSkill();
                  
                  CPacketCancelUseSkill packet2;
                  packet2.pack(pPlayer);
                  m_pNetStream->send(&packet2, sizeof(packet2));
               }

               pPlayer->setTargetPosition((float)mx, (float)my, true);

               CActionEvent actEvent;
               actEvent.m_event = AET_NOT_REACH;
               CActionDispatch::getInstance()->sendEvnet(m_machineName, pPlayer->getUID(), actEvent);

               CPacketTargetPos packet3;
               packet3.pack(pPlayer, true);
               m_pNetStream->send(&packet3, sizeof(packet3));
            }
         }
      }
   }
}
#endif
// } Add by Darren Chen on 2013/01/03