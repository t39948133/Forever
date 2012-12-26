#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "CUnitObject.h"
#include "CEquip.h"
#include "CBackPack.h"
#include <map>

class CPlayer:public CUnitObject
{
public:
	CPlayer(std::string strName, long long uid, char level = 1);	//ミà︹ 肚单(箇砞ミ1)
	void addXP(unsigned int xp);	//糤XP unsigned ぃ盿璽计
	unsigned int getXP();			//弄XP
	unsigned int getXPMax();		//弄程XP
	CBackPack getBackPack();
	void wearEquip(unsigned int id);
	void shedEquip(EquipSlot grid);

private:
	unsigned int m_xp;	//竒喷
	unsigned int m_xpMax;	//程竒喷
	char m_levelMax;	//程蔼单 箇砞50
	std::map<EquipSlot , int> m_mEquip;	//
	CBackPack m_backPack;

	void upDateEquipAttr();
	void wearToEquipSlot(EquipSlot es, unsigned int id);
};

#endif