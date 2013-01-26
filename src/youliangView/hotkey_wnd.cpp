#include "hotkey_wnd.h"
#include "item.h"
#include "skill.h"

void HotKeyWnd::init (int _x, int _y, Player* pPlr)
{
	pPlayer = pPlr ;

	x = _x ;
	y = _y ;
	w = BUTTON_COUNT*ICON_SIZE ;
	h = ICON_SIZE ;

	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		hotKeyInfo[i].type = HotKeyInfo::TYPE_NULL ;
		hotKeyInfo[i].itemID = -1 ;
	}
	

#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;

	//熱鍵內容(食物或技能)
	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		vpBtn[i] = new ImageButton ;
		vpBtn[i]->init (overlayUI, i*35, 0, ICON_SIZE, ICON_SIZE, i) ;
		ItemInfo* pInfo = Item::getInfo (i) ;
		vpBtn[i]->setImage ((const Ogre::String)pInfo->image) ;
		addChild (vpBtn[i]) ;
	}

	//相對應熱鍵值
	for (int i = 0; i<TEXT_COUNT/2; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (overlayUI, i*35, 0, ICON_SIZE, ICON_SIZE) ;
		char buf[256] ;
		if (i == TEXT_COUNT/2-1)
		{
			vpText[i]->setText ("0", 1, 1, 0) ;
		}else
		{
			sprintf_s (buf, sizeof (buf), "%d", i+1) ;
			vpText[i]->setText (buf, 1, 1, 0) ;
		}
		
		addChild (vpText[i]) ;
	}

	//堆疊數量
	for (int i = TEXT_COUNT/2; i<TEXT_COUNT; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (overlayUI, (i-TEXT_COUNT/2)*ICON_SIZE+20, 20, ICON_SIZE,ICON_SIZE) ;		
		addChild (vpText[i]) ;
	}	

#else _PROJECT_GDI_
	//熱鍵內容(食物或技能)
	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		vpBtn[i] = new TextButton ;
		vpBtn[i]->init (i*ICON_SIZE, 0, ICON_SIZE, ICON_SIZE, i) ;
		addChild (vpBtn[i]) ;
	}

	//相對應熱鍵值
	for (int i = 0; i<TEXT_COUNT/2; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init (i*ICON_SIZE, -18, ICON_SIZE, ICON_SIZE) ;
		char buf[256] ;
		if (i == TEXT_COUNT/2-1)
		{
			vpText[i]->setText ("0", 1, 1, 0) ;
		}else
		{
			sprintf_s (buf, sizeof (buf), "%d", i+1) ;
			vpText[i]->setText (buf, 1, 1, 0) ;
		}
		
		addChild (vpText[i]) ;
	}

	//堆疊數量
	for (int i = TEXT_COUNT/2; i<TEXT_COUNT; i++)
	{
		vpText[i] = new TextArea ;
		vpText[i]->init ((i-TEXT_COUNT/2)*ICON_SIZE+20, 20, ICON_SIZE, ICON_SIZE) ;		
		addChild (vpText[i]) ;
	}
	
#endif
}

bool HotKeyWnd::canDrag (int tx, int ty)
{
	return false ;
}

void HotKeyWnd::addFoodHotKey (int id, int _itemID)//道具編號 
{
	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		if (hotKeyInfo[i].type == HotKeyInfo::TYPE_FOOD && 
			hotKeyInfo[i].itemID == _itemID)
		{
			break ;			
		}

		if (hotKeyInfo[i].type == HotKeyInfo::TYPE_SKILL)
		{
		}else if (hotKeyInfo[i].type == HotKeyInfo::TYPE_NULL)
		{
			hotKeyInfo[i].type = HotKeyInfo::TYPE_FOOD ;			
			hotKeyInfo[i].itemID = _itemID ;

			Item* pItem = pPlayer->backpack.getItem (id) ;
			if (pItem != NULL)
			{
				ItemInfo* pInfo = pItem->getInfo () ;
				if (pInfo != NULL)
				{
#ifdef _PROJECT_OGRE_3D_
					vpBtn[i]->setImage ((const Ogre::String)pInfo->image) ;
#else _PROJECT_GDI_
					vpBtn[i]->str = pInfo->name ;
#endif					
					char buf[256] ;
					sprintf_s (buf, sizeof (buf), "%d", pItem->getStack ()) ;
					vpText[i+10]->setText (buf, 0, 1, 0) ;
					break ;
				}
			}			
		}		
	}
}

void HotKeyWnd::addSkillHotKey (int id)
{
	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		if (hotKeyInfo[i].type == HotKeyInfo::TYPE_SKILL && hotKeyInfo[i].skillID == id )
		{
			break ;			
		}

		if (hotKeyInfo[i].type == HotKeyInfo::TYPE_FOOD)
		{
		}else if (hotKeyInfo[i].type == HotKeyInfo::TYPE_NULL)
		{
			hotKeyInfo[i].type = HotKeyInfo::TYPE_SKILL ;
			
			hotKeyInfo[i].skillID = id ;

			SkillInfo* pInfo = Skill::getInfo (id) ;
			if (pInfo != NULL)
			{
#ifdef _PROJECT_OGRE_3D_
				vpBtn[i]->setImage ((const Ogre::String)pInfo->image) ;
#else _PROJECT_GDI_
				vpBtn[i]->str = pInfo->name ;
#endif
					break ;
			}
		}		
	}
}

void HotKeyWnd::onCommand (int id)
{
	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		if (hotKeyInfo[i].type == HotKeyInfo::TYPE_NULL)
		{
			break ;
		}else if (hotKeyInfo[i].type == HotKeyInfo::TYPE_FOOD)
		{
		}else if (hotKeyInfo[i].type == HotKeyInfo::TYPE_SKILL)
		{
		}
	}
}

void HotKeyWnd::onCommandR (int id)
{
	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		if (i == id)
		{
			hotKeyInfo[i].type = HotKeyInfo::TYPE_NULL ;			
			hotKeyInfo[i].itemID = -1 ;

#ifdef _PROJECT_OGRE_3D_
			vpBtn[i]->setImage ("") ;
#else _PROJECT_GDI_
			vpBtn[i]->str = "" ;
#endif
			vpText[i+10]->setText ("", 0, 1, 0) ;
			break ;
		}		
	}
}

#ifdef _PROJECT_OGRE_3D_
void HotKeyWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void HotKeyWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}
#endif





