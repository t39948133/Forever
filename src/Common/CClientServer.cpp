#include "CClientServer.h"
#include "CItem.h"
#include "CSkill.h"
#include "CBuff.h"
#include "CMonster.h"

#include <network\gp_socket.h>

CClientServer::CClientServer()
{
   m_pvWorldServer = new std::vector<CWorldServer *>();
   for(int i = 0; i < MAX_WORLDSERVER; i++) {
      std::string machineName = std::string("CWorldServer::") + toString<int>(i);
      CWorldServer *pWorldServer = new CWorldServer(machineName);
      m_pvWorldServer->push_back(pWorldServer);
   }

   m_pvGameServer = new std::vector<CGameServer *>();
   for(int i = 0; i < MAX_SERVER; i++) {
      std::string machineName = std::string("CGameServer::") + toString<int>(i);
      CGameServer *pGameServer = new CGameServer(machineName);
      m_pvGameServer->push_back(pGameServer);
   }

#ifdef _GAMEENGINE_3D_
   m_pRenderCore = CRenderLoader::getInstance()->getGraphicsRender("RenderEngine::OGRE");
   if(m_pRenderCore != NULL)
      m_pRenderCore->addGameFlowListener(this);

   m_pvGameClient = new std::vector<CGameClient3D *>();
   for(int i = 0; i < MAX_CLIENT; i++) {
      std::string machineName = std::string("CGameClient3D::") + toString<int>(i);
      CGameClient3D *pGameClient = new CGameClient3D(machineName);
      m_pvGameClient->push_back(pGameClient);
   }
#elif _GAMEENGINE_2D_
   m_pvGameClient = new std::vector<CGameClient *>();
   for(int i = 0; i < MAX_CLIENT; i++) {
      std::string machineName = std::string("CGameClient::") + toString<int>(i);
      CGameClient *pGameClient = new CGameClient(machineName);
      m_pvGameClient->push_back(pGameClient);
   }
#endif
}

CClientServer::~CClientServer()
{
#ifdef _GAMEENGINE_3D_
   if(m_pvGameClient != NULL) {
      std::vector<CGameClient3D *>::iterator it = m_pvGameClient->begin();
      while(it != m_pvGameClient->end()) {
         delete (*it);
         it++;
      }
      m_pvGameClient->clear();
      delete m_pvGameClient;
      m_pvGameClient = NULL;
   }

   m_pRenderCore = NULL;
   CRenderLoader::releaseInstance();
#elif _GAMEENGINE_2D_
   if(m_pvGameClient != NULL) {
      std::vector<CGameClient *>::iterator it = m_pvGameClient->begin();
      while(it != m_pvGameClient->end()) {
         delete (*it);
         it++;
      }
      m_pvGameClient->clear();
      delete m_pvGameClient;
      m_pvGameClient = NULL;
   }
#endif

   if(m_pvGameServer != NULL) {
      std::vector<CGameServer *>::iterator it = m_pvGameServer->begin();
      while(it != m_pvGameServer->end()) {
         delete (*it);
         it++;
      }
      m_pvGameServer->clear();
      delete m_pvGameServer;
      m_pvGameServer = NULL;
   }

   if(m_pvWorldServer != NULL) {
      std::vector<CWorldServer *>::iterator it = m_pvWorldServer->begin();
      while(it != m_pvWorldServer->end()) {
         delete (*it);
         it++;
      }
      m_pvWorldServer->clear();
      delete m_pvWorldServer;
      m_pvWorldServer = NULL;
   }

   CItem::release();
   CSkill::release();
   CBuff::release();
   CMonster::release();
}

#ifdef _GAMEENGINE_3D_
void CClientServer::run()
{
   m_pRenderCore->run();
}
#elif _GAMEENGINE_2D_
void CClientServer::init()
{
   m_bShowClient = true;
   GP::NetStream::fnInitShareData(NULL);

   CItem::initItem();    // 建立物品表
   CSkill::initSkill();  // 建立技能表
   CBuff::initBuff();
   CMonster::initMonster(); //建立怪物表

   for(int i = 0; i < MAX_WORLDSERVER; i++)
      m_pvWorldServer->at(i)->init(2000 + i);

   for(int i = 0; i < MAX_SERVER; i++)
      m_pvGameServer->at(i)->init(2200 + i);
   
   m_curClient = 0;
   m_curServer = 0;

   for(int i = 0; i < MAX_CLIENT; i++)
      m_pvGameClient->at(i)->init();
}

void CClientServer::work(HWND hWnd)
{
   m_fps.work();

   std::vector<CWorldServer *>::iterator itWorldServer = m_pvWorldServer->begin();
   while(itWorldServer != m_pvWorldServer->end()) {
      (*itWorldServer)->work(hWnd, m_fps.getTimePass());
      itWorldServer++;
   }

   std::vector<CGameServer *>::iterator itGameServer = m_pvGameServer->begin();
   while(itGameServer != m_pvGameServer->end()) {
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
		m_bShowClient = false;
		m_curServer = 1;
	}

   for(int i = 0; i < MAX_CLIENT; i++) {
		if(i == m_curClient)
         m_pvGameClient->at(i)->work(hWnd, m_fps.getTimePass(), true);
		else
			m_pvGameClient->at(i)->work(hWnd, m_fps.getTimePass(), false);
	}
}

void CClientServer::draw(HDC hdc)
{
   Rectangle(hdc, 0, 0, 900, 900);

   if(m_bShowClient) {
      m_pvGameClient->at(m_curClient)->draw(hdc);

		char buf[256];
      memset(buf, 0, sizeof(buf));
		sprintf_s(buf, sizeof(buf), "Client_%d", m_curClient);
      TextOut(hdc, 3, 3, buf, strlen(buf));
	}
   else {
      m_pvGameServer->at(m_curServer)->draw(hdc);

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
   m_bShowClient = true;
   GP::NetStream::fnInitShareData(NULL);

   CItem::initItem();       // 建立物品表
   CSkill::initSkill();     // 建立技能表
   CBuff::initBuff();       // 建立Buff表
   CMonster::initMonster(); // 建立怪物表

   for(int i = 0; i < MAX_WORLDSERVER; i++)
      m_pvWorldServer->at(i)->init(2000 + i);

   for(int i = 0; i < MAX_SERVER; i++)
      m_pvGameServer->at(i)->init(2200 + i);
   
   m_curClient = 0;
   m_curServer = 0;
}

bool CClientServer::frameRenderingQueued(float timeSinceLastFrame)
{
   std::vector<CWorldServer *>::iterator itWorldServer = m_pvWorldServer->begin();
   while(itWorldServer != m_pvWorldServer->end()) {
      (*itWorldServer)->work(m_pRenderCore->getRenderHwnd(), timeSinceLastFrame);
      itWorldServer++;
   }

   std::vector<CGameServer *>::iterator itGameServer = m_pvGameServer->begin();
   while(itGameServer != m_pvGameServer->end()) {
      (*itGameServer)->work(m_pRenderCore->getRenderHwnd(), timeSinceLastFrame);
      itGameServer++;
   }

   return true;
}

void CClientServer::destoryScene()
{
}
#endif  // #ifdef _GAMEENGINE_3D_