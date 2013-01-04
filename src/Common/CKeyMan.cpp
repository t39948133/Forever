/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CKeyMan.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/13 */
#include "CKeyMan.h"

CKeyMan::CKeyMan()
{
   m_keyState[KEY_W].setKey('W');
	m_keyState[KEY_A].setKey('A');
	m_keyState[KEY_S].setKey('S');
	m_keyState[KEY_D].setKey('D');

   m_keyState[KEY_LBUTTON].setKey(VK_LBUTTON);
}

bool CKeyMan::isPress(VIRTUAL_KEY key)
{
	return m_keyState[key].isPress();
}

bool CKeyMan::isDown(VIRTUAL_KEY key)
{
	return m_keyState[key].isDown();
}

bool CKeyMan::isUp(VIRTUAL_KEY key)
{
	return m_keyState[key].isDown() == false;
}

void CKeyMan::work()
{
	for(int i = 0; i <KEY_COUNT; i++)
		m_keyState[i].work();
}