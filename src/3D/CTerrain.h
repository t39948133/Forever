/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CTerrain.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/28 */
#ifndef _CTERRAIN_H_
#define _CTERRAIN_H_
#include "Common.h"

#include <ETTerrainManager.h>
#include <ETTerrainInfo.h>
#include <ETBrush.h>
#include <ETSplattingManager.h>

#include <OgreStringConverter.h>
#include <OgreViewport.h>
#include <OgreTextureManager.h>
#include <OgreTexture.h>
#include <OgreCamera.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>

/** @brief 3D地形 */
class CTerrain
{
   public:
      CTerrain();
      ~CTerrain();

      /** @brief 初始化
        * @param pSceneManager 場景管理員
        * @param pCamera       攝影機 */
      void init(Ogre::SceneManager *pSceneManager, Ogre::Camera *pCamera);

      /** @brief 取得射線射到地形的位置座標
        * @param [in]  mouseRay 滑鼠點地板的射線
        * @param [out] pos      位置座標
        * @return true - 該射線是打到地板 / false - 該射線沒有打到地板 */
      bool getRayPos(Ogre::Ray &mouseRay, Ogre::Vector3 &pos);

      /** @brief 地形要塗什麼材質上色 (地形編輯器用)
        * @param mouseRay        滑鼠點地板的射線
        * @param iChoseTexture   用哪張材質上色
        * @param editBrush       用那個筆刷來塗
        * @param fBrushIntensity 筆刷的強度(用來決定新材質上色的深淺) */
      void paint(Ogre::Ray &mouseRay, int iChosenTexture, ET::Brush editBrush, float fBrushIntensity);

      /** @brief 地表拉高/降低 (地形編輯器用)
        * @param mouseRay        滑鼠點地板的射線
        * @param editBrush       用哪個筆刷來拉高/降低
        * @param fBrushIntensity 筆刷的強度(用來決定地表拉高/降低的深淺) */
      void deform(Ogre::Ray &mouseRay, ET::Brush editBrush, float fBrushIntensity);

      /** @brief 地表產生真實陰影 */
      void updateLightmap();

      /** @brief 儲存地表
        * @param id  那個場景 */
      void saveTerrain(int id);

      /** @brief 讀取地表
        * @param id  那個場景 */
      void loadTerrain(int id);

      /** @brief 記憶體釋放 */
      void release();

   private:
      ET::TerrainManager    *m_pTerrainMgr;
      ET::SplattingManager  *m_pSplatMgr;
	   const ET::TerrainInfo *m_pTerrainInfo;
};

#endif  // #ifndef _CTERRAIN_H_