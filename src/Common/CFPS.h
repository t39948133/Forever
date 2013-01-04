/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CFPS.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/26 */
#ifndef _CFPS_H_
#define _CFPS_H_
#include "Common.h"

class CFPS
{
   public:
      CFPS();

      int getFPS();
      float getTimePass();
      void work();

   private:
      int   m_iFPS;          // FPS
      int   m_iFrameCount;   // 畫面更新次數
      float m_fNextFPSTime;  // 下次要計算fps的時間
      float m_fTimePass;
      int   m_iPreTime;      // 上一次gameWork的時間
};

#endif  // #ifndef _CFPS_H_