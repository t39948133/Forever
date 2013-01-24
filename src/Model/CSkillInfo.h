#ifndef _CSKILLINFO_H_
#define _CSKILLINFO_H_

#include "Common.h"

class CSkillInfo
{
   public:
      void initSkillInfo(tagSKILL_TYPE type, int level, std::string icomName, 
                         std::string name, std::string desc, int actionID,
								 int castMP, float castTime, float coolTime,
                         float castRange, AttackTarget target,
                         AdvancedAttribute effectAttr,
                         FloatPrecentAttribute effectAttrPercent, int bufID,
                         int motionEffects, int triggerMotion, bool requireWeapon,
                         bool requireShield);   //初始設定

      tagSKILL_TYPE         getType();               //取得技能種類
      int                   getLevel();              //取得學習等級
      std::string           geticonName();           //取得圖示
      std::string           getName();               //取得名字
      std::string           getDesc();               //取得說明
      int					    getActionID();		     //取得技能動作ID
      int                   getCastMP();             //取得消耗
      float                 getCastTime();           //取得施法時間
      float                 getCoolDown();           //取得冷卻時間
      float                 getCastRange();          //取得施展距離
      AttackTarget          getTarget();             //取得目標
      AdvancedAttribute     getEffectAttr();         //取得影響屬性
      FloatPrecentAttribute getEffectAttrPercent();  //取得百分比影響屬性
      int					    getBuffID();		        //取得BuffID
      int					    getMotionEffects();	     //取得狀態效果
      int					    getTriggerMotion();	     //取得觸發狀態
      bool                  isRequireWeapon();       //是否需要武器
      bool                  isRequireShield();       //是否需要盾牌

      void                  read(FILE* pFile);  //讀檔
#ifdef _GAMEENGINE_2D_EDITOR_
    void                write(FILE* pFile); //寫檔
#endif //#ifdef _GAMEENGINE_2D_EDITOR_

      SkillClassType        getClassType();
      ~CSkillInfo();

   protected:

   private:
      tagSKILL_TYPE         m_type;               //技能種類
      int                   m_iLevel;		        //學習等級
      std::string           m_iconName;           //圖示
      std::string           m_strName;	           //名字
      std::string           m_strDesc;	           //說明
      int                   m_iActionID;          //技能動作ID
      int                   m_iCastMP;            //消耗
      float                 m_fCastTime;	        //施法時間	
      float                 m_fCoolDown;	        //冷卻時間
      float                 m_fCastRange;	        //施展距離
	   AttackTarget          m_target;	           //目標類型
      AdvancedAttribute     m_effectAttr;         //影響的屬性
      FloatPrecentAttribute m_effectAttrPercent;  //百分比屬性
      int                   m_iBuffID;            //BuffID
      int				       m_iMotionEffects;	  //狀態效果
      int				       m_iTriggerMotion;	  //如果有這狀態增加觸發
      bool                  m_bRequireWeapon;	  //需要武器
      bool                  m_bRequireShield;	  //需要盾牌    
#ifdef _GAMEENGINE_2D_EDITOR_
    friend class DLGSkill;
#endif //#ifdef _GAMEENGINE_2D_EDITOR_
};

#endif