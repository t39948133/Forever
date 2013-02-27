/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameServer.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/24 */
#ifndef _CGAMESERVER_H_
#define _CGAMESERVER_H_
#include "CScene.h"
#include "CFPS.h"
#include "CNetPlayer.h"
#include "CMonsterMap.h"
#include "CPacketFirstLogin.h"
#include "CPacketPlayerDataWG.h"
#include "CPacketTargetPos.h"
#include "CPacketUseItem.h"
#include "CPacketEquipData.h"
#include "CPacketCanUseSkill.h"
#include "CPacketCancelUseSkill.h"
#include "CPacketBuyItem.h"
#include "CPacketTargetObject.h"
#include "CPacketKeyActionEvent.h"
#include "IMonsterAIEventListener.h"
#include "ISceneMonsterEventListener.h"
#include "IPlayerBackpackEventListener.h"
#include "IPlayerEquipEventListener.h"
#include "IAdvAttrEventListener.h"
#include "ISkillEventListener.h"
#include "IFightEventListener.h"
#include "IDeadEventListener.h"
#include "IPlayerAttrEventListener.h"

#include <network\gp_socket.h>

class CGameServer : public CScene,
                    public IMonsterAIEventListener,
                    public ISceneMonsterEventListener,
                    public IPlayerBackpackEventListener,
                    public IPlayerEquipEventListener,
                    public IAdvAttrEventListener,
                    public ISkillEventListener,
                    public IFightEventListener,
                    public IDeadEventListener,
                    public IPlayerAttrEventListener
{
   public:
      CGameServer(std::string machineName);
      ~CGameServer();

      /** @brief 初始化
        * @param port 此台伺服器的listen port */
      void init(int port);

      /** @brief 邏輯更新
        * @param hWnd 主視窗 
        * @param timePass 一個frame幾秒 */
      void work(HWND hWnd, float timePass);

      long long generateUID();

#ifdef _GAMEENGINE_2D_
      /** @brief 2D繪圖
        * @param hDC 繪圖區 */
      void draw(HDC hdc);
#endif  // #ifdef _GAMEENGINE_2D_

   private:
      // IMonsterAIEventListener
      /* virtual */ void updateMonsterTargetObject(CMonster *pMonster, long long newTargetObjectUID);
      /* virtual */ void updateMonsterAI(CMonster *pMonster);

      // ISceneMonsterEventListener
      /* virtual */ void updateAddMonster(CMonster *pMonster);

      // IPlayerBackpackEventListener
      /* virtual */ void updatePlayerBackpack(CBackpack *pBackpack);

      // IPlayerEquipEventListener
      /* virtual */ void updatePlayerEquip(CPlayer *pPlayer, EquipSlot equipSlot, int itemId);

      // IAdvAttrEventListener
      /* virtual */ void updateAdvAttr(CUnitObject *pUnitObject);

      // ISkillEventListener
      /* virtual */ void updateAddSkill(CUnitObject *pUnitObject, int skillID);
      /* virtual */ void updateSkillAvailable(CSkill *pSkill);
      /* virtual */ void updateSkillCoolDown(CSkill *pSkill);

      // IFightEventListener
      /* virtual */ void updateFightActionEvent(CUnitObject *pUnitObject, CActionEvent *pActEvent);
      /* virtual */ void updateFightTargetPosition(CUnitObject *pUnitObject);
      /* virtual */ void updateFightTargetDead(CUnitObject *pUnitObject, CUnitObject *pTargetObject);

      // IDeadEventListener
      /* virtual */ void updateDead(long long uid);

      // IPlayerAttrEventListener
      /* virtual */ void updatePlayerAttr(CPlayer *pPlayer, unsigned int offsetXP, long long offsetMoney);

      void doMonsterAIIdle(CMonster *pMonster);
      void doMonsterAIGoals(CMonster *pMonster);
      void doMonsterAIDolly(CMonster *pMonster);
      void doMonsterAIReturn(CMonster *pMonster);
      void doMonsterAIAttack(CMonster *pMonster);

      /** @brief 怪物移動 */
      void moveMonster(CMonster *pMonster, float x, float y);

      /** @brief 處理與Client之間的網路連線 */
      void procAccept();

      /** @brief 處理與WorldServer之間的網路連線 */
      void procWorldServer();

      /** @brief 處理與Client之間的封包 */
      void procNetPlayer(CNetPlayer *pNetPlayer);

      CNetPlayer* getNetPlayer(long long netID);

      void sendPlayerDataToOtherClient(CNetPlayer *pNetPlayer);
      void sendNearPlayerToClient(CNetPlayer *pNetPlayer);
      void sendNearMonsterToClient(CNetPlayer *pNetPlayer);
		void sendNearNPCToClient(CNetPlayer *pNetPlayer);

      /** @brief 將pNetPlayer的資料送給其他Client */
      void sendPacket(CNetPlayer *pNetPlayer, void *pPacket, int packetSize);

      /** @brief 接收Client第一次登入
        * @param pNetPlayer Client端玩家
        * @param pPacket    封包 */
      void onRecvFirstLogin(CNetPlayer *pNetPlayer, CPacketFirstLogin *pPacket);

      /** @brief 接收玩家資料(World Server傳過來)
        * @param pPacket    封包 */
      void onRecvPlayerDataWG(CPacketPlayerDataWG *pPacket);

      /** @brief 接收玩家目標位置 */
      void onRecvTargetPos(CNetPlayer *pNetPlayer, CPacketTargetPos *pPacket);

      /** @brief 接收玩家使用物品 */
      void onRecvUseItem(CNetPlayer *pNetPlayer, CPacketUseItem *pPacket);

      /** @brief 接收卸下裝備 */
      void onRecvShedEquip(CNetPlayer *pNetPlayer, CPacketEquipData *pPacket);

      /** @brief 接收能不能使用技能 */
      void onRecvCanUseSkill(CNetPlayer *pNetPlayer, CPacketCanUseSkill *pPacket);

      /** @brief 接收取消使用技能 */
      void onRecvCancelUseSkill(CNetPlayer *pNetPlayer, CPacketCancelUseSkill *pPacket);

      /** @brief 接收買物品 */
      void onRecvBuyItem(CNetPlayer *pNetPlayer, CPacketBuyItem *pPacket);

      /** @brief 接收玩家的目標物 */
      void onRecvTargetObject(CNetPlayer *pNetPlayer, CPacketTargetObject *pPacket);

      /** @brief 接收按鍵動作訊息 */
      void onRecvKeyActionEvent(CNetPlayer *pNetPlayer, CPacketKeyActionEvent *pPacket);

      std::string              m_machineName;     // 機器名稱 (用來識別是不同機器, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      int                      m_port;
      long long                m_curUID;
      long long                m_curNetID;
      GP::NetListener          m_listener;
      GP::NetStream           *m_pWorldStream;    // World Server的網路連線
      std::list<CNetPlayer *> *m_pNetPlayerList;  // 此場景的所有網路玩家
      CMonsterMap              m_monsterMap;
};

#endif  // #ifndef _CGAMESERVER_H_