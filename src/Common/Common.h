/** Copyright (c) 2012-2013 Digital Content Institute.
  * All Rights Reserved.
  *
  * @檔案:     Common.h
  * @用途:     共用
  * @開發者: 
  * @更新日期: 2012/11/27 */
#ifndef _COMMON_H_
#define _COMMON_H_
#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

struct AdvancedAttribute	//進階屬性
{ 
	int iHP;	//生命力
	int iMP;	//精神力
	int iHPMax;	//最大生命力
	int iMPMax;	//最大精神力
	int iATK;	//物理攻擊力
	int	iDEF;	//物理防禦力
	int iHIT;	//物理命中率
	int iCRI;	//物理暴擊率
	int iMATK;	//魔法攻擊力
	int iMDEF;	//魔法防禦力
	int	iMHIT;	//魔法命中率
	int iMCRI;	//魔法暴擊率
	int iSDEF;	//盾牌防禦力
	int iWDEF;	//武器防禦力
	int iFlee;	//迴避率
	float fMove;//移動速度 預設值 6.0
	float fATKSpeed;//攻擊速度 揮擊動作以秒為單位 1下 1.5 秒 預設值 1.5
	float fCasting;//施展速度 以秒為單位 1.0 秒 預設值 1.0
	
};

enum EquipSlot	//裝備槽
{
	MAIN_HAND,	//主手
	OFF_HAND,	//副手
	CHEST,		//上衣
	LEGS,		//褲子
	SHOULDER,	//肩甲
	GLOVES,		//手套
	BOOTS		//鞋子
};



#endif  //_COMMON_H_