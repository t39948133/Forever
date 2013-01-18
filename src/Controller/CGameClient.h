/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameClient.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#ifndef _CGAMECLIENT_H_
#define _CGAMECLIENT_H_
#include "CScene.h"
//#include "CPacketFirstLogin.h"
//#include "CPacketChangeScene.h"
//#include "CPacketChangeSceneLogin.h"
//#include "CPacketPlayerInit.h"

//#include <network\gp_socket.h>

#ifdef _GAMEENGINE_2D_
#include "CFPS.h"
#include "CKeyMan.h"
#include "CWindowMan.h"
#include "CTargetInfoWnd.h"
#endif  // #ifdef _GAMEENGINE_2D_

//typedef enum tagGAME_STATE {
//   STATE_LOGIN,              // 第一次登入
//   STATE_CHANGESCENE_LOGIN,  // 場景切換登入
//   STATE_PLAY                // 開始玩
//} CLIENT_STATE;  // 遊戲狀態

/** @brief Client端遊戲流程控制 */
class CGameClient
{
   public:
      CGameClient();
      ~CGameClient();

      /** @brief Client端初始化 */
      void init();

#ifdef _GAMEENGINE_2D_
      /** @brief Client端邏輯運算 
        *        至少每秒執行30次, 最好能夠維持在60次
        * @param hWnd Client端視窗 */
      void work(HWND hWnd);
#elif _GAMEENGINE_3D_
      /** @brief Client端邏輯運算 
        *        至少每秒執行30次, 最好能夠維持在60次
        * @param timePass 一個frame幾秒
        * @param hWnd     Client端視窗 */
      void work(float timePass, HWND hWnd);
#endif

#ifdef _GAMEENGINE_2D_
      /** @brief Client端繪圖動作 
        * @param hdc 繪圖裝置 */
      void draw(HDC hdc);
#endif  // #ifdef _GAMEENGINE_2D_

   protected:
      /** @brief 取得場景
        * @return 場景 */
      CScene* getScene();

      /** @brief UI初始化 */
      virtual void initUI();

   private:
      /** @brief 遊戲第一次登入的邏輯運算 */
      //void workLogin();

      /** @brief 遊戲切換場景的登入邏輯運算
        * @param hWnd Client端視窗 */
      //void workChangeSceneLogin();

      /** @brief 遊戲開始玩的邏輯運算
        * @param timePass 一個frame幾秒
        * @param hWnd     Client端視窗 */
      void workPlay(float timePass, HWND hWnd);

      /** @brief 切換遊戲場景
        * @param pNetStream 舊server連線
        * @param pPacket    封包 */
      //void onRecvChangeScene(GP::NetStream *pNetStream, CPacketChangeScene *pPacket);

      /** @brief 玩家初始化
        * @param pNetStream server連線
        * @param pPacket    封包 */
      //void onRecvPlayerInit(GP::NetStream *pNetStream, CPacketPlayerInit *pPacket);

      CScene        *m_pScene;          // 遊戲場景管理
      //CLIENT_STATE   m_gameState;       // 遊戲狀態
      //GP::NetStream *m_pNetStream;      // 對server的網路連線 (WorldServer或SceneServer)
      //bool           m_bSendLogin;
      //long long      m_mainPlayerNetID; // 玩家的網路編號

#ifdef _GAMEENGINE_2D_
      void doKeyControl();              // 按鍵控制
      void doUI(HWND hWnd);

      CFPS            m_fps;             // FPS產生器
      CKeyMan         m_keyMan;          // 鍵盤/滑鼠監控管理員
      CWindowMan     *m_pWindowMan;      // 視窗管理員
      CTargetInfoWnd *m_pTargetInfoWnd;  // 目標視窗
      bool            m_mouseMove;
      bool            m_keyMove;
#endif  // #ifdef _GAMEENGINE_2D_
};

#endif  // #ifndef _CGAMECLIENT_H_