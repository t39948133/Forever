#ifndef _CUNITOBJECT_H_
#define _CUNITOBJECT_H_

#include "Common.h"
#include "CSkill.h"
#include "CBuff.h"
// Add by Darren Chen on 2012/12/22 {
#include "CActionDispatch.h"

typedef struct tagPOSITION {
   float fX;
   float fY;
} POSITION;
// } Add by Darren Chen on 2012/12/22

class CUnitObject
{
   public:
      CUnitObject(std::string strName, long long uid, char level = 0); //建立角色 傳入名字、等級(預設建立後為0級)

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
      BasisAttribute getBasAttr();                 //取得基礎屬性

      std::list<CBuff> getBuff();      //取得身上的Buff表
      void addBuff(unsigned int id);   //增加Buff

      std::vector<CSkill> getSkill();  //取得學會的技能表
      bool addSkill(unsigned int id);  //學技能

      // Add by Darren Chen on 2012/12/22 {
      virtual ~CUnitObject();

      /** @brief 邏輯動作
        * @param timePass 一個frame幾秒 */
      void work(float timePass);

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
      const POSITION& getPosition();

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
      const POSITION& getTargetPosition();

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

#ifdef _GAMEENGINE_2D_
      /** @brief Client端繪圖動作 
        * @param hdc 繪圖裝置 */
      void draw(HDC hdc);
#endif
      // } Add by Darren Chen on 2012/12/22

   protected:
      std::vector<CSkill>  m_vSkill;         //擁有的技能

      // Add by Darren Chen on 2012/12/27 {
      CActionSystem       *m_pActionSystem;  // 動作系統
      // } Add by Darren Chen on 2012/12/27

   private:
      long long             m_uid;	   //唯一編號
      char                  m_level;	//等級
      std::string           m_strName;	//名字
      BasisAttribute        m_basAttr;	//基本數值
      AdvancedAttribute     m_advAttr;	//屬性
      ObscureAttribute      m_obsAttr;	//隱藏數值
      ComplexAttribute      m_comAttr;	//狀態屬性
      FloatPrecentAttribute m_preAttr; //浮點數百分比屬性
      std::list<CBuff>      m_lBuff;	//身上的Buff

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

      bool     m_bFaceTarget;     // 是否面對目標
#endif

      POSITION m_position;        // 角色X,Y座標 (2D)
      POSITION m_targetPosition;  // 目標點X,Y座標 (2D)
      float    m_fDirection;      // 角色方向(單位: 弧度), 逆時針方向旋轉為+, 順時針方向旋轉為-, 方向為0是朝下
      // } Add by Darren Chen on 2012/12/22
};

#endif