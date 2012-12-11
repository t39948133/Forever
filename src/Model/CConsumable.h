#ifndef _CCONSUMABLE_H_
#define _CCONSUMABLE_H_

#include "CItem.h"

class CConsumable:public CItem	//耗材性物品
{
public:
	std::wstring getDesc();
	virtual void read(FILE* pFile);
	virtual void write(FILE* pFile);
	void initWeapon(std::wstring name, ItemType type, bool soulBind,
					char level, int stackLimit, int sellPrice, int buyPrice,
					std::wstring desc, EdibleEffectType effect, int much);


private:
	std::wstring m_strDesc;		//物品描述
	EdibleEffectType m_effect;	//效果種類
	int m_iMuch;				//影響數值
};


#endif