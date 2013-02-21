#ifndef _CMONSTERINFO_H_
#define _CMONSTERINFO_H_

#include "Common.h"
#include "CSkill.h"

class CMonsterInfo
{
   public:
      CMonsterInfo();
      ~CMonsterInfo();//加delet skill

      std::string           getName();          //取得名稱
      std::string           getDesc();          //取得說明
      std::string           getMeshName();      //取得模型名稱
      char                  getWistom();        //取得AI等級
      unsigned int          getxp();            //取得給予經驗
      MonsterType           getATKtype();       //取得攻擊類型
      MonsterGrade          getLevelGrade();    //取得階級類型
      float                 getAlert();         //取得警戒範圍
      float                 getRegress();       //取得追擊範圍
      AdvancedAttribute     getAdvAttr();       //取得基本素質

      //---1/19--add-
      std::string           getActionSystemFile();    //取得動作檔案名稱
      char                  getLevel();         //取得等級
      long long             getMoney();         //取得掉落金錢
      std::vector<int>      getReware();        //取得掉落物品ID
      std::vector<int>      getSkill();         //取得擁有的技能ID

      //--1/19
      void initMonsterInfo(std::string name, std::string desc,
                           std::string meshName, std::string actionSystem,
                           char level, char wistom, unsigned int xp, MonsterType atkType,
                           MonsterGrade levelGrade, float alert, float regress, AdvancedAttribute advAttr,
                           long long money, std::vector<int> reware, std::vector<int> skill);  //初始設定

      void                  read(FILE* pFile);  //讀檔
      void                  write(FILE* pFile); //寫檔
      MonsterClass          getClassType();     //取得型態類別

   private:
      std::string           m_strName;          //名稱
      std::string           m_strDesc;          //說明
      std::string           m_strMeshName;      //模型名稱
      std::string           m_strActionSystemFile;    //動作檔案名稱
      char                  m_Level;            //等級
      char                  m_Wistom;           //AI等級
      unsigned int          m_ixp;              //給予經驗
      MonsterType           m_ATKtype;          //主動、被動攻擊
      MonsterGrade          m_LevelGrade;       //階級
      float                 m_fAlert;           //警戒範圍
      float                 m_fRegress;         //追擊範圍
      AdvancedAttribute     m_advAttr;          //基本素質
      long long             m_Money;            //掉落金錢
      std::vector<int>      m_vReware;          //掉落物品ID
      std::vector<int>      m_vSkill;           //技能ID
};

#endif