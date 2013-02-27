#include "CClientServer.h"
#include "CItem.h"
#include "CSkill.h"
#include "CBuff.h"
#include "CMonster.h"
#include "CMonsterArea.h"
#include "CNPC.h"
#include "CQuest.h"

#include <network\gp_socket.h>

CClientServer::CClientServer()
{
   for(int i = 0; i < MAX_WORLDSERVER; i++) {
      std::string machineName = std::string("CWorldServer::") + toString<int>(i);
      CWorldServer *pWorldServer = new CWorldServer(machineName);
      m_worldServer.push_back(pWorldServer);
   }

   for(int i = 0; i < MAX_SERVER; i++) {
      std::string machineName = std::string("CGameServer::") + toString<int>(i);
      CGameServer *pGameServer = new CGameServer(machineName);
      m_gameServer.push_back(pGameServer);
   }

#ifdef _GAMEENGINE_3D_
   m_pRenderCore = CRenderLoader::getInstance()->getGraphicsRender("RenderEngine::OGRE");
   if(m_pRenderCore != NULL)
      m_pRenderCore->addGameFlowListener(this);

   m_bShowClient = true;
   GP::NetStream::fnInitShareData(NULL);

   CBuff::initBuff();       // 建立Buff表
   CItem::initItem();       // 建立物品表
   CSkill::initSkill();     // 建立技能表
   CMonster::initMonster(); // 建立怪物表
   CMonsterArea::initMonsterArea();
	CNPC::initNPC();
	CQuest::initQuest();

   for(int i = 0; i < MAX_WORLDSERVER; i++)
      m_worldServer.at(i)->init(2000 + i);

   for(int i = 0; i < MAX_SERVER; i++)
      m_gameServer.at(i)->init(2200 + i);
   
   m_curClient = 0;
   m_curServer = 0;

   for(int i = 0; i < MAX_CLIENT; i++) {
      std::string machineName = std::string("CGameClient3D::") + toString<int>(i);
      CGameClient3D *pGameClient = new CGameClient3D(machineName);
      m_gameClient.push_back(pGameClient);
   }
#elif _GAMEENGINE_2D_
   for(int i = 0; i < MAX_CLIENT; i++) {
      std::string machineName = std::string("CGameClient::") + toString<int>(i);
      CGameClient *pGameClient = new CGameClient(machineName);
      m_gameClient.push_back(pGameClient);
   }
#endif
}

CClientServer::~CClientServer()
{
#ifdef _GAMEENGINE_3D_
   std::vector<CGameClient3D *>::iterator itGameClient = m_gameClient.begin();
   while(itGameClient != m_gameClient.end()) {
      delete (*itGameClient);
      ++itGameClient;
   }
   m_gameClient.clear();

   m_pRenderCore = NULL;
   CRenderLoader::releaseInstance();
#elif _GAMEENGINE_2D_
   std::vector<CGameClient *>::iterator itGameClient = m_gameClient.begin();
   while(itGameClient != m_gameClient.end()) {
      delete (*itGameClient);
      ++itGameClient;
   }
   m_gameClient.clear();
#endif

   std::vector<CGameServer *>::iterator itGameServer = m_gameServer.begin();
   while(itGameServer != m_gameServer.end()) {
      delete (*itGameServer);
      ++itGameServer;
   }
   m_gameServer.clear();

   std::vector<CWorldServer *>::iterator itWorldServer = m_worldServer.begin();
   while(itWorldServer != m_worldServer.end()) {
      delete (*itWorldServer);
      ++itWorldServer;
   }
   m_worldServer.clear();

   CMonster::release();
   CSkill::release();
   CItem::release();
   CBuff::release();
	CMonsterArea::release();
	CNPC::release();
	CQuest::release();
}

#ifdef _GAMEENGINE_3D_
void CClientServer::run()
{
   m_pRenderCore->run();
}
#elif _GAMEENGINE_2D_
void CClientServer::init()
{
   if(MAX_CLIENT > 0)
      m_bShowClient = true;
   else
      m_bShowClient = false;

   GP::NetStream::fnInitShareData(NULL);

   CBuff::initBuff();
   CItem::initItem();    // 建立物品表
   CSkill::initSkill();  // 建立技能表
   CMonster::initMonster(); //建立怪物表
   CMonsterArea::initMonsterArea();
	CNPC::initNPC();
	CQuest::initQuest();

   for(int i = 0; i < MAX_WORLDSERVER; i++)
      m_worldServer.at(i)->init(2000 + i);

   for(int i = 0; i < MAX_SERVER; i++)
      m_gameServer.at(i)->init(2200 + i);
   
   m_curClient = 0;
   m_curServer = 0;

   for(int i = 0; i < MAX_CLIENT; i++)
      m_gameClient.at(i)->init();
}

void CClientServer::work(HWND hWnd)
{
   m_fps.work();

   std::vector<CWorldServer *>::iterator itWorldServer = m_worldServer.begin();
   while(itWorldServer != m_worldServer.end()) {
      (*itWorldServer)->work(hWnd, m_fps.getTimePass());
      itWorldServer++;
   }

   std::vector<CGameServer *>::iterator itGameServer = m_gameServer.begin();
   while(itGameServer != m_gameServer.end()) {
      (*itGameServer)->work(hWnd, m_fps.getTimePass());
      itGameServer++;
   }

   if(GetAsyncKeyState(VK_F1) < 0) {
		m_bShowClient = true;
		m_curClient = 0;
	}
   else if(GetAsyncKeyState(VK_F2) < 0) {
		m_bShowClient = true;
		m_curClient = 1;
	}
   else if(GetAsyncKeyState(VK_F3) < 0) {
		m_bShowClient = true;
		m_curClient = 2;
	}
	else if(GetAsyncKeyState(VK_F4) < 0) {
		m_bShowClient = false;
		m_curServer = 0;
	}
	else if(GetAsyncKeyState(VK_F5) < 0) {
      if(MAX_SERVER > 1) {
		   m_bShowClient = false;
		   m_curServer = 1;
      }
	}

   for(int i = 0; i < MAX_CLIENT; i++) {
		if(i == m_curClient)
         m_gameClient.at(i)->work(hWnd, m_fps.getTimePass(), true);
		else
			m_gameClient.at(i)->work(hWnd, m_fps.getTimePass(), false);
	}
}

void CClientServer::draw(HDC hdc)
{
   Rectangle(hdc, 0, 0, 900, 900);

   if(m_bShowClient) {
      m_gameClient.at(m_curClient)->draw(hdc);

		char buf[256];
      memset(buf, 0, sizeof(buf));
		sprintf_s(buf, sizeof(buf), "Client_%d", m_curClient);
      TextOut(hdc, 3, 3, buf, strlen(buf));
	}
   else {
      m_gameServer.at(m_curServer)->draw(hdc);

		char buf[256];
      memset(buf, 0, sizeof(buf));
		sprintf_s(buf, sizeof(buf), "Server_%d", m_curServer);
		TextOut(hdc, 3, 3, buf, strlen(buf));
	}
}
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

#ifdef _GAMEENGINE_3D_
void CClientServer::createScene()
{
}

bool CClientServer::frameRenderingQueued(float timeSinceLastFrame)
{
   if(MAX_WORLDSERVER > 0) {
      std::vector<CWorldServer *>::iterator itWorldServer = m_worldServer.begin();
      while(itWorldServer != m_worldServer.end()) {
         (*itWorldServer)->work(m_pRenderCore->getRenderHwnd(), timeSinceLastFrame);
         ++itWorldServer;
      }
   }

   if(MAX_SERVER > 0) {
      std::vector<CGameServer *>::iterator itGameServer = m_gameServer.begin();
      while(itGameServer != m_gameServer.end()) {
         (*itGameServer)->work(m_pRenderCore->getRenderHwnd(), timeSinceLastFrame);
         ++itGameServer;
      }
   }

   return true;
}

void CClientServer::destoryScene()
{
}
#endif  // #ifdef _GAMEENGINE_3D_