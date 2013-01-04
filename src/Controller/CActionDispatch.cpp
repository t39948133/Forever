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

void CActionDispatch::addActionSystem(long long uid, CActionSystem *pActionSystem)
{
   std::map<long long, CActionSystem *>::iterator it = m_pEventTable->find(uid);
   if(it != m_pEventTable->end())
      it->second = pActionSystem;
   else
      m_pEventTable->insert(std::make_pair(uid, pActionSystem));
}

void CActionDispatch::sendEvnet(long long uid, CActionEvent &actEvent)
{
   std::map<long long, CActionSystem *>::iterator it = m_pEventTable->find(uid);
   if(it != m_pEventTable->end())
      it->second->sendEvent(actEvent);
}

CActionDispatch::CActionDispatch()
{
   m_pEventTable = new std::map<long long, CActionSystem *>();
}

CActionDispatch::~CActionDispatch()
{
   m_pEventTable->clear();
   delete m_pEventTable;
   m_pEventTable = NULL;
}

