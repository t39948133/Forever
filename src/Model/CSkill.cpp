#include "CSkill.h"

void CSkill::initSkill(tagSKILL_TYPE type, int level, std::string icomName, 
                       std::string name, std::string desc, int actionID,
					   float castTime, float coolTime, float castRange,
					   AttackTarget target, AdvancedAttribute effectAttr,
					   FloatPrecentAttribute effectAttrPercent, int bufID,
					   int motionEffects,int triggerMotion,bool weapon,
                       bool shield)
{
    m_type  = type;
	m_iLevel = level;
	m_iconName = icomName;
	m_strName = name;
	m_strDesc = desc;
	m_iActionID = actionID;
	m_fCastTime = castTime;
	m_fCoolDown = coolTime;
	m_fCastRange = castRange;
	m_target = target;
	m_effectAttr = effectAttr;
	m_effectAttrPercent = effectAttrPercent;
	m_iBuffID = bufID;
	m_iMotionEffects = motionEffects;
	m_iTriggerMotion = triggerMotion;
	m_bWeapon = weapon;
    m_bShield = shield;
}

tagSKILL_TYPE  CSkill::getType()
{
    return m_type;
}

int CSkill::getLevel()
{
    return m_iLevel;
}

std::string CSkill::geticonName()
{
    return m_iconName;
}

std::string CSkill::getName()
{
    return m_strName;
}

std::string CSkill::getDesc()
{
    return m_strDesc;
}

int CSkill::getActionID()
{
	return m_iActionID;
}

float CSkill::getCastTime()
{
    return m_fCastTime;
}

float CSkill::getCoolDown()
{
    return m_fCoolDown;
}

float CSkill::getCastRange()
{
    return m_fCastRange;
}

AttackTarget CSkill::getTarget()
{
    return m_target;
}

AdvancedAttribute CSkill::getEffectAttr()
{
    return m_effectAttr;
}

FloatPrecentAttribute CSkill::getEffectAttrPercent()
{
	return m_effectAttrPercent;
}

int CSkill::getBuffID()
{
	return m_iBuffID;
}

int CSkill::getMotionEffects()
{
	return m_iMotionEffects;
}

int CSkill::getTriggerMotion()
{
	return m_iTriggerMotion;
}

bool CSkill::getWeapon()
{
    return m_bWeapon;
}

bool CSkill::getSield()
{
    return m_bShield;
}

void CSkill::read(FILE *pFile)
{
    int version = 0 ;
	fread (&version, sizeof (version), 1, pFile) ;

    fread (&m_type, sizeof (m_type), 1, pFile);
    fread (&m_iLevel, sizeof (m_iLevel), 1, pFile);
    fread (&m_iconName, sizeof (m_iconName), 1, pFile);
    fread (&m_strName, sizeof (m_strName), 1, pFile);
    fread (&m_strDesc, sizeof (m_strDesc), 1, pFile);
	fread (&m_iActionID, sizeof(m_iActionID), 1, pFile);
    fread (&m_fCastTime, sizeof (m_fCastTime), 1, pFile);
    fread (&m_fCoolDown, sizeof (m_fCoolDown), 1, pFile);
    fread (&m_fCastRange, sizeof (m_fCastRange), 1, pFile);
    fread (&m_target, sizeof (m_target), 1, pFile);
    fread (&m_effectAttr, sizeof (m_effectAttr), 1, pFile);
    fread (&m_effectAttrPercent, sizeof (m_effectAttrPercent), 1, pFile);
    fread (&m_iBuffID, sizeof (m_iBuffID), 1, pFile);
    fread (&m_iMotionEffects, sizeof (m_iMotionEffects), 1, pFile);
    fread (&m_iTriggerMotion, sizeof (m_iTriggerMotion), 1, pFile);
    fread (&m_bWeapon, sizeof (m_bWeapon), 1, pFile);
    fread (&m_bShield, sizeof (m_bShield), 1, pFile);
}

int getClassType()
{
    return SKILL;
}