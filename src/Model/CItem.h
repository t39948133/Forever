#ifndef _CITEM_H_
#define _CITEM_H_

#include "Common.h"





class CItem					//物品
{
public:
	std::wstring getName();	//取得名字
	ItemType getItemType();	//取得哪種物品(ItemType分類)
	bool getSoulBind();		//取得是否綁定
	char getLevel();		//取得可使用等級
	int getStackLimit();	//取得堆疊上限
	int getSellPrice();		//取得賣價
	int getBuyPrice();		//取得買價
	bool isWeapon();		//檢查是否武器
	bool isArmor();			//檢查是否防具
	bool isConsumable();	//檢查是否消耗物品

	virtual void read(FILE* pFile);		//讀檔
	virtual void write(FILE* pFile);	//編檔
	AdvancedItem* getAll();		//一次取得所有需要外流的項目資訊, 使用完資料後自行delete

protected:

	void setName(std::wstring name);
	void setItemType(ItemType type);
	void setSoulBind(bool soulBind);
	void setLevel(char level);
	void setStackLimit(int stackLimit);
	void setSellPrice(int sellPrice);
	void setBuyPrice(int buyPrice);

private:
	std::wstring m_strName;	//名稱
	ItemType m_type;		//種類
	bool m_bSoulBind;		//綁定
	char m_level;			//等級
	int m_iStackLimit;		//堆疊上限
	int m_iSellPrice;		//賣價
	int m_iBuyPrice;		//買價
};



#endif