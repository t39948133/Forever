#ifndef _CSKILL_H_
#define _CSKILL_H_

#include "Common.h"
#include "CSkillInfoLoader.h"
#include "obj_mTable.h"
#include "ISkillEventListener.h"

typedef ObjTable<CSkillInfo*, CSkillInfoLoader> SKILL_INFO;

class CSkill:public SKILL_INFO
{
   public:
      static void initSkill();   //初始

      CSkill();
      ~CSkill();

      float getSurplus(); //取得冷卻時間
      bool getAvailable();    //取得是否有裝備
      void create(unsigned int skillID);   //設定成哪個技能
      void startCoolDown();  // 開始計算冷卻時間 Add by Darren Chen on 2013/01/16
      void updateCoolDown(float timePass); //更新冷卻時間  Modify by Darren Chen on 2013/01/13
      bool isReady(); //是否冷卻完了
      bool canLearn(unsigned int lv); //目前等級可不可以學
      void checkAvailable(std::map<EquipSlot, int> equip);    //更新穿的裝備

      // Add by Darren Chen on 2013/01/21 {
      /** @brief 加入監聽技能事件的物件
        * @param pListener 監聽者 */
      void addSkillEventListener(ISkillEventListener *pListener);

      /** @brief 移除監聽技能事件的物件
        * @param pListener 監聽者 */
      void removeSkillEventListener(ISkillEventListener *pListener);
      // } Add by Darren Chen on 2013/01/21

   private:
	   float m_fSurplus;   //目前冷卻時間
	   bool m_bAvailable;  //是否裝備需要裝備

      // Add by Darren Chen on 2013/01/21 {
      /** @brief 通知技能冷卻時間有更新 */
      void notifySkillCoolDownUpdate();

      /** @brief 通知技能可不可用有更新 */
      void notifySkillAvailableUpdate();

      std::set<ISkillEventListener *> m_skillEventListeners;   // 監聽技能改變的監聽者列表
      // } Add by Darren Chen on 2013/01/21
};

#endif