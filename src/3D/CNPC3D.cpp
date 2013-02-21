#include "CNPC3D.h"
#include "CRenderLoader.h"

#include <OgreQuaternion.h>
#include <OgreSkeletonInstance.h>
#include <OgreSkeletonManager.h>

unsigned int CNPC3D::m_iNPCCount = 0;

CNPC3D::CNPC3D(CNPC *pNPC, Ogre::SceneManager *pSceneManager) : m_pNPC2D(pNPC),
																					 m_pSceneManager(pSceneManager)
{
	m_pRenderCore = CRenderLoader::getInstance()->getGraphicsRender("RenderEngine::OGRE");

	char buf[256];
   memset(buf, 0, sizeof(buf));
   sprintf(buf, "%s::CNPC3D::%d", m_pNPC2D->getMachineName().c_str(), m_iNPCCount++);
   m_pNPCNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode(buf);

   m_nameOverlay = NULL;

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

      m_nameOverlay = new CObjectTitle(m_pBodyEntity, m_pRenderCore->getCamera(), "NCTaiwanFont", 20.0f);
	}
}

void CNPC3D::update(float timeSinceLastFrame)
{
   // m_pNPC2D的work動作都在CScene內處理

   if(m_pNPC2D->isChangeAction()) {
      CAction *pNewAction = m_pNPC2D->getCurAction();
      setAnimation(pNewAction->getAnimationName() + "::" + m_pNPCNode->getName());
   }
   else
      playAnimation(timeSinceLastFrame);

   if((m_pNPC2D->isMove() == true) && (m_pNPC2D->isReachTarget() == false)) {
      // 怪物位置改變時, 一律視為用滑鼠移動
      FPOS targetPos = m_pNPC2D->getTargetPosition();
      FPOS curPos = m_pNPC2D->getPosition();

      FPOS offsetPos;
      offsetPos.fX = targetPos.fX - curPos.fX;
      offsetPos.fY = targetPos.fY - curPos.fY;

      m_mouseDirection = Ogre::Vector3::ZERO;
      m_mouseDirection.x = offsetPos.fX;
      m_mouseDirection.z = offsetPos.fY;

      move(timeSinceLastFrame, m_mouseDirection);
   }
   else {
      // 怪物沒有改變位置時
      FPOS pos = m_pNPC2D->getPosition();
      setPosition(pos.fX, 0, pos.fY);
      setDirection(m_pNPC2D->getDirection());
   }

   m_nameOverlay->setTitle(m_pNPC2D->getName());
   m_nameOverlay->update();
}

void CNPC3D::release()
{
   if(m_nameOverlay != NULL) {
      delete m_nameOverlay;
      m_nameOverlay = NULL;
   }

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
      if((*it)->hasEnded() == true)
         (*it)->setTimePosition(0.0f);

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

void CNPC3D::move(float timeSinceLastFrame, Ogre::Vector3 &offsetDirection)
{
   if(offsetDirection != Ogre::Vector3::ZERO) {
      // 當offsetDirection不等於0時, 代表移動

      // 數值清空
      m_goalDirection = Ogre::Vector3::ZERO;

      // 偏移量方向為目標方向
      m_goalDirection = offsetDirection;
      m_goalDirection.y = 0;
      m_goalDirection.normalise(); // 以目標方向為單位

      // 取得角色的Z軸方向旋轉到m_goalDirection的方向
      Ogre::Quaternion toGoal = m_pNPCNode->getOrientation().zAxis().getRotationTo(m_goalDirection);

      // 取得轉向後的方向是幾度角
      Ogre::Real yawToGoal = toGoal.getYaw().valueDegrees();

      // 更新轉向後的方向(弧度)
      m_pNPC2D->addDirection(toGoal.getYaw().valueRadians());

      // 模型Y軸旋轉
      m_pNPCNode->yaw(Ogre::Degree(yawToGoal));

      // 模型移動Z軸
      AdvancedAttribute advAttr = m_pNPC2D->getAdvAttr();
      m_pNPCNode->translate(0, 0, timeSinceLastFrame * advAttr.fMove, Ogre::Node::TS_LOCAL);

      // 更新模型座標點
      Ogre::Vector3 newPos = m_pNPCNode->getPosition();
      m_pNPC2D->setPosition(newPos.x, newPos.z);
   }
}