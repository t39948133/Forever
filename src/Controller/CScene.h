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

/** @brief 場景管理
  *        管理這個場景內有哪些玩家 */
class CScene
{
   public:
      CScene();
      ~CScene();

      /** @brief 新增玩家
        * @param  uid 玩家編號
        * @return 玩家物件 */
      CPlayer* addPlayer(long long uid, bool bMainPlayer = false);

      /** @brief 刪除玩家
        * @param uid 玩家編號 */
      void removePlayer(long long uid);

      /** @brief 刪除所有東西 */
      void removeAll();

      void loadScene(SCENE_TYPE scene);

      /** @brief 取得玩家 */
      CPlayer* getMainPlayer();

      /** @brief 邏輯動作
        * @param timePass 一個frame幾秒 */
      void work(float timePass);

#ifdef _GAMEENGINE_2D_
      void draw(HDC hdc);
#endif  // #ifdef _GAMEENGINE_2D_

   private:
      std::list<CPlayer *> *m_pvtPlayer;   // 場景內的所有玩家
      CPlayer              *m_pMainPlayer; // 玩家
      SCENE_TYPE            m_scene;       // 那個場景
};

#endif  // #ifndef _CSCENE_H_