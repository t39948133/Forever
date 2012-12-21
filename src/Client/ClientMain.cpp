#include "Common.h"
#include "CUnitObject.h"
#include "CPlayer.h"
#include "CItem.h"
#include "CWeapon.h"
#include "CItemTable.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{

	AdvancedItem *itemInfo;		//item的項目資料struct
	CItem item;					//要讀取的item
	itemInfo = item.getAll();	//取得資訊

	itemInfo->level=20;				//取name

	if(itemInfo != NULL)
	{
		delete itemInfo;
		itemInfo = NULL;
	}

	CItemTable cta;
	cta.initItemTable();
	cta;

	CItem* pk;
	pk = cta.getInfo(0);

	WeaponWieldType ti;
	ti = ((CWeapon*)pk)->getWield();

	CPlayer player("xXX",123);	//_T _TEXT的意思 可將內容轉為文字用的2個bytes 1個字

	CItemTable* pBPItem;
	pBPItem = player.m_backPack.getItem(0);
	pk = pBPItem->getInfo();
	ti = ((CWeapon*)pk)->getWield();


   return 0;
}