/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionSystem.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/21 */
#include "CActionSystem.h"
#include "CActionDispatch.h"
#include "CKeyActionEvent.h"
#include "CWASDKeyActionEvent.h"
#include "CCastSkillActionEvent.h"
#include "CPlaySoundNotifyActionEvent.h"

CActionSystem::CActionSystem(std::string machineName, long long uid) : m_machineName(machineName),
                                                                       m_uid(uid), 
                                                                       m_fCurTime(0.0f),
                                                                       m_iCurAction(0),
                                                                       m_bChangeAction(false)
{
   m_pEventQueue = new std::vector<CActionEvent *>();
   m_pNotifyQueue = new std::vector<CNotifyActionEvent *>();
   m_pActionVector = new std::vector<CAction *>();
   m_pKeyDownSet = new std::set<int>;

   CActionDispatch::getInstance()->addActionSystem(m_machineName, uid, this);
}

CActionSystem::~CActionSystem()
{
   CActionDispatch::getInstance()->removeActionSystem(m_machineName, m_uid);

   m_pKeyDownSet->clear();
   delete m_pKeyDownSet;
   m_pKeyDownSet = NULL;

   if(m_pEventQueue != NULL) {
      std::vector<CActionEvent *>::iterator itEvent = m_pEventQueue->begin();
      while(itEvent != m_pEventQueue->end()) {
         delete (*itEvent);
         itEvent++;
      }
      m_pEventQueue->clear();
      delete m_pEventQueue;
      m_pEventQueue = NULL;
   }

   if(m_pNotifyQueue != NULL) {
      std::vector<CNotifyActionEvent *>::iterator itNotify = m_pNotifyQueue->begin();
      while(itNotify != m_pNotifyQueue->end()) {
         delete (*itNotify);
         itNotify++;
      }
      m_pNotifyQueue->clear();
      delete m_pNotifyQueue;
      m_pNotifyQueue = NULL;
   }

   if(m_pActionVector != NULL) {
      std::vector<CAction *>::iterator itAction = m_pActionVector->begin();
      while(itAction != m_pActionVector->end()) {
         delete (*itAction);
         itAction++;
      }
      m_pActionVector->clear();
      delete m_pActionVector;
      m_pActionVector = NULL;
   }
}

void CActionSystem::work(float timePass)
{
   m_bChangeAction = false;

   float fPreTime = m_fCurTime;  // 上一次的時間
   m_fCurTime += timePass;

   int nextActID = -1;
   if(m_pActionVector->size() > 0) {
      std::vector<CActionEvent *>::iterator it = m_pEventQueue->begin();
      if(it != m_pEventQueue->end()) {
         nextActID = m_pActionVector->at(m_iCurAction)->work(fPreTime, m_fCurTime, (*it), m_pKeyDownSet);
         delete (*it);
         m_pEventQueue->erase(it);
      }
      else
         nextActID = m_pActionVector->at(m_iCurAction)->work(fPreTime, m_fCurTime, NULL, m_pKeyDownSet);
   }

   /** nextActID = 0   沒有下一個動作
     * nextActID = -1  動作還沒播放完畢 */
   if(nextActID > 0)
      changeAction(nextActID);
   else if(nextActID == 0)
      m_fCurTime = 0.0f;

   procNotify();
}

bool CActionSystem::isChangeAction()
{
   return m_bChangeAction;
}

CAction* CActionSystem::getCurAction()
{
   if(m_pActionVector->size() > 0)
      return m_pActionVector->at(m_iCurAction);
   else
      return NULL;
}

void CActionSystem::addAction(CAction *pAction)
{
   pAction->setUID(m_uid);
   pAction->setMachineName(m_machineName);
   m_pActionVector->push_back(pAction);
}

bool CActionSystem::isMove()
{
   CAction *pCurAction = getCurAction();
   if(pCurAction != NULL)
      return pCurAction->isMove();
   else
      return false;
}

std::vector<std::string> CActionSystem::getAllAnimationName()
{
   std::vector<std::string> vtAnimationName;

   std::vector<CAction *>::iterator it = m_pActionVector->begin();
   while(it != m_pActionVector->end()) {
      vtAnimationName.push_back((*it)->getAnimationName());
      it++;
   }

   return vtAnimationName;
}

#ifdef _GAMEENGINE_2D_
void CActionSystem::draw(HDC hdc, int x, int y)
{
   char buf[50];
   memset(buf, 0, sizeof(buf));

   CAction *pCurAction = getCurAction();
   if(pCurAction != NULL)
      sprintf_s(buf, sizeof(buf), "%s : %.3f", getCurAction()->getName().c_str(), m_fCurTime);
   else
      sprintf_s(buf, sizeof(buf), "沒有載入動作系統");

   TextOut(hdc, x, y, buf, strlen(buf));
}
#endif

void CActionSystem::write(std::string fileName)
{
   FILE *pFile; 
   fopen_s(&pFile, fileName.c_str(), "wb");

	int version = 0;
	fwrite(&version, sizeof(version), 1, pFile);

	int count = m_pActionVector->size();
	fwrite(&count, sizeof(count), 1, pFile);

   std::vector<CAction *>::iterator it = m_pActionVector->begin();
   while(it != m_pActionVector->end()) {
      (*it)->write(pFile);
      it++;
   }

	fclose(pFile);
}

bool CActionSystem::read(std::string fileName)
{
   FILE *pFile; 
   fopen_s(&pFile, fileName.c_str(), "rb");

   if(pFile == NULL)
      return false;

   m_actionFile = fileName;

   int version = 0;
	fread(&version, sizeof(version), 1, pFile);

	int count = 0;
	fread(&count, sizeof(count), 1, pFile);
   for(int i = 0; i < count; i++) {
      ACTION_DATA actData;
      memset(&actData, 0, sizeof(actData));

      CAction *pAction = new CAction();
      pAction->init(actData);

      addAction(pAction);
   }

   std::vector<CAction *>::iterator it = m_pActionVector->begin();
   while(it != m_pActionVector->end()) {
      (*it)->read(pFile);
      it++;
   }

	fclose(pFile);

   return true;
}

void CActionSystem::addDrawWeaponNotifyListener(IDrawWeaponNotifyListener *pListener)
{
   std::set<IDrawWeaponNotifyListener *>::iterator it = m_drawWeaponNotifyListeners.find(pListener);
   if(it == m_drawWeaponNotifyListeners.end())
      m_drawWeaponNotifyListeners.insert(pListener);
}

void CActionSystem::removeDrawWeaponNotifyListener(IDrawWeaponNotifyListener *pListener)
{
   std::set<IDrawWeaponNotifyListener *>::iterator it = m_drawWeaponNotifyListeners.find(pListener);
   if(it != m_drawWeaponNotifyListeners.end())
      m_drawWeaponNotifyListeners.erase(it);
}

void CActionSystem::addPutinWeaponNotifyListener(IPutinWeaponNotifyListener *pListener)
{
   std::set<IPutinWeaponNotifyListener *>::iterator it = m_putinWeaponNotifyListeners.find(pListener);
   if(it == m_putinWeaponNotifyListeners.end())
      m_putinWeaponNotifyListeners.insert(pListener);
}

void CActionSystem::removePutinWeaponNotifyListener(IPutinWeaponNotifyListener *pListener)
{
   std::set<IPutinWeaponNotifyListener *>::iterator it = m_putinWeaponNotifyListeners.find(pListener);
   if(it != m_putinWeaponNotifyListeners.end())
      m_putinWeaponNotifyListeners.erase(it);
}

void CActionSystem::addPlaySoundNotifyListener(IPlaySoundNotifyListener *pListener)
{
   std::set<IPlaySoundNotifyListener *>::iterator it = m_playSoundNotifyListeners.find(pListener);
   if(it == m_playSoundNotifyListeners.end())
      m_playSoundNotifyListeners.insert(pListener);
}

void CActionSystem::removePlaySoundNotifyListener(IPlaySoundNotifyListener *pListener)
{
   std::set<IPlaySoundNotifyListener *>::iterator it = m_playSoundNotifyListeners.find(pListener);
   if(it != m_playSoundNotifyListeners.end())
      m_playSoundNotifyListeners.erase(it);
}

void CActionSystem::changeAction(int newActionID)
{
   for(int i = 0; i < (int)m_pActionVector->size(); i++) {
      CAction *pAction = m_pActionVector->at(i);
      if(pAction->getID() == newActionID) {
         m_bChangeAction = true;
         m_fCurTime = 0.0f;
         m_iCurAction = i;
         break;
      }
   }
}

void CActionSystem::sendEvent(CActionEvent &actEvent)
{
   switch(actEvent.m_event) {
      case AET_REACH:
      case AET_NOT_REACH: {
         CActionEvent *pActionEvent = new CActionEvent();
         *pActionEvent = actEvent;
         m_pEventQueue->push_back(pActionEvent);
         break;
      }

      case AET_KEY: {
         CKeyActionEvent *pKeyActionEvent = new CKeyActionEvent();
         CKeyActionEvent &srcKeyActionEvent = (CKeyActionEvent &)actEvent;
         *pKeyActionEvent = srcKeyActionEvent;
         m_pEventQueue->push_back(pKeyActionEvent);
         break;
      }

      case AET_KEY_WASD: {
         CWASDKeyActionEvent *pWASDKeyActionEvent = new CWASDKeyActionEvent();
         CWASDKeyActionEvent &srcWASDKeyActionEvent = (CWASDKeyActionEvent &)actEvent;
         *pWASDKeyActionEvent = srcWASDKeyActionEvent;
         m_pEventQueue->push_back(pWASDKeyActionEvent);
         break;
      }

      case AET_CAST_SKILL: {
         CCastSkillActionEvent *pCastSkillActionEvent = new CCastSkillActionEvent();
         CCastSkillActionEvent &srcCastSkillActionEvent = (CCastSkillActionEvent &)actEvent;
         *pCastSkillActionEvent = srcCastSkillActionEvent;
         m_pEventQueue->push_back(pCastSkillActionEvent);
         break;
      }
   }
}

void CActionSystem::sendNotify(CNotifyActionEvent *pNotifyActionEvent)
{
   m_pNotifyQueue->push_back(pNotifyActionEvent);
}

void CActionSystem::procNotify()
{
   std::vector<CNotifyActionEvent *>::iterator itNotifyActionEvent = m_pNotifyQueue->begin();
   if(itNotifyActionEvent != m_pNotifyQueue->end()) {
      switch((*itNotifyActionEvent)->m_event) {
         case AET_NOTIFY_DRAW_WEAPON: {
            std::set<IDrawWeaponNotifyListener *>::iterator it = m_drawWeaponNotifyListeners.begin();
            while(it != m_drawWeaponNotifyListeners.end()) {
               (*it)->notifyDrawWeapon();
               it++;
            }
            break;
         }

         case AET_NOTIFY_PUTIN_WEAPON: {
            std::set<IPutinWeaponNotifyListener *>::iterator it = m_putinWeaponNotifyListeners.begin();
            while(it != m_putinWeaponNotifyListeners.end()) {
               (*it)->notifyPutinWeapon();
               it++;
            }
            break;
         }

         case AET_NOTIFY_PLAY_SOUND: {
            CPlaySoundNotifyActionEvent *pPlaySoundNotifyActionEvent = (CPlaySoundNotifyActionEvent *)(*itNotifyActionEvent);
            std::set<IPlaySoundNotifyListener *>::iterator it = m_playSoundNotifyListeners.begin();
            while(it != m_playSoundNotifyListeners.end()) {
               (*it)->notifyPlaySound(pPlaySoundNotifyActionEvent->m_soundFile);
               it++;
            }
            break;
         }
      }

      m_pNotifyQueue->erase(itNotifyActionEvent);
   }
}