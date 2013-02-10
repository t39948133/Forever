#ifndef _CUNITOBJECT_H_
#define _CUNITOBJECT_H_

#include "Common.h"
#include "CSkill.h"
#include "CBuff.h"
// Add by Darren Chen on 2012/12/22 {
#include "CActionDispatch.h"
#include "CFightSystem.h"
#include "IAdvAttrEventListener.h"
#include "ISkillEventListener.h"
#include "IDrawWeaponNotifyListener.h"
#include "IPlaySoundNotifyListener.h"
// } Add by Darren Chen on 2012/12/22

class CUnitObject : public IPlaySoundNotifyListener
{
   public:
      CUnitObject(std::string machineName, std::string strName, long long uid, char level = 0); //建立角色 傳入名字、等級(預設建立後為0級)
      virtual ~CUnitObject();  // Add by Darren Chen on 2013/01/12

      std::string getMachineName();

      long long getUID();	   //取得唯一編號
      std::string getName();	//取得角色名字
      char getLevel();	      //取得等級

      void addHP(int hp);	//增加/減少HP
      int getHP();	      //取得HP
      int getHPMax();	   //取得最大HP

      void addMP(int mp);	//增加/減少MP
      int getMP();	      //取得MP
      int getMPMax();	   //取得最大MP

      void setAdvAttr(AdvancedAttribute advAttr);	//設定屬性
      AdvancedAttribute getAdvAttr();	            //取得屬性
      void setBasAttr(BasicAttribute basAttr);     //設定基本素質
      BasicAttribute getBasAttr();                 //取得基礎素質

      std::list<CBuff> getBuff();      //取得身上的Buff表
      void addBuff(unsigned int id);   //增加Buff

      std::vector<CSkill *> getSkill();  //取得學會的技能表
      CSkill* getSkill(int skillID);
      bool addSkill(int skillID);    //學技能

      // Add by Darren Chen on 2012/12/22 {
      /** @brief 是否可使用技能
        * @param skillID       技能編號
        * @return true  - 可以使用
        *         false - 不可以使用 */
      bool canUseSkill(int skillID);

      /** @brief 開始施展技能
        * @param skillID       技能編號 */
      void startCastSkill(int skillID);

      /** @brief 使用技能
        * @param skillID       技能編號 */
      void useSkill(int skillID);

      /** @brief 是否在施展技能
        * @return true  - 是
        *         false - 否 */
      bool isCastSkill();

      /** @brief 邏輯動作
        * @param timePass 一個frame幾秒 */
      virtual void work(float timePass);

      /** @brief 加一個方向偏移量來改變角色方向
        * @param offsetDirection 方向偏移量(弧度) */
      void addDirection(float offsetDirection);

      /** @brief 設定角色方向
        * @param direction 方向(弧度) */
      void setDirection(float direction);

      /** @brief 取得角色方向
        * @return 方向(弧度) */
      float getDirection();

      /** @brief 設定位置
        * @param x x座標
        * @param y y座標 */
      void setPosition(float x, float y);

      /** @brief 取得位置
        * @return 位置 */
      const FPOS& getPosition();

      /** @brief 設定目標點位置
        * @param x x座標
        * @param y y座標 */
      void setTargetPosition(float x, float y);

#ifdef _GAMEENGINE_2D_
      /** @brief 設定目標點位置
        * @param x           x座標
        * @param y           y座標
        * @param bFaceTarget 是否面對目標 */
      void setTargetPosition(float x, float y, bool bFaceTarget);
#endif

      /** @brief 取得目標點位置
        * @return 位置 */
      const FPOS& getTargetPosition();

      /** @brief 是否到達目標點
        * @return true  - 是
        *         false - 否 */ 
      bool isReachTarget();

      /** @brief 是否改變動作
        * @return true  - 改變
        *         false - 沒改變 */
      bool isChangeAction();

      /** @brief 取得目前的動作資訊
        * @return 動作資訊 */
      CAction* getCurAction();

      /** @brief 是否能移動
        * @return true  - 是
        *         false - 否 */
      bool isMove();

      /** @brief 設定鍵盤讓角色移動模式 */
      void setKeyMoveEnabled(bool bEnable);

      /** @brief 取得所有動畫名稱
        * @return 所有動畫名稱 */
      std::vector<std::string> getAllAnimationName();

      /** @brief 設定目標物 (玩家/怪物/NPC)
        * @param pUnitObject 目標物 */
      void setTargetObject(CUnitObject *pUnitObject); 

      /** @brief 取得目標物 */
      CUnitObject* getTargetObject();

      /** @brief 加入監聽進階屬性事件的物件
        * @param pListener 監聽者 */
      void addAdvAttrEventListener(IAdvAttrEventListener *pListener);

      /** @brief 移除監聽進階屬性事件的物件
        * @param pListener 監聽者 */
      void removeAdvAttrEventListener(IAdvAttrEventListener *pListener);

      /** @brief 加入監聽技能事件的物件
        * @param pListener 監聽者 */
      void addSkillEventListener(ISkillEventListener *pListener);

      /** @brief 移除監聽技能事件的物件
           * @param pListener 監聽者 */
      void removeSkillEventListener(ISkillEventListener *pListener);

      void addDrawWeaponNotifyListener(IDrawWeaponNotifyListener *pListener);
      void removeDrawWeaponNotifyListener(IDrawWeaponNotifyListener *pListener);

      void addPutinWeaponNotifyListener(IPutinWeaponNotifyListener *pListener);
      void removePutinWeaponNotifyListener(IPutinWeaponNotifyListener *pListener);

#ifdef _GAMEENGINE_2D_
      /** @brief 是否被點選
        * @param x 滑鼠的X座標
        * @param y 滑鼠的Y座標
        * @return ture - 被點選
        *         false - 沒有被點選 */
      bool isClick(float x, float y);

      /** @brief Client端繪圖動作 
        * @param hdc 繪圖裝置 */
      virtual void draw(HDC hdc);
#endif
      // } Add by Darren Chen on 2012/12/22

      virtual void skillDamage(AdvancedAttribute targetAttr);

   protected:
      std::vector<CSkill *>  m_vSkill;          //擁有的技能

      // Add by Darren Chen on 2012/12/27 {
      CActionSystem         *m_pActionSystem;   // 動作系統
      CFightSystem          *m_pFightSystem;    // 戰鬥系統         
      // } Add by Darren Chen on 2012/12/27

   private:
      friend class CPacketPlayerDataWG;  // 允許CPacketPlayerDataWG物件直接對private/protected成員做存取
      friend class CPacketPlayerInit;    // 允許CPacketPlayerInit物件直接對private/protected成員做存取
      friend class CPacketPlayerData;

      int getHPR();   //取得回復的生命力點
      int getMPR();   //取得回復的精神力點

      void updateBuff(float timepass);    //更新所有Buff的時間
      void SkillCoolDown(float timepass); //更新所有技能的冷卻

      /** @brief 通知AdvAttr有更新 */
      void notifyAdvAttrUpdate();

      /** @brief 通知技能有更新 */
      void notifySkillUpdate();

      // IPlaySoundNotifyListener
      /* virtual */ void notifyPlaySound(std::string soundFile);

      void setUID(long long uid);

#ifdef _GAMEENGINE_2D_
      /** @brief 2D版本移動
        * @param timePass 一個frame幾秒
        * @param targetX  目標點X座標
        * @param targetY  目標點Y座標
        * @param bFaceTarget 是否面對目標點 */
      void move(float timePass, float targetX, float targetY, bool bFaceTarget);

      bool          m_bFaceTarget;     // 是否面對目標
#endif

      std::string            m_machineName;     // 機器名稱 (用來識別是不同機器, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      long long              m_uid;	            //唯一編號
      char                   m_level;	         //等級
      std::string            m_strName;         //名字
      BasicAttribute         m_basAttr;         //基本數值
      AdvancedAttribute      m_advAttr;         //屬性
      ObscureAttribute       m_obsAttr;         //隱藏數值
      ComplexAttribute       m_comAttr;         //狀態造成屬性變化暫存
      FloatPrecentAttribute  m_preAttr;         //狀態造成屬性浮點數(百分比)
                                                //變化暫存
      std::list<CBuff>       m_lBuff;	         //身上的Buff
      FPOS                   m_position;        // 角色X,Y座標 (2D)
      FPOS                   m_targetPosition;  // 目標點X,Y座標 (2D)
      float                  m_fDirection;      // 角色方向(單位: 弧度), 逆時針方向旋轉為+, 順時針方向旋轉為-, 方向為0是朝下
      CUnitObject           *m_pTargetObject;   // 目標物
      bool                   m_bKeyMoveEnabled; // 鍵盤移動模式

      std::set<IAdvAttrEventListener *>  m_advAttrEventListeners;  // 監聽AdvancedAttribute改變的監聽者列表
      std::set<ISkillEventListener *>    m_skillEventListeners;    // 監聽技能改變的監聽者列表
      // } Add by Darren Chen on 2012/12/22
};

#endif