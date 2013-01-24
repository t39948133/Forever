#include "CBuffInfo.h"

void CBuffInfo::initBuffInfo(std::string name, std::string desc, std::string iconName,
                    ComplexAttribute attr, FloatPrecentAttribute attrPercent,
                    float continued, bool harmful)
{
    m_strName = name;
    m_strDesc = desc;
    m_iconName = iconName;
    m_Attr = attr;
    m_AttrPercent = attrPercent;
    m_fContinued = continued;
    m_bHarmful = harmful;
}

std::string CBuffInfo::getName()
{
    return m_strName;
}

std::string CBuffInfo::getDesc()
{
    return m_strDesc;
}

std::string CBuffInfo::getIconName()
{
    return m_iconName;
}

ComplexAttribute CBuffInfo::getAttr()
{
    return m_Attr;
}

FloatPrecentAttribute CBuffInfo::getPercentAttr()
{
    return m_AttrPercent;
}

float CBuffInfo::getContinued()
{
    return m_fContinued;
}

bool CBuffInfo::isHarmful()
{
    return m_bHarmful;
}

CBuffInfo::CBuffInfo()
{
}

CBuffInfo::~CBuffInfo()
{
}

void CBuffInfo::read(FILE* pFile)
{
    int version = 0 ;
	fread (&version, sizeof (version), 1, pFile) ;

    
	fread (&m_strName, sizeof (m_strName), 1, pFile) ;
	fread (&m_iconName, sizeof (m_iconName), 1, pFile) ;
    char buf[longStrSize];
    fread (buf, sizeof(buf), 1, pFile);
    m_strDesc = buf;
	fread (&m_Attr, sizeof (m_Attr), 1, pFile) ;
	fread (&m_AttrPercent, sizeof (m_AttrPercent), 1, pFile) ;
	fread (&m_fContinued, sizeof (m_fContinued), 1, pFile) ;
	fread (&m_bHarmful, sizeof (m_bHarmful), 1, pFile) ;
}

#ifdef _GAMEENGINE_2D_EDITOR_
void CBuffInfo::write(FILE* pFile)
{
    int version = 0 ;
	fwrite (&version, sizeof (version), 1, pFile) ;

	fwrite (&m_strName, sizeof (m_strName), 1, pFile) ;
	fwrite (&m_iconName, sizeof (m_iconName), 1, pFile) ;
	fwrite (const_cast<char *>(m_strDesc.c_str()), longStrSize, 1, pFile) ;
	fwrite (&m_Attr, sizeof (m_Attr), 1, pFile) ;
	fwrite (&m_AttrPercent, sizeof (m_AttrPercent), 1, pFile) ;
	fwrite (&m_fContinued, sizeof (m_fContinued), 1, pFile) ;
	fwrite (&m_bHarmful, sizeof (m_bHarmful), 1, pFile) ;
}
#endif //#ifdef _GAMEENGINE_2D_EDITOR_

BuffClassType CBuffInfo::getClassType()
{
	return BUFF;
}