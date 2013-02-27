/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CMonster3D.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/10 */
#include "CMonster3D.h"
#include "CRenderLoader.h"

#include <OgreQuaternion.h>
#include <OgreSkeletonInstance.h>
#include <OgreSkeletonManager.h>

unsigned int CMonster3D::m_iMonsterCount = 0;

CMonster3D::CMonster3D(CMonster *pMonster, Ogre::SceneManager *pSceneManager, CTerrain &terrain) : m_pMonster2D(pMonster),
                                                                                                   m_pSceneManager(pSceneManager),
                                                                                                   m_terrain(terrain)
{
   m_pRenderCore = CRenderLoader::getInstance()->getGraphicsRender("RenderEngine::OGRE");

   char buf[256];
   memset(buf, 0, sizeof(buf));
   sprintf(buf, "%s::CMonster3D::%d", m_pMonster2D->getMachineName().c_str(), m_iMonsterCount++);
   m_pMonsterNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(buf);

   m_pBodyEntity = NULL;

   m_pvtAnimationSet = new std::vector<Ogre::AnimationState *>();
}

CMonster3D::~CMonster3D()
{
   release();

   if(m_pvtAnimationSet != NULL) {
      m_pvtAnimationSet->clear();
      delete m_pvtAnimationSet;
      m_pvtAnimationSet = NULL;
   }

   m_pSceneManager->getRootSceneNode()->removeChild(m_pMonsterNode);
   m_pMonsterNode = NULL;

   m_pSceneManager = NULL;
}

void CMonster3D::setup()
{
   CMonsterInfo *pMonsterInfo = CMonster::getInfo(m_pMonster2D->getID());
   if(pMonsterInfo != NULL) {
      m_pBodyEntity = m_pSceneManager->createEntity(pMonsterInfo->getMeshName());

      std::string meshName = pMonsterInfo->getMeshName();
      size_t idx = meshName.find(".mesh");
      m_meshName = meshName.substr(0, idx);

      m_pMonsterNode->attachObject(m_pBodyEntity);

      // 設定位置
      const FPOS pos = m_pMonster2D->getPosition();
      m_pMonsterNode->setPosition(pos.fX, 0, pos.fY);

      // 設定方向 (臉朝向-Z軸與2D方向相同)
      m_pMonsterNode->resetOrientation();
      m_pMonsterNode->yaw(Ogre::Radian(m_pMonster2D->getDirection()));

      // 載入相關動作
      std::vector<std::string> vtAnimationName = m_pMonster2D->getAllAnimationName();
      std::vector<std::string>::iterator it = vtAnimationName.begin();
      while(it != vtAnimationName.end()) {
         if((*it).length() > 0) {
            std::string skeletonFile = (*it) + std::string(".skeleton");
            setupSkeleton(skeletonFile);
         }
         it++;
      }

      // 設定動作
      CAction *pNewAction = m_pMonster2D->getCurAction();
      setAnimation(pNewAction->getAnimationName() + "::" + m_pMonsterNode->getName());

      m_nameOverlay.init(m_pBodyEntity, m_pRenderCore->getCamera(), "NCTaiwanFont", 20.0f);
   }
}

void CMonster3D::update(float timeSinceLastFrame, Ogre::SceneNode *pCameraNode)
{
   // m_pMonster2D的work動作都在CScene內處理

   if(m_pMonster2D->isChangeAction()) {
      CAction *pNewAction = m_pMonster2D->getCurAction();
      setAnimation(pNewAction->getAnimationName() + "::" + m_pMonsterNode->getName());
   }
   else
      playAnimation(timeSinceLastFrame);

   // 計算Y值, 要黏著3D地形
   Ogre::Vector3 terrianPos(m_pMonster2D->getPosition().fX, 500, m_pMonster2D->getPosition().fY);
   Ogre::Vector3 dir(0, -1, 0);
   Ogre::Ray ray(terrianPos, dir);
   m_terrainHeight = Ogre::Vector3::ZERO;
   m_terrain.getRayPos(ray, m_terrainHeight);

   FPOS pos = m_pMonster2D->getPosition();
   setPosition(pos.fX, m_terrainHeight.y, pos.fY);
   setDirection(m_pMonster2D->getDirection());

   m_nameOverlay.setTitle(m_pMonster2D->getName());
   m_nameOverlay.update(m_pMonsterNode, pCameraNode);
}

void CMonster3D::release()
{
   m_pvtAnimationSet->clear();
   m_pMonsterNode->detachAllObjects();

   if(m_pBodyEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pBodyEntity);
      m_pBodyEntity = NULL;
   }

   m_pMonster2D = NULL;  // 由CScene物件來刪除
}

const Ogre::Vector3& CMonster3D::getPosition()
{
   return m_pMonsterNode->getPosition();
}

CMonster* CMonster3D::getMonster2D()
{
   return m_pMonster2D;
}

void CMonster3D::setUID(long long uid)
{
   m_pMonsterNode->setUserAny(Ogre::Any(uid));
}

void CMonster3D::setPosition(float x, float y, float z)
{
   m_pMonsterNode->setPosition(x, y, z);
}

void CMonster3D::setDirection(float direction)
{
   // 設定方向 (臉朝向-Z軸與2D方向相同)
   m_pMonsterNode->resetOrientation();
   m_pMonsterNode->yaw(Ogre::Radian(direction));
}

void CMonster3D::setAnimation(std::string animationName)
{
   // 清除動畫
   std::vector<Ogre::AnimationState *>::iterator it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      (*it)->setEnabled(false);
      it++;
   }
   m_pvtAnimationSet->clear();

   // 重新設定動畫
   m_pvtAnimationSet->push_back(m_pBodyEntity->getAnimationState(animationName));

   it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      (*it)->setTimePosition(0.0f);
      (*it)->setLoop(false);
      (*it)->setEnabled(true);
      it++;
   }
}

void CMonster3D::playAnimation(float timeSinceLastFrame)
{
   std::vector<Ogre::AnimationState *>::iterator it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      if((*it)->hasEnded() == true) {
         int nextActID = m_pMonster2D->getCurAction()->getNextActionID();
         if(nextActID == 0)
            (*it)->setTimePosition(0.0f);
      }

      (*it)->addTime(timeSinceLastFrame);
      it++;
   }
}

void CMonster3D::setupSkeleton(std::string skeletonFile)
{
   Ogre::SkeletonPtr pSkeletonBody = Ogre::SkeletonManager::getSingleton().getByName(m_meshName + ".skeleton");

   Ogre::Skeleton::BoneHandleMap boneHandleMap;
  
   Ogre::SkeletonPtr pNewSkeleton = Ogre::SkeletonManager::getSingleton().load(skeletonFile, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
   Ogre::Animation *pSrcAnimation = pNewSkeleton->getAnimation(0);
   std::string newAnimationName = pSrcAnimation->getName() + "::" + m_pMonsterNode->getName();
   Ogre::Animation *pNewAnimation = pNewSkeleton->createAnimation(newAnimationName, pSrcAnimation->getLength());
   Ogre::Animation *pCloneAnimation = pNewSkeleton->getAnimation(0)->clone(newAnimationName);
   *pNewAnimation = *pCloneAnimation;
   pNewSkeleton->removeAnimation(pSrcAnimation->getName());

   pNewSkeleton->_buildMapBoneByHandle(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonBody->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   Ogre::SkeletonManager::getSingleton().remove(skeletonFile);

   m_pBodyEntity->getSkeleton()->_refreshAnimationState(m_pBodyEntity->getAllAnimationStates());
}