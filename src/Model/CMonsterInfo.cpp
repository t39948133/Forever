#include "CMonsterInfo.h"
#include "AttributeSet.h"

CMonsterInfo::CMonsterInfo()
{
    AttributeClear(m_basAttr);
}

CMonsterInfo::~CMonsterInfo()
{
}

void CMonsterInfo::initMonsterInfo(std::string name, std::string desc,
                                   std::string meshName, std::string meshTexture,
                                   std::string actionSystem, char level, char wistom,
                                   unsigned int xp, MonsterType atkType,
                                   MonsterGrade levelGrade, float alert, float regress,
                                   BasicAttribute basAttr, long long money,
                                   std::vector<int> reware, std::vector<CSkill*> skill)
{
    m_strName = name;
    m_strDesc = desc;
    m_strMeshName = meshName;
    m_strMeshTexture = meshTexture;
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

std::string CMonsterInfo::getMeshTexture()
{
    return m_strMeshTexture;
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

std::vector<CSkill*> CMonsterInfo::getSkill()
{
    return m_vSkill;
}

void CMonsterInfo::read(FILE *pFile)
{
    int version = 0;
    fread(&version, sizeof(version), 1, pFile);
    fread(&m_strName, sizeof(m_strName), 1,pFile);
    char buf[longStrSize];
    fread(buf, sizeof(buf), 1, pFile);
    m_strDesc = buf;
    memset(buf, 0, longStrSize);
    fread(buf, sizeof(buf), 1, pFile);
    m_strMeshName = buf;
    memset(buf, 0, longStrSize);
    fread(buf, sizeof(buf), 1, pFile);
    m_strMeshTexture = buf;
    memset(buf, 0, longStrSize);
    fread(buf, sizeof(buf), 1, pFile);
    m_strActionSystemFile = buf;
    memset(buf, 0, longStrSize);
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
    for(int i = 0; size > i; i++)
    {
        int skillID = -1;
        fread(&skillID, sizeof(skillID), 1, pFile);
        if(NULL != CSkill::getInfo(skillID))
        {
            CSkill* pSkill = new CSkill();
            pSkill->create(skillID);
            m_vSkill.push_back(pSkill);
        }
    }
}

#ifdef _GAMEENGINE_2D_EDITOR_
void CMonsterInfo::write(FILE *pFile)
{
    int version = 0;
    fwrite(&version, sizeof(version), 1, pFile);
    fwrite(&m_strName, sizeof(m_strName), 1,pFile);
    fwrite(const_cast<char*> (m_strDesc.c_str()), longStrSize, 1, pFile);
    fwrite(const_cast<char*> (m_strMeshName.c_str()), longStrSize, 1, pFile);
    fwrite(const_cast<char*> (m_strMeshTexture.c_str()), longStrSize, 1, pFile);
    fwrite(const_cast<char*> (m_strActionSystemFile.c_str()), longStrSize, 1, pFile);
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
    }
    size = m_vSkill.size();
    fwrite(&size, sizeof(size), 1, pFile);
    std::vector<CSkill*>::iterator ps = m_vSkill.begin();
    while(m_vSkill.end() != ps)
    {
        int skillID;
        skillID = (*ps)->getID();
        fwrite(&skillID, sizeof(skillID), 1, pFile);
    }
}
#endif //#ifdef _GAMEENGINE_2D_EDITOR_

MonsterClass CMonsterInfo::getClassType()
{
    return MONSTER;
}