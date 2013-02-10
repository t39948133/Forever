/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionDispatch.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/22 */
#include "CActionDispatch.h"

CActionDispatch *CActionDispatch::m_pInstance = NULL;

CActionDispatch* CActionDispatch::getInstance()
{
   if(m_pInstance == NULL)
      m_pInstance = new CActionDispatch();

   return m_pInstance;
}

void CActionDispatch::releaseInstance()
{
   if(m_pInstance != NULL) {
      delete m_pInstance;
      m_pInstance = NULL;
   }
}

void CActionDispatch::addActionSystem(std::string &machineName, long long uid, CActionSystem *pActionSystem)
{
   std::string dispatchID = getDispatchIdentify(machineName, uid);

   std::map<std::string, CActionSystem *>::iterator it = m_pEventTable->find(dispatchID);
   if(it != m_pEventTable->end())
      it->second = pActionSystem;
   else
      m_pEventTable->insert(std::make_pair(dispatchID, pActionSystem));
}

void CActionDispatch::removeActionSystem(std::string &machineName, long long uid)
{
   std::string dispatchID = getDispatchIdentify(machineName, uid);

   std::map<std::string, CActionSystem *>::iterator it = m_pEventTable->find(dispatchID);
   if(it != m_pEventTable->end())
      m_pEventTable->erase(it);
}

void CActionDispatch::sendEvnet(std::string &machineName, long long uid, CActionEvent &actEvent)
{
   std::string dispatchID = getDispatchIdentify(machineName, uid);

   std::map<std::string, CActionSystem *>::iterator it = m_pEventTable->find(dispatchID);
   if(it != m_pEventTable->end())
      it->second->sendEvent(actEvent);
}

void CActionDispatch::sendNotify(std::string &machineName, long long uid, CNotifyActionEvent *pNotifyActionEvent)
{
   std::string dispatchID = getDispatchIdentify(machineName, uid);

   std::map<std::string, CActionSystem *>::iterator it = m_pEventTable->find(dispatchID);
   if(it != m_pEventTable->end())
      it->second->sendNotify(pNotifyActionEvent);
}

CActionDispatch::CActionDispatch()
{
   m_pEventTable = new std::map<std::string, CActionSystem *>();
}

CActionDispatch::~CActionDispatch()
{
   m_pEventTable->clear();
   delete m_pEventTable;
   m_pEventTable = NULL;
}

std::string CActionDispatch::getDispatchIdentify(std::string &machineName, long long uid)
{
   std::string ret = machineName + "::" + toString<long long>(uid);

   return ret;
}