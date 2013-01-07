#ifndef _CSKILL_H_
#define _CSKILL_H_

#include "CSkillInfoLoader.h"
#include "obj_mTable.h"
#include <map>

typedef ObjTable<CSkillInfo*, CSkillInfoLoader> SKILL_INFO;

class CSkill:public SKILL_INFO
{
public:
    static void initSkill();   //初始
	float getSurplus(); //取得冷卻時間
	bool getAvailable();    //取得是否有裝備
	void create(unsigned int id);   //設定成哪個技能
	void afterTime(float timePass); //更新冷卻時間
	bool isReady(); //是否冷卻完了
    bool canLearn(unsigned int lv); //目前等級可不可以學
    void chackAvailable(std::map<EquipSlot, int> equip);    //更新穿的裝備
    CSkill();
    ~CSkill();

private:
	float m_fSurplus;   //目前冷卻時間
	bool m_bAvailable;  //是否裝備需要裝備
};

#endif