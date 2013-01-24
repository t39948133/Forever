/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPlayer3D.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#include "CPlayer3D.h"
#include "CRenderLoader.h"
#include <OgreQuaternion.h>
#include <OgreSkeletonInstance.h>
#include <OgreSkeletonManager.h>

CPlayer3D::CPlayer3D(CPlayer *pPlayer, Ogre::SceneManager *pSceneManager) : m_pPlayer2D(pPlayer),
                                                                            m_pSceneManager(pSceneManager)
{
   CGraphicsRender *pRenderCore = CRenderLoader::getInstance()->getGraphicsRender("RenderEngine::OGRE");
   pRenderCore->addKeyEventListener(this);

   m_pPlayerNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode("Forever::Player");

   m_pHairEntity = NULL;
   m_pHeadEntity = NULL;
   m_pBodyEntity = NULL;
   m_pFootEntity = NULL;
   m_pHandEntity = NULL;
   m_pLegEntity = NULL;
   m_pShoulderEntity = NULL;

   m_mouseDirection = Ogre::Vector3::ZERO;
   m_keyDirection = Ogre::Vector3::ZERO;
   m_goalDirection = Ogre::Vector3::ZERO;
   m_fTurnSpeed = 500.0f;
   m_bMouseMove = false;

   m_pvtAnimationSet = new std::vector<Ogre::AnimationState *>();
}

CPlayer3D::~CPlayer3D()
{
   release();

   if(m_pvtAnimationSet != NULL) {
      m_pvtAnimationSet->clear();
      delete m_pvtAnimationSet;
      m_pvtAnimationSet = NULL;
   }

   m_pSceneManager->getRootSceneNode()->removeChild(m_pPlayerNode);
   m_pPlayerNode = NULL;

   m_pSceneManager = NULL;
}

void CPlayer3D::setup()
{
   m_pHairEntity = m_pSceneManager->createEntity("LM023_Hair.mesh");
   m_pHairEntity->setMaterialName("LM023_Hair");

   m_pHeadEntity = m_pSceneManager->createEntity("LM001_Head.mesh");
   m_pHeadEntity->setMaterialName("LM001_Head");
   
   m_pBodyEntity = m_pSceneManager->createEntity("LMDF_C001_Body.mesh");
   m_pBodyEntity->setMaterialName("LMDF_C001_Body");

   m_pFootEntity = m_pSceneManager->createEntity("LMDF_C001_FootShort.mesh");
   m_pFootEntity->setMaterialName("LMDF_C001_Foot");

   m_pHandEntity = m_pSceneManager->createEntity("LMDF_C001_HandShort.mesh");
   m_pHandEntity->setMaterialName("LMDF_C001_Hand");

   m_pLegEntity = m_pSceneManager->createEntity("LMDF_C001_Leg.mesh");
   m_pLegEntity->setMaterialName("LMDF_C001_Leg");

   m_pPlayerNode->attachObject(m_pHairEntity);
   m_pPlayerNode->attachObject(m_pHeadEntity);
   m_pPlayerNode->attachObject(m_pBodyEntity);
   m_pPlayerNode->attachObject(m_pFootEntity);
   m_pPlayerNode->attachObject(m_pHandEntity);
   m_pPlayerNode->attachObject(m_pLegEntity);

   // 設定玩家位置
   const FPOS pos = m_pPlayer2D->getPosition();
   m_pPlayerNode->setPosition(pos.fX, 0, pos.fY);

   // 設定玩家的方向 (臉朝向-Z軸與2D方向相同)
   m_pPlayerNode->resetOrientation();
   m_pPlayerNode->yaw(Ogre::Radian(m_pPlayer2D->getDirection()));

   // 載入相關動作
   setupSkeleton("lm_nidle_001.skeleton");
   setupSkeleton("lm_nrun_001.skeleton");
   setupSkeleton("lm_cdraw_2weapon_001.skeleton");
   setupSkeleton("lm_cidle_2weapon_001.skeleton");
   setupSkeleton("lm_nputin_2weapon_001.skeleton");

   // 設定動作
   CAction *pNewAction = m_pPlayer2D->getCurAction();
   setAnimation(pNewAction->getAnimationName());
}

void CPlayer3D::update(float timeSinceLastFrame, Ogre::SceneNode *pCameraNode)
{
   // m_pPlayer2D的work動作都在CScene內處理

   if(m_pPlayer2D->isChangeAction()) {
      CAction *pNewAction = m_pPlayer2D->getCurAction();
      setAnimation(pNewAction->getAnimationName());
   }
   else
      playAnimation(timeSinceLastFrame);
   
   if(m_keyDirection != Ogre::Vector3::ZERO) {
      // 鍵盤移動
      move(timeSinceLastFrame, pCameraNode, m_keyDirection);

      Ogre::Vector3 curPos = m_pPlayerNode->getPosition();
      m_pPlayer2D->setTargetPosition(curPos.x, curPos.z);
   }
   else {
      // 滑鼠移動
      if(m_pPlayer2D->isMove() == true) {
         m_bMouseMove = true;
         FPOS targetPos = m_pPlayer2D->getTargetPosition();
         FPOS curPos = m_pPlayer2D->getPosition();

         FPOS offsetPos;
         offsetPos.fX = targetPos.fX - curPos.fX;
         offsetPos.fY = targetPos.fY - curPos.fY;

         m_mouseDirection = Ogre::Vector3::ZERO;
         m_mouseDirection.x = offsetPos.fX;
         m_mouseDirection.z = offsetPos.fY;

         move(timeSinceLastFrame, m_mouseDirection);
      }
      else {
         if(m_bMouseMove == true) {
            if(m_pPlayer2D->isReachTarget() == true) {
               m_bMouseMove = false;
               FPOS targetPos = m_pPlayer2D->getTargetPosition();
               m_pPlayer2D->setPosition(targetPos.fX, targetPos.fY);
               m_pPlayerNode->setPosition(targetPos.fX, 0, targetPos.fY);

               CActionEvent actEvent;
               actEvent.m_event = AET_REACH;
               CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getUID(), actEvent);
            }
         }
      }
   }
}

void CPlayer3D::release()
{
   m_pvtAnimationSet->clear();
   m_pPlayerNode->detachAllObjects();

   if(m_pHairEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pHairEntity);
      m_pHairEntity = NULL;
   }

   if(m_pHeadEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pHeadEntity);
      m_pHeadEntity = NULL;
   }

   if(m_pBodyEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pBodyEntity);
      m_pBodyEntity = NULL;
   }

   if(m_pFootEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pFootEntity);
      m_pFootEntity = NULL;
   }

   if(m_pHandEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pHandEntity);
      m_pHandEntity = NULL;
   }

   if(m_pLegEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pLegEntity);
      m_pLegEntity = NULL;
   }

   if(m_pShoulderEntity != NULL) {
      m_pSceneManager->destroyEntity(m_pShoulderEntity);
      m_pShoulderEntity = NULL;
   }

   m_pPlayer2D = NULL;  // 由CScene物件來刪除
}

const Ogre::Vector3& CPlayer3D::getPosition()
{
   return m_pPlayerNode->getPosition();
}

void CPlayer3D::setMouseTargetPosition(Ogre::Vector3 &targetPos)
{
   m_pPlayer2D->setTargetPosition(targetPos.x, targetPos.z);

   if(m_pPlayer2D->isReachTarget() == false) {
      CActionEvent actEvent;
      actEvent.m_event = AET_NOT_REACH;
      CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getUID(), actEvent);
   }
}

void CPlayer3D::setAnimation(std::string animationName)
{
   // 清除動畫
   std::vector<Ogre::AnimationState *>::iterator it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      (*it)->setEnabled(false);
      it++;
   }
   m_pvtAnimationSet->clear();

   // 重新設定動畫
   m_pvtAnimationSet->push_back(m_pHairEntity->getAnimationState(animationName));
   m_pvtAnimationSet->push_back(m_pHeadEntity->getAnimationState(animationName));
   m_pvtAnimationSet->push_back(m_pBodyEntity->getAnimationState(animationName));
   m_pvtAnimationSet->push_back(m_pFootEntity->getAnimationState(animationName));
   m_pvtAnimationSet->push_back(m_pHandEntity->getAnimationState(animationName));
   m_pvtAnimationSet->push_back(m_pLegEntity->getAnimationState(animationName));

   it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      (*it)->setTimePosition(0.0f);
      (*it)->setLoop(false);
      (*it)->setEnabled(true);
      it++;
   }
}

void CPlayer3D::playAnimation(float timeSinceLastFrame)
{
   std::vector<Ogre::AnimationState *>::iterator it = m_pvtAnimationSet->begin();
   while(it != m_pvtAnimationSet->end()) {
      if((*it)->hasEnded() == true)
         (*it)->setTimePosition(0.0f);

      (*it)->addTime(timeSinceLastFrame);
      it++;
   }
}

void CPlayer3D::setupSkeleton(std::string skeletonFile)
{
   Ogre::SkeletonPtr pSkeletonHair = Ogre::SkeletonManager::getSingleton().getByName("LM023_Hair.skeleton");
   Ogre::SkeletonPtr pSkeletonHead = Ogre::SkeletonManager::getSingleton().getByName("LM001_Head.skeleton");
   Ogre::SkeletonPtr pSkeletonBody = Ogre::SkeletonManager::getSingleton().getByName("LMDF_C001_Body.skeleton");
   Ogre::SkeletonPtr pSkeletonFoot = Ogre::SkeletonManager::getSingleton().getByName("LMDF_C001_Footshort.skeleton");
   Ogre::SkeletonPtr pSkeletonHand = Ogre::SkeletonManager::getSingleton().getByName("LMDF_C001_Handshort.skeleton");
   Ogre::SkeletonPtr pSkeletonLeg  = Ogre::SkeletonManager::getSingleton().getByName("LMDF_C001_Leg.skeleton");

   Ogre::Skeleton::BoneHandleMap boneHandleMap;
  
   Ogre::SkeletonPtr pNewSkeleton = Ogre::SkeletonManager::getSingleton().load(skeletonFile, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
   pNewSkeleton->_buildMapBoneByHandle(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonHair->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonHead->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonBody->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonFoot->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonHand->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   pSkeletonLeg->_mergeSkeletonAnimations(pNewSkeleton.getPointer(), boneHandleMap);
   Ogre::SkeletonManager::getSingleton().remove(skeletonFile);

   m_pHairEntity->getSkeleton()->_refreshAnimationState(m_pHairEntity->getAllAnimationStates());
   m_pHeadEntity->getSkeleton()->_refreshAnimationState(m_pHeadEntity->getAllAnimationStates());
   m_pBodyEntity->getSkeleton()->_refreshAnimationState(m_pBodyEntity->getAllAnimationStates());
   m_pFootEntity->getSkeleton()->_refreshAnimationState(m_pFootEntity->getAllAnimationStates());
   m_pHandEntity->getSkeleton()->_refreshAnimationState(m_pHandEntity->getAllAnimationStates());
   m_pLegEntity->getSkeleton()->_refreshAnimationState(m_pLegEntity->getAllAnimationStates());
}

void CPlayer3D::move(float timeSinceLastFrame, Ogre::SceneNode *pCameraNode, Ogre::Vector3 &offsetDirection)
{
   if(offsetDirection != Ogre::Vector3::ZERO) {
      // 當offsetDirection不等於0時, 代表移動

      // 數值清空
      m_goalDirection = Ogre::Vector3::ZERO;

      // 以攝影機的方向計算鍵盤的方向
      m_goalDirection += (offsetDirection.z * pCameraNode->getOrientation().zAxis());
      m_goalDirection += (offsetDirection.x * pCameraNode->getOrientation().xAxis());
      m_goalDirection.y = 0;
      m_goalDirection.normalise(); // 以計算後的方向為單位

      // 取得角色的Z軸方向旋轉到m_goalDirection的方向
      Ogre::Quaternion toGoal = m_pPlayerNode->getOrientation().zAxis().getRotationTo(m_goalDirection);

      // 取得轉向後的方向是幾度角
      Ogre::Real yawToGoal = toGoal.getYaw().valueDegrees();

      // 更新轉向後的方向(弧度)
      m_pPlayer2D->addDirection(toGoal.getYaw().valueRadians());

      // 模型Y軸旋轉
      m_pPlayerNode->yaw(Ogre::Degree(yawToGoal));

      // 模型移動Z軸
      AdvancedAttribute advAttr = m_pPlayer2D->getAdvAttr();
      m_pPlayerNode->translate(0, 0, timeSinceLastFrame * advAttr.fMove, Ogre::Node::TS_LOCAL);

      // 更新模型座標點
      Ogre::Vector3 newPos = m_pPlayerNode->getPosition();
      m_pPlayer2D->setPosition(newPos.x, newPos.z);
   }
}

void CPlayer3D::move(float timeSinceLastFrame, Ogre::Vector3 &offsetDirection)
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
      Ogre::Quaternion toGoal = m_pPlayerNode->getOrientation().zAxis().getRotationTo(m_goalDirection);

      // 取得轉向後的方向是幾度角
      Ogre::Real yawToGoal = toGoal.getYaw().valueDegrees();

      // 更新轉向後的方向(弧度)
      m_pPlayer2D->addDirection(toGoal.getYaw().valueRadians());

      // 模型Y軸旋轉
      m_pPlayerNode->yaw(Ogre::Degree(yawToGoal));

      // 模型移動Z軸
      AdvancedAttribute advAttr = m_pPlayer2D->getAdvAttr();
      m_pPlayerNode->translate(0, 0, timeSinceLastFrame * advAttr.fMove, Ogre::Node::TS_LOCAL);

      // 更新模型座標點
      Ogre::Vector3 newPos = m_pPlayerNode->getPosition();
      m_pPlayer2D->setPosition(newPos.x, newPos.z);
   }
}

void CPlayer3D::keyDown(const OIS::KeyEvent &evt)
{
   switch(evt.key) {
      case OIS::KC_W: {
         m_keyDirection.z = -1;

         CActionEvent actEvent;
         actEvent.m_event = AET_KEY_WASD;
         actEvent.m_iKeyDownID = 'W';
         CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getUID(), actEvent);
         break;
      }

      case OIS::KC_A: {
         m_keyDirection.x = -1;

         CActionEvent actEvent;
         actEvent.m_event = AET_KEY_WASD;
         actEvent.m_iKeyDownID = 'A';
         CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getUID(), actEvent);
         break;
      }

      case OIS::KC_S: {
         m_keyDirection.z = 1;

         CActionEvent actEvent;
         actEvent.m_event = AET_KEY_WASD;
         actEvent.m_iKeyDownID = 'S';
         CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getUID(), actEvent);
         break;
      }

      case OIS::KC_D: {
         m_keyDirection.x = 1;

         CActionEvent actEvent;
         actEvent.m_event = AET_KEY_WASD;
         actEvent.m_iKeyDownID = 'D';
         CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getUID(), actEvent);
         break;
      }
      
      case OIS::KC_X: {
         CActionEvent actEvent;
         actEvent.m_event = AET_KEY;
         actEvent.m_iKeyID = 'X';
         CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getUID(), actEvent);
         break;
      }
   }
}

void CPlayer3D::keyUp(const OIS::KeyEvent &evt)
{
   if((evt.key == OIS::KC_W) && (m_keyDirection.z == -1)) {
      m_keyDirection.z = 0;

      CActionEvent actEvent;
      actEvent.m_event = AET_KEY_WASD;
      actEvent.m_iKeyUpID = 'W';
      CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getUID(), actEvent);
   }
   else if((evt.key == OIS::KC_A) && (m_keyDirection.x == -1)) {
      m_keyDirection.x = 0;

      CActionEvent actEvent;
      actEvent.m_event = AET_KEY_WASD;
      actEvent.m_iKeyUpID = 'A';
      CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getUID(), actEvent);
   }
   else if((evt.key == OIS::KC_S) && (m_keyDirection.z == 1)) {
      m_keyDirection.z = 0;

      CActionEvent actEvent;
      actEvent.m_event = AET_KEY_WASD;
      actEvent.m_iKeyUpID = 'S';
      CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getUID(), actEvent);
   }
   else if((evt.key == OIS::KC_D) && (m_keyDirection.x == 1)) {
      m_keyDirection.x = 0;

      CActionEvent actEvent;
      actEvent.m_event = AET_KEY_WASD;
      actEvent.m_iKeyUpID = 'D';
      CActionDispatch::getInstance()->sendEvnet(m_pPlayer2D->getUID(), actEvent);
   }
}