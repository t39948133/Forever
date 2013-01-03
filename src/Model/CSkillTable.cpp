#include "CSkillTable.h"
#include "AttributeSet.h"
#include "CPlayer.h"

void CSkillTable::initSkillTable()
{
	if(SKILL_INFO::read("Skill.la"))
	{
	}
	else
	{
		CSkill* ps = new CSkill();
		AdvancedAttribute adv;
		FloatPrecentAttribute preAttr;

		AttributeClear(adv);
        adv.fATKSpeed = 0.0f;
        adv.fCasting = 0.0f;
        adv.fMove = 0.0f;
		AttributeClear(preAttr);

		preAttr.fHPMax = 25;

		ps->initSkill(TYPE_ACTIVE, 1, "", "主神盔甲",
			"回復自身25%生命力，在3分鐘內，最大生命提高50%、生命回復速度提升50點",
			-1, 0, 6, 0, SELF, adv, preAttr, 0, -1, -1, false, false);
        addInfo(ps);
	}
}

CSkillTable::CSkillTable() : m_bAvailable(false) , m_fSurplus(0.0f)
{
}

CSkillTable::~CSkillTable()
{
}
float CSkillTable::getSurplus()
{
	return m_fSurplus;
}

bool CSkillTable::getAvailable()
{
	return m_bAvailable;
}

void CSkillTable::create(unsigned int id)
{
	SKILL_INFO::create(id);

	CSkill* pInfo = getInfo();
	if(NULL != pInfo)
	{
		m_fSurplus = 0.0f;
        m_bAvailable = true;
	}
}

void CSkillTable::afterTime(float timePass)
{
	m_fSurplus -= timePass;
	if(0.0f > m_fSurplus)
	{
		m_fSurplus =  0.0f;
	}
}

bool CSkillTable::isReady()
{
	return 0.0f >= m_fSurplus;
}

bool CSkillTable::canLearn(unsigned int lv)
{
    CSkill* pInfo = getInfo();
    if(NULL != pInfo)
    {
        return lv >= (unsigned int)pInfo->getLevel();
    }
    return false;
}

void CSkillTable::chackAvailable(std::map<EquipSlot, int> equip)
{
	CSkill* pInfo = getInfo();
	if(NULL != pInfo)
	{
		bool bW = true;
		bool bS = true;
		if(pInfo->getWeapon())
		{
			if(equip.end() == equip.find(MAIN_HAND))
			{
				bW = false;
			}
		}
		if(pInfo->getSield())
		{
			if(equip.end() == equip.find(OFF_HAND))
			{
				bS = false;
			}
		}
		if(false == pInfo->getWeapon() && false == pInfo->getSield())
		{
			m_bAvailable = true;
		}
		else
		{
			if(false == bW || false == bS)
			{
				m_bAvailable = false;
			}
			else
			{
				m_bAvailable = true;
			}
		}
	}
}