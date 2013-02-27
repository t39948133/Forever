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
#include "CPacketPlayerInit.h"
#include "CPacketPlayerData.h"
#include "CPacketTargetPos.h"
#include "CPacketMonsterData.h"
#include "CPacketTargetObject.h"
#include "CPacketActionEvent.h"
#include "CPacketUseSkill.h"
#include "CPacketBackpackData.h"
#include "CPacketEquipData.h"
#include "CPacketAdvAttrData.h"
#include "CPacketAddSkill.h"
#include "CPacketCanUseSkill.h"
#include "CPacketDead.h"
#include "CPacketPlayerDeadReset.h"
#include "CPacketNPCData.h"
#include "CPacketMoney.h"
#include "CPacketXP.h"
#include "CPacketCancelUseSkill.h"
#include "CPacketKeyActionEvent.h"

#include <network\gp_socket.h>

#ifdef _GAMEENGINE_2D_
#include "CFPS.h"
#include "CKeyMan.h"
#include "CWindowMan.h"
#include "CTargetInfoWnd.h"
#endif  // #ifdef _GAMEENGINE_2D_

/** @brief Client端遊戲流程控制 */
class CGameClient
{
   public:
      enum {STATE_LOGIN,         // 第一次登入
            STATE_CHANGE_LOGIN,  // 場景切換登入
            STATE_PLAY};         // 開始玩

      CGameClient(std::string machineName);
      ~CGameClient();

      /** @brief Client端初始化 */
      void init();
      
      std::string getMachineName();

#ifdef _GAMEENGINE_2D_
      /** @brief Client端邏輯運算 
        *        至少每秒執行30次, 最好能夠維持在60次
        * @param hWnd     Client端視窗
        * @param timePass 一個frame幾秒
        * @param bActive  正在顯示的視窗 */
      void work(HWND hWnd, float timePass, bool bActive);
#elif _GAMEENGINE_3D_
      /** @brief Client端邏輯運算 
        *        至少每秒執行30次, 最好能夠維持在60次
        * @param hWnd     Client端視窗
        * @param timePass 一個frame幾秒 */
      void work(HWND hWnd, float timePass);
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

      GP::NetStream* getNetStream();

      /** @brief UI初始化 */
      virtual void initUI();

      /** @brief 玩家初始化資料
        * @param pPacket    封包 */
      virtual void onRecvPlayerInit(CPacketPlayerInit *pPacket);

      /** @brief 接收其他玩家資料
        * @param pPacket 封包 */
      virtual void onRecvPlayerData(CPacketPlayerData *pPacket);

      /** @brief 接收怪物資料
        * @param pPacket 封包 */
      virtual void onRecvMonsterData(CPacketMonsterData *pPacket);

      /** @brief 接收更換裝備資料 */
      virtual void onRecvEquipData(CPacketEquipData *pPacket);

      /** @brief 接收死亡資料 */
      virtual void onRecvDead(CPacketDead *pPacket);

      /** @brief 接收玩家死亡後重生 */
      virtual void onRecvPlayerDeadReset(CPacketPlayerDeadReset *pPacket);

      virtual void onRecvNPCData(CPacketNPCData *pPacket);

   private:
      /** @brief 遊戲第一次登入的邏輯運算 */
      void workLogin();

      /** @brief 遊戲開始玩的邏輯運算
        * @param hWnd     Client端視窗 
        * @param timePass 一個frame幾秒 */
      void workPlay(HWND hWnd, float timePass);
      
      /** @brief 接收目標物的位置 */
      void onRecvTargetPos(CPacketTargetPos *pPacket);

      /** @brief 接收鎖定哪個目標物 */
      void onRecvTargetObject(CPacketTargetObject *pPacket);

      /** @brief 接收要發出什麼動作訊息 */
      void onRecvActionEvent(CPacketActionEvent *pPacket);

      /** @brief 接收使用哪個技能 */
      void onRecvUseSkill(CPacketUseSkill *pPacket);

      /** @brief 接收背包資料 */
      void onRecvBackpackData(CPacketBackpackData *pPacket);

      /** @brief 接收進階屬性資料 */
      void onRecvAdvAttrData(CPacketAdvAttrData *pPacket);

      /** @brief 接收學習技能 */
      void onRecvAddSkill(CPacketAddSkill *pPacket);

      /** @brief 接收可以使用技能(Server回覆) */
      void onRecvCanUseSkill(CPacketCanUseSkill *pPacket);

      /** @brief 接收錢資料 */
      void onRecvMoney(CPacketMoney *pPacket);

      /** @brief 接收經驗值資料 */
      void onRecvXP(CPacketXP *pPacket);

      /** @brief 接收取消使用技能 */
      void onRecvCancelUseSkill(CPacketCancelUseSkill *pPacket);

      /** @brief 接收按鍵動作系統訊息 */
      void onRecvKeyActionEvent(CPacketKeyActionEvent *pPacket);

      std::string    m_machineName;     // 機器名稱 (用來識別是不同機器, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      CScene        *m_pScene;          // 遊戲場景管理
      GP::NetStream *m_pNetStream;      // 對Game Server的網路連線
      int            m_gameState;       // 遊戲狀態
      bool           m_bSendLogin;

#ifdef _GAMEENGINE_2D_
      void doKeyControl();              // 按鍵控制
      void doUI(HWND hWnd);

      CKeyMan         m_keyMan;          // 鍵盤/滑鼠監控管理員
      CWindowMan     *m_pWindowMan;      // 視窗管理員
      CTargetInfoWnd *m_pTargetInfoWnd;  // 目標視窗
      bool            m_keyMove;
#endif  // #ifdef _GAMEENGINE_2D_
};

#endif  // #ifndef _CGAMECLIENT_H_