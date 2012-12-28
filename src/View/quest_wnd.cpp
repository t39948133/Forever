#include "quest_wnd.h"
#include "backpack_wnd.h"
#include "item.h"
#include "image_button.h"

//背包視窗
void QuestWnd::init (int _x, int _y, Player* pb)
{
	pPlayer = pb ;
	x = _x ;
	y = _y ;
	w = 200 ;
	h = TEXT_COUNT*CELL_SIZE ;

#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;
	
	for (int i = 0; i<TEXT_COUNT; i++)
	{
		TextArea* pTA = new TextArea ;
		pTA->init (overlayUI, 0, i*CELL_SIZE, w, CELL_SIZE) ;
		if (i == 0)
		{	
			pTA->setText ("任務名稱", 1, 1, 1) ;
		}else if (i == 1)
		{
			pTA->setText ("任務解釋", 1, 1, 1) ;
		}else
		{
		}

		addChild (pTA) ;
	}
#else _PROJECT_GDI_

	TextButton* pBtn = new TextButton ;
	pBtn->init (0, 0, w, h, 0) ;
	addChild (pBtn) ;
	
	for (int i = 0; i<TEXT_COUNT; i++)
	{
		TextArea* pTA = new TextArea ;
		pTA->init (0, i*CELL_SIZE, w, CELL_SIZE) ;
		if (i == 0)
		{	
			pTA->setText ("任務名稱", 1, 1, 1) ;
		}else if (i == 1)
		{
			pTA->setText ("任務解釋", 1, 1, 1) ;
		}else
		{
		}

		addChild (pTA) ;
	}
#endif
}

bool QuestWnd::canDrag (int tx, int ty)
{
	return false ;
}

void QuestWnd::onCommand (int id)
{
}

#ifdef _PROJECT_OGRE_3D_	
void QuestWnd::onMove ()
{
}

void QuestWnd::setZOrder (int z)
{
}

void QuestWnd::onSwitch ()
{
}
#endif

/*
void QuestWnd::draw (HDC hdc, int ox, int oy)
{
	Window::draw (hdc, ox, oy) ;

	int i = 0 ;
	V_QUEST::iterator pi = pPlayer->questMap.vQuest.begin () ;
	while (pi != pPlayer->questMap.vQuest.end ())
	{
		QuestInfo* pinfo = pi->getInfo () ;

		TextOut (hdc, 2+x, 2+y+(i+1)*CELL_SIZE, pinfo->name,
					pinfo->name.length ()) ;

		++ pi ;
		i ++ ;
	}
}
*/


