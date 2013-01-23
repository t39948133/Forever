#include "CSkill.h"
#include "AttributeSet.h"
#include "CPlayer.h"

void CSkill::initSkill()
{
	if(SKILL_INFO::read("Skill.la"))
   {
   }
	else
	{
      AdvancedAttribute adv;
      FloatPrecentAttribute preAttr;

      // 主神盔甲
      AttributeClear(adv);
      adv.fATKSpeed = 0.0f;
      adv.fCasting = 0.0f;
      adv.fMove = 0.0f;

      AttributeClear(preAttr);
      preAttr.fHP = 25;    // 生命力恢復25%

      // buff: 在3分鐘內，最大生命提高50%、生命回復速度提升50點 (還沒做)
      CSkillInfo* ps = new CSkillInfo();
      ps->initSkillInfo(TYPE_ACTIVE, 1, "Skill/Knight/Stonebody_g1", "主神盔甲",
	      "回復自身25%生命力，在3分鐘內，最大生命提高50%、生命回復速度提升50點",
	      6, 0, 0, 6.0f * 60.0f, 0, SELF, adv, preAttr, 0, -1, -1, false, false);    //mp = 113
      addInfo(ps);

      //-----------------------------------------------

      // 猛烈一擊
      AttributeClear(adv);
      adv.iHP = -138;        // 造成138的傷害
      adv.fATKSpeed = 0.0f;
      adv.fCasting = 0.0f;
      adv.fMove = 0.0f;

      AttributeClear(preAttr);

      CSkillInfo *psc = new CSkillInfo();
      psc->initSkillInfo(TYPE_ACTIVE, 1, "Skill/Knight/Robusthit_g1", "猛烈一擊", "對目標造成 138 的物理傷害",
         7, 0, 0, 10.0f, 50.0f, ENEMY, adv, preAttr, 0, -1, -1, true, false);
      addInfo(psc);
	}
}

CSkill::CSkill() : m_bAvailable(false) , m_fSurplus(0.0f)
{
}

CSkill::~CSkill()
{
}

float CSkill::getSurplus()
{
	return m_fSurplus;
}

bool CSkill::getAvailable()
{
	return m_bAvailable;
}

void CSkill::create(unsigned int skillID)
{
   if(false == SKILL_INFO::checkID(skillID))
   {
     return;
   }
	SKILL_INFO::create(skillID);

	CSkillInfo* pInfo = getInfo();
	if(NULL != pInfo)
   {
		m_fSurplus = 0.0f;
      m_bAvailable = true;
	}
}

void CSkill::startCoolDown()
{
   CSkillInfo *pInfo = getInfo();
	if(NULL != pInfo)
      m_fSurplus = pInfo->getCoolDown();
}

bool CSkill::updateCoolDown(float timePass)
{
   if(m_fSurplus == 0.0f)
      return false;

	m_fSurplus -= timePass;
	if(0.0f > m_fSurplus)
	{
		m_fSurplus =  0.0f;
	}
   return true;
}

bool CSkill::isReady()
{
	return 0.0f >= m_fSurplus;
}

bool CSkill::canLearn(unsigned int lv)
{
   CSkillInfo* pInfo = getInfo();
   if(NULL != pInfo)
   {
      return lv >= (unsigned int)pInfo->getLevel();
   }
   return false;
}

void CSkill::checkAvailable(std::map<EquipSlot, int> equip)
{
	CSkillInfo* pInfo = getInfo();
	if(NULL != pInfo)
	{
		bool bW = true;
		bool bS = true;
      if(pInfo->isRequireWeapon())
      {
			if(equip.end() == equip.find(MAIN_HAND))
			{
				bW = false;
			}
      }

      if(pInfo->isRequireShield())
		{
			if(equip.end() == equip.find(OFF_HAND))
         {
				bS = false;
         }
		}

      if(false == pInfo->isRequireWeapon() && false == pInfo->isRequireShield())
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