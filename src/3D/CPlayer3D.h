/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPlayer3D.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#ifndef _CPLAYER3D_H_
#define _CPLAYER3D_H_
#include "Common.h"
#include "CGraphicsRender.h"
#include "CPlayer.h"
#include "CObjectTitle.h"
#include "CTerrain.h"
#include "IKeyEventListener.h"
#include "IPlayerEquipEventListener.h"
#include "IDrawWeaponNotifyListener.h"
#include "IPutinWeaponNotifyListener.h"

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreAnimationState.h>

#include <network\gp_socket.h>

class CPlayer3D : public IKeyEventListener,
                  public IPlayerEquipEventListener,
                  public IDrawWeaponNotifyListener,
                  public IPutinWeaponNotifyListener
{
   public:
      CPlayer3D(CPlayer *pPlayer, Ogre::SceneManager *pSceneManager, GP::NetStream *pNetStream, CTerrain &terrain);
      ~CPlayer3D();

      /** @brief 設定模型 */
      void setup();

      /** @brief 更新模型邏輯運算
        * @param timeSinceLastFrame 1Frame是幾秒
        * @param pCameraNode        以攝影機的位置/方向為基準來運算 */
      void update(float timeSinceLastFrame, Ogre::SceneNode *pCameraNode);

      /** @brief 釋放模型 */
      void release();

      /** @brief 取得座標位置
        * @return 3D座標位置 */
      const Ogre::Vector3& getPosition();
      
      /** @brief 設定滑鼠目標點位置
        * @param targetPos 目標點位置 */
      void setMouseTargetPosition(Ogre::Vector3 &targetPos);

      CPlayer* getPlayer2D();

      void setUID(long long uid);

      void setMainPlayer(bool bMainPlayer);

   private:
      friend class CPacketPlayerInit;
      friend class CPacketPlayerData;
      friend class CPacketEquipData;
      friend class CPacketPlayerDeadReset;

      void setPosition(float x, float y, float z);
      void setDirection(float direction);

      /** @brief 切換成哪個動作
        * @param animationName 動作名稱 */
      void setAnimation(std::string animationName);

      /** @brief 播放動作
        * @param timeSinceLastFrame 1個Frame經過幾秒 */
      void playAnimation(float timeSinceLastFrame);

      /** @brief 安裝動作
        * @param skeletonFile 動作檔 */
      void setupSkeleton(std::string skeletonFile);

      /** @brief 安裝/卸下裝備
        * @param pBaseEntity  角色那個部位模型
        * @param pSlotEntity  哪個裝備槽模型
        * @param itemId       新裝備代碼
        * @return 安裝或卸下的模型 */
      Ogre::Entity* setupArmor(Ogre::Entity *pBaseEntity, Ogre::Entity *pSlotEntity, int itemId);

      // IKeyEventListener
      /* virtual */ void keyDown(const OIS::KeyEvent &evt);
      /* virtual */ void keyUp(const OIS::KeyEvent &evt);

      // IPlayerEquipEventListener
      /* virtual */ void updatePlayerEquip(CPlayer *pPlayer, EquipSlot equipSlot, int itemId);

      // IDrawWeaponNotifyListener
      /* virtual */ void notifyDrawWeapon();

      // IPutinWeaponNotifyListener
      /* virtual */ void notifyPutinWeapon();

      std::vector<Ogre::AnimationState *> *m_pvtAnimationSet;  // 當前角色的動畫集合(所有模型)

      // Title
      CObjectTitle        m_nameOverlay;      // 顯示於3D的角色名稱

      // 攝影機控制相關參數
      Ogre::Vector3       m_mouseDirection;   // 滑鼠移動方向與偏移量
      Ogre::Vector3       m_keyDirection;     // 鍵盤移動方向與偏移量
      Ogre::Vector3       m_goalDirection;    // 目標方向

      // 3D模型相關參數
      std::string         m_mainHandBoneName;     // 主手武器放在那個骨頭的名稱
      std::string         m_offHandBoneName;      // 副手武器放在那個骨頭的名稱
      Ogre::Entity       *m_pHairEntity;          // 頭髮模型 (基本模型)
      Ogre::Entity       *m_pHeadEntity;          // 臉部模型 (基本模型)
      Ogre::Entity       *m_pBodyEntity;          // 身體模型 (基本模型)
      Ogre::Entity       *m_pFootEntity;          // 腳模型 (基本模型)
      Ogre::Entity       *m_pHandEntity;          // 手模型 (基本模型)
      Ogre::Entity       *m_pLegEntity;           // 腿模型 (基本模型)
      Ogre::Entity       *m_pMainHandSlotEntity;  // 主手槽模型
      Ogre::Entity       *m_pOffHandSlotEntity;   // 副手槽模型
      Ogre::Entity       *m_pChestSlotEntity;     // 上衣槽模型
      Ogre::Entity       *m_pPantsSlotEntity;     // 褲子槽模型
      Ogre::Entity       *m_pGloveSlotEntity;     // 手套槽模型
      Ogre::Entity       *m_pBootSlotEntity;      // 鞋子槽模型
      Ogre::Entity       *m_pShoulderSlotEntity;  // 肩甲槽模型
      Ogre::SceneNode    *m_pPlayerNode;          // 角色節點
      Ogre::SceneManager *m_pSceneManager;        // 場景管理員
      CGraphicsRender    *m_pRenderCore;          // 繪圖引擎

      GP::NetStream      *m_pNetStream;
      CTerrain           &m_terrain;              // 3D地形
      Ogre::Vector3       m_terrainHeight;        // 3D地形高度
      bool                m_bMainPlayer;          // 是主角嗎?
      CPlayer            *m_pPlayer2D;            // 玩家

      static unsigned int m_iPlayerCount;
};

#endif // #ifndef _CPLAYER3D_H_