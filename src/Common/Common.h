/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   Common.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/11/27 */
#ifndef _COMMON_H_
#define _COMMON_H_
#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
// Add by Darren Chen on 2012/12/22 {
#include <list>
#include <map>
#include <set>
#include <time.h>
#include <math.h>
#include <sstream>
// } Add by Darren Chen on 2012/12/22

#ifdef _GAMEENGINE_3D_
#include <OgreUTFString.h>
#endif

struct BasicAttribute
{
	int iSTR;	//力量
	int iVIT;	//體力
	int iDEX;	//命中
	int iAGI;	//敏捷
	int iINT;	//智力
	int iWIL;	//意志
};

//進階屬性
struct AdvancedAttribute	
{ 
	int iHP;	         //生命力
	int iMP;	         //精神力
	int iHPMax;	      //最大生命力
	int iMPMax;	      //最大精神力
	int iATK;	      //物理攻擊力
	int iDEF;	      //物理防禦力
	int iHIT;	      //物理命中率
	int iCRI;	      //物理暴擊率
	int iMATK;	      //魔法攻擊力
	int iMDEF;	      //魔法防禦力
	int iMHIT;	      //魔法命中率
	int iMCRI;	      //魔法暴擊率
	int iSDEF;	      //盾牌防禦力
	int iWDEF;	      //武器防禦力
	int iFlee;	      //迴避率
	float fMove;      //移動速度 預設值 6.0
	float fATKSpeed;  //攻擊速度 揮擊動作以秒為單位 1下 1.5 秒 預設值 1.5
	float fCasting;   //施展速度 以秒為單位 1.0 秒 預設值 1.0
};

struct ObscureAttribute
{
	int iHPR;			//生命回復量
	int iMPR;			//精神回復量
};

//裝備槽
enum EquipSlot	
{
   SLOT_NULL,
	MAIN_HAND,	//主手
	OFF_HAND,	//副手
	CHEST,		//上衣
	LEGS,		   //褲子
	SHOULDER,	//護肩
	GLOVE,		//手套
	BOOT,		   //鞋子
   BELT,       //腰帶
   MAX_SLOT
};

enum ItemClassType
{
	WEAPON,
	ARMOR,
	CONSUMABLE,
};

//物品種類
enum ItemType	
{
	DAGGER,		//匕首
	SWORD,		//長劍
	MACE,		   //釘錘
	STAVE,		//法杖
	SPELLBOOK,	//法書
	ORB,		   //法珠
	GREATSWORD,	//巨劍
	POLEARM,	   //戰戟
	BOW,		   //弓
	CLOTH,		//長袍
	LEATHER,	   //皮甲
	CHAIN,		//鏈甲
	PLATE,		//金屬甲
	SHIELDS,	   //盾牌
	POTION,		//藥水
	FOOD,		   //食物
	SCROLL,		//卷軸
	ITEM_TYPE_TOTAL,	//總數
};

//裝備品質
enum EquipQuality	
{
	COMMON,	//普通
	RARE,	   //稀有
	LEGEND,	//傳承
	UNIQUE,	//獨特
	EPIC	//英雄
};

//單持武器/雙持
enum WeaponWieldType	
{
	ONE_HAND,	//主手
	TWO_HAND	   //副手
};

//裝備位置
enum ArmorWearType	
{
	CLOTHES,	   //衣服
	BELTS,		//腰帶
	PANTS,		//褲子
	PAULDRONS,	//護肩
	GLOVES,		//手套
	BOOTS		   //鞋子
};

struct AdvancedItem
{
	std::string name;	//名稱
	std::string iconName;//圖示名稱
	ItemType type;		//種類
	bool soulBind;		//綁定
	char level;			//等級
	int stackLimit;		//堆疊上限
	int sellPrice;		//賣價
	int buyPrice;		//買價
};

enum EdibleEffectType
{
	EDIBLE_HP,		//補血
	EDIBLE_MP,		//補魔
	EDIBLE_HP_MAX,	//增加最大血量
	EDIBLE_MP_MAX,	//增加最大魔量
	EDIBLE_SKILL,	//技能
};

enum AttackTarget
{
	ENEMY,				//怪物
	TEAM,				//友方
	SELF,				//自己
	GROUND,				//範圍
};

struct ComplexAttribute
{
	AdvancedAttribute AdvAttr;		//影響屬性
	ObscureAttribute ObsAttr;
};

struct FloatPrecentAttribute
{
    float fHP;			//生命力
	float fMP;			//精神力
	float fHPMax;			//最大生命力
	float fMPMax;			//最大精神力
	float fATK;			//物理攻擊力
	float fDEF;			//物理防禦力
	float fHIT;			//物理命中率
	float fCRI;			//物理暴擊率
	float fMATK;			//魔法攻擊力
	float fMDEF;			//魔法防禦力
	float fMHIT;			//魔法命中率
	float fMCRI;			//魔法暴擊率
	float fSDEF;			//盾牌防禦力
	float fWDEF;			//武器防禦力
	float fFlee;			//迴避率
	float fMove;		//移動速度 預設值 6.0
	float fATKSpeed;	//攻擊速度 揮擊動作以秒為單位 1下 1.5 秒 預設值 1.5
	float fCasting;		//施展速度 以秒為單位 1.0 秒 預設值 1.0
    float fHPR;			//生命回復量
	float fMPR;			//精神回復量
};

enum tagSKILL_TYPE 
{
	TYPE_ACTIVE,    // 主動技能
	TYPE_PASSIVE    // 被動技能
};

enum SkillClassType
{
    SKILL,
};

enum BuffClassType
{
	BUFF,
};

enum MonsterType
{
    MONSTER_ACTIVE,     //主動
    MONSTER_PASSIVE,    //被動
};

enum MonsterGrade
{
    REGULAR_GRADE, //普通
    ELITE_GRADE,  //菁英
    HERO_GRADE,   //英雄
    LEGEND_GRADE, //傳說
};

enum MonsterClass
{
    MONSTER,
};

enum MonsterArea
{
	MONSTERAREA,
};

struct AngerValue
{
    long long uid;
    int iHatred;
};

enum MonsterState
{
    IDLE,       //閒置
    DOLLY,      //移動
    GOALS,      //得到攻擊目標
    ATTACK,     //攻擊
    RETURN,     //返回
    ESTABLISH,  //建立中
};

const int BACK_ROW = 9;		//row橫 
const int BACK_COLUMN = 3;	//column直
const int BACK_MAX = BACK_ROW * BACK_COLUMN;	//格數
const int SKILL_MAX = 11;
const int UI_HOTKEY_NUM = 10;

// Add by Darren Chen on 2012/12/13 {
/** @brief 取得目前系統的日期與時間
  * @return 字串型態的日期與時間(格式: "2013/01/01 23:59:59") */
std::string getCurDateTime();

/** @brief 取得滑鼠座標(Client區座標)
  * @param [in] hWnd 要取得哪個視窗的座標
  * @param [out] cx  滑鼠X座標
  * @param [out] cy  滑鼠Y座標 */
void getMousePos(HWND hWnd, int &cx, int &cy);

/** @brief 取得滑鼠的螢幕座標
  * @param [out] cx 滑鼠X座標
  * @param [out] cy 滑鼠Y座標 */
void getMouseScreenPos(int &cx, int &cy);

/** @brief 取得兩個座標點之間的距離
  * @param x1 第一個座標點X
  * @param y1 第一個座標點Y
  * @param x2 第二個座標點X
  * @param y2 第二個座標點Y
  * @return 兩點之間的距離 */
float getDistance(float x1, float y1, float x2, float y2);

/** @brief 移動第一個座標點位置到第二個座標點
  * @param [in/out] x1 第一個座標點X
  * @param [in/out] y1 第一個座標點Y
  * @param [in] x2     第二個座標點X
  * @param [in] y2     第二個座標點Y
  * @param [in] step   每次移動的距離 */   
void movePoint(float &x1, float &y1, float x2, float y2, float step); 

#ifdef _GAMEENGINE_3D_
Ogre::UTFString ConvertToUTFString(const std::string & str);
#endif

template<class T>
    std::string toString(const T& t)
{
     std::ostringstream stream;
     stream << t;
     return stream.str();
}

template<class T>
    T fromString(const std::string& s)
{
     std::istringstream stream (s);
     T t;
     stream >> t;
     return t;
}

typedef enum tagACTION_EVENT_TYPE {
   AET_NULL,                  // 沒有事件
   AET_REACH,                 // 到達目標點   (座標無更動)
   AET_NOT_REACH,             // 未到達目標點 (座標更動中)
   AET_KEY,                   // 快捷鍵
   AET_KEY_WASD,              // WASD按鍵
   AET_CAST_SKILL,            // 施展技能
   AET_DAMAGE,                // 受傷
   AET_DIE,                   // 死亡

   //--- 以下是動作系統發出的訊息
   AET_NOTIFY_BEGIN = 200,    // 通知訊息的開始, 此訊息動作編輯器不使用
   AET_NOTIFY_DRAW_WEAPON,    // 拔武器
   AET_NOTIFY_PUTIN_WEAPON,   // 收武器
   AET_NOTIFY_PLAY_SOUND,     // 播放動作音效
   AET_NOTIFY_ATTACK,         // 攻擊扣血
} ACTION_EVENT_TYPE;  // 動作事件種類

const std::string SOUND_DIR   = "../media/sound/";  // 音效路徑
const int ACTION_IDLE         = 1;  // 等待
const int ACTION_RUN          = 2;  // 跑步
const int ACTION_DRAW_WEAPON  = 3;  // 拔出武器
const int ACTION_FIGHT        = 4;  // 戰鬥姿態
const int ACTION_FIGHT_RUN    = 5;  // 戰鬥姿態跑步
const int ACTION_PUTIN_WEAPON = 6;  // 收回武器
const int ACTION_ATTACK       = 7;  // 普通攻擊
const int ACTION_DAMAGE       = 8;  // 受到傷害
const int ACTION_DIE          = 9;  // 死亡
// } Add by Darren Chen on 2012/12/13

typedef struct tagPOSITION {
   float fX;
   float fY;
} FPOS;

enum NPCType
{
	STORE,		//商店
	VILLAGER,	//對話
	PRINCIPAL,	//任務
};

enum NPCClassType
{
	NPC,
};

enum QuestType
{
	KILL,		//殺怪
	TALK,		//對話
	TAKE,		//收集物品
};

enum QuestClassType
{
	QUEST,
};

enum QuestState
{
	QUEST_NULL,			//這任務不能接
	QUEST_CAN_TAKE,		//這任務可以接
	QUEST_WORKING,		//正在進行
	QUEST_FINISH		//這任務已繳交完成
};

struct Reware
{
	int ItemKind;
	int ItemStack;
};

#endif  // #ifndef _COMMON_H_