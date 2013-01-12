/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameClient3D.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/04 */
#ifndef _CGAMECLIENT3D_H_
#define _CGAMECLIENT3D_H_
#include "CGraphicsRender.h"
#include "CRenderLoader.h"
#include "CPlayer3D.h"
#include "CTerrain.h"
#include "CGameClient.h"
#include "CWindowMan3D.h"

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreSceneQuery.h>

class CGameClient3D : public IGameFlowListener,
                      public IMouseEventListener,
                      public CGameClient
{
   public:
      CGameClient3D();
      ~CGameClient3D();

      void run();

   protected:
      // CGameClient
      /* virtual */ void initUI();

   private:
      // IGameFlowListener
      /* virtual */ void createScene();
      /* virtual */ bool frameRenderingQueued(float timeSinceLastFrame);
      /* virtual */ void destoryScene();

      // IMouseEventListener
      /* virtual */ void mouseDown(const OIS::MouseEvent &evt);
      /* virtual */ void mouseMove(const OIS::MouseEvent &evt);
      /* virtual */ void mouseUp(const OIS::MouseEvent &evt);

      /** @brief 設定攝影機
        * @param pCamera 攝影機
        * @param pos     依據某個座標來設定攝影機 */
      void setupCamera(Ogre::Camera *pCamera, const Ogre::Vector3 &pos);

      /** @brief 更新攝影機控制 
        * @param timeSinceLastFrame 一個frame幾秒
        * @param pos                依據某個座標來設定攝影機 */
      void updateCamera(float timeSinceLastFrame, const Ogre::Vector3 &pos);

      /** @brief 釋放攝影機 */
      void releaseCamera();

      CWindowMan3D        *m_pWindowMan;     // UI視窗管理

      CPlayer3D           *m_pPlayer;        // 玩家操控
      CTerrain            *m_pTerrain;       // 3D地形
      Ogre::RaySceneQuery *m_pRayQuery;      // 場景射線的詢問物件

      float                m_fPivotPitch;    // 目前仰視角度(正值)與俯視角度(負值)

      Ogre::SceneNode     *m_pCameraPivot;   // 角色身上的Node (高度約在肩膀上)
      Ogre::SceneNode     *m_pCameraGoal;    // 攝影機的目的點, 距離m_pCameraPivot的後面10的地方 (角色背後10的距離)
      Ogre::SceneNode     *m_pCameraNode;    // 攝影機真正所在, 會跟著m_pCameraGoal來移動

      Ogre::SceneManager  *m_pSceneManager;  // Ogre scene manager
      CGraphicsRender     *m_pRenderCore;    // 繪圖引擎
};

#endif // #ifndef _CGAMECLIENT3D_H_