#include "CNPC3D.h"
#include "CRenderLoader.h"

#include <OgreQuaternion.h>
#include <OgreSkeletonInstance.h>
#include <OgreSkeletonManager.h>

unsigned int CNPC3D::m_iNPCCount = 0;

CNPC3D::CNPC3D(CNPC *pNPC, Ogre::SceneManager *pSceneManager, CTerrain &terrain) : m_pNPC2D(pNPC),
																					                    m_pSceneManager(pSceneManager),
                                                                                   m_terrain(terrain)
{
	m_pRenderCore = CRenderLoader::getInstance()->getGraphicsRender("RenderEngine::OGRE");

	char buf[256];
   memset(buf, 0, sizeof(buf));
   sprintf(buf, "%s::CNPC3D::%d", m_pNPC2D->getMachineName().c_str(), m_iNPCCount++);
   m_pNPCNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(buf);

   m_pBodyEntity = NULL;

   m_pvtAnimationSet = new std::vector<Ogre::AnimationState *>();
}

CNPC3D::~CNPC3D()
{
	release();

   if(m_pvtAnimationSet != NULL) {
      m_pvtAnimationSet->clear();
      delete m_pvtAnimationSet;
      m_pvtAnimationSet = NULL;
   }

   m_pSceneManager->getRootSceneNode()->removeChild(m_pNPCNode);
   m_pNPCNode = NULL;

   m_pSceneManager = NULL;
}

void CNPC3D::setup()
{
	CNPCInfo *pNPCInfo = CNPC::getInfo(m_pNPC2D->getID());
	if(pNPCInfo != NULL)
	{
		m_pBodyEntity = m_pSceneManager->createEntity(pNPCInfo->getMeshName());

      std::string meshName = pNPCInfo->getMeshName();
      size_t idx = meshName.find(".mesh");
      m_meshName = meshName.substr(0, idx);

      m_pNPCNode->attachObject(m_pBodyEntity);

      // 設定位置
      const FPOS pos = m_pNPC2D->getPosition();
      m_pNPCNode->setPosition(pos.fX, 0, pos.fY);

      // 設定方向 (臉朝向-Z軸與2D方向相同)
      m_pNPCNode->resetOrientation();
      m_pNPCNode->yaw(Ogre::Radian(m_pNPC2D->getDirection()));

      // 載入相關動作
      std::vector<std::string> vtAnimationName = m_pNPC2D->getAllAnimationName();
      std::vector<std::string>::iterator it = vtAnimationName.begin();
      while(it != vtAnimationName.end()) {
         if((*it).length() > 0) {
            std::string skeletonFile = (*it) + std::string(".skeleton");
            setupSkeleton(skeletonFile);
         }
         it++;
		}

		// 設定動作
      CAction *pNewAction = m_pNPC2D->getCurAction();
      setAnimation(pNewAction->getAnimationName() + "::" + m_pNPCNode->getName());

      m_nameOverlay.init(m_pBodyEntity, m_pRenderCore->getCamera(), "NCTaiwanFont", 20.0f);
	}
}

void CNPC3D::update(float timeSinceLastFrame, Ogre::SceneNode *pCameraNode)
{
   // m_pNPC2D的work動作都在CScene內處理

   if(m_pNPC2D->isChangeAction()) {
      CAction *pNewAction = m_pNPC2D->getCurAction();
      setAnimation(pNewAction->getAnimationName() + "::" + m_pNPCNode->getName());
   }
   else
      playAnimation(timeSinceLastFrame);

   // 計算Y值, 要黏著3D地形
   Ogre::Vector3 terrianPos(m_pNPC2D->getPosition().fX, 500, m_pNPC2D->getPosition().fY);
   Ogre::Vector3 dir(0, -1, 0);
   Ogre::Ray ray(terrianPos, dir);
   m_terrainHeight = Ogre::Vector3::ZERO;
   m_terrain.getRayPos(ray, m_terrainHeight);

   FPOS pos = m_pNPC2D->getPosition();
   setPosition(pos.fX, m_terrainHeight.y, pos.fY);
   setDirection(m_pNPC2D->getDirection());

   m_nameOverlay.setTitle(m_pNPC2D->getName());
   m_nameOverlay.update(m_pNPCNode, pCameraNode);
}

void CNPC3D::release()
{
   m_pvtAnimationSet->clear();
   m_pNPCNode->detachAllObjects();

   if(m_pBodyEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pBodyEntity);
      m_pBodyEntity = NULL;
   }

   m_pNPC2D = NULL;  // 由CScene物件來刪除
}

const Ogre::Vector3& CNPC3D::getPosition()
{
   return m_pNPCNode->getPosition();
}

CNPC* CNPC3D::getNPC2D()
{
   return m_pNPC2D;
}

void CNPC3D::setUID(long long uid)
{
   m_pNPCNode->setUserAny(Ogre::Any(uid));
}

void CNPC3D::setPosition(float x, float y, float z)
{
   m_pNPCNode->setPosition(x, y, z);
}

void CNPC3D::setDirection(float direction)
{
   // 設定方向 (臉朝向-Z軸與2D方向相同)
   m_pNPCNode->resetOrientation();
   m_pNPCNode->yaw(Ogre::Radian(direction));
}

void CNPC3D::setAnimation(std::string animationName)
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

void CNPC3D::playAnimation(float timeSinceLastFrame)
{
   std::vector<Ogre::AnimationState *>::iterator it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      if((*it)->hasEnded() == true) {
         int nextActID = m_pNPC2D->getCurAction()->getNextActionID();
         if(nextActID == 0)
            (*it)->setTimePosition(0.0f);
      }

      (*it)->addTime(timeSinceLastFrame);
      it++;
   }
}

void CNPC3D::setupSkeleton(std::string skeletonFile)
{
   Ogre::SkeletonPtr pSkeletonBody = Ogre::SkeletonManager::getSingleton().getByName(m_meshName + ".skeleton");

   Ogre::Skeleton::BoneHandleMap boneHandleMap;
  
   Ogre::SkeletonPtr pNewSkeleton = Ogre::SkeletonManager::getSingleton().load(skeletonFile, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
   Ogre::Animation *pSrcAnimation = pNewSkeleton->getAnimation(0);
   std::string newAnimationName = pSrcAnimation->getName() + "::" + m_pNPCNode->getName();
   Ogre::Animation *pNewAnimation = pNewSkeleton->createAnimation(newAnimationName, pSrcAnimation->getLength());
   Ogre::Animation *pCloneAnimation = pNewSkeleton->getAnimation(0)->clone(newAnimationName);
   *pNewAnimation = *pCloneAnimation;
   pNewSkeleton->removeAnimation(pSrcAnimation->getName());

   pNewSkeleton->_buildMapBoneByHandle(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonBody->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   Ogre::SkeletonManager::getSingleton().remove(skeletonFile);

   m_pBodyEntity->getSkeleton()->_refreshAnimationState(m_pBodyEntity->getAllAnimationStates());
}