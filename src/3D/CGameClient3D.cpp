/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameClient3D.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/04 */
#include "CGameClient3D.h"
#include "CPlayerInfoWnd.h"
#include "CBackpackWnd.h"
#include "CSkillWnd.h"
#include "CHudWnd.h"
#include "CHotKeyWnd.h"
#include "CPlayerStateWnd.h"

#include <OgreMeshManager.h>
#include <OgreMath.h>

#ifdef _DEBUGLOG
#include "LogWindow.h"
extern CLogWindow glog;
#endif  // #ifdef _DEBUG

CGameClient3D::CGameClient3D(std::string machineName) : CGameClient(machineName)
{
   m_pScene3D = NULL;
   m_fPivotPitch = 0;
   m_pTerrain = new CTerrain();
   m_pRayQuery = NULL;
   m_pWindowMan = new CWindowMan3D();

   m_pRenderCore = CRenderLoader::getInstance()->getGraphicsRender("RenderEngine::OGRE");
   if(m_pRenderCore != NULL) {
      m_pRenderCore->addGameFlowListener(this);
      m_pRenderCore->addMouseEventListener(this);
   }
}

CGameClient3D::~CGameClient3D()
{
   if(m_pWindowMan != NULL) {
      delete m_pWindowMan;
      m_pWindowMan = NULL;
   }

   if(m_pTerrain != NULL) {
      delete m_pTerrain;
      m_pTerrain = NULL;
   }

   if(m_pScene3D != NULL) {
      delete m_pScene3D;
      m_pScene3D = NULL;
   }

   m_pRenderCore = NULL;
}

void CGameClient3D::initUI()
{
   CPlayer *pPlayer2D = this->getScene()->getMainPlayer();

   RECT rect;
   memset(&rect, 0, sizeof(rect));
   HWND hRenderWnd = m_pRenderCore->getRenderHwnd();
   GetClientRect(hRenderWnd, &rect);

   CPlayerInfoWnd *pPlayerInfoWnd = new CPlayerInfoWnd();
   pPlayerInfoWnd->init(10, 10, pPlayer2D);
   m_pWindowMan->addWnd(pPlayerInfoWnd);

   CBackpackWnd *pBackpackWnd = new CBackpackWnd();
   pBackpackWnd->init(10, 411, pPlayer2D);
   m_pWindowMan->addWnd(pBackpackWnd);

   CSkillWnd *pSkillWnd = new CSkillWnd();
   pSkillWnd->init(500, 10, pPlayer2D);
   m_pWindowMan->addWnd(pSkillWnd);

   int hudX = ((rect.right - rect.left) - 856) / 2;
   int hudY = ((rect.bottom - rect.top) - 126);

   CHotKeyWnd *pHotKeyWnd = new CHotKeyWnd();
   int hotkeyX = hudX + 381;
   int hotkeyY = hudY + 75;
   pHotKeyWnd->init(hotkeyX, hotkeyY, pPlayer2D);
   m_pWindowMan->addWnd(pHotKeyWnd);
   m_pRenderCore->addKeyEventListener(pHotKeyWnd);

   CPlayerStateWnd *pPlayerStateWnd = new CPlayerStateWnd();
   int playerstateX = hudX + 98;
   int playerstateY = hudY + 70;
   pPlayerStateWnd->init(playerstateX, playerstateY, pPlayer2D);
   m_pWindowMan->addWnd(pPlayerStateWnd);

   CHudWnd *pHudWnd = new CHudWnd();
   pHudWnd->init(hudX, hudY, pPlayer2D);
   m_pWindowMan->addWnd(pHudWnd);
}

void CGameClient3D::onRecvPlayerInit(CPacketPlayerInit *pPacket)
{
   CPlayer3D *pMainPlayer = m_pScene3D->getMainPlayer3D();
   if(pMainPlayer != NULL)
      pPacket->unpack(pMainPlayer);

   // createScene完成, 取得GameServer的玩家資料
   m_bCreateScene = false;  
}

void CGameClient3D::onRecvPlayerData(CPacketPlayerData *pPacket)
{
   CPlayer3D *pPlayer = m_pScene3D->getPlayer3D(pPacket->getUID());
   if(pPlayer == NULL) {
      CPlayer *pNewPlayer2D = this->getScene()->addPlayer(pPacket->getUID());
      pPlayer = m_pScene3D->addPlayer3D(pNewPlayer2D);
   }

   pPacket->unpack(pPlayer);
}

void CGameClient3D::createScene()
{
   CGameClient::init();

   m_pSceneManager = m_pRenderCore->getSceneManager();
   m_pScene3D = new CScene3D(m_pSceneManager, this->getNetStream());

   m_pRayQuery = m_pSceneManager->createRayQuery(Ogre::Ray());

   // 設定場景環境光源
   m_pSceneManager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

   // 建立玩家模型 (資料未定)
   CPlayer *pPlayer2D = this->getScene()->getMainPlayer();
   CPlayer3D *pMainPlayer = m_pScene3D->addPlayer3D(pPlayer2D, true);

   // 依據玩家模型位置來設定攝影機
   setupCamera(m_pRenderCore->getCamera(), pMainPlayer->getPosition());

   // 地形初始化
   m_pTerrain->init(m_pSceneManager, m_pRenderCore->getCamera());

   // createScene還沒完成, 必須等待GameServer的玩家資料
   m_bCreateScene = true;  
}

bool CGameClient3D::frameRenderingQueued(float timeSinceLastFrame)
{
   CGameClient::work(m_pRenderCore->getRenderHwnd(), timeSinceLastFrame);

   if(m_bCreateScene == false) {
      m_pScene3D->work(timeSinceLastFrame, m_pCameraNode);

      // 以玩家角色的位置來更新攝影機的邏輯運算
      updateCamera(timeSinceLastFrame, m_pScene3D->getMainPlayer3D()->getPosition());
   }

   return true;
}

void CGameClient3D::destoryScene()
{
   m_pWindowMan->deleteAllWindow();

   m_pSceneManager->destroyQuery(m_pRayQuery);
   m_pRayQuery = NULL;

   releaseCamera();

   m_pTerrain->release();
   
   m_pScene3D->clear();

   this->getScene()->clear();
}

void CGameClient3D::mouseDown(const OIS::MouseEvent &evt)
{
   if(evt.state.buttonDown(OIS::MB_Left)) {   
      int xPos = evt.state.X.abs;
      int yPos = evt.state.Y.abs;
      int width = evt.state.width;
      int height = evt.state.height;

      if(m_pWindowMan->isPressWindow(xPos, yPos) == false) {
         Ogre::Camera *pCamera = m_pRenderCore->getCamera();

         // 從camera到滑鼠點擊的X,Y座標為依據產生一條射線
         Ogre::Ray mouseRay = pCamera->getCameraToViewportRay(xPos / (float)width, yPos / (float)height);
         m_pRayQuery->setRay(mouseRay);

         // 尋找這條射線打到什麼3D物件
         Ogre::RaySceneQueryResult &result = m_pRayQuery->execute();
         Ogre::RaySceneQueryResult::iterator it = result.begin();
         while(it != result.end()) {
            std::string nodeName = (*it).movable->getName();
            if(nodeName.find("ETTerrain") != std::string::npos) {
               // 滑鼠點到地板

               Ogre::Vector3 newPos;
               m_pTerrain->getRayPos(mouseRay, newPos);
               m_pScene3D->getMainPlayer3D()->setMouseTargetPosition(newPos);
               break;
            }

            it++;
         }
      }
   }
}

void CGameClient3D::mouseMove(const OIS::MouseEvent &evt)
{
   // 滑鼠右鍵按著不放
   if(evt.state.buttonDown(OIS::MB_Right)) { 
      int xPos = evt.state.X.abs;
      int yPos = evt.state.Y.abs;
      if(m_pWindowMan->isPressWindow(xPos, yPos) == false) {
         /** 改變Y軸旋轉方向
           * evt.state.X 為滑鼠移動的X變動量 */
         Ogre::Real dx = (float)evt.state.X.rel;

         /** 改變X軸旋轉方向
           * evt.state.Y 為滑鼠移動的Y變動量 */
         Ogre::Real dy = (float)evt.state.Y.rel;

         if(abs(dx) > abs(dy)) {
            // 若X座標變動量大於Y座標變動量, 便以X座標變動量為準

            /** 以主角為中心點旋轉Y軸 (視角水平旋轉)
              * 滑鼠往左移動, 攝影機以主角的Y軸為軸心向右旋轉
              * 滑鼠往右移動, 攝影機以主角的Y軸為軸心向左旋轉 */
            dx *= -1.0f;

            m_pCameraPivot->yaw(Ogre::Degree(dx), Ogre::Node::TS_WORLD);  
         }
         else {
            // 若Y座標變動量大於X座標變動量, 便以Y座標變動量為準

            /** tanθ = y / x, 求θ角度可以知道翻轉到角色腳下最大角度(與地板的角度)
              * 用途: 攝影機向下翻轉時卡到地板就不再翻轉, 免得鏡頭會轉到底板底下 */
            Ogre::Real x = m_pCameraGoal->_getDerivedPosition().distance(m_pCameraPivot->_getDerivedPosition());
            Ogre::Real y = abs(m_pCameraGoal->_getDerivedPosition().y);
            Ogre::Real withGroundRadian = atan(y / x);  // θ = tan-1(y / x)算出的是弧度
            Ogre::Real withGroundDegree = withGroundRadian * 180 / Ogre::Math::PI;  // 角度=弧度*180/PI;

            /** 以主角為中心點旋轉X軸, 限制最大俯視角度為70度與仰視角度為withGroundDegree度 (視角垂直旋轉)
              * 滑鼠往下移動, 攝影機以主角的X軸為軸心向上翻轉到角色頭頂
              * 滑鼠往上移動, 攝影機以主角的X軸為軸心向下翻轉到角色腳下 */
            dy *= -1.0f;

            if(!(m_fPivotPitch + dy < -60 && dy < 0) &&              // 限制翻轉到頭頂的角度最大60度
               !(m_fPivotPitch + dy > withGroundDegree && dy > 0)) { // 限制翻轉到腳底的角度
                  m_pCameraPivot->pitch(Ogre::Degree(dy));
                  m_fPivotPitch += dy;
            }
         }
      }
   }

   // 滑鼠滾輪滾動時, Z值不會為0
   if(evt.state.Z.rel != 0) { 
      // 計算攝影機目標點與角色的距離
      Ogre::Real dist = m_pCameraGoal->_getDerivedPosition().distance(m_pCameraPivot->_getDerivedPosition());

      /** 計算滑鼠滾輪的滾動量
        * 由於滑鼠滾輪滾動一格是120點, 這個滾動數值對遊戲來說實在太大所以除2000後再做計算
        * 往前滾動 Z 是正值, 往後滾動 Z 是負值
        * 滑鼠滾輪向下滾時, 鏡頭為縮小
        * 滑鼠滾輪向上滾時, 鏡頭為放大 */
      Ogre::Real distChange = ((float)evt.state.Z.rel / 2000.0f) * dist;
      distChange *= -1.0f;

	   // 限制放大/縮小的距離
      if(!(dist + distChange < 8  && distChange < 0) &&  // 放大限制距離
         !(dist + distChange > 40 && distChange > 0))    // 縮小限制距離
         m_pCameraGoal->translate(0, 0, distChange, Ogre::Node::TS_LOCAL);
   }
}

void CGameClient3D::mouseUp(const OIS::MouseEvent &evt)
{
}

void CGameClient3D::setupCamera(Ogre::Camera *pCamera, const Ogre::Vector3 &pos)
{
   // 建立一個在角色身上的節點, 高度約在角色肩膀位置
   m_pCameraPivot = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
   m_pCameraPivot->setPosition(pos + Ogre::Vector3::UNIT_Y * 5);

   /** 建立一個攝影機的目標節點, 攝影機會對應到此節點,
     * 而這個節點的位置會距離角色節點Z方向10的距離上 */
   m_pCameraGoal = m_pCameraPivot->createChildSceneNode(Ogre::Vector3(0, 0, 10));

   /** 建立攝影機節點, 攝影機會綁在此節點上.
     * 而這個節點的位置會在角色後方10的距離上 */
   m_pCameraNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
   m_pCameraNode->setPosition(m_pCameraPivot->getPosition() - m_pCameraGoal->getPosition());
   m_pCameraNode->attachObject(pCamera);

   m_pCameraPivot->setFixedYawAxis(true);
   m_pCameraGoal->setFixedYawAxis(true);
	m_pCameraNode->setFixedYawAxis(true);

   // 攝影機看著角色節點的位置
   m_pCameraNode->lookAt(m_pCameraPivot->getPosition(), Ogre::Node::TS_WORLD);
}

void CGameClient3D::updateCamera(float timeSinceLastFrame, const Ogre::Vector3 &pos)
{
   /** 取得角色最新的位置點套用至m_pCameraPivot節點上
     * m_pCameraPivot移動時, m_pCameraGoal也會跟著一起移動 */
   m_pCameraPivot->setPosition(pos + Ogre::Vector3::UNIT_Y * 5.0f);

   // 計算攝影機目標點與攝影機節點的差距距離
   Ogre::Vector3 offset = m_pCameraGoal->_getDerivedPosition() - m_pCameraNode->getPosition();

   // 依據差距距離移動攝影機
   m_pCameraNode->translate(offset);

   // 攝影機看著角色位置
   m_pCameraNode->lookAt(m_pCameraPivot->getPosition(), Ogre::Node::TS_WORLD);
}

void CGameClient3D::releaseCamera()
{
   m_pCameraGoal->detachAllObjects();
   m_pSceneManager->getRootSceneNode()->removeChild(m_pCameraGoal);
   m_pCameraGoal = NULL;

   m_pCameraPivot->detachAllObjects();
   m_pSceneManager->getRootSceneNode()->removeChild(m_pCameraPivot);
   m_pCameraPivot = NULL;

   m_pCameraNode->detachAllObjects();
   m_pSceneManager->getRootSceneNode()->removeChild(m_pCameraNode);
   m_pCameraNode = NULL;
}