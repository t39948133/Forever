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
	std::string			getMeshName();		//取得模型名稱
		
	virtual void read(FILE* pFile);
#ifdef _GAMEENGINE_2D_EDITOR_
	virtual void write(FILE* pFile);
#endif //#ifdef _GAMEENGINE_2D_EDITOR_

protected:
	void setQuality(EquipQuality quality);
	void setBaseAttr(AdvancedAttribute baseAttr);
	void setExtendAttr(AdvancedAttribute extendAttr);
	void setMeshName(std::string mesh);

private:
	EquipQuality m_quality;			//品質
	AdvancedAttribute m_baseAttr;	//裝備基本能力
	AdvancedAttribute m_extendAttr;	//裝備額外能力
	std::string			m_strMeshName;	//模型名稱
};

#endif  // #ifndef _CEQUIPINFO_H_