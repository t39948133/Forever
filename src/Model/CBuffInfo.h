#ifndef _CBUFFINFO_H_
#define _CBUFFINFO_H_

#include "Common.h"

class CBuffInfo
{
public:
    void initBuffInfo(std::string name, std::string desc, std::string iconName,
                    ComplexAttribute attr, FloatPrecentAttribute attrPercent,
                    float continued, bool harmful);		//初始
    std::string getName();				//取得名稱
    std::string getDesc();				//取得說明
    std::string getIconName();			//取得圖示名稱
    ComplexAttribute getAttr();			//取得屬性
    FloatPrecentAttribute getPercentAttr();	//取得影響百分比
    float getContinued();				//取得最大持續時間
    bool isHarmful();					//取得是否有害

    CBuffInfo();
    ~CBuffInfo();

    void read(FILE* pFile);				//讀黨

	BuffClassType getClassType();

private:
    std::string m_strName;				//名稱
    std::string m_strDesc;				//說明
    std::string m_iconName;				//圖示名稱
    ComplexAttribute m_Attr;			//影響屬性
    FloatPrecentAttribute m_AttrPercent;		//百分比屬性
    float m_fContinued;					//持續時間
    bool m_bHarmful;					//有害/增益

};

#endif