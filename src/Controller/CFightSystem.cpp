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
#include "CUnitObject.h"
#include "CPlayer.h"
#include "CMonster.h"

CFightSystem::CFightSystem()
{
   m_pUseSkill = NULL;
}

void CFightSystem::init(std::string machineName, long long uid)
{
   m_machineName = machineName;
   m_uid = uid;
}

void CFightSystem::useSkill(CSkill *pSkill)
{
   m_pUseSkill = pSkill;
}

bool CFightSystem::isCastSkill()
{
   if(m_pUseSkill != NULL)
      return true;
   else
      return false;
}

void CFightSystem::setUID(long long uid)
{
   m_uid = uid;
}

void CFightSystem::addFightEventListener(IFightEventListener *pListener)
{
   std::set<IFightEventListener *>::iterator it = m_fightEventListeners.find(pListener);
   if(it == m_fightEventListeners.end())
      m_fightEventListeners.insert(pListener);
}

void CFightSystem::removeFightEventListener(IFightEventListener *pListener)
{
   std::set<IFightEventListener *>::iterator it = m_fightEventListeners.find(pListener);
   if(it != m_fightEventListeners.end())
      m_fightEventListeners.erase(it);
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
            CActionDispatch::getInstance()->sendEvnet(m_machineName, m_uid, actEvent);

            CPlayer *pPlayer = dynamic_cast<CPlayer *>(pSelfObject);
            if(pPlayer != NULL)
               notifyActionEventUpdate(pSelfObject, &actEvent);
         }
         else if(pSelfCurAction->getID() == ACTION_RUN) {  // 跑步

            CActionEvent actEvent;
            actEvent.m_event = AET_REACH;
            CActionDispatch::getInstance()->sendEvnet(m_machineName, m_uid, actEvent);

            CPlayer *pPlayer = dynamic_cast<CPlayer *>(pSelfObject);
            if(pPlayer != NULL)
               notifyActionEventUpdate(pSelfObject, &actEvent);
         }
         else if(pSelfCurAction->getID() == ACTION_FIGHT) {  // 戰鬥姿態
            // 判斷距離，距離太遠要切換跑步動作且人物要移動 (只有玩家可使用此功能)
            if(pTargetObject != NULL) {
               CPlayer *pPlayer = dynamic_cast<CPlayer *>(pSelfObject);
               if(pPlayer != NULL) {
                  float distance = getDistance(pSelfObject->getPosition().fX, pSelfObject->getPosition().fY,
                                               pTargetObject->getPosition().fX, pTargetObject->getPosition().fY);
                  CSkillInfo *pUseSkillInfo = m_pUseSkill->getInfo();
                  if(distance > pUseSkillInfo->getCastRange()) {

                     size_t idx = m_machineName.find("Server");
                     if(idx != std::string::npos) {
#ifdef _GAMEENGINE_3D_
                        pSelfObject->setTargetPosition(pTargetObject->getPosition().fX, pTargetObject->getPosition().fY);
#elif _GAMEENGINE_2D_
                        pSelfObject->setTargetPosition(pTargetObject->getPosition().fX, pTargetObject->getPosition().fY, true);
#endif
                        CActionEvent actEvent;
                        actEvent.m_event = AET_NOT_REACH;
                        CActionDispatch::getInstance()->sendEvnet(pSelfObject->getMachineName(), pSelfObject->getUID(), actEvent);

                        notifyTargetPositionUpdate(pSelfObject);
                     }

                     return;
                  }
               }
            }

            // 判斷施法時間，是否要切換吟唱動作

            // 發送施展技能訊息切換動作
            CCastSkillActionEvent actEvent;
            actEvent.m_event = AET_CAST_SKILL;
            actEvent.m_bCastSkill = true;
            actEvent.m_iCastSkillID = m_pUseSkill->getID();
            actEvent.m_fCastSkillTime = m_pUseSkill->getInfo()->getCastTime();
            CActionDispatch::getInstance()->sendEvnet(m_machineName, m_uid, actEvent);

            // 判斷有無連續技，有的話要通知UI

            m_pUseSkill = NULL;
         }
         else if(pSelfCurAction->getID() == ACTION_FIGHT_RUN) {  // 戰鬥姿態跑步
            size_t idx = m_machineName.find("Server");
            if(idx != std::string::npos) {
               // 判斷距離，距離太遠繼續跑步動作且人物要移動 (只有玩家可使用此功能)
               if(pTargetObject != NULL) {
                  CPlayer *pPlayer = dynamic_cast<CPlayer *>(pSelfObject);
                  if(pPlayer != NULL) {
                     float distance = getDistance(pSelfObject->getPosition().fX, pSelfObject->getPosition().fY,
                                                  pTargetObject->getPosition().fX, pTargetObject->getPosition().fY);
                     CSkillInfo *pUseSkillInfo = m_pUseSkill->getInfo();
                     if(distance > pUseSkillInfo->getCastRange()) {
#ifdef _GAMEENGINE_3D_
                        pSelfObject->setTargetPosition(pTargetObject->getPosition().fX, pTargetObject->getPosition().fY);
#elif _GAMEENGINE_2D_
                        pSelfObject->setTargetPosition(pTargetObject->getPosition().fX, pTargetObject->getPosition().fY, true);
#endif
                        CActionEvent actEvent;
                        actEvent.m_event = AET_NOT_REACH;
                        CActionDispatch::getInstance()->sendEvnet(pSelfObject->getMachineName(), pSelfObject->getUID(), actEvent);

                        notifyTargetPositionUpdate(pSelfObject);

                        return;
                     }
                  }
               }

               CActionEvent actEvent;
               actEvent.m_event = AET_REACH;
               CActionDispatch::getInstance()->sendEvnet(m_machineName, m_uid, actEvent);

               CPlayer *pPlayer = dynamic_cast<CPlayer *>(pSelfObject);
               if(pPlayer != NULL)
                  notifyActionEventUpdate(pSelfObject, &actEvent);
            }
         }
      }
   }
}

void CFightSystem::notifyActionEventUpdate(CUnitObject *pUnitObject, CActionEvent *pActEvent)
{
   std::set<IFightEventListener *>::iterator it = m_fightEventListeners.begin();
   while(it != m_fightEventListeners.end()) {
      (*it)->updateFightActionEvent(pUnitObject, pActEvent);
      ++it;
   }
}

void CFightSystem::notifyTargetPositionUpdate(CUnitObject *pUnitObject)
{
   std::set<IFightEventListener *>::iterator it = m_fightEventListeners.begin();
   while(it != m_fightEventListeners.end()) {
      (*it)->updateFightTargetPosition(pUnitObject);
      ++it;
   }
}