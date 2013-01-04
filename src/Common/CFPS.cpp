/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CFPS.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/26 */
#include "CFPS.h"

CFPS::CFPS()
{
   m_iFPS = 0;
   m_iFrameCount = 0;
   m_iPreTime = 0;
   m_fNextFPSTime = (float)(GetTickCount() + 1000);
}

int CFPS::getFPS()
{
   return m_iFPS;
}

float CFPS::getTimePass()
{
   return m_fTimePass;
}

void CFPS::work()
{
   m_iFrameCount++;
   int nowTime = GetTickCount();

   if(nowTime > m_fNextFPSTime) {
      m_iFPS = m_iFrameCount;
      m_iFrameCount = 0;
      m_fNextFPSTime = (float)(nowTime + 1000);
   }

   if(m_iPreTime == 0) {
      // 第一次執行
      m_fTimePass = 0;
   }
   else 
      m_fTimePass = (float)(nowTime - m_iPreTime) / 1000.0f;

   m_iPreTime = nowTime;
}