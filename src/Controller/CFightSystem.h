/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CFightSystem.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/28 */
#ifndef _CFIGHTSYSTEM_H_
#define _CFIGHTSYSTEM_H_
#include "CSkill.h"
#include "IFightEventListener.h"

class CUnitObject;

/** @brief 提供戰鬥的流程與連續技使用
  *        戰鬥過程會控制動作系統 */
class CFightSystem
{
   public:
      CFightSystem();

      void init(std::string machineName, long long uid);
      void useSkill(CSkill *pSkill);
      bool isCastSkill();
      void setUID(long long uid);

      void addFightEventListener(IFightEventListener *pListener);
      void removeFightEventListener(IFightEventListener *pListener);

      /** @brief 邏輯動作
        * @param timePass 一個frame幾秒
        * @param pSelfObject   自己
        * @param pTargetObject 目標物 */
      void work(float timePass, CUnitObject *pSelfObject, CUnitObject *pTargetObject);

   private:
      void notifyActionEventUpdate(CUnitObject *pSelfObject, CActionEvent *pActEvent);
      void notifyTargetPositionUpdate(CUnitObject *pSelfObject);
      void notifyTargetDeadUpdate(CUnitObject *pSelfObject, CUnitObject *pTargetObject);

      std::string    m_machineName;   // 機器名稱 (用來識別是不同機器, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      long long      m_uid;           // 玩家、怪物、NPC的唯一編號
      CSkill        *m_pUseSkill;
      int            m_castSkillID;   // 目前施展技能的ID
      bool           m_bFightState;

      std::set<IFightEventListener *>  m_fightEventListeners;    // 監聽戰鬥系統事件的監聽者列表
};

#endif  // #ifndef _CFIGHTSYSTEM_H_