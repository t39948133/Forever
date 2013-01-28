#include "CSkillInfo.h"

void CSkillInfo::initSkillInfo(tagSKILL_TYPE type, int level, std::string icomName, 
                               std::string name, std::string desc, int actionID,
					   int castMP, float castTime, float coolTime, float castRange,
                               AttackTarget target, AdvancedAttribute effectAttr,
                               FloatPrecentAttribute effectAttrPercent, int bufID,
                               int motionEffects,int triggerMotion,bool requireWeapon,
                               bool requireShield)
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
   m_bRequireWeapon = requireWeapon;
   m_bRequireShield = requireShield;
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

bool CSkillInfo::isRequireWeapon()
{
    return m_bRequireWeapon;
}

bool CSkillInfo::isRequireShield()
{
    return m_bRequireShield;
}

void CSkillInfo::read(FILE *pFile)
{
   char buf[256];

   int version = 0 ;
   fread (&version, sizeof (version), 1, pFile) ;

   fread (&m_type, sizeof (m_type), 1, pFile);
   fread (&m_iLevel, sizeof (m_iLevel), 1, pFile);

   // read m_iconName {
   int iconNameSize = 0;
   fread(&iconNameSize, sizeof(iconNameSize), 1, pFile);
   memset(buf, 0, sizeof(buf));
   fread(buf, iconNameSize, 1, pFile);
   m_iconName = buf;
   // } read m_iconName

   // read m_strName {
   int nameSize = 0;
   fread(&nameSize, sizeof(nameSize), 1, pFile);
   memset(buf, 0, sizeof(buf));
   fread(buf, nameSize, 1, pFile);
   m_strName = buf;
   // } read m_strName

   // read m_strDesc {
   int descSize = 0;
   fread(&descSize, sizeof(descSize), 1, pFile);
   memset(buf, 0, sizeof(buf));
   fread(buf, descSize, 1, pFile);
   m_strDesc = buf;
   // } read m_strDesc

   fread (&m_iActionID, sizeof(m_iActionID), 1, pFile);
   fread (&m_iCastMP, sizeof (m_iCastMP), 1, pFile);
   fread (&m_fCastTime, sizeof (m_fCastTime), 1, pFile);
   fread (&m_fCoolDown, sizeof (m_fCoolDown), 1, pFile);
   fread (&m_fCastRange, sizeof (m_fCastRange), 1, pFile);   
   fread (&m_target, sizeof (m_target), 1, pFile);
   fread (&m_effectAttr, sizeof (m_effectAttr), 1, pFile);
   fread (&m_effectAttrPercent, sizeof (m_effectAttrPercent), 1, pFile);
   fread (&m_iBuffID, sizeof (m_iBuffID), 1, pFile);
   fread (&m_iMotionEffects, sizeof (m_iMotionEffects), 1, pFile);
   fread (&m_iTriggerMotion, sizeof (m_iTriggerMotion), 1, pFile);
   fread (&m_bRequireWeapon, sizeof (m_bRequireWeapon), 1, pFile);
   fread (&m_bRequireShield, sizeof (m_bRequireShield), 1, pFile);
}

#ifdef _GAMEENGINE_2D_EDITOR_
void CSkillInfo::write(FILE *pFile)
{
   int version = 0 ;
   fwrite (&version, sizeof (version), 1, pFile) ;

   fwrite (&m_type, sizeof (m_type), 1, pFile);
   fwrite (&m_iLevel, sizeof (m_iLevel), 1, pFile);

   // write m_iconName {
   int iconNameSize = m_iconName.size();
   fwrite(&iconNameSize, sizeof(iconNameSize), 1, pFile);
   fwrite(m_iconName.c_str(), m_iconName.size(), 1, pFile);
   // } write m_iconName

   // write m_strName {
   int nameSize = m_strName.size();
   fwrite(&nameSize, sizeof(nameSize), 1, pFile);
   fwrite(m_strName.c_str(), m_strName.size(), 1, pFile);
   // } write m_strName

   // write m_strDesc {
   int descSize = m_strDesc.size();
   fwrite(&descSize, sizeof(descSize), 1, pFile);
   fwrite(m_strDesc.c_str(), m_strDesc.size(), 1, pFile);
   // } write m_strDesc

   fwrite (&m_iActionID, sizeof(m_iActionID), 1, pFile);
   fwrite (&m_iCastMP, sizeof(m_iCastMP), 1, pFile);
   fwrite (&m_fCastTime, sizeof (m_fCastTime), 1, pFile);
   fwrite (&m_fCoolDown, sizeof (m_fCoolDown), 1, pFile);
   fwrite (&m_fCastRange, sizeof (m_fCastRange), 1, pFile);
   fwrite (&m_target, sizeof (m_target), 1, pFile);
   fwrite (&m_effectAttr, sizeof (m_effectAttr), 1, pFile);
   fwrite (&m_effectAttrPercent, sizeof (m_effectAttrPercent), 1, pFile);
   fwrite (&m_iBuffID, sizeof (m_iBuffID), 1, pFile);
   fwrite (&m_iMotionEffects, sizeof (m_iMotionEffects), 1, pFile);
   fwrite (&m_iTriggerMotion, sizeof (m_iTriggerMotion), 1, pFile);
   fwrite (&m_bRequireWeapon, sizeof (m_bRequireWeapon), 1, pFile);
   fwrite (&m_bRequireShield, sizeof (m_bRequireShield), 1, pFile);
}
#endif //#ifdef _GAMEENGINE_2D_EDITOR_

SkillClassType CSkillInfo::getClassType()
{
    return SKILL;
}

CSkillInfo::~CSkillInfo()
{
}