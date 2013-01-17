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
        std::vector<int> vReware, long long money);	//建構 傳入怪物的所有資料
	~CMonster();
    static void			initMonster();						//建立唯一怪物表(僅在場景初始
                                                            //時呼叫一次)
	void				addHate(long long uid, int ihp);    //增加仇恨值 AngerValue 傳入
                                                            //攻擊者的UID 造成的仇恨值
	long long			getTarget();						//取出攻擊目標
	int             	getReware();						//取得掉落物品(傳回掉落物品的
                                                            //id vector)
	long long			getMoney();							//取得掉落金錢
    unsigned int		getXP();							//取得經驗
    void                work(float timePass);
	#ifdef _GAMEENGINE_2D_
	/** @brief Client端繪圖動作 
     * @param hdc 繪圖裝置 */
	void		draw(HDC hdc);
	#endif

private:
	std::list<AngerValue>	m_lHatred;			//仇恨值列表
	std::vector<int>		m_vReware;			//掉落物品
	long long				m_Money;			//掉落金錢
	long long				m_Target;			//目標
    
    bool                    create(unsigned int id);    //設定哪種怪
    void                    targetUpdate();
};

#endif