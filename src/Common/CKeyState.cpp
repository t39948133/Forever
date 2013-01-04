/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CKeyState.cpp
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/13 */
#include "CKeyState.h"

CKeyState::CKeyState()
{
   m_iKeyID = 0;
   m_bPrevDown = false;
   m_bPress = false;
   m_bDown = false;
}

void CKeyState::setKey(int key)
{
   m_iKeyID = key;
}

bool CKeyState::isPress()
{
   return m_bPress;
}

bool CKeyState::isDown()
{
   return m_bDown;
}

void CKeyState::work()
{
   if(GetAsyncKeyState(m_iKeyID) < 0) {
      // 按鍵按下

      if(m_bPrevDown == false)
         m_bPress = true;  // 上次放開, 這次壓著, 代表是剛剛壓下的瞬間
      else
         m_bPress = false; // 上次壓著, 這次壓著, 代表是持續壓著的狀態

      m_bDown = true;
      m_bPrevDown = m_bDown;  // 記住這次狀態
   }
   else {
      // 按鍵放開

      m_bDown = false;
      m_bPrevDown = false;
      m_bPress = false;
   }
}