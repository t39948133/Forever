#include "CScene3D.h"

CScene3D::CScene3D(Ogre::SceneManager *pSceneManager, GP::NetStream *pNetStream) : m_pSceneManager(pSceneManager),
                                                                                   m_pNetStream(pNetStream)
{
   m_pMainPlayer = NULL;
   m_pPlayer3DList = new std::list<CPlayer3D *>();
}

CScene3D::~CScene3D()
{
   if(m_pPlayer3DList != NULL) {
      std::list<CPlayer3D *>::iterator it = m_pPlayer3DList->begin();
      while(it != m_pPlayer3DList->end()) {
         delete (*it);
         it++;
      }
      m_pPlayer3DList->clear();
      delete m_pPlayer3DList;
      m_pPlayer3DList = NULL;
   }
}

CPlayer3D* CScene3D::addPlayer3D(CPlayer *pPlayer2D, bool bMainPlayer)
{
   CPlayer3D *pPlayer = new CPlayer3D(pPlayer2D, m_pSceneManager, m_pNetStream);
   pPlayer->setup();
   m_pPlayer3DList->push_back(pPlayer);

   if(bMainPlayer == true)
      m_pMainPlayer = pPlayer;

   return pPlayer;
}

CPlayer3D* CScene3D::getPlayer3D(long long uid)
{
   std::list<CPlayer3D *>::iterator it = m_pPlayer3DList->begin();
   while(it != m_pPlayer3DList->end()) {
      if((*it)->getPlayer2D()->getUID() == uid)
         return (*it);

      it++;
   }

   return NULL;
}

void CScene3D::removePlayer3D(long long uid)
{
   std::list<CPlayer3D *>::iterator it = m_pPlayer3DList->begin();
   while(it != m_pPlayer3DList->end()) {
      if((*it)->getPlayer2D()->getUID() == uid) {
         delete (*it);
         m_pPlayer3DList->erase(it);
         return;
      }
         
      it++;
   }
}

CPlayer3D* CScene3D::getMainPlayer3D()
{
   return m_pMainPlayer;
}

void CScene3D::clear()
{
   if(m_pPlayer3DList != NULL) {
      std::list<CPlayer3D *>::iterator it = m_pPlayer3DList->begin();
      while(it != m_pPlayer3DList->end()) {
         delete (*it);
         it++;
      }
      m_pPlayer3DList->clear();
   }
}

void CScene3D::work(float timePass, Ogre::SceneNode *pCameraNode)
{
   std::list<CPlayer3D *>::iterator itPlayer3D = m_pPlayer3DList->begin();
   while(itPlayer3D != m_pPlayer3DList->end()) {
      if((*itPlayer3D) == m_pMainPlayer) {
         // 以m_pCameraNode為基準, 對玩家角色做邏輯運算
         (*itPlayer3D)->update(timePass, pCameraNode);  
      }
      else
         (*itPlayer3D)->update(timePass);

      itPlayer3D++;
   }
}