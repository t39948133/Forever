#ifndef _CMONSTER_H_
#define _CMONSTER_H_
#include "CUnitObject.h"
#include "CMonsterInfoLoader.h"
#include "obj_mTable.h"

typedef ObjTable<CMonsterInfo*, CMonsterInfoLoader> MONSTER_INFO;

class CScene;

class CMonster:public MONSTER_INFO,
               public CUnitObject
{
   public:
      CMonster(int kindID, long long uid, float fx, float fy);	//建構 傳入怪物的所有資料
      ~CMonster();
      static void          initMonster();						      //建立唯一怪物表(僅在場景初
                                                               //始時呼叫一次)
      void                 addHate(long long uid, int damage); //增加仇恨值 AngerValue 傳入
                                                               //攻擊者的UID 造成的仇恨值
      long long            getTarget();						      //取出攻擊目標
      int                  getReware();						      //取得掉落物品(傳回掉落物品
                                                               //的id)
      long long            getMoney();							      //取得掉落金錢
      unsigned int         getXP();							         //取得經驗
      void                 work(float timePass, CScene& scene);
      bool                 isDead();
      std::vector<CSkill*> getSkill();
#ifdef _GAMEENGINE_2D_
      /** @brief Client端繪圖動作 
        * @param hdc 繪圖裝置 */
      /* virtual */ void draw(HDC hdc);
#endif

   private:
      MonsterState           m_state;             //目前狀態
      std::list<AngerValue>  m_lHatred;			  //仇恨值列表
      FPOS                   m_bonPosition;       // 出生X,Y座標 (2D)
	 FPOS							 m_anchorPosition;	//進入戰鬥定位點

      bool                   create(unsigned int id);    //設定哪種怪
      void                   targetUpdate(CScene& scene);
      void					     AIAction(float timePass, CScene& scene);
      bool                   getBack();
};

#endif  // #ifndef _CMONSTER_H_