#ifndef _CEQUIPINFO_H_
#define _CEQUIPINFO_H_
#include "Common.h"
#include "CItemInfo.h"

//裝備性物品資訊
class CEquipInfo : public CItemInfo			
{
public:
	EquipQuality getQuality();			//取得品質
	AdvancedAttribute getBaseAttr();	//取得基本能力
	AdvancedAttribute getExtendAttr();	//取得額外能力
		
	virtual void read(FILE* pFile);

protected:
	void setQuality(EquipQuality quality);
	void setBaseAttr(AdvancedAttribute baseAttr);
	void setExtendAttr(AdvancedAttribute extendAttr);

private:
	EquipQuality m_quality;			//品質
	AdvancedAttribute m_baseAttr;	//裝備基本能力
	AdvancedAttribute m_extendAttr;	//裝備額外能力
};

#endif  // #ifndef _CEQUIPINFO_H_