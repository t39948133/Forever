/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameClient.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#include "CGameClient.h"
#include "CItem.h"
#include "CSkill.h"

#ifdef _GAMEENGINE_2D_
#include "CPlayerInfoWnd.h"
#include "CBackpackWnd.h"
#include "CSkillWnd.h"
#endif  // #ifdef _GAMEENGINE_2D_

CGameClient::CGameClient()
{
   CItem::initItem();    // 建立物品表
   CSkill::initSkill();  // 建立技能表

   //m_pNetStream = NULL;
   m_pScene = new CScene();

#ifdef _GAMEENGINE_2D_
   m_pWindowMan = new CWindowMan();
   m_mouseMove = false;
   m_keyMove = false;
#endif  // #ifdef _GAMEENGINE_2D_
}

CGameClient::~CGameClient()
{
   //if(m_pNetStream != NULL) {
   //   m_pNetStream->stopConnection();
   //   delete m_pNetStream;
   //   m_pNetStream = NULL;
   //}

   if(m_pScene != NULL) {
      delete m_pScene;
      m_pScene = NULL;
   }

#ifdef _GAMEENGINE_2D_
   if(m_pWindowMan != NULL) {
      delete m_pWindowMan;
      m_pWindowMan = NULL;
   }
#endif  // #ifdef _GAMEENGINE_2D_

   CItem::release();
   CSkill::release();
}

void CGameClient::init()
{
   //m_mainPlayerNetID = -1;
   //m_bSendLogin = false;
   //m_gameState = STATE_LOGIN;

   // 連線到World Server來取得角色資料
   //GP::NetAddress addr;
	//addr.setIPPort("127.0.0.1:2000");
   //m_pNetStream = new GP::NetStream();
	//m_pNetStream->startConnect(addr);

   //單機版用
   CPlayer *pPlayer = m_pScene->addPlayer(1, true);

   initUI();
}

#ifdef _GAMEENGINE_2D_
void CGameClient::work(HWND hWnd)
{
   m_fps.work();
   m_keyMan.work();

   //if(m_gameState == STATE_LOGIN)
   //   workLogin();
   //else if(m_gameState == STATE_CHANGESCENE_LOGIN)
   //   workChangeSceneLogin();
   //else if(m_gameState == STATE_PLAY)
      workPlay(m_fps.getTimePass(), hWnd);
}
#elif _GAMEENGINE_3D_
void CGameClient::work(float timePass, HWND hWnd)
{
   //if(m_gameState == STATE_LOGIN)
   //   workLogin();
   //else if(m_gameState == STATE_CHANGESCENE_LOGIN)
   //   workChangeSceneLogin();
   //else if(m_gameState == STATE_PLAY)
      workPlay(timePass, hWnd);
}
#endif  // #ifdef _GAMEENGINE_2D_ && #elif _GAMEENGINE_3D_

#ifdef _GAMEENGINE_2D_
void CGameClient::draw(HDC hdc)
{
   Rectangle(hdc, 0, 0, 900, 900) ;
   m_pScene->draw(hdc);
   m_pWindowMan->draw(hdc);
}
#endif  // #ifndef _GAMEENGINE_2D_

CScene* CGameClient::getScene()
{
   return m_pScene;
}

void CGameClient::initUI()
{
#ifdef _GAMEENGINE_2D_
   CPlayer *pPlayer = m_pScene->getMainPlayer();

   CPlayerInfoWnd *pPlayerInfoWnd = new CPlayerInfoWnd();
   pPlayerInfoWnd->init(10, 10, pPlayer);
   m_pWindowMan->addWnd(pPlayerInfoWnd);

   CBackpackWnd *pBackpackWnd = new CBackpackWnd();
   pBackpackWnd->init(10, 411, pPlayer);
   m_pWindowMan->addWnd(pBackpackWnd);

   CSkillWnd *pSkillWnd = new CSkillWnd();
   pSkillWnd->init(500, 10, pPlayer);
   m_pWindowMan->addWnd(pSkillWnd);
#endif  // #ifdef _GAMEENGINE_2D_
}

//void CGameClient::workLogin()
//{
//   m_pNetStream->procPackage();
//   if(m_pNetStream->isConnected()) {
//      if(m_bSendLogin == false) {
//         CPacketFirstLogin packetFirstLogin;
//         m_pNetStream->send(&packetFirstLogin, sizeof(packetFirstLogin));
//         m_bSendLogin = true;
//      }
//
//      GP::NetBuffer netBuff;
//      if(m_pNetStream->getFullPackage(netBuff)) {
//         CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
//         if(pPacket->getPacketType() == PACKET_CHANCE_SCENE)
//            onRecvChangeScene(m_pNetStream, (CPacketChangeScene *)pPacket);
//      }
//   }
//}

//void CGameClient::workChangeSceneLogin()
//{
//   m_pNetStream->procPackage();
//   if(m_pNetStream->isConnected()) {
//      if(m_bSendLogin == false) {
//         CPacketChangeSceneLogin packetChangeSceneLogin;
//         packetChangeSceneLogin.pack(m_mainPlayerNetID);
//         m_pNetStream->send(&packetChangeSceneLogin, sizeof(packetChangeSceneLogin));
//         m_bSendLogin = true;
//      }
//
//      GP::NetBuffer netBuff;
//      if(m_pNetStream->getFullPackage(netBuff)) {
//         CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
//         if(pPacket->getPacketType() == PACKET_PLAYER_INIT)
//            onRecvPlayerInit(m_pNetStream, (CPacketPlayerInit *)pPacket);
//      }
//   }
//}

void CGameClient::workPlay(float timePass, HWND hWnd)
{
   m_pScene->work(timePass);

#ifdef _GAMEENGINE_2D_
   doUI(hWnd);
   doKeyControl();
#endif  // #ifdef _GAMEENGINE_2D_

   //m_pNetStream->procPackage();
   //if(m_pNetStream->isConnected()) {
   //   GP::NetBuffer netBuff;
   //   if(m_pNetStream->getFullPackage(netBuff)) {
   //      CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
   //      // Todo: 與Scene Server之間的封包處理
   //   }
   //}
}

//void CGameClient::onRecvChangeScene(GP::NetStream *pNetStream, CPacketChangeScene *pPacket)
//{
//   m_gameState = STATE_CHANGESCENE_LOGIN;
//
//   // 舊資料刪除
//   pNetStream->stopConnection();
//   m_pScene->removeAll();
//
//   // 讀取封包
//   std::string ipAddr;
//   SCENE_TYPE scene;
//   pPacket->unpack(&m_mainPlayerNetID, &ipAddr, &scene);
//
//   m_pScene->loadScene(scene);
//
//   m_bSendLogin = false;
//
//   // 連線到Scene Server
//   GP::NetAddress addr;
//   addr.setIPPort(ipAddr.c_str());
//   pNetStream->startConnect(addr);
//}

//void CGameClient::onRecvPlayerInit(GP::NetStream *pNetStream, CPacketPlayerInit *pPacket)
//{
//   m_gameState = STATE_PLAY;
//
//   CPlayer *pPlayer = m_pScene->addPlayer(-1, true);
//   pPacket->unpack(pPlayer);
//}

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
      if(m_mouseMove == true) {
         CActionEvent actEvent;
         actEvent.m_event = AET_REACH;
         CActionDispatch::getInstance()->sendEvnet(pPlayer->getUID(), actEvent);
         m_mouseMove = false;
      }

      float moveX = pPlayer->getPosition().fX + 1.0f * sin(fmod(fMoveDirection, 2.0f * 3.1415926f));
      float moveY = pPlayer->getPosition().fY + 1.0f * cos(fmod(fMoveDirection, 2.0f * 3.1415926f));
      pPlayer->setTargetPosition(moveX, moveY, false);

      CActionEvent actEvent;
      actEvent.m_event = AET_KEY_WASD;
      actEvent.m_iKeyDownID = 'W';
      CActionDispatch::getInstance()->sendEvnet(pPlayer->getUID(), actEvent);
      m_keyMove = true;
   }
   else {
      if(m_keyMove == true) {
         // 停止移動
         POSITION curPos = pPlayer->getPosition();
         pPlayer->setTargetPosition(curPos.fX, curPos.fY);

         CActionEvent actEvent;
         actEvent.m_event = AET_KEY_WASD;
         actEvent.m_iKeyUpID = 'W';
         CActionDispatch::getInstance()->sendEvnet(pPlayer->getUID(), actEvent);
         m_keyMove = false;
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
         if(pPlayer != NULL) {
            if(m_keyMove == true) {
               POSITION curPos = pPlayer->getPosition();
               pPlayer->setTargetPosition(curPos.fX, curPos.fY);

               CActionEvent actEvent;
               actEvent.m_event = AET_KEY_WASD;
               actEvent.m_iKeyUpID = 'W';
               CActionDispatch::getInstance()->sendEvnet(pPlayer->getUID(), actEvent);
               m_keyMove = false;
            }

            pPlayer->setTargetPosition((float)mx, (float)my, true);

            CActionEvent actEvent;
            actEvent.m_event = AET_NOT_REACH;
            CActionDispatch::getInstance()->sendEvnet(pPlayer->getUID(), actEvent);
            m_mouseMove = true;
         }
      }
   }
   
   if(m_mouseMove == true) {
      if(pPlayer->isReachTarget() == true) {
         CActionEvent actEvent;
         actEvent.m_event = AET_REACH;
         CActionDispatch::getInstance()->sendEvnet(pPlayer->getUID(), actEvent);
         m_mouseMove = false;
      }
   }
}
#endif
// } Add by Darren Chen on 2013/01/03