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
   char buf[256];

   int version = 0 ;
   fread (&version, sizeof (version), 1, pFile) ;

   // read m_strName {
   int nameSize = 0;
   fread(&nameSize, sizeof(nameSize), 1, pFile);
   memset(buf, 0, sizeof(buf));
   fread(buf, nameSize, 1, pFile);
   m_strName = buf;
   // } read m_strName

   // read m_iconName {
   int iconNameSize = 0;
   fread(&iconNameSize, sizeof(iconNameSize), 1, pFile);
   memset(buf, 0, sizeof(buf));
   fread(buf, iconNameSize, 1, pFile);
   m_iconName = buf;
   // } read m_iconName

   // read m_strDesc {
   int descSize = 0;
   fread(&descSize, sizeof(descSize), 1, pFile);
   memset(buf, 0, sizeof(buf));
   fread(buf, descSize, 1, pFile);
   m_strDesc = buf;
   // } read m_strDesc

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

   // write m_strName {
   int nameSize = m_strName.size();
   fwrite(&nameSize, sizeof(nameSize), 1, pFile);
   fwrite(m_strName.c_str(), m_strName.size(), 1, pFile);
   // } write m_strName

   // write m_iconName {
   int iconNameSize = m_iconName.size();
   fwrite(&iconNameSize, sizeof(iconNameSize), 1, pFile);
   fwrite(m_iconName.c_str(), m_iconName.size(), 1, pFile);
   // } write m_iconName

   // write m_strDesc {
   int descSize = m_strDesc.size();
   fwrite(&descSize, sizeof(descSize), 1, pFile);
   fwrite(m_strDesc.c_str(), m_strDesc.size(), 1, pFile);
   // } write m_strDesc

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