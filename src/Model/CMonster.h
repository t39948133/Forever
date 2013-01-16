#ifndef _CMONSTER_H_
#define _CMONSTER_H_

#include "CUnitObject.h"
#include "CMonsterInfoLoader.h"
#include "obj_mTable.h"

typedef ObjTable<CMonsterInfo*, CMonsterInfoLoader> MONSTER_INFO;

class CMonster:public MONSTER_INFO,
               public CUnitObject
{
public:
    CMonster(int id, long long uid, char level, float dx, float dy,
        std::vector<CSkill> vSkill, std::list<AngerValue> lHatred,
        std::vector<int> vReware, long long money);
	~CMonster();
    static void initMonster();
	void		addHate(AngerValue hate);
	long long	getTarget();
	int			getReware();
	long long	getMoney();
    unsigned int    getXP();         
	#ifdef _GAMEENGINE_2D_
	/** @brief Client端繪圖動作 
     * @param hdc 繪圖裝置 */
	void		draw(HDC hdc);
	#endif

private:
	std::list<AngerValue>	m_lHatred;			//仇恨值列表
	std::vector<int>		m_vReware;			//掉落物品
	long long				m_Money;			//掉落金錢
    
    bool                    create(unsigned int id);    //
};

#endif