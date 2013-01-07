#ifndef _CCONSUMABLEINFO_H_
#define _CCONSUMABLEINFO_H_

#include "CItemInfo.h"

class CConsumableInfo:public CItemInfo	//耗材性物品
{
public:
	std::string getDesc();			//取得物品描述
	EdibleEffectType getEffect();	//取得哪種效果
	int getMuch();					//取得影響數值
	void initConsumableInfo(std::string name, std::string iconName, ItemType type, bool soulBind,
					char level, int stackLimit, int sellPrice, int buyPrice,
					std::string desc, EdibleEffectType effect, int much);
	
	~CConsumableInfo();
	ItemClassType getClassType ();

	virtual void read(FILE* pFile);


private:
	std::string m_strDesc;		//物品描述
	EdibleEffectType m_effect;	//效果種類
	int m_iMuch;				//影響數值
};


#endif