#include "CMonsterInfo.h"
#include "AttributeSet.h"

CMonsterInfo::CMonsterInfo()
{
    memset(&m_basAttr, 0, sizeof(m_basAttr));
}

CMonsterInfo::~CMonsterInfo()
{
}

void CMonsterInfo::initMonsterInfo(std::string name, std::string desc,
                                   std::string meshName, 
                                   std::string actionSystem, char level, char wistom,
                                   unsigned int xp, MonsterType atkType,
                                   MonsterGrade levelGrade, float alert, float regress,
                                   BasicAttribute basAttr, long long money,
                                   std::vector<int> reware, std::vector<int> skill)
{
    m_strName = name;
    m_strDesc = desc;
    m_strMeshName = meshName;
    m_strActionSystemFile = actionSystem;
    m_Level = level;
    m_Wistom = wistom;
    m_ixp = xp;
    m_ATKtype = atkType;
    m_LevelGrade = levelGrade;
    m_fAlert = alert;
    m_fRegress = regress;
    m_basAttr = basAttr;
    m_Money = money;
    m_vReware = reware;
    m_vSkill = skill;
}

std::string CMonsterInfo::getName()
{
    return m_strName;
}

std::string CMonsterInfo::getDesc()
{
    return m_strDesc;
}

std::string CMonsterInfo::getMeshName()
{
    return m_strMeshName;
}

char CMonsterInfo::getWistom()
{
    return m_Wistom;
}

unsigned int CMonsterInfo::getxp()
{
    return m_ixp;
}

MonsterType CMonsterInfo::getATKtype()
{
    return m_ATKtype;
}

MonsterGrade CMonsterInfo::getLevelGrade()
{
    return m_LevelGrade;
}

float CMonsterInfo::getAlert()
{
    return m_fAlert;
}

float CMonsterInfo::getRegress()
{
    return m_fRegress;
}

BasicAttribute CMonsterInfo::getBasAttr()
{
    return m_basAttr;
}

std::string CMonsterInfo::getActionSystemFile()
{
    return m_strActionSystemFile;
}

char CMonsterInfo::getLevel()
{
    return m_Level;
}

long long CMonsterInfo::getMoney()
{
    return m_Money;
}

std::vector<int> CMonsterInfo::getReware()
{
    return m_vReware;
}

std::vector<int> CMonsterInfo::getSkill()
{
    return m_vSkill;
}

void CMonsterInfo::read(FILE *pFile)
{
   char buf[256];

   int version = 0;
   fread(&version, sizeof(version), 1, pFile);

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

   // read m_strMeshName {
   int meshNameSize = 0;
   fread(&meshNameSize, sizeof(meshNameSize), 1, pFile);
   memset(buf, 0, sizeof(buf));
   fread(buf, meshNameSize, 1, pFile);
   m_strMeshName = buf;
   // } read m_strMeshName

   // read m_strActionSystemFile {
   int actionSystemFileNameSize = 0;
   fread(&actionSystemFileNameSize, sizeof(actionSystemFileNameSize), 1, pFile);
   memset(buf, 0, sizeof(buf));
   fread(buf, actionSystemFileNameSize, 1, pFile);
   m_strActionSystemFile = buf;
   // } read m_strActionSystemFile

    memset(buf, 0, sizeof(buf));
   fread(&m_Level, sizeof(m_Level), 1, pFile);
   fread(&m_Wistom, sizeof(m_Wistom), 1, pFile);
   fread(&m_ixp, sizeof(m_ixp), 1, pFile);
   fread(&m_ATKtype, sizeof(m_ATKtype), 1, pFile);
   fread(&m_LevelGrade, sizeof(m_LevelGrade), 1, pFile);
   fread(&m_fAlert, sizeof(m_fAlert), 1, pFile);
   fread(&m_fRegress, sizeof(m_fRegress), 1, pFile);
   fread(&m_basAttr, sizeof(m_basAttr), 1, pFile);
   fread(&m_Money, sizeof(m_Money), 1, pFile);
   int size = 0;
   fread(&size, sizeof(size), 1, pFile);
   for(int i = 0; size > i; i++)
   {
      int itemID = -1;
      fread(&itemID, sizeof(itemID), 1, pFile);
      if(-1 != itemID)
      {
         m_vReware.push_back(itemID);
      }
   }
   size = 0;
   fread(&size, sizeof(size), 1, pFile);
   for(int i = 0; i < size; i++) {
      int skillID = -1;
      fread(&skillID, sizeof(skillID), 1, pFile);
      if(skillID > -1)
         m_vSkill.push_back(skillID);
   }
}

#ifdef _GAMEENGINE_2D_EDITOR_
void CMonsterInfo::write(FILE *pFile)
{
   int version = 0;
   fwrite(&version, sizeof(version), 1, pFile);

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

   // write m_strMeshName {
   int meshNameSize = m_strMeshName.size();
   fwrite(&meshNameSize, sizeof(meshNameSize), 1, pFile);
   fwrite(m_strMeshName.c_str(), m_strMeshName.size(), 1, pFile);
   // } write m_strMeshName

   // write m_strActionSystemFile {
   int actionSystemFileNameSize = m_strActionSystemFile.size();
   fwrite(&actionSystemFileNameSize, sizeof(actionSystemFileNameSize), 1, pFile);
   fwrite(m_strActionSystemFile.c_str(), m_strActionSystemFile.size(), 1, pFile);
   // } write m_strActionSystemFile

   fwrite(&m_Level, sizeof(m_Level), 1, pFile);
   fwrite(&m_Wistom, sizeof(m_Wistom), 1, pFile);
   fwrite(&m_ixp, sizeof(m_ixp), 1, pFile);
   fwrite(&m_ATKtype, sizeof(m_ATKtype), 1, pFile);
   fwrite(&m_LevelGrade, sizeof(m_LevelGrade), 1, pFile);
   fwrite(&m_fAlert, sizeof(m_fAlert), 1, pFile);
   fwrite(&m_fRegress, sizeof(m_fRegress), 1, pFile);
   fwrite(&m_basAttr, sizeof(m_basAttr), 1, pFile);
   fwrite(&m_Money, sizeof(m_Money), 1, pFile);
   int size = 0;
   size = m_vReware.size();
   fwrite(&size, sizeof(size), 1, pFile);
   std::vector<int>::iterator pr = m_vReware.begin();
   while(m_vReware.end() != pr)
   {
      int itemID;
      itemID = (*pr);
      fwrite(&itemID, sizeof(itemID), 1, pFile);
      pr++;
   }
   size = m_vSkill.size();
   fwrite(&size, sizeof(size), 1, pFile);
   std::vector<int>::iterator ps = m_vSkill.begin();
   while(ps != m_vSkill.end()) {
      int skillID = (*ps);
      fwrite(&skillID, sizeof(skillID), 1, pFile);
      ps++;
   }
}
#endif //#ifdef _GAMEENGINE_2D_EDITOR_

MonsterClass CMonsterInfo::getClassType()
{
    return MONSTER;
}