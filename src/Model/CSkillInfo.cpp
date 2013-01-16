#include "CSkillInfo.h"

void CSkillInfo::initSkillInfo(tagSKILL_TYPE type, int level, std::string icomName, 
                       std::string name, std::string desc, int actionID,
					   int castMP, float castTime, float coolTime, float castRange,
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
    m_iCastMP = castMP;
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

tagSKILL_TYPE  CSkillInfo::getType()
{
    return m_type;
}

int CSkillInfo::getLevel()
{
    return m_iLevel;
}

std::string CSkillInfo::geticonName()
{
    return m_iconName;
}

std::string CSkillInfo::getName()
{
    return m_strName;
}

std::string CSkillInfo::getDesc()
{
    return m_strDesc;
}

int CSkillInfo::getActionID()
{
	return m_iActionID;
}

int CSkillInfo::getCastMP()
{
    return m_iCastMP;
}

float CSkillInfo::getCastTime()
{
    return m_fCastTime;
}

float CSkillInfo::getCoolDown()
{
    return m_fCoolDown;
}

float CSkillInfo::getCastRange()
{
    return m_fCastRange;
}

AttackTarget CSkillInfo::getTarget()
{
    return m_target;
}

AdvancedAttribute CSkillInfo::getEffectAttr()
{
    return m_effectAttr;
}

FloatPrecentAttribute CSkillInfo::getEffectAttrPercent()
{
	return m_effectAttrPercent;
}

int CSkillInfo::getBuffID()
{
	return m_iBuffID;
}

int CSkillInfo::getMotionEffects()
{
	return m_iMotionEffects;
}

int CSkillInfo::getTriggerMotion()
{
	return m_iTriggerMotion;
}

bool CSkillInfo::getWeapon()
{
    return m_bWeapon;
}

bool CSkillInfo::getSield()
{
    return m_bShield;
}

void CSkillInfo::read(FILE *pFile)
{
    int version = 0 ;
	fread (&version, sizeof (version), 1, pFile) ;

    fread (&m_type, sizeof (m_type), 1, pFile);
    fread (&m_iLevel, sizeof (m_iLevel), 1, pFile);
    fread (&m_iconName, sizeof (m_iconName), 1, pFile);
    fread (&m_strName, sizeof (m_strName), 1, pFile);
    char buf[longStrSize];
    fread (buf, sizeof(buf), 1, pFile);
    m_strDesc = buf;
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

SkillClassType CSkillInfo::getClassType()
{
    return SKILL;
}

CSkillInfo::~CSkillInfo()
{
}