#ifndef _CMONSTERINFO_H_
#define _CMONSTERINFO_H_

#include "Common.h"

class CMonsterInfo
{
public:
    CMonsterInfo();
    ~CMonsterInfo();
    std::string         getName();          //取得名稱
    std::string         getDesc();          //取得說明
    std::string         getMeshName();      //取得模型名稱
    std::string         getMeshTexture();   //取得模型貼圖
    char                getWistom();        //取得AI等級
    unsigned int        getxp();            //取得基本經驗
    MonsterType         getATKtype();       //取得攻擊類型
    MonsterGrade        getLevelGrade();    //取得階級類型
    float               getAlert();         //取得警戒範圍
    float               getRegress();       //取得追擊範圍
    BasicAttribute      getBasAttr();       //取得基本素質
    void initMonsterInfo(std::string name, std::string desc,
                         std::string meshName, std::string meshTexture, char wistom,
                         unsigned int xp, MonsterType atkType, MonsterGrade levelGrade, float alert,
		                   float regress, BasicAttribute basAttr);  //初始設定

    void                read(FILE* pFile);  //讀檔
    void                write(FILE* pFile); //寫檔
    MonsterClass        getClassType();     //取得型態類別

private:
    std::string         m_strName;          //名稱
    std::string         m_strDesc;          //說明
    std::string         m_strMeshName;      //模型名稱
    std::string         m_strMeshTexture;   //模型貼圖
    char                m_Wistom;           //AI等級
    unsigned int        m_ixp;              //1等時的基本經驗
                                            //(角色取得經驗:基本經驗乘上怪物等級)
    MonsterType         m_ATKtype;          //主動、被動攻擊
    MonsterGrade        m_LevelGrade;       //階級
    float               m_fAlert;           //警戒範圍
    float               m_fRegress;         //追擊範圍
    BasicAttribute      m_basAttr;          //基本素質
};

#endif