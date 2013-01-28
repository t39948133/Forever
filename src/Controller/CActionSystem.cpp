/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionSystem.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/21 */
#include "CActionSystem.h"
#include "CActionDispatch.h"

CActionSystem::CActionSystem(long long uid) : m_uid(uid), 
                                              m_fCurTime(0.0f),
                                              m_iCurAction(0),
                                              m_bChangeAction(false)
{
   m_pvtEventQueue = new std::vector<CActionEvent *>();
   m_pvtActionSet = new std::vector<CAction *>();
   m_pKeyDownList = new std::list<int>();

   CActionDispatch::getInstance()->addActionSystem(uid, this);
}

CActionSystem::~CActionSystem()
{
   m_pKeyDownList->clear();
   delete m_pKeyDownList;
   m_pKeyDownList = NULL;

   std::vector<CActionEvent *>::iterator itEvent = m_pvtEventQueue->begin();
   while(itEvent != m_pvtEventQueue->end()) {
      delete (*itEvent);
      itEvent++;
   }
   m_pvtEventQueue->clear();
   delete m_pvtEventQueue;
   m_pvtEventQueue = NULL;

   std::vector<CAction *>::iterator itAction = m_pvtActionSet->begin();
   while(itAction != m_pvtActionSet->end()) {
      delete (*itAction);
      itAction++;
   }
   m_pvtActionSet->clear();
   delete m_pvtActionSet;
   m_pvtActionSet = NULL;
}

void CActionSystem::work(float timePass)
{
   m_bChangeAction = false;

   m_fCurTime += timePass;

   int nextActID = -1;
   if(m_pvtActionSet->size() > 0) {
      std::vector<CActionEvent *>::iterator it = m_pvtEventQueue->begin();
      if(it != m_pvtEventQueue->end()) {
         nextActID = m_pvtActionSet->at(m_iCurAction)->work(m_fCurTime, (*it), m_pKeyDownList);
         delete (*it);
         m_pvtEventQueue->erase(it);
      }
      else
         nextActID = m_pvtActionSet->at(m_iCurAction)->work(m_fCurTime, NULL, m_pKeyDownList);
   }

   /** nextActID = 0   沒有下一個動作
     * nextActID = -1  動作還沒播放完畢 */
   if(nextActID > 0)
      changeAction(nextActID);
   else if(nextActID == 0)
      m_fCurTime = 0.0f;
}

bool CActionSystem::isChangeAction()
{
   return m_bChangeAction;
}

CAction* CActionSystem::getCurAction()
{
   if(m_pvtActionSet->size() > 0)
      return m_pvtActionSet->at(m_iCurAction);
   else
      return NULL;
}

void CActionSystem::addAction(CAction *pAction)
{
   m_pvtActionSet->push_back(pAction);
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

   std::vector<CAction *>::iterator it = m_pvtActionSet->begin();
   while(it != m_pvtActionSet->end()) {
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

	int count = m_pvtActionSet->size();
	fwrite(&count, sizeof(count), 1, pFile);

   std::vector<CAction *>::iterator it = m_pvtActionSet->begin();
   while(it != m_pvtActionSet->end()) {
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

   std::vector<CAction *>::iterator it = m_pvtActionSet->begin();
   while(it != m_pvtActionSet->end()) {
      (*it)->read(pFile);
      it++;
   }

	fclose(pFile);

   return true;
}

void CActionSystem::changeAction(int newActionID)
{
   for(int i = 0; i < (int)m_pvtActionSet->size(); i++) {
      CAction *pAction = m_pvtActionSet->at(i);
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
   CActionEvent *pEvent = new CActionEvent();
   *pEvent = actEvent;
   m_pvtEventQueue->push_back(pEvent);
}