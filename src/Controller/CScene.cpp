/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CScene.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#include "CScene.h"
#include "AttributeSet.h"

CScene::CScene()
{
   m_pvtPlayer = new std::list<CPlayer *>();
   m_pvtMonster = new std::list<CMonster *>();
   m_pMainPlayer = NULL;
}

CScene::~CScene()
{
   removeAll();
}

CPlayer* CScene::addPlayer(long long uid, bool bMainPlayer)
{
   CPlayer *pPlayer = new CPlayer("player", uid);
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
   CMonster *pMonster = new CMonster(kindID, uid, x, y);

   m_pvtMonster->push_back(pMonster);

   return pMonster;
}

void CScene::removeAll()
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

   m_pMainPlayer = NULL;
}

void CScene::loadScene(SCENE_TYPE scene)
{
   m_scene = scene;
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
      (*itMonster)->work(timePass, *this);
      if((*itMonster)->isDead())
         itMonster = m_pvtMonster->erase(itMonster);
      else
         itMonster++;
   }
}

std::list<CPlayer *>* CScene::getvtPlayer()
{
	return m_pvtPlayer;
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