/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CScene.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#include "CScene.h"
#include "AttributeSet.h"

CScene::CScene(std::string machineName) : m_machineName(machineName)
{
   m_pvtPlayer = new std::list<CPlayer *>();
   m_pvtMonster = new std::list<CMonster *>();
	m_pvtNPC = new std::vector<CNPC *>();
   m_pMainPlayer = NULL;
}

CScene::~CScene()
{
   if(m_pvtPlayer != NULL) {
      std::list<CPlayer *>::iterator itPlayer = m_pvtPlayer->begin();
      while(itPlayer != m_pvtPlayer->end()) {
         delete (*itPlayer);
         itPlayer++;
      }
      m_pvtPlayer->clear();
      delete m_pvtPlayer;
      m_pvtPlayer = NULL;
   }

   if(m_pvtMonster != NULL) {
      std::list<CMonster *>::iterator itMonster = m_pvtMonster->begin();
      while(itMonster != m_pvtMonster->end()) {
         delete (*itMonster);
         itMonster++;
      }
      m_pvtMonster->clear();
      delete m_pvtMonster;
      m_pvtMonster = NULL;
   }

	if(m_pvtNPC != NULL) {
		std::vector<CNPC *>::iterator itNPC = m_pvtNPC->begin();
		while(itNPC != m_pvtNPC->end()) {
			delete (*itNPC);
			itNPC++;
		}
		m_pvtNPC->clear();
		delete m_pvtNPC;
		m_pvtNPC = NULL;
	}
}

CPlayer* CScene::addPlayer(long long uid, bool bMainPlayer)
{
   CPlayer *pPlayer = new CPlayer(m_machineName, "player", uid);
   m_pvtPlayer->push_back(pPlayer);

   if(bMainPlayer == true)
      m_pMainPlayer = pPlayer;

   return pPlayer;
}

void CScene::removePlayer(long long uid)
{
   std::list<CPlayer *>::iterator it = m_pvtPlayer->begin();
   while(it != m_pvtPlayer->end()) {
      if((*it)->getUID() == uid) {
         m_pvtPlayer->erase(it);
         break;
      }
      it++;
   }
}

CMonster* CScene::addMonster(long long uid, int kindID, float x, float y)
{
   CMonster *pMonster = new CMonster(m_machineName, kindID, uid, x, y);
   m_pvtMonster->push_back(pMonster);

   notifyAddMonsterUpdate(pMonster);

   return pMonster;
}

void CScene::removeMonster(long long uid)
{
	std::list<CMonster *>::iterator it = m_pvtMonster->begin();
	while(it != m_pvtMonster->end()) {
		if((*it)->getUID() == uid) {
			m_pvtMonster->erase(it);
			break;
		}
		it++;
	}
}

CNPC* CScene::addNPC(long long uid, int kindID, float x, float y, float direction)
{
	CNPC *pNPC = new CNPC(m_machineName, kindID, uid, x, y);
   pNPC->setDirection(direction);
   m_pvtNPC->push_back(pNPC);

   return pNPC;
}

void CScene::removeNPC(long long uid)
{
	std::vector<CNPC *>::iterator it = m_pvtNPC->begin();
	while(it != m_pvtNPC->end()) {
		if((*it)->getUID() == uid) {
			m_pvtNPC->erase(it);
			break;
		}
		it++;
	}
}

void CScene::clear()
{
   if(m_pvtPlayer != NULL) {
      std::list<CPlayer *>::iterator itPlayer = m_pvtPlayer->begin();
      while(itPlayer != m_pvtPlayer->end()) {
         delete (*itPlayer);
         itPlayer++;
      }
      m_pvtPlayer->clear();
   }

   if(m_pvtMonster != NULL) {
      std::list<CMonster *>::iterator itMonster = m_pvtMonster->begin();
      while(itMonster != m_pvtMonster->end()) {
         delete (*itMonster);
         itMonster++;
      }
      m_pvtMonster->clear();
   }

	if(m_pvtNPC != NULL) {
		std::vector<CNPC *>::iterator itNPC = m_pvtNPC->begin();
		while(itNPC != m_pvtNPC->end()) {
			delete(*itNPC);
			itNPC++;
		}
		m_pvtNPC->clear();
	}

   m_pMainPlayer = NULL;
}

CPlayer* CScene::getMainPlayer()
{
   return m_pMainPlayer;
}

CPlayer* CScene::getPlayer(long long uid)
{
   std::list<CPlayer *>::iterator it = m_pvtPlayer->begin();
   while(it != m_pvtPlayer->end()) {
      if((*it)->getUID() == uid)
         return (*it);
  
      it++;
   }

   return NULL;
}

CMonster* CScene::getMonster(long long uid)
{
   std::list<CMonster *>::iterator it = m_pvtMonster->begin();
   while(it != m_pvtMonster->end()) {
      if((*it)->getUID() == uid)
         return (*it);
  
      it++;
   }

   return NULL;
}

CNPC* CScene::getNPC(long long uid)
{
	std::vector<CNPC *>::iterator it = m_pvtNPC->begin();
	while(it != m_pvtNPC->end()) {
		if((*it)->getUID() == uid)
			return (*it);
		it++;
	}
	return NULL;
}

CUnitObject* CScene::getUnitObject(long long uid)
{
   CUnitObject *pUnitObject = NULL;

   pUnitObject = getPlayer(uid);
   if(pUnitObject != NULL)
      return pUnitObject;

   pUnitObject = getMonster(uid);
   if(pUnitObject != NULL)
      return pUnitObject;

	pUnitObject = getNPC(uid);
	if(pUnitObject != NULL)
		return pUnitObject;

   return NULL;
}

void CScene::work(float timePass)
{
   std::list<CPlayer *>::iterator itPlayer = m_pvtPlayer->begin();
   while(itPlayer != m_pvtPlayer->end()) {
      (*itPlayer)->work(timePass);
      itPlayer++;
   }

   std::list<CMonster *>::iterator itMonster = m_pvtMonster->begin();
   while(itMonster != m_pvtMonster->end()) {
      (*itMonster)->work(timePass);

      size_t idx = m_machineName.find("Server");
      if(idx != std::string::npos) {
         if((*itMonster)->isDead()) {
			   long long uid = (*itMonster)->getUID();
			    ++itMonster;
			   removeMonster(uid);
		   }
         else
             ++itMonster;
      }
      else
         ++itMonster;
   }

   std::vector<CNPC *>::iterator itNPC = m_pvtNPC->begin();
	while(itNPC != m_pvtNPC->end()) {
		(*itNPC)->work(timePass);
		itNPC++;
	}
}

std::list<CPlayer *>* CScene::getAllPlayer()
{
	return m_pvtPlayer;
}

std::list<CMonster *>* CScene::getAllMonster()
{
   return m_pvtMonster;
}

std::vector<CNPC *>* CScene::getAllNPC()
{
	return m_pvtNPC;
}

#ifdef _GAMEENGINE_2D_
CPlayer* CScene::getPlayer(float x, float y)
{
   std::list<CPlayer *>::iterator it = m_pvtPlayer->begin();
   while(it != m_pvtPlayer->end()) {
      if((*it)->isClick(x, y) == true)
         return (*it);
  
      it++;
   }

   return NULL;
}

CMonster* CScene::getMonster(float x, float y)
{
   std::list<CMonster *>::iterator it = m_pvtMonster->begin();
   while(it != m_pvtMonster->end()) {
      if((*it)->isClick(x, y) == true)
         return (*it);
  
      it++;
   }

   return NULL;
}

CNPC* CScene::getNPC(float x, float y)
{
	std::vector<CNPC *>::iterator it = m_pvtNPC->begin();
	while(it != m_pvtNPC->end()){
		if((*it)->isClick(x, y) == true)
			return (*it);
		it++;
	}
	return NULL;
}

CUnitObject* CScene::getUnitObject(float x, float y)
{
   CUnitObject *pUnitObject = NULL;

   pUnitObject = getPlayer(x, y);
   if(pUnitObject != NULL)
      return pUnitObject;

   pUnitObject = getMonster(x, y);
   if(pUnitObject != NULL)
      return pUnitObject;

	pUnitObject = getNPC(x, y);
	if(pUnitObject != NULL)
		return pUnitObject;

   return NULL;
}

void CScene::draw(HDC hdc)
{
   std::list<CPlayer *>::iterator itPlayer = m_pvtPlayer->begin();
   while(itPlayer != m_pvtPlayer->end()) {
      (*itPlayer)->draw(hdc);
      itPlayer++;
   }

   std::list<CMonster *>::iterator itMonster = m_pvtMonster->begin();
   while(itMonster != m_pvtMonster->end()) {
      (*itMonster)->draw(hdc);
      itMonster++;
   }

	std::vector<CNPC *>::iterator itNPC = m_pvtNPC->begin();
	while(itNPC != m_pvtNPC->end()) {
		(*itNPC)->draw(hdc);
		itNPC++;
	}
}
#endif  // #ifdef _GAMEENGINE_2D_

void CScene::addSceneMonsterEventListener(ISceneMonsterEventListener *pListener)
{
   std::set<ISceneMonsterEventListener *>::iterator it = m_monsterEventListeners.find(pListener);
   if(it == m_monsterEventListeners.end())
      m_monsterEventListeners.insert(pListener);
}

void CScene::removeSceneMonsterEventListener(ISceneMonsterEventListener *pListener)
{
   std::set<ISceneMonsterEventListener *>::iterator it = m_monsterEventListeners.find(pListener);
   if(it != m_monsterEventListeners.end())
      m_monsterEventListeners.erase(it);
}

void CScene::notifyAddMonsterUpdate(CMonster *pNewMonster)
{
   std::set<ISceneMonsterEventListener *>::iterator it = m_monsterEventListeners.begin();
   while(it != m_monsterEventListeners.end()) {
      (*it)->updateAddMonster(pNewMonster);
      it++;
   }
}