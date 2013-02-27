#ifndef _CMONSTER_H_
#define _CMONSTER_H_
#include "CUnitObject.h"
#include "CMonsterInfoLoader.h"
#include "obj_mTable.h"
#include "IMonsterAIEventListener.h"

typedef ObjTable<CMonsterInfo*, CMonsterInfoLoader> MONSTER_INFO;

class CScene;

class CMonster:public MONSTER_INFO,
               public CUnitObject
{
   public:
      CMonster(std::string machineName, int kindID, long long uid, float fx, float fy);	//建構 傳入怪物的所有資料
      ~CMonster();
      static void          initMonster();						      //建立唯一怪物表(僅在場景初始時呼叫一次)

      void                 addHate(long long uid, int damage); //增加仇恨值 AngerValue 傳入攻擊者的UID 造成的仇恨值
      void                 removeHate(long long uid);
      void                 clearHate();

      int                  getReware();						      //取得掉落物品(傳回掉落物品的id)
      long long            getMoney();							      //取得掉落金錢
      unsigned int         getXP();							         //取得經驗
      void                 work(float timePass);

      void                 setState(MonsterState state);
      MonsterState         getState();
      FPOS                 getBornPosition();
      FPOS                 getAnchorPosition();
      bool                 isMonsterTargetTooFarAway();

      void addMonsterAIEventListener(IMonsterAIEventListener *pListener);
      void removeMonsterAIEventListener(IMonsterAIEventListener *pListener);

#ifdef _GAMEENGINE_2D_
      /** @brief Client端繪圖動作 
        * @param hdc 繪圖裝置 */
      /* virtual */ void draw(HDC hdc);
#endif

   private:
      friend class CPacketMonsterData;

      bool                   create(unsigned int id);    //設定哪種怪
      long long              updateTargetObjectUID();    //由仇恨表中更新要鎖定的敵人UID

      MonsterState           m_state;             //目前狀態
      std::list<AngerValue>  m_lHatred;			  //仇恨值列表
      FPOS                   m_bornPosition;      //出生X,Y座標 (2D)
      FPOS						  m_anchorPosition;	  //進入戰鬥定位點

      std::set<IMonsterAIEventListener *>    m_monsterAIListeners;    // 監聽要執行怪物AI的監聽者列表
};

#endif  // #ifndef _CMONSTER_H_