#include "CBuff.h"

void CBuff::initBuff(std::string name, std::string desc, std::string iconName,
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

std::string CBuff::getName()
{
    return m_strName;
}

std::string CBuff::getDesc()
{
    return m_strDesc;
}

std::string CBuff::getIconName()
{
    return m_iconName;
}

ComplexAttribute CBuff::getAttr()
{
    return m_Attr;
}

FloatPrecentAttribute CBuff::getPercentAttr()
{
    return m_AttrPercent;
}

float CBuff::getContinued()
{
    return m_fContinued;
}

bool CBuff::isHarmful()
{
    return m_bHarmful;
}

CBuff::CBuff()
{
}

CBuff::~CBuff()
{
}

void CBuff::read(FILE* pFile)
{
    int version = 0 ;
	fread (&version, sizeof (version), 1, pFile) ;

    
	fread (&m_strName, sizeof (m_strName), 1, pFile) ;
	fread (&m_strDesc, sizeof (m_strDesc), 1, pFile) ;
	fread (&m_iconName, sizeof (m_iconName), 1, pFile) ;
	fread (&m_Attr, sizeof (m_Attr), 1, pFile) ;
	fread (&m_AttrPercent, sizeof (m_AttrPercent), 1, pFile) ;
	fread (&m_fContinued, sizeof (m_fContinued), 1, pFile) ;
	fread (&m_bHarmful, sizeof (m_bHarmful), 1, pFile) ;
}

int CBuff::getClassType()
{
	return BUFF;
}