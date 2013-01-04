/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionEventHandler.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/21 */
#include "CActionEventHandler.h"

CActionEventHandler::CActionEventHandler()
{
   m_iNextActionID = 0;
}

CActionEventHandler::~CActionEventHandler()
{
}

void CActionEventHandler::init(CActionEvent &triggerEvent, int nextActionID)
{
   m_triggerEvent  = triggerEvent;
   m_iNextActionID = nextActionID;
}

int CActionEventHandler::getNextActionID()
{
   return m_iNextActionID;
}

bool CActionEventHandler::check(CActionEvent *pEvent, std::list<int> *pKeyDownList)
{
   if(pEvent == NULL)
      return false;

   if(pEvent->m_event == m_triggerEvent.m_event) {
      
      if(pEvent->m_event == AET_KEY) {
         if(pEvent->m_iKeyID == m_triggerEvent.m_iKeyID)
            return true;
         else
            return false;
      }
      else if(pEvent->m_event == AET_KEY_WASD) {
         if((m_triggerEvent.m_iKeyDownID > 0) && (pEvent->m_iKeyDownID == m_triggerEvent.m_iKeyDownID)) {
            // 按鍵按下

            // 尋找按下的按鍵是否存在於列表中
            std::list<int>::iterator it = pKeyDownList->begin();
            while(it != pKeyDownList->end()) {
               if((*it) == pEvent->m_iKeyDownID)
                  break;

               it++;
            }

            // 找不到此按下的按鍵
            if(it == pKeyDownList->end()) {
               pKeyDownList->push_back(pEvent->m_iKeyDownID);  // 加入按鍵
               return true;
            }
            else
               return false;
         }
         else if((m_triggerEvent.m_iKeyUpID > 0) && (pEvent->m_iKeyUpID == m_triggerEvent.m_iKeyUpID)) {
            // 按鍵放開

            // 尋找放開的按鍵是否之前有存在於列表中
            std::list<int>::iterator it = pKeyDownList->begin();
            while(it != pKeyDownList->end()) {
               if((*it) == pEvent->m_iKeyUpID)
                  break;

               it++;
            }

            // 找到放開按鍵
            if(it != pKeyDownList->end()) {
               pKeyDownList->erase(it);      // 刪除表中按鍵
               
               if(pKeyDownList->size() > 0)
                  return false;   // 列表中還有其他按下的按鍵, 則是不變換動作
               else
                  return true;    // 列表中再無任何按下的按鍵, 則變換動作
            }
            else
               return false;
         }
         else if((m_triggerEvent.m_iKeyUpID > 0) && (m_triggerEvent.m_iKeyUpID == pEvent->m_iKeyDownID)) {
            // 監控的按鍵為KeyUP狀態, 但是現階段進來的按鍵訊息是監控按鍵的KeyDown狀態

            // 尋找按下的按鍵是否存在於列表中
            std::list<int>::iterator it = pKeyDownList->begin();
            while(it != pKeyDownList->end()) {
               if((*it) == pEvent->m_iKeyDownID)
                  break;

               it++;
            }

            // 找不到此按下的按鍵
            if(it == pKeyDownList->end())
               pKeyDownList->push_back(pEvent->m_iKeyDownID);  // 加入按鍵

            return false;  // 由於不符合監控按鍵狀態, 所以不變換動作
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