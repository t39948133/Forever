#include "player_info_wnd.h"
#include "image_button.h"
#include "backpack.h"

void PlayerInfoWnd::init (int _x, int _y, Player* pPlr)
{
	bVisible = true ;
	pPlayer = pPlr ;
	x = _x ;
	y = _y ;
	w = 540 ;
	h = 400 ;

	for (int i = 0; i<BUTTON_COUNT; i++)
		playerInfo[i].itemID = -1 ;

#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;
//	overlayUI.getOverlay ()->hide () ;
	overlayUI.setImage ("playerInfo") ;

for (int i = 0; i<BUTTON_COUNT; i++)
	{
		vpBtn[i] = new ImageButton ;

		if (i == 0)//劍
		{
			vpBtn[i]->init (overlayUI, 11, 67, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 1)//盾
		{
			vpBtn[i]->init (overlayUI, 228, 67, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 2)//首飾
		{
			vpBtn[i]->init (overlayUI, 11, 123, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 3)//首飾
		{
			vpBtn[i]->init (overlayUI, 228, 123, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 4)//上衣
		{
			vpBtn[i]->init (overlayUI, 11, 179, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 5)//肩甲
		{
			vpBtn[i]->init (overlayUI, 228, 179, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 6)//褲子
		{
			vpBtn[i]->init (overlayUI, 11, 235, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 7)//手套
		{
			vpBtn[i]->init (overlayUI, 228, 235, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 8)//戒指
		{
			vpBtn[i]->init (overlayUI, 11, 291, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 9)//戒指
		{
			vpBtn[i]->init (overlayUI, 228, 291, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 10)//鞋子
		{
			vpBtn[i]->init (overlayUI, 11, 347, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 11)//腰帶
		{
			vpBtn[i]->init (overlayUI, 228, 347, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 12)//屬性
		{
			vpBtn[i]->init (overlayUI, 285, 65, 250, 333, i) ;
			vpBtn[i]->setImage ("") ;
		}else if (i == 13)//主角圖
		{
			vpBtn[i]->init (overlayUI, 64, 65, 160, 333, i) ;
			vpBtn[i]->setImage ("") ;
		}
		addChild (vpBtn[i]) ;
	}

	//視窗基本資訊
	for (int i = 0; i<3; i++)
	{
		vpText[i] = new TextArea ;
		char buf[256] ;
		if (i == 0)
		{
			vpText[i]->init (overlayUI, 240, 8, 540, 20) ;
			vpText[i]->setText ("角色資訊", 1, 1, 1) ;
		}else if (i == 1)
		{
			vpText[i]->init (overlayUI, 105, 38, 270, 20) ;
			vpText[i]->setText ("主角名稱", 1, 1, 1) ;
		}else if (i == 2)
		{
			vpText[i]->init (overlayUI, 310, 38, 270, 20) ;
			sprintf_s (buf, sizeof (buf), "等級 %d  / 經驗值    %d", pPlayer->data.m_level, pPlayer->data.m_xp) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
		}
		addChild (vpText[i]) ;
	}
		
	for (int i = 3; i<TEXT_COUNT; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (overlayUI, 300, (i-3)*18+66, 200, 20) ;
		char buf[256] ;		
		if (i == 3)
		{
			sprintf_s (buf, sizeof (buf), "生命力                  %d", pPlayer->data.iHP) ;
		}else if (i == 4)
		{
			sprintf_s (buf, sizeof (buf), "精神力                  %d", pPlayer->data.iMP) ;
		}else if (i == 5)
		{
			sprintf_s (buf, sizeof (buf), "最大生命力          %d", pPlayer->data.iHPMax) ;
		}else if (i == 6)
		{
			sprintf_s (buf, sizeof (buf), "最大精神力          %d", pPlayer->data.iMPMax) ;
		}else if (i == 7)
		{
			sprintf_s (buf, sizeof (buf), "物理攻擊力          %d", pPlayer->data.iATK) ;
		}else if (i == 8)
		{
			sprintf_s (buf, sizeof (buf), "物理防禦力          %d", pPlayer->data.iDEF) ;
		}else if (i == 9)
		{
			sprintf_s (buf, sizeof (buf), "物理命中率          %d", pPlayer->data.iHIT) ;
		}else if (i == 10)
		{
			sprintf_s (buf, sizeof (buf), "物理暴擊率          %d", pPlayer->data.iCRI) ;
		}else if (i == 11)
		{
			sprintf_s (buf, sizeof (buf), "魔法攻擊力          %d", pPlayer->data.iMATK) ;
		}else if (i == 12)
		{
			sprintf_s (buf, sizeof (buf), "魔法防禦力          %d", pPlayer->data.iMDEF) ;
		}else if (i == 13)
		{
			sprintf_s (buf, sizeof (buf), "魔法命中率          %d", pPlayer->data.iMHIT) ;
		}else if (i == 14)
		{
			sprintf_s (buf, sizeof (buf), "魔法暴擊率          %d", pPlayer->data.iMCRI) ;
		}else if (i == 15)
		{
			sprintf_s (buf, sizeof (buf), "盾牌防禦力          %d", pPlayer->data.iSDEF) ;
		}else if (i == 16)
		{
			sprintf_s (buf, sizeof (buf), "武器防禦力          %d", pPlayer->data.iWDEF) ;
		}else if (i == 17)
		{
			sprintf_s (buf, sizeof (buf), "迴避率                  %d", pPlayer->data.iFlee) ;
		}else if (i == 18)
		{
			sprintf_s (buf, sizeof (buf), "移動速度              %.1f", pPlayer->data.fMove) ;
		}else if (i == 19)
		{
			sprintf_s (buf, sizeof (buf), "攻擊速度              %.1f", pPlayer->data.fATKSpeed) ;
		}else if (i == 20)
		{
			sprintf_s (buf, sizeof (buf), "施展速度              %.1f", pPlayer->data.fCasting) ;
		}
		vpText[i]->setText (buf, 1, 1, 1) ;
		addChild (vpText[i]) ;
	}

#else _PROJECT_GDI_

for (int i = 0; i<BUTTON_COUNT; i++)
	{
		vpBtn[i] = new TextButton ;

		if (i == 0)//劍
		{
			vpBtn[i]->init (11, 67, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 1)//盾
		{
			vpBtn[i]->init (228, 67, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 2)//首飾
		{
			vpBtn[i]->init (11, 123, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 3)//首飾
		{
			vpBtn[i]->init (228, 123, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 4)//上衣
		{
			vpBtn[i]->init (11, 179, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 5)//肩甲
		{
			vpBtn[i]->init (228, 179, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 6)//褲子
		{
			vpBtn[i]->init (11, 235, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 7)//手套
		{
			vpBtn[i]->init (228, 235, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 8)//戒指
		{
			vpBtn[i]->init (11, 291, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 9)//戒指
		{
			vpBtn[i]->init (228, 291, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 10)//鞋子
		{
			vpBtn[i]->init (11, 347, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 11)//腰帶
		{
			vpBtn[i]->init (228, 347, ICON_SIZE, ICON_SIZE, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 12)//屬性
		{
			vpBtn[i]->init (285, 65, 250, 333, i) ;
			vpBtn[i]->str = "" ;
		}else if (i == 13)//主角圖
		{
			vpBtn[i]->init (64, 65, 160, 333, i) ;
			vpBtn[i]->str = "" ;
		}
		addChild (vpBtn[i]) ;
	}

	//視窗基本資訊
	for (int i = 0; i<3; i++)
	{
		vpText[i] = new TextArea ;
		char buf[256] ;
		if (i == 0)
		{
			vpText[i]->init (240, 8, 540, 20) ;
			vpText[i]->setText ("角色資訊", 1, 1, 1) ;
		}else if (i == 1)
		{
			vpText[i]->init (105, 38, 270, 20) ;
			vpText[i]->setText ("主角名稱", 1, 1, 1) ;
		}else if (i == 2)
		{
			vpText[i]->init (310, 38, 270, 20) ;
			sprintf_s (buf, sizeof (buf), "等級 %d  / 經驗值    %d", pPlayer->data.m_level, pPlayer->data.m_xp) ;
			vpText[i]->setText (buf, 1, 1, 1) ;
		}
		addChild (vpText[i]) ;
	}
		
	for (int i = 3; i<TEXT_COUNT; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (300, (i-3)*18+66, 200, 20) ;
		char buf[256] ;		
		if (i == 3)
		{
			sprintf_s (buf, sizeof (buf), "生命力                  %d", pPlayer->data.iHP) ;
		}else if (i == 4)
		{
			sprintf_s (buf, sizeof (buf), "精神力                  %d", pPlayer->data.iMP) ;
		}else if (i == 5)
		{
			sprintf_s (buf, sizeof (buf), "最大生命力          %d", pPlayer->data.iHPMax) ;
		}else if (i == 6)
		{
			sprintf_s (buf, sizeof (buf), "最大精神力          %d", pPlayer->data.iMPMax) ;
		}else if (i == 7)
		{
			sprintf_s (buf, sizeof (buf), "物理攻擊力          %d", pPlayer->data.iATK) ;
		}else if (i == 8)
		{
			sprintf_s (buf, sizeof (buf), "物理防禦力          %d", pPlayer->data.iDEF) ;
		}else if (i == 9)
		{
			sprintf_s (buf, sizeof (buf), "物理命中率          %d", pPlayer->data.iHIT) ;
		}else if (i == 10)
		{
			sprintf_s (buf, sizeof (buf), "物理暴擊率          %d", pPlayer->data.iCRI) ;
		}else if (i == 11)
		{
			sprintf_s (buf, sizeof (buf), "魔法攻擊力          %d", pPlayer->data.iMATK) ;
		}else if (i == 12)
		{
			sprintf_s (buf, sizeof (buf), "魔法防禦力          %d", pPlayer->data.iMDEF) ;
		}else if (i == 13)
		{
			sprintf_s (buf, sizeof (buf), "魔法命中率          %d", pPlayer->data.iMHIT) ;
		}else if (i == 14)
		{
			sprintf_s (buf, sizeof (buf), "魔法暴擊率          %d", pPlayer->data.iMCRI) ;
		}else if (i == 15)
		{
			sprintf_s (buf, sizeof (buf), "盾牌防禦力          %d", pPlayer->data.iSDEF) ;
		}else if (i == 16)
		{
			sprintf_s (buf, sizeof (buf), "武器防禦力          %d", pPlayer->data.iWDEF) ;
		}else if (i == 17)
		{
			sprintf_s (buf, sizeof (buf), "迴避率                  %d", pPlayer->data.iFlee) ;
		}else if (i == 18)
		{
			sprintf_s (buf, sizeof (buf), "移動速度              %.1f", pPlayer->data.fMove) ;
		}else if (i == 19)
		{
			sprintf_s (buf, sizeof (buf), "攻擊速度              %.1f", pPlayer->data.fATKSpeed) ;
		}else if (i == 20)
		{
			sprintf_s (buf, sizeof (buf), "施展速度              %.1f", pPlayer->data.fCasting) ;
		}
		vpText[i]->setText (buf, 1, 1, 1) ;
		addChild (vpText[i]) ;
	}
#endif
}

bool PlayerInfoWnd::canDrag (int tx, int ty)
{
	return ty < 30 ;
}

void PlayerInfoWnd::onCommand (int id)
{
	
}

void PlayerInfoWnd::wearEquip (int _itemID)//道具編號 
{
/*	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		ItemInfo* pInfo = Item::getInfo (_itemID) ;
		if (pInfo != NULL)
		{			
			playerInfo[i].itemID = _itemID ;
			if (pInfo->equipPos == ItemInfo::EQUIP_WEAPON && i == PlayerInfoWnd::BUTTON_WEAPON)
			{				
#ifdef _PROJECT_OGRE_3D_
					vpBtn[i]->setImage ((const Ogre::String)pInfo->image) ;
#else _PROJECT_GDI_
					vpBtn[i]->str = pInfo->name ;
#endif
					break ;							
			}else if (pInfo->equipPos == ItemInfo::EQUIP_SHIELD && i == PlayerInfoWnd::BUTTON_SHIELD)
			{				
#ifdef _PROJECT_OGRE_3D_
					vpBtn[i]->setImage ((const Ogre::String)pInfo->image) ;
#else _PROJECT_GDI_
					vpBtn[i]->str = pInfo->name ;
#endif
					break ;				
			}			
		}
	}	*/
}

#ifdef _PROJECT_OGRE_3D_
void PlayerInfoWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void PlayerInfoWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}

void PlayerInfoWnd::onSwitch ()
{
	if (bVisible)
		overlayUI.getOverlay ()->show () ;
	else
		overlayUI.getOverlay ()->hide () ;
}
#endif

