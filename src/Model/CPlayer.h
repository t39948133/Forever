#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "CUnitObject.h"
#include "CEquip.h"
#include "CBackPack.h"
#include <map>

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

private:
	unsigned int m_xp;	//經驗值
	unsigned int m_xpMax;	//最大經驗值
	char m_levelMax;	//最高等級 預設50
	std::map<EquipSlot , int> m_mEquip;	//
	CBackPack m_backPack;

	void upDateEquipAttr();
	void wearToEquipSlot(EquipSlot es, unsigned int id);
};

#endif