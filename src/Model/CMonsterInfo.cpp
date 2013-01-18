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
                                   char wistom, unsigned int xp, MonsterType atkType,
                                   MonsterGrade levelGrade, float alert, float regress,
								           BasicAttribute basAttr)
{
    m_strName = name;
    m_strDesc = desc;
    m_strMeshName = meshName;
    m_strMeshTexture = meshTexture;
    m_Wistom = wistom;
    m_ixp = xp;
    m_ATKtype = atkType;
    m_LevelGrade = levelGrade;
    m_fAlert = alert;
    m_fRegress = regress;
    m_basAttr = basAttr;
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
    fread(&m_Wistom, sizeof(m_Wistom), 1, pFile);
    fread(&m_ixp, sizeof(m_ixp), 1, pFile);
    fread(&m_ATKtype, sizeof(m_ATKtype), 1, pFile);
    fread(&m_LevelGrade, sizeof(m_LevelGrade), 1, pFile);
    fread(&m_fAlert, sizeof(m_fAlert), 1, pFile);
    fread(&m_fRegress, sizeof(m_fRegress), 1, pFile);
    fread(&m_basAttr, sizeof(m_basAttr), 1, pFile);
}

void CMonsterInfo::write(FILE *pFile)
{
    int version = 0;
    fwrite(&version, sizeof(version), 1, pFile);
    fwrite(&m_strName, sizeof(m_strName), 1,pFile);
    fwrite(const_cast<char*> (m_strDesc.c_str()), longStrSize, 1, pFile);
    fwrite(const_cast<char*> (m_strMeshName.c_str()), longStrSize, 1, pFile);
    fwrite(const_cast<char*> (m_strMeshTexture.c_str()), longStrSize, 1, pFile);
    fwrite(&m_Wistom, sizeof(m_Wistom), 1, pFile);
    fwrite(&m_ixp, sizeof(m_ixp), 1, pFile);
    fwrite(&m_ATKtype, sizeof(m_ATKtype), 1, pFile);
    fwrite(&m_LevelGrade, sizeof(m_LevelGrade), 1, pFile);
    fwrite(&m_fAlert, sizeof(m_fAlert), 1, pFile);
    fwrite(&m_fRegress, sizeof(m_fRegress), 1, pFile);
    fwrite(&m_basAttr, sizeof(m_basAttr), 1, pFile);
}

MonsterClass CMonsterInfo::getClassType()
{
    return MONSTER;
}