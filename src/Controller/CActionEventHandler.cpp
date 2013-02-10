/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionEventHandler.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/21 */
#include "CActionEventHandler.h"
#include "CKeyActionEvent.h"
#include "CWASDKeyActionEvent.h"
#include "CCastSkillActionEvent.h"
#include "CNotifyActionEvent.h"
#include "CPlaySoundNotifyActionEvent.h"
#include "CActionDispatch.h"

CActionEventHandler::CActionEventHandler() : m_pTriggerEvent(NULL),
                                             m_iNextActionID(0),
                                             m_uid(-1)
{
}

CActionEventHandler::~CActionEventHandler()
{
   if(m_pTriggerEvent != NULL) {
      delete m_pTriggerEvent;
      m_pTriggerEvent = NULL;
   }

   m_iNextActionID = 0;
}

void CActionEventHandler::init(CActionEvent *pTriggerEvent, int nextActionID)
{
   m_pTriggerEvent  = pTriggerEvent;
   m_iNextActionID = nextActionID;
}

int CActionEventHandler::getNextActionID()
{
   return m_iNextActionID;
}

bool CActionEventHandler::check(float fPreTime, float fCurTime, CActionEvent *pEvent, std::set<int> *pKeyDownSet)
{
   if(pEvent == NULL) {
      if(m_pTriggerEvent->m_event > AET_NOTIFY_BEGIN) {
         CNotifyActionEvent *pTriggerEvent = (CNotifyActionEvent *)m_pTriggerEvent;
         if((fPreTime <= pTriggerEvent->m_fBeginTime) &&
            (fCurTime >= pTriggerEvent->m_fBeginTime)) {
            CActionDispatch::getInstance()->sendNotify(m_machineName, m_uid, pTriggerEvent);
            return false; // 不換動作
         }
         else
            return false;  // 不換動作
      }
      else
         return false;
   }

   if(pEvent->m_event == m_pTriggerEvent->m_event) {
      
      if(pEvent->m_event == AET_KEY) {
         CKeyActionEvent *pTriggerEvent = (CKeyActionEvent *)m_pTriggerEvent;
         CKeyActionEvent *pCurrentEvent = (CKeyActionEvent *)pEvent;
         if(*pTriggerEvent == *pCurrentEvent)
            return true;
         else
            return false;
      }
      else if(pEvent->m_event == AET_KEY_WASD) {
         CWASDKeyActionEvent *pTriggerEvent = (CWASDKeyActionEvent *)m_pTriggerEvent;
         CWASDKeyActionEvent *pCurrentEvent = (CWASDKeyActionEvent *)pEvent;

         if(*pTriggerEvent == *pCurrentEvent) {
            int keyID = -1;
            if(pTriggerEvent->m_iKeyDownID > 0)
               keyID = pCurrentEvent->m_iKeyDownID;
            else if(pTriggerEvent->m_iKeyUpID > 0)
               keyID = pCurrentEvent->m_iKeyUpID;

            std::set<int>::iterator it = pKeyDownSet->find(keyID);
            if(it == pKeyDownSet->end()) {
               if(pCurrentEvent->m_iKeyUpID > 0)
                  return false;

               pKeyDownSet->insert(keyID);
               return true;
            }
            else {
               if(pCurrentEvent->m_iKeyDownID > 0)
                  return false;   // 列表中已經存在此按鍵，不變換動作

               pKeyDownSet->erase(it);
               if(pKeyDownSet->size() > 0)
                  return false;   // 列表中還有其他按下的按鍵, 不變換動作
               else
                  return true;    // 列表中再無任何按下的按鍵, 變換動作
            }
         }
         else
            return false;
      }
      else
         return true;
   }
   else
      return false;
}

void CActionEventHandler::setUID(long long uid)
{
   m_uid = uid;
}

void CActionEventHandler::setMachineName(std::string machineName)
{
   m_machineName = machineName;
}

void CActionEventHandler::write(FILE *pFile)
{
   int version = 0;
	fwrite(&version, sizeof(version), 1, pFile);

   int iEvent = (int)(m_pTriggerEvent->m_event);
   fwrite(&iEvent, sizeof(iEvent), 1, pFile);

   switch(m_pTriggerEvent->m_event) {
      case AET_KEY: {     
         CKeyActionEvent *pTriggerEvent = (CKeyActionEvent *)m_pTriggerEvent;
         fwrite(&(pTriggerEvent->m_iKeyID), sizeof(pTriggerEvent->m_iKeyID), 1, pFile);
         break;
      }

      case AET_KEY_WASD: {
         CWASDKeyActionEvent *pTriggerEvent = (CWASDKeyActionEvent *)m_pTriggerEvent;
         fwrite(&(pTriggerEvent->m_iKeyDownID), sizeof(pTriggerEvent->m_iKeyDownID), 1, pFile);
         fwrite(&(pTriggerEvent->m_iKeyUpID), sizeof(pTriggerEvent->m_iKeyUpID), 1, pFile);
         break;
      }

      case AET_CAST_SKILL: {
         CCastSkillActionEvent *pTriggerEvent = (CCastSkillActionEvent *)m_pTriggerEvent;

         int iCastSkill = 0;
         if(pTriggerEvent->m_bCastSkill == true)
            iCastSkill = 1;
         else
            iCastSkill = 0;
         fwrite(&iCastSkill, sizeof(iCastSkill), 1, pFile);

         fwrite(&(pTriggerEvent->m_iCastSkillID), sizeof(pTriggerEvent->m_iCastSkillID), 1, pFile);
         fwrite(&(pTriggerEvent->m_fCastSkillTime), sizeof(pTriggerEvent->m_fCastSkillTime), 1, pFile);
         break;
      }

      case AET_NOTIFY_DRAW_WEAPON: 
      case AET_NOTIFY_PUTIN_WEAPON: {
         CNotifyActionEvent *pTriggerEvent = (CNotifyActionEvent *)m_pTriggerEvent;
         fwrite(&(pTriggerEvent->m_fBeginTime), sizeof(pTriggerEvent->m_fBeginTime), 1, pFile);
         fwrite(&(pTriggerEvent->m_fEndTime), sizeof(pTriggerEvent->m_fEndTime), 1, pFile);
         break;
      }

      case AET_NOTIFY_PLAY_SOUND: {
         CPlaySoundNotifyActionEvent *pTriggerEvent = (CPlaySoundNotifyActionEvent *)m_pTriggerEvent;
         fwrite(&(pTriggerEvent->m_fBeginTime), sizeof(pTriggerEvent->m_fBeginTime), 1, pFile);
         fwrite(&(pTriggerEvent->m_fEndTime), sizeof(pTriggerEvent->m_fEndTime), 1, pFile);

         int soundFileSize = pTriggerEvent->m_soundFile.size();
         fwrite(&soundFileSize, sizeof(soundFileSize), 1, pFile);
         fwrite(pTriggerEvent->m_soundFile.c_str(), pTriggerEvent->m_soundFile.size(), 1, pFile);
         break;
      }
   }
   
   fwrite(&m_iNextActionID, sizeof(m_iNextActionID), 1, pFile);
}

void CActionEventHandler::read(FILE *pFile)
{
   int version = 0;
	fread(&version, sizeof(version), 1, pFile);

   int iEvent = 0;
   fread(&iEvent, sizeof(iEvent), 1, pFile);
   m_pTriggerEvent->m_event = (ACTION_EVENT_TYPE)iEvent;

   switch(m_pTriggerEvent->m_event) {
      case AET_KEY: {
         CKeyActionEvent *pTriggerEvent = new CKeyActionEvent();
         pTriggerEvent->m_event = AET_KEY;
         fread(&(pTriggerEvent->m_iKeyID), sizeof(pTriggerEvent->m_iKeyID), 1, pFile);

         delete m_pTriggerEvent;
         m_pTriggerEvent = pTriggerEvent;
         break;
      }

      case AET_KEY_WASD: {
         CWASDKeyActionEvent *pTriggerEvent = new CWASDKeyActionEvent();
         pTriggerEvent->m_event = AET_KEY_WASD;
         fread(&(pTriggerEvent->m_iKeyDownID), sizeof(pTriggerEvent->m_iKeyDownID), 1, pFile);
         fread(&(pTriggerEvent->m_iKeyUpID), sizeof(pTriggerEvent->m_iKeyUpID), 1, pFile);

         delete m_pTriggerEvent;
         m_pTriggerEvent = pTriggerEvent;
         break;
      }

      case AET_CAST_SKILL: {
         CCastSkillActionEvent *pTriggerEvent = new CCastSkillActionEvent();
         pTriggerEvent->m_event = AET_CAST_SKILL;

         int iCastSkill = 0;
         fread(&iCastSkill, sizeof(iCastSkill), 1, pFile);
         if(iCastSkill == 0)
            pTriggerEvent->m_bCastSkill = false;
         else if(iCastSkill == 1)
            pTriggerEvent->m_bCastSkill = true;

         fread(&(pTriggerEvent->m_iCastSkillID), sizeof(pTriggerEvent->m_iCastSkillID), 1, pFile);
         fread(&(pTriggerEvent->m_fCastSkillTime), sizeof(pTriggerEvent->m_fCastSkillTime), 1, pFile);

         delete m_pTriggerEvent;
         m_pTriggerEvent = pTriggerEvent;
         break;
      }

      case AET_NOTIFY_DRAW_WEAPON: {
         CNotifyActionEvent *pTriggerEvent = new CNotifyActionEvent();
         pTriggerEvent->m_event = AET_NOTIFY_DRAW_WEAPON;
         fread(&(pTriggerEvent->m_fBeginTime), sizeof(pTriggerEvent->m_fBeginTime), 1, pFile);
         fread(&(pTriggerEvent->m_fEndTime), sizeof(pTriggerEvent->m_fEndTime), 1, pFile);

         delete m_pTriggerEvent;
         m_pTriggerEvent = pTriggerEvent;
         break;
      }

      case AET_NOTIFY_PUTIN_WEAPON: {
         CNotifyActionEvent *pTriggerEvent = new CNotifyActionEvent();
         pTriggerEvent->m_event = AET_NOTIFY_PUTIN_WEAPON;
         fread(&(pTriggerEvent->m_fBeginTime), sizeof(pTriggerEvent->m_fBeginTime), 1, pFile);
         fread(&(pTriggerEvent->m_fEndTime), sizeof(pTriggerEvent->m_fEndTime), 1, pFile);

         delete m_pTriggerEvent;
         m_pTriggerEvent = pTriggerEvent;
         break;
      }

      case AET_NOTIFY_PLAY_SOUND: {
         CPlaySoundNotifyActionEvent *pTriggerEvent = new CPlaySoundNotifyActionEvent();
         pTriggerEvent->m_event = AET_NOTIFY_PLAY_SOUND;
         fread(&(pTriggerEvent->m_fBeginTime), sizeof(pTriggerEvent->m_fBeginTime), 1, pFile);
         fread(&(pTriggerEvent->m_fEndTime), sizeof(pTriggerEvent->m_fEndTime), 1, pFile);

         int soundFileSize = 0;
         fread(&soundFileSize, sizeof(soundFileSize), 1, pFile);
         char buf[256];
         memset(buf, 0, sizeof(buf));
         fread(buf, soundFileSize, 1, pFile);
         pTriggerEvent->m_soundFile = buf;

         delete m_pTriggerEvent;
         m_pTriggerEvent = pTriggerEvent;
         break;
      }
   }
   
   fread(&m_iNextActionID, sizeof(m_iNextActionID), 1, pFile);
}