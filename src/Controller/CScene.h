/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CScene.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#ifndef _CSCENE_H_
#define _CSCENE_H_
#include "Common.h"
#include "CPlayer.h"
#include "CMonster.h"

/** @brief 場景管理
  *        管理這個場景內有哪些玩家 */
class CScene
{
   public:
      CScene();
      ~CScene();

      /** @brief 新增玩家
        * @param uid         唯一編號
        * @param bMainPlayer 是否為主角
        * @return 玩家物件 */
      CPlayer* addPlayer(long long uid, bool bMainPlayer = false);

      /** @brief 刪除玩家
        * @param uid 唯一編號 */
      void removePlayer(long long uid);

      /** @brief 新增怪物
        * @param uid    唯一編號
        * @param kindID 怪物種類編號
        * @param x      座標X
        * @param y      座標Y
        * @return 怪物物件 */
      CMonster* addMonster(long long uid, int kindID, float x, float y);

      /** @brief 刪除所有東西 */
      void removeAll();

      void loadScene(SCENE_TYPE scene);

      /** @brief 取得主角玩家 */
      CPlayer* getMainPlayer();

      /** @brief 取得玩家
        * @param uid 唯一編號
        * @return 玩家物件 */
      CPlayer* getPlayer(long long uid);

      /** @brief 取得怪物
        * @param uid 唯一編號
        * @return 怪物物件 */
      CMonster* getMonster(long long uid);

      /** @brief 取得作戰單位 (可能是玩家/怪物/NPC)
        * @param uid 唯一編號
        * @return 作戰單位物件 */
      CUnitObject* getUnitObject(long long uid);

      /** @brief 邏輯動作
        * @param timePass 一個frame幾秒 */
      void work(float timePass);

      std::list<CPlayer *>* getvtPlayer();

#ifdef _GAMEENGINE_2D_
      /** @brief 取得玩家
        * @param x 滑鼠點擊的X座標
        * @param y 滑鼠點擊的Y座標
        * @return 玩家物件 */
      CPlayer* getPlayer(float x, float y);

      /** @brief 取得怪物
        * @param x 滑鼠點擊的X座標
        * @param y 滑鼠點擊的Y座標
        * @return 怪物物件 */
      CMonster* getMonster(float x, float y);

      /** @brief 取得作戰單位
        * @param x 滑鼠點擊的X座標
        * @param y 滑鼠點擊的Y座標
        * @return 作戰單位物件 */
      CUnitObject* getUnitObject(float x, float y);

      void draw(HDC hdc);
#endif  // #ifdef _GAMEENGINE_2D_

   private:
      std::list<CPlayer *>  *m_pvtPlayer;   // 場景內所有玩家
      std::list<CMonster *> *m_pvtMonster;  // 場景內所有怪物
      CPlayer               *m_pMainPlayer; // 玩家
      SCENE_TYPE             m_scene;       // 那個場景
};

#endif  // #ifndef _CSCENE_H_