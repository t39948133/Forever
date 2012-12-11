#ifndef _CUNITOBJECT_H_
#define _CUNITOBJECT_H_

#include "Common.h"
#include "AttributeSet.h"

class CUnitObject
{
public:
	CUnitObject(std::wstring strName,char level=0); //建立角色 傳入名字、等級(預設建立後為0級)

	std::wstring getName();	//取得角色名字
	char getLevel();	//取得等級

	void addHP(int hp);	//增加/減少HP
	int getHP();	//取得HP
	int getHPMax();	//取得最大HP

	void addMP(int mp);	//增加/減少MP
	int getMP();	//取得MP
	int getMPMax();	//取得最大MP
  
	void setAdvAttr(AdvancedAttribute advAttr);	//設定屬性
	AdvancedAttribute getAdvAttr();	//取得屬性

private:
	char m_level;	//等級
	std::wstring m_strName;	//名字
	AdvancedAttribute m_advAttr;	//屬性

};

#endif