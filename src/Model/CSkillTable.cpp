#include "CSkillTable.h"
#include "AttributeSet.h"

void CSkillTable::initSkillTable()
{
	if(SKILL_INFO::read("Skill.la"))
	{
	}
	else
	{
		CSkill* ps = new CSkill();
		AdvancedAttribute adv;
		AdvancedAttribute advPercent;

		AttributeClear(adv);
		AttributeClear(advPercent);

		advPercent.iHPMax = 25;

		ps->initSkill(TYPE_ACTIVE, 1, "", "主神盔甲",
			"回復自身25%生命力，在3分鐘內，最大生命提高50%、生命回復速度提升50點",
			-1, 0, 6, 0, SELF, adv, advPercent, 0, -1, -1, false, false);
	}
}

CSkillTable::CSkillTable()
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

void CSkillTable::create(unsigned int id, CPlayer* pPlayer)
{
	SKILL_INFO::create(id);

	CSkill* pInfo = getInfo();
	if(NULL != pInfo)
	{
		m_fSurplus = pInfo->getCoolDown();
		checkAvailable(pPlayer);
	}
}

void CSkillTable::checkAvailable(CPlayer* pPlayer)
{
	CSkill* pInfo = getInfo();
	if(NULL != pInfo)
	{
		bool bW = true;
		bool bS = true;
		if(pInfo->getWeapon())
		{
			if((-1) == pPlayer->getEquip(MAIN_HAND))
			{
				bW = false;
			}
		}
		if(pInfo->getSield())
		{
			if((-1) == pPlayer->getEquip(OFF_HAND))
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