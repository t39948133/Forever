/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CFightSystem.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/28 */
#include "CFightSystem.h"
#include "CAction.h"
#include "CActionDispatch.h"
#include "CCastSkillActionEvent.h"

CFightSystem::CFightSystem(long long uid) : m_uid(uid),
                                            m_pUseSkill(NULL)
{
}

void CFightSystem::useSkill(CSkill *pSkill)
{
   m_pUseSkill = pSkill;
}

void CFightSystem::work(float timePass, CUnitObject *pSelfObject, CUnitObject *pTargetObject)
{
   if(m_pUseSkill != NULL) {
      if(pSelfObject->canUseSkill(m_pUseSkill->getID()) == true) {
         CAction *pSelfCurAction = pSelfObject->getCurAction();

         if(pSelfCurAction->getID() == ACTION_IDLE) {  // 等待

            // 發送施展技能訊息切換動作 (等待->拔出武器->戰鬥姿態)
            CCastSkillActionEvent actEvent;
            actEvent.m_event = AET_CAST_SKILL;
            CActionDispatch::getInstance()->sendEvnet(m_uid, actEvent);
         }
         else if(pSelfCurAction->getID() == ACTION_RUN) {  // 跑步

            
         }
         else if(pSelfCurAction->getID() == ACTION_FIGHT) {  // 戰鬥姿態
            // 判斷距離，距離太遠要切換跑步動作且人物要移動

            // 判斷施法時間，是否要切換吟唱動作

            // 發送施展技能訊息切換動作
            CCastSkillActionEvent actEvent;
            actEvent.m_event = AET_CAST_SKILL;
            actEvent.m_bCastSkill = true;
            actEvent.m_iCastSkillID = m_pUseSkill->getID();
            //actEvent.m_fCastSkillTime = m_pUseSkill->getInfo()->getCastTime();
            CActionDispatch::getInstance()->sendEvnet(m_uid, actEvent);

            // 扣血計算

            // 判斷有無連續技，有的話要通知UI

            m_pUseSkill = NULL;
         }
      }
   }
}