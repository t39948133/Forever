/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CAction.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/20 */
#include "CAction.h"
#include "CSkill.h"
#include "CCastSkillActionEvent.h"

CAction::CAction() : m_iID(0),
                     m_fTime(0.0f),
                     m_iNextActID(-1),
                     m_bMove(false),
                     m_uid(-1)
{
}

CAction::~CAction()
{
   std::vector<CActionEventHandler *>::iterator it = m_eventHandlerSet.begin();
   while(it != m_eventHandlerSet.end()) {
      delete (*it);
      ++it;
   }
   m_eventHandlerSet.clear();
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
   pHandler->setUID(m_uid);
   pHandler->setMachineName(m_machineName);
   m_eventHandlerSet.push_back(pHandler);
}

int CAction::getID()
{
   return m_iID;
}

int CAction::work(float fPreTime, float fCurTime, CActionEvent *pEvent, std::set<int> *pKeyDownSet)
{
   // 檢查受影響的事件有沒有被觸發, 有被觸發就需要換相對應的動作
   std::vector<CActionEventHandler *>::iterator it = m_eventHandlerSet.begin();
   while(it != m_eventHandlerSet.end()) {
      if((*it)->check(fPreTime, fCurTime, pEvent, pKeyDownSet) == true) {
         int nextActionID = (*it)->getNextActionID();
         
         // 判斷要施展那個技能動作
         if(pEvent->m_event == AET_CAST_SKILL) {
            CCastSkillActionEvent *pCastSkillActionEvent = (CCastSkillActionEvent *)pEvent;
            if(pCastSkillActionEvent->m_bCastSkill == true) {
               CSkillInfo *pSkillInfo = CSkill::getInfo(pCastSkillActionEvent->m_iCastSkillID);
               if(pSkillInfo != NULL)
                  nextActionID = pSkillInfo->getActionID();
            }
         }

         return nextActionID;
      }

      ++it;
   }

   if(fCurTime > m_fTime)
      return m_iNextActID;  // 動作播完, 換下一個動作

   return -1;  // 動作還沒播放結束
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

void CAction::setUID(long long uid)
{
   m_uid = uid;

   std::vector<CActionEventHandler *>::iterator it = m_eventHandlerSet.begin();
   while(it != m_eventHandlerSet.end()) {
      (*it)->setUID(m_uid);
      ++it;
   }
}

void CAction::setMachineName(std::string machineName)
{
   m_machineName = machineName;

   std::vector<CActionEventHandler *>::iterator it = m_eventHandlerSet.begin();
   while(it != m_eventHandlerSet.end()) {
      (*it)->setMachineName(m_machineName);
      ++it;
   }
}

void CAction::write(FILE *pFile)
{
   int version = 0;
	fwrite(&version, sizeof(version), 1, pFile);

   fwrite(&m_iID, sizeof(m_iID), 1, pFile);
   
   int nameSize = m_name.size();
   fwrite(&nameSize, sizeof(nameSize), 1, pFile);
   fwrite(m_name.c_str(), m_name.size(), 1, pFile);

   fwrite(&m_fTime, sizeof(m_fTime), 1, pFile);

   int animationNameSize = m_animationName.size();
   fwrite(&animationNameSize, sizeof(animationNameSize), 1, pFile);
   fwrite(m_animationName.c_str(), m_animationName.size(), 1, pFile);

   fwrite(&m_iNextActID, sizeof(m_iNextActID), 1, pFile);

   int iMove = 0;
   if(m_bMove == true) {
      iMove = 1;
      fwrite(&iMove, sizeof(iMove), 1, pFile);
   }
   else if(m_bMove == false) {
      iMove = 0;
      fwrite(&iMove, sizeof(iMove), 1, pFile);
   }

   int count = m_eventHandlerSet.size();
	fwrite(&count, sizeof(count), 1, pFile);

   std::vector<CActionEventHandler *>::iterator it = m_eventHandlerSet.begin();
   while(it != m_eventHandlerSet.end()) {
      (*it)->write(pFile);
      ++it;
   }
}

void CAction::read(FILE *pFile)
{
   int version = 0;
	fread(&version, sizeof(version), 1, pFile);

   fread(&m_iID, sizeof(m_iID), 1, pFile);

   int nameSize = 0;
   fread(&nameSize, sizeof(nameSize), 1, pFile);
   char buf[256];
   memset(buf, 0, sizeof(buf));
   fread(buf, nameSize, 1, pFile);
   m_name = buf;

   fread(&m_fTime, sizeof(m_fTime), 1, pFile);

   int animationNameSize = 0;
   fread(&animationNameSize, sizeof(animationNameSize), 1, pFile);
   char buf1[256];
   memset(buf1, 0, sizeof(buf1));
   fread(buf1, animationNameSize, 1, pFile);
   m_animationName = buf1;

   fread(&m_iNextActID, sizeof(m_iNextActID), 1, pFile);

   int iMove = 0;
   fread(&iMove, sizeof(iMove), 1, pFile);
   if(iMove == 0)
      m_bMove = false;
   else if(iMove == 1)
      m_bMove = true;

   int count = 0;
	fread(&count, sizeof(count), 1, pFile);
   for(int i = 0; i < count; i++) {
      CActionEvent *pActionEvent = new CActionEvent();

      CActionEventHandler *pActionEventHandler = new CActionEventHandler();
      pActionEventHandler->init(pActionEvent, 0);

      addEventHandler(pActionEventHandler);
   }

   std::vector<CActionEventHandler *>::iterator it = m_eventHandlerSet.begin();
   while(it != m_eventHandlerSet.end()) {
      (*it)->read(pFile);
      ++it;
   }
}