#include "CUnitObject.h"
#include "AttributeSet.h"

CUnitObject::CUnitObject(std::string strName, long long uid, char level) : m_strName(strName),m_uid(uid),m_level(level)
{
	AttributeClear(m_basAttr);
	AttributeClear(m_advAttr);
	AttributeClear(m_obsAttr);
	AttributeClear(m_comAttr);
    m_comAttr.AdvAttr.fATKSpeed = 0.0f;
    m_comAttr.AdvAttr.fCasting = 0.0f;
    m_comAttr.AdvAttr.fMove = 0.0f;
    AttributeClear(m_preAttr);
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
	else if(m_advAttr.iHP > getHPMax())	//干﹀禬筁程﹀秖 玂程﹀秖
	{
		m_advAttr.iHP = getHPMax();
	}
}

int CUnitObject::getHP()
{
	return m_advAttr.iHP;
}

int CUnitObject::getHPMax()
{
    int hpMax = m_advAttr.iHPMax;

    hpMax += m_comAttr.AdvAttr.iHPMax;
    if(0.0f > m_preAttr.fHPMax)
    {
        hpMax =(int) (hpMax * m_preAttr.fHPMax);
    }

	return hpMax;
}

void CUnitObject::addMP(int mp)
{
	m_advAttr.iMP += mp;
	if(m_advAttr.iMP < 0 || m_advAttr.iMP == 0)	//⊿臸
	{
		m_advAttr.iMP = 0;
	}
	else if(m_advAttr.iMP > getMPMax())	//臸禬筁程臸 玂程臸
	{
		m_advAttr.iMP = getMPMax();
	}
}

int CUnitObject::getMP()
{
	return m_advAttr.iMP;
}

int CUnitObject::getMPMax()
{
    int mpMax = m_advAttr.iMPMax;

    mpMax += m_comAttr.AdvAttr.iMPMax;

    if(0.0f > m_preAttr.fMPMax)
    {
        mpMax = (int) (mpMax * m_preAttr.fMPMax);
}
  
	return mpMax;
}

int CUnitObject::getHPR()
{
	int hpr = m_obsAttr.iHPR;

    hpr += m_comAttr.ObsAttr.iHPR;

    if(0.0f > m_preAttr.fHPR)
{
        hpr = (int) (hpr * m_preAttr.fHPR);
}

    return hpr;
}

int CUnitObject::getMPR()
{
	int mpr = m_obsAttr.iMPR;

    mpr += m_comAttr.ObsAttr.iMPR;

    if(0.0f > m_preAttr.fMPR)
{
        mpr = (int) (mpr * m_preAttr.fMPR);
    }

    return mpr;
}
  
void CUnitObject::setAdvAttr(AdvancedAttribute advattr)
{
	m_advAttr = advattr;	//砞﹚妮┦戈
    if(getHPMax() < m_advAttr.iHP)
    {
        m_advAttr.iHP = getHPMax();
    }
    if(getMPMax() < m_advAttr.iMP)
    {
        m_advAttr.iMP = getMPMax();
    }
}

AdvancedAttribute CUnitObject::getAdvAttr()
{
    AdvancedAttribute attr = m_advAttr;

    AttributeAdd(attr, m_comAttr.AdvAttr);
    AttributeMulti(attr, m_preAttr);

	return attr;
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
        else
        {
        pi++;
    }
    }

	pi = m_lBuff.begin();
	CBuff* pBuff;

	while(m_lBuff.end() != pi)
	{
		pBuff = pi->getInfo();
		AttributeAdd(m_comAttr, pBuff->getAttr());
		AttributeMulti(m_preAttr, pBuff->getPercentAttr());
		pi++;
	}
}

void CUnitObject::addBuff(unsigned int id)
{
    CBuffTable bt;
    bt.create(id);
    m_lBuff.push_back(bt);
    updateBuff(0.0f);
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
    CSkillTable st ;
    st.create(id);
    if(st.canLearn(m_level))
    {
        m_vSkill.push_back(st);
        return true;
    }
    return false;

}