#ifndef _CEQUIP_H_
#define _CEQUIP_H_

#include "Common.h"
#include "CItem.h"

class CEquip:public CItem			//裝備性物品
{
public:
	EquipQuality getQuality();
	AdvancedAttribute getBaseAttr();
	AdvancedAttribute getExtendAttr();
		
	virtual void read(FILE* pFile);
	virtual void write(FILE* pFile);

protected:
	void setQuality(EquipQuality quality);
	void setBaseAttr(AdvancedAttribute baseAttr);
	void setExtendAttr(AdvancedAttribute extendAttr);

private:
	EquipQuality m_quality;			//品質
	AdvancedAttribute m_baseAttr;	//裝備基本能力
	AdvancedAttribute m_extendAttr;	//裝備額外能力
};



#endif