#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "CUnitObject.h"
#include "CBackPack.h"

class CPlayer:public CUnitObject
{
public:
	CPlayer(std::string strName, long long uid, char level = 1);	//建立角色 傳入名字、等級(預設建立後為1級)
	void addXP(unsigned int xp);	//增加XP unsigned 不帶負數
	unsigned int getXP();			//讀取XP
	unsigned int getXPMax();		//讀取最大XP
	CBackPack getBackPack();		//取得背包
	void wearEquip(unsigned int id);//穿上 id 號裝備
	void shedEquip(EquipSlot grid);	//脫下 哪格裝備欄 裝備
	std::map<EquipSlot, int> getEquip();	//取得裝備map陣列
	int getEquip(EquipSlot equip);	//取得哪一格裝備

   // Add by Darren Chen on 2012/12/26 {
#ifdef _GAMEENGINE_2D_
   /** @brief Client端繪圖動作 
     * @param hdc 繪圖裝置 */
   void draw(HDC hdc);
#endif
   // } Add by Darren Chen on 2012/12/26

private:
	unsigned int m_xp;	//經驗值
	unsigned int m_xpMax;	//最大經驗值
	char m_levelMax;	//最高等級 預設50
	std::map<EquipSlot, int> m_mEquip;	//裝備欄
	CBackPack m_backPack;   //背包

	void upDateEquipAttr(); //更新裝備造成的角色屬性
	void wearToEquipSlot(EquipSlot es, unsigned int id);    //穿到裝備欄上
};

#endif