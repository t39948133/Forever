#include "CUnitObject.h"
#include "AttributeSet.h"

CUnitObject::CUnitObject(std::string strName, long long uid, char level) : m_strName(strName),m_uid(uid),m_level(level)
{
	//AttributeClear(m_basAttr);
	AttributeClear(m_advAttr);
	AttributeClear(m_comAttr);
    CBuffTable buffTable;
    buffTable.initCBuffTable(); //ぇэ祘Α㊣
    CSkillTable skillTable;
    skillTable.initSkillTable();
}

long long CUnitObject::getUID()
{
	return m_uid;
}

std::string CUnitObject::getName()
{
	return m_strName;
}

char CUnitObject::getLevel()
{
	return m_level;
}

void CUnitObject::addHP(int hp)
{
	m_advAttr.iHP += hp;
	if(m_advAttr.iHP < 0 || m_advAttr.iHP == 0)	//⊿﹀ 
	{
		m_advAttr.iHP = 0;
		//祘Α
	}
	else if(m_advAttr.iHP > m_advAttr.iHPMax)	//干﹀禬筁程﹀秖 玂程﹀秖
	{
		m_advAttr.iHP = m_advAttr.iHPMax;
	}
}

int CUnitObject::getHP()
{
	return m_advAttr.iHP;
}

int CUnitObject::getHPMax()
{
	return m_advAttr.iHPMax;
}

void CUnitObject::addMP(int mp)
{
	m_advAttr.iMP += mp;
	if(m_advAttr.iMP < 0 || m_advAttr.iMP == 0)	//⊿臸
	{
		m_advAttr.iMP = 0;
	}
	else if(m_advAttr.iMP > m_advAttr.iMPMax)	//臸禬筁程臸 玂程臸
	{
		m_advAttr.iMP = m_advAttr.iMPMax;
	}
}

int CUnitObject::getMP()
{
	return m_advAttr.iMP;
}

int CUnitObject::getMPMax()
{
	return m_advAttr.iMPMax;
}
  
void CUnitObject::addHPR(int hpr)
{
	m_obsAttr.iHPR += hpr;
}

void CUnitObject::addMPR(int mpr)
{
	m_obsAttr.iMPR += mpr;
}
  
void CUnitObject::setAdvAttr(AdvancedAttribute advattr)
{
	m_advAttr = advattr;	//砞﹚妮┦戈
}

AdvancedAttribute CUnitObject::getAdvAttr()
{
	return m_advAttr;
}

BasisAttribute CUnitObject::getBasAttr()
{
	return m_basAttr;
}

std::list<CBuffTable> CUnitObject::getBuff()
{
    return m_lBuff;
}

void CUnitObject::updateBuff(float timepass)
{
    std::list<CBuffTable>::iterator pi = m_lBuff.begin();

    while(m_lBuff.end() != pi)
    {
        if(pi->afterTime(timepass))
        {
            pi = m_lBuff.erase(pi);
        }
        pi++;
    }

	pi = m_lBuff.begin();
	CBuff* pBuff;

	while(m_lBuff.end() != pi)
	{
		pBuff = pi->getInfo();
		AttributeAdd(m_comAttr, pBuff->getAttr());
		pBuff->getPercentAttr();
		pi++;
	}
}

void CUnitObject::addBuff(unsigned int id)
{
    CBuffTable buffTable;
    buffTable.create(id);
    m_lBuff.push_back(buffTable);
}

std::vector<CSkillTable> CUnitObject::getSkill()
{
    return m_vSkill;
}

void CUnitObject::SkillCoolDown(float timepass)
{
    std::vector<CSkillTable>::iterator pi = m_vSkill.begin();
    while(m_vSkill.end() != pi)
    {
        pi->afterTime(timepass);
        pi++;
    }
}

bool CUnitObject::addSkill(unsigned int id)
{
    CSkillTable skillTable;
    skillTable.create(id);
    if(skillTable.canLearn(m_level))
    {
        m_vSkill.push_back(skillTable);
        return true;
    }
    return false;

}