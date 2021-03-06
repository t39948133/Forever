#ifndef _CNPC3D_H_
#define _CNPC3D_H_

#include "Common.h"
#include "CGraphicsRender.h"
#include "CNPC.h"
#include "CObjectTitle.h"
#include "CTerrain.h"

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreAnimationState.h>

#include <network\gp_socket.h>

class CNPC3D
{
public:
	CNPC3D(CNPC *pNPC, Ogre::SceneManager *pSceneManager, CTerrain &terrain);
	~CNPC3D();

	/** @brief 設定模型 */
	void	setup();

   /** @brief 更新模型邏輯運算
	  * @param timeSinceLastFrame 1Frame是幾秒 */
   void update(float timeSinceLastFrame, Ogre::SceneNode *pCameraNode);

   /** @brief 釋放模型 */
   void release();

   /** @brief 取得座標位置
     * @return 3D座標位置 */
   const Ogre::Vector3& getPosition();

   CNPC* getNPC2D();

   void setUID(long long uid);
private:
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

   std::vector<Ogre::AnimationState *> *m_pvtAnimationSet;  // 當前角色的動畫集合(所有模型)

   // Title
   CObjectTitle        m_nameOverlay;      // 顯示於3D的角色名稱

   Ogre::Vector3       m_mouseDirection;   // 滑鼠移動方向與偏移量
   Ogre::Vector3       m_goalDirection;    // 目標方向

   std::string         m_meshName;         // 模型名稱, 沒有附檔名
   Ogre::Entity       *m_pBodyEntity;      // 身體模型 (基本模型)
   Ogre::SceneNode    *m_pNPCNode;         // 角色節點
   CTerrain           &m_terrain;          // 3D地形
   Ogre::Vector3       m_terrainHeight;    // 3D地形高度
   Ogre::SceneManager *m_pSceneManager;    // 場景管理員
   CGraphicsRender    *m_pRenderCore;      // 繪圖引擎

   CNPC					 *m_pNPC2D;           // NPC

   static unsigned int m_iNPCCount;
};

#endif	//#ifndef _CNPC3D_H_