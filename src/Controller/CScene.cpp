/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CScene.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#include "CScene.h"

CScene::CScene()
{
   m_pvtPlayer = new std::list<CPlayer *>();
   m_pMainPlayer = NULL;
}

CScene::~CScene()
{
   std::list<CPlayer *>::iterator it = m_pvtPlayer->begin();
   while(it != m_pvtPlayer->end()) {
      delete (*it);
      it++;
   }
   m_pvtPlayer->clear();
   delete m_pvtPlayer;
   m_pvtPlayer = NULL;

   m_pMainPlayer = NULL;
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

void CScene::removeAll()
{
   std::list<CPlayer *>::iterator it = m_pvtPlayer->begin();
   while(it != m_pvtPlayer->end()) {
      delete (*it);
      it++;
   }
   m_pvtPlayer->clear();

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

void CScene::work(float timePass)
{
   std::list<CPlayer *>::iterator it = m_pvtPlayer->begin();
   while(it != m_pvtPlayer->end()) {
      (*it)->work(timePass);
      it++;
   }
}

#ifdef _GAMEENGINE_2D_
void CScene::draw(HDC hdc)
{
   std::list<CPlayer *>::iterator it = m_pvtPlayer->begin();
   while(it != m_pvtPlayer->end()) {
      (*it)->draw(hdc);
      it++;
   }
}
#endif  // #ifdef _GAMEENGINE_2D_