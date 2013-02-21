#include "CSkill.h"
#include "AttributeSet.h"
#include "CPlayer.h"

void CSkill::initSkill()
{
   if(SKILL_INFO::read("../Skill.fla") == false)
      SKILL_INFO::read("Skill.fla");
}

CSkill::CSkill() : m_bAvailable(false) , m_fSurplus(0.0f)
{
}

CSkill::~CSkill()
{
   m_skillEventListeners.clear();
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

void CSkill::updateCoolDown(float timePass)
{
   if(m_fSurplus == 0.0f)
      return;

	m_fSurplus -= timePass;
	if(0.0f > m_fSurplus)
		m_fSurplus =  0.0f;

   notifySkillCoolDownUpdate();
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

   notifySkillAvailableUpdate();
}

// Add by Darren Chen on 2013/01/21 {
void CSkill::addSkillEventListener(ISkillEventListener *pListener)
{
   std::set<ISkillEventListener *>::iterator it = m_skillEventListeners.find(pListener);
   if(it == m_skillEventListeners.end())
      m_skillEventListeners.insert(pListener);
}

void CSkill::removeSkillEventListener(ISkillEventListener *pListener)
{
   std::set<ISkillEventListener *>::iterator it = m_skillEventListeners.find(pListener);
   if(it != m_skillEventListeners.end())
      m_skillEventListeners.erase(it);
}

void CSkill::notifySkillCoolDownUpdate()
{
   std::set<ISkillEventListener *>::iterator it = m_skillEventListeners.begin();
   while(it != m_skillEventListeners.end()) {
      (*it)->updateSkillCoolDown(this);
      it++;
   }
}

void CSkill::notifySkillAvailableUpdate()
{
   std::set<ISkillEventListener *>::iterator it = m_skillEventListeners.begin();
   while(it != m_skillEventListeners.end()) {
      (*it)->updateSkillAvailable(this);
      it++;
   }
}
// } Add by Darren Chen on 2013/01/21