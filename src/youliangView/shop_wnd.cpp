#include "shop_wnd.h"
#include "item.h"
#include "image_button.h"


void ShopWnd::init (int _x, int _y, Player* pb, ItemInfoWnd* pi)
{
	bVisible = true ;
	pPlayer = pb ;
	pItemInfoWnd = pi ;
	x = _x ;
	y = _y ;
	w = 410 ;
	h = 351 ;

#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;
	overlayUI.setImage ("shop") ;

	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			vpBtn[i*2+m] = new ImageButton ;
			vpBtn[i*2+m]->init (overlayUI, m*205+4, i*60+55, ICON_SIZE, ICON_SIZE, i*2+m) ;
			ItemInfo* pInfo = Item::getInfo (i*2+m) ;
			vpBtn[i*2+m]->setImage ((const Ogre::String)pInfo->image) ;
			addChild (vpBtn[i*2+m]) ;
		}

	//close button
	vpBtn[CLOSE_BUTTON] = new ImageButton ;
	vpBtn[CLOSE_BUTTON]->init (overlayUI, 400, 5, 20, 20, CLOSE_BUTTON) ;
	vpBtn[CLOSE_BUTTON]->setImage ("") ;
	addChild (vpBtn[CLOSE_BUTTON]) ;

	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			vpText[i*2+m] = new TextArea ;
			vpText[i*2+m]->init (overlayUI, m*205+64, i*60+55, 180, 60) ;
			ItemInfo* pInfo = Item::getInfo (i*2+m) ;
			vpText[i*2+m]->setText (pInfo->name, 0, 0, 1) ;
			addChild (vpText[i*2+m]) ;
		}

	vpText[CLOSE_TEXT] = new TextArea ;
	vpText[CLOSE_TEXT]->init (overlayUI, 400, 5, 20, 20) ;
	vpText[CLOSE_TEXT]->setText ("X", 1, 1, 1) ;
	addChild (vpText[CLOSE_TEXT]) ;

	vpText[SHOP_TEXT] = new TextArea ;
	vpText[SHOP_TEXT]->init (overlayUI, 185, 15, 40, 20) ;
	vpText[SHOP_TEXT]->setText ("°Ó©±", 1, 1, 1) ;
	addChild (vpText[SHOP_TEXT]) ;

		
#else _PROJECT_GDI_
	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			vpBtn[i*2+m] = new TextButton ;
			vpBtn[i*2+m]->init (m*205+4, i*60+55, ICON_SIZE, ICON_SIZE, i*2+m) ;
			ItemInfo* pInfo = Item::getInfo (i*2+m) ;
			vpBtn[i*2+m]->str = pInfo->name ;
			addChild (vpBtn[i*2+m]) ;
		}

	//close button
	vpBtn[CLOSE_BUTTON] = new TextButton ;
	vpBtn[CLOSE_BUTTON]->init (400, 5, 20, 20, CLOSE_BUTTON) ;
	vpBtn[CLOSE_BUTTON]->str = "" ;
	addChild (vpBtn[CLOSE_BUTTON]) ;

	for (int i = 0; i<5; i++)
		for (int m = 0; m<2; m++)
		{		
			vpText[i*2+m] = new TextArea ;
			vpText[i*2+m]->init (m*205+64, i*60+55, 180, 60) ;
			ItemInfo* pInfo = Item::getInfo (i*2+m) ;
			vpText[i*2+m]->setText (pInfo->name, 0, 0, 1) ;
			addChild (vpText[i*2+m]) ;
		}

	vpText[CLOSE_TEXT] = new TextArea ;
	vpText[CLOSE_TEXT]->init (400, 5, 20, 20) ;
	vpText[CLOSE_TEXT]->setText ("X", 1, 1, 1) ;
	addChild (vpText[CLOSE_TEXT]) ;

	vpText[SHOP_TEXT] = new TextArea ;
	vpText[SHOP_TEXT]->init (185, 15, 40, 20) ;
	vpText[SHOP_TEXT]->setText ("°Ó©±", 1, 1, 1) ;
	addChild (vpText[SHOP_TEXT]) ;

#endif
}

bool ShopWnd::canDrag (int tx, int ty)
{
	return ty < 60 ;
}

void ShopWnd::onCommand (int id)
{
}

void ShopWnd::onCommandFocus (int id)
{
	Item* pItem = pPlayer->backpack.getItem (id) ;
	if (pItem != NULL)
	{
		ItemInfo* pInfo = pItem->getInfo () ;
		if (pInfo != NULL)
		{
			pItemInfoWnd->setItem (pInfo->name) ;	
			pItemInfoWnd->setPos (x+(id%2)*205+60, y+(id/2)*60+20) ; 
			setInfoWnd (pItemInfoWnd) ;
			pItemInfoWnd->show (true) ;
		}else
		{
			pItemInfoWnd->show (false) ;
		}
	}else
	{
		pItemInfoWnd->show (false) ;
	}
}

#ifdef _PROJECT_OGRE_3D_
void ShopWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void ShopWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}

void ShopWnd::onSwitch ()
{
	if (bVisible)
		overlayUI.getOverlay ()->show () ;
	else
		overlayUI.getOverlay ()->hide () ;
}
#endif

