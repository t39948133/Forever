#ifndef _CUNITOBJECT_H_
#define _CUNITOBJECT_H_

#include "Common.h"
#include "CSkill.h"
#include "CBuff.h"
// Add by Darren Chen on 2012/12/22 {
#include "CActionDispatch.h"
#include "IModelEventListener.h"

typedef struct tagPOSITION {
   float fX;
   float fY;
} FPOS;
// } Add by Darren Chen on 2012/12/22

class CUnitObject
{
   public:
      CUnitObject(std::string strName, long long uid, char level = 0); //建立角色 傳入名字、等級(預設建立後為0級)
      virtual ~CUnitObject();  // Add by Darren Chen on 2013/01/12

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
      BasicAttribute getBasAttr();                 //取得基礎素質

      std::list<CBuff> getBuff();      //取得身上的Buff表
      void addBuff(unsigned int id);   //增加Buff

      std::vector<CSkill *> getSkill();  //取得學會的技能表
      bool addSkill(unsigned int skillID);    //學技能

      // Add by Darren Chen on 2012/12/22 {
      /** @brief 是否可使用技能
        * @param skillID       技能編號
        * @return true  - 可以使用
        *         false - 不可以使用 */
      bool canUseSkill(unsigned int skillID);

      /** @brief 開始施展技能
        * @param skillID       技能編號 */
      void startCastSkill(unsigned int skillID);

      /** @brief 使用技能
        * @param skillID       技能編號 */
      void useSkill(unsigned int skillID);

      /** @brief 是否在施展技能
        * @return true  - 是
        *         false - 否 */
      bool isCastSkill();

      /** @brief 邏輯動作
        * @param timePass 一個frame幾秒 */
    virtual void        work(float timePass);

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

      /** @brief 設定目標物 (玩家/怪物/NPC)
        * @param pUnitObject 目標物 */
      void setTargetObject(CUnitObject *pUnitObject); 

      /** @brief 取得目標物 */
      CUnitObject* getTargetObject();

      /** @brief 加入Model事件的監聽者
        * @param pListener 監聽者 */
      void addModelEventListener(IModelEventListener *pListener);

      /** @brief 移除Model事件的監聽者
        * @param pListener 監聽者 */
      void removeModelEventListener(IModelEventListener *pListener);

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
      void setBasAttr(BasicAttribute basAttr);  //設定基本素質
      std::vector<CSkill *>  m_vSkill;          //擁有的技能

      // Add by Darren Chen on 2012/12/27 {
      /** @brief 通知監聽者本物件的AdvAttr有更新 */
      void notifyUpdateAdvAttr();

      /** @brief 通知監聽者本物件的Skill有更新 */
      void notifyUpdateSkill();

      /** @brief 通知監聽者本物件的技能冷卻時間有更新
        * @param pSkill 技能 */
      void notifyUpdateCoolDown(CSkill *pSkill);

      CActionSystem                   *m_pActionSystem;        // 動作系統
      std::set<IModelEventListener *>  m_modelEventListeners;  // 本物件資料變動時有哪些監聽者要知道
      // } Add by Darren Chen on 2012/12/27

   private:
      long long              m_uid;	     //唯一編號
      char                   m_level;	  //等級
      std::string            m_strName;  //名字
      BasicAttribute         m_basAttr;  //基本數值
      AdvancedAttribute      m_advAttr;  //屬性
      ObscureAttribute       m_obsAttr;  //隱藏數值
      ComplexAttribute       m_comAttr;  //狀態造成屬性變化暫存
      FloatPrecentAttribute  m_preAttr;  //狀態造成屬性浮點數(百分比)
                                         //變化暫存
      std::list<CBuff>       m_lBuff;	  //身上的Buff

      int getHPR();   //取得回復的生命力點
      int getMPR();   //取得回復的精神力點

      void updateBuff(float timepass);    //更新所有Buff的時間
      void SkillCoolDown(float timepass); //更新所有技能的冷卻

      // Add by Darren Chen on 2012/12/22 {
      //friend class CPacketPlayerData;  // 允許CPacketPlayerData物件直接對private/protected成員做存取
      //friend class CPacketPlayerInit;  // 允許CPacketPlayerInit物件直接對private/protected成員做存取

#ifdef _GAMEENGINE_2D_
      /** @brief 2D版本移動
        * @param timePass 一個frame幾秒
        * @param targetX  目標點X座標
        * @param targetY  目標點Y座標
        * @param bFaceTarget 是否面對目標點 */
      void move(float timePass, float targetX, float targetY, bool bFaceTarget);

      bool          m_bFaceTarget;     // 是否面對目標
#endif

      FPOS          m_position;        // 角色X,Y座標 (2D)
      FPOS          m_targetPosition;  // 目標點X,Y座標 (2D)
      float         m_fDirection;      // 角色方向(單位: 弧度), 逆時針方向旋轉為+, 順時針方向旋轉為-, 方向為0是朝下

      bool          m_bCastSkill;      // 是否要施展技能
      CUnitObject  *m_pTargetObject;   // 目標物
      unsigned int  m_iCastSkillID;    // 施展技能的編號
      float         m_fCastSkillTime;  // 施展技能的吟唱時間
      // } Add by Darren Chen on 2012/12/22
};

#endif