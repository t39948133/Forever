#include "CPlayer.h"

CPlayer::CPlayer(std::wstring strName, long long uid, char level) : CUnitObject(strName, uid, level), m_levelMax(50)
{
}

void CPlayer::addXP(unsigned int xp)
{
	m_xp += xp;
	if(m_xpMax < m_xp)	//取得經驗後 可升級
	{		
		m_xp -= m_xpMax;
		//升級function
	}
}

unsigned int CPlayer::getXP()
{
	return m_xp;
}

unsigned int CPlayer::getXPMax()
{
	return m_xpMax;
}
