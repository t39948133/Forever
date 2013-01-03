#ifndef _CUNITOBJECT_H_
#define _CUNITOBJECT_H_

#include "Common.h"
#include "CSkillTable.h"
#include "CBuffTable.h"
#include <list>

class CUnitObject
{
public:
	CUnitObject(std::string strName, long long uid, char level = 0); //建立角色 傳入名字、等級(預設建立後為0級)

	long long getUID();	//取得唯一編號
	std::string getName();	//取得角色名字
	char getLevel();	//取得等級

	void addHP(int hp);	//增加/減少HP
	int getHP();	//取得HP
	int getHPMax();	//取得最大HP

	void addMP(int mp);	//增加/減少MP
	int getMP();	//取得MP
	int getMPMax();	//取得最大MP
  
	void setAdvAttr(AdvancedAttribute advAttr);	//設定屬性
	AdvancedAttribute getAdvAttr();	//取得屬性
	BasisAttribute getBasAttr();    //取得基礎屬性

    std::list<CBuffTable> getBuff();    //取得身上的Buff表
    void addBuff(unsigned int id);      //增加Buff

    std::vector<CSkillTable> getSkill();    //取得學會的技能表
    bool addSkill(unsigned int id);         //學技能

protected:
    std::vector<CSkillTable> m_vSkill;  //擁有的技能

private:
	long long m_uid;	//唯一編號
	char m_level;	//等級
	std::string m_strName;	//名字
	BasisAttribute m_basAttr;		//基本數值
	AdvancedAttribute m_advAttr;	//屬性
	ObscureAttribute m_obsAttr;		//隱藏數值
	ComplexAttribute m_comAttr;		//狀態屬性
    FloatPrecentAttribute m_preAttr;//浮點數百分比屬性
    std::list<CBuffTable> m_lBuff;	//身上的Buff


	int getHPR();   //取得回復的生命力點
	int getMPR();   //取得回復的精神力點

    void updateBuff(float timepass);    //更新所有Buff的時間
    void SkillCoolDown(float timepass);     //更新所有技能的冷卻
};

#endif