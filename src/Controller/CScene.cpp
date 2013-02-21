/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CScene.cpp
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#include "CScene.h"
#include "AttributeSet.h"

CScene::CScene(std::string machineName) : m_machineName(machineName)
{
   m_pvtPlayer = new std::list<CPlayer *>();
   m_pvtMonster = new std::list<CMonster *>();
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

CUnitObject* CScene::getUnitObject(long long uid)
{
   CUnitObject *pUnitObject = NULL;

   pUnitObject = getPlayer(uid);
   if(pUnitObject != NULL)
      return pUnitObject;

   pUnitObject = getMonster(uid);
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
      if((*itMonster)->isDead()) {
			long long uid = (*itMonster)->getUID();
			itMonster++;
			removeMonster(uid);
		}
      else
         itMonster++;
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

CUnitObject* CScene::getUnitObject(float x, float y)
{
   CUnitObject *pUnitObject = NULL;

   pUnitObject = getPlayer(x, y);
   if(pUnitObject != NULL)
      return pUnitObject;

   pUnitObject = getMonster(x, y);
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