#ifndef _CSKILLTABLE_H_
#define _CSKILLTABLE_H_

#include "CSkillInfoLoader.h"
#include "CPlayer.h"
#include "obj_mTable.h"

typedef ObjTable<CSkill*, CSkillInfoLoader> SKILL_INFO;

class CSkillTable:public SKILL_INFO
{
public:
    static void initSkillTable();
	float getSurplus();
	bool getAvailable();
	void create(unsigned int id, CPlayer* pPlayer);
	void checkAvailable(CPlayer* pPlayer);
	void afterTime(float timePass);
	bool isReady();
    CSkillTable();
    ~CSkillTable();

private:
	float m_fSurplus;
	bool m_bAvailable;
};

#endif