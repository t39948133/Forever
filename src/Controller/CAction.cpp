/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CAction.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/20 */
#include "CAction.h"
#include "CSkill.h"

CAction::CAction() : m_iID(0),
                     m_fTime(0.0f),
                     m_iNextActID(-1),
                     m_bMove(false)
{
   m_pvtEventHandlerSet = new std::vector<CActionEventHandler *>();
}

CAction::~CAction()
{
   std::vector<CActionEventHandler *>::iterator it = m_pvtEventHandlerSet->begin();
   while(it != m_pvtEventHandlerSet->end()) {
      delete (*it);
      it++;
   }
   m_pvtEventHandlerSet->clear();
   delete m_pvtEventHandlerSet;
   m_pvtEventHandlerSet = NULL;
}

void CAction::init(ACTION_DATA &data)
{
   m_iID           = data.iID;
   m_name          = data.name;
   m_fTime         = data.fTime;
   m_animationName = data.animationName;
   m_iNextActID    = data.iNextActID;
   m_bMove         = data.bMove;
}

void CAction::addEventHandler(CActionEventHandler *pHandler)
{
   m_pvtEventHandlerSet->push_back(pHandler);
}

int CAction::getID()
{
   return m_iID;
}

int CAction::work(float fCurTime, CActionEvent *pEvent, std::list<int> *pKeyDownList)
{
   if(fCurTime > m_fTime) {
      // 動作播完, 換下一個動作
      return m_iNextActID;
   }
   else {
      // 檢查受影響的事件有沒有被觸發, 有被觸發就需要換相對應的動作
      std::vector<CActionEventHandler *>::iterator it = m_pvtEventHandlerSet->begin();
      while(it != m_pvtEventHandlerSet->end()) {
         if((*it)->check(pEvent, pKeyDownList) == true) {
            int nextActionID = (*it)->getNextActionID();
            
            // 判斷要施展那個技能動作
            if((m_iID == 4) && (pEvent->m_bCastSkill == true)) {
               CSkillInfo *pSkillInfo = CSkill::getInfo(pEvent->m_iCastSkillID);
               if(pSkillInfo != NULL) {
                  if(pEvent->m_fCastSkillTime == 0)  // 立即施展, 無吟唱動作
                     nextActionID = pSkillInfo->getActionID();
                  else {
                     // 有吟唱動作
                     // Todo: 還沒做
                  }
               }
            }

            return nextActionID;
         }

         it++;
      }

      return -1;  // 動作還沒播放結束
   }
}

std::string CAction::getAnimationName()
{
   return m_animationName;
}

bool CAction::isMove()
{
   return m_bMove;
}

std::string CAction::getName()
{
   return m_name;
}