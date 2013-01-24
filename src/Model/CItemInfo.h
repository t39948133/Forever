#ifndef _CITEMINFO_H_
#define _CITEMINFO_H_
#include "Common.h"

//物品資訊
class CItemInfo			
{
public:
	std::string getName();	//取得名字
	std::string geticonName();
	ItemType getItemType();	//取得哪種物品(ItemType分類)
	bool getSoulBind();		//取得是否綁定
	char getLevel();		//取得可使用等級
	int getStackLimit();	//取得堆疊上限
	int getSellPrice();		//取得賣價
	int getBuyPrice();		//取得買價

	virtual ~CItemInfo();
	virtual ItemClassType getClassType () = 0;		//回傳那一種class(武器、防具、消耗性物品)

	virtual void read(FILE* pFile);		//讀檔
#ifdef _GAMEENGINE_2D_EDITOR_
	virtual void write(FILE* pFile);	//編檔
#endif //#ifdef _GAMEENGINE_2D_EDITOR_
	AdvancedItem* getAll();		//一次取得所有需要外流的項目資訊, 使用完資料後自行delete

protected:
	void setName(std::string name);
   void seticonName(std::string iconName);
	void setItemType(ItemType type);
	void setSoulBind(bool soulBind);
	void setLevel(char level);
	void setStackLimit(int stackLimit);
	void setSellPrice(int sellPrice);
	void setBuyPrice(int buyPrice);

private:
	std::string m_strName;	//名稱
   std::string m_iconName; //圖示名稱
	ItemType m_type;		//種類
	bool m_bSoulBind;		//綁定
	char m_level;			//等級
	int m_iStackLimit;		//堆疊上限
	int m_iSellPrice;		//賣價
	int m_iBuyPrice;		//買價
#ifdef _GAMEENGINE_2D_EDITOR_
	friend class DLGItem;
#endif //#ifdef _GAMEENGINE_2D_EDITOR_
};

#endif