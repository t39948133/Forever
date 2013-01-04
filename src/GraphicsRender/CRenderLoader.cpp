/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CRenderLoader.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/03 */
#include "CRenderLoader.h"
#include "COgreRender.h"

CRenderLoader *CRenderLoader::m_pInstance = NULL;

CRenderLoader::CRenderLoader()
{
   m_pRenderCore = NULL;
   m_pEngineTable = new std::map<std::string, CGraphicsRender*>();

   registerGraphicsRender(new COgreRender());
}

CRenderLoader::~CRenderLoader()
{
   std::map<std::string, CGraphicsRender*>::iterator it = m_pEngineTable->begin();
   while(it != m_pEngineTable->end()) {
      delete it->second;
      it++;
   }

   m_pEngineTable->clear();
   delete m_pEngineTable;
   m_pEngineTable = NULL;

   m_pRenderCore = NULL;
}

CRenderLoader* CRenderLoader::getInstance()
{
   if(m_pInstance == NULL)
      m_pInstance = new CRenderLoader();

   return m_pInstance;
}

void CRenderLoader::releaseInstance()
{
   if(m_pInstance != NULL) {
      delete m_pInstance;
      m_pInstance = NULL;
   }
}

CGraphicsRender* CRenderLoader::getGraphicsRender(const std::string &renderName)
{
   if(m_pRenderCore == NULL) {
      std::map<std::string, CGraphicsRender*>::iterator it = m_pEngineTable->find(renderName);
      if(it != m_pEngineTable->end())
         m_pRenderCore = it->second;
   }
   
   return m_pRenderCore;
}  

void CRenderLoader::registerGraphicsRender(CGraphicsRender *pRender)
{
   m_pEngineTable->insert(std::make_pair(pRender->getRenderName(), pRender));
}