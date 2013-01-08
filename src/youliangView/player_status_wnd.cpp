#include "player_status_wnd.h"
#include "image_button.h"

void PlayerStatusWnd::init (int _x, int _y, Player* pu)
{
	pPlayer = pu ;
	x = _x ;
	y = _y ;
	w = 230 ;
	h = 78 ;

#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;
	overlayUI.setImage ("KAMEN-stup") ;

	for (int i = 0; i<BUTTON_COUNT; i++)
	{		
		ImageButton* pBtn = new ImageButton ;
		pBtn->init (overlayUI, 25, i*(CELL_SIZE+3)+3*(i+1), w-33, CELL_SIZE, i) ;
		if (i == 0)
		{
			pBtn->setImage ("ogreborder") ;
		}else if (i == 0)
		{
			pBtn->setImage ("ogreborder") ;
		}else 
		{
			pBtn->setImage ("ogreborder") ;
		}
		
		addChild (pBtn) ;
	}

	for (int i = 0; i<TEXT_COUNT; i++)
	{
		TextArea* pTA = new TextArea ;
		pTA->init (overlayUI, 0, i*(CELL_SIZE+3)+3*(i+1), 30, 30) ;
		char buf[256] ;
		if (i == 0)
		{	
			sprintf_s (buf, sizeof (buf), "HP             %d/ %d", pPlayer->data.iHP, pPlayer->data.iHPMax) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 1)
		{
			sprintf_s (buf, sizeof (buf), "MP             %d/ %d", pPlayer->data.iMP, pPlayer->data.iMPMax) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else
		{
			sprintf_s (buf, sizeof (buf), "XP             %d/ %d", pPlayer->data.m_xp, pPlayer->data.m_xpMax) ;
			pTA->setText (buf, 1, 1, 1) ;
		}

		addChild (pTA) ;
	}
#else _PROJECT_GDI_
	for (int i = 0; i<BUTTON_COUNT; i++)
	{
		pvBtn[i] = new TextButton ;
		pvBtn[i]->init (25, i*(CELL_SIZE+3)+3*(i+1), 200, CELL_SIZE, i) ;
		addChild (pvBtn[i]) ;
	}

	for (int i = 0; i<TEXT_COUNT; i++)
	{
		TextArea* pTA = new TextArea ;
		pTA->init (0, i*(CELL_SIZE+3)+3*(i+1), 30, 30) ;
		
		if (i == 0)
		{	

			pTA->setText ("HP", 1, 1, 1) ;
		}else if (i == 1)
		{		
			
			pTA->setText ("MP", 1, 1, 1) ;
		}else
		{	
			
			pTA->setText ("XP", 1, 1, 1) ;
		}

		addChild (pTA) ;
	}

	for (int i = 0; i<TEXT_COUNT; i++)
	{
		TextArea* pTA = new TextArea ;
		pTA->init (100, i*(CELL_SIZE+3)+3*(i+1), 30, 30) ;
		char buf[256] ;
		if (i == 0)
		{	
			sprintf_s (buf, sizeof (buf), "%d/ %d", pPlayer->data.iHP, pPlayer->data.iHPMax) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else if (i == 1)
		{		
			sprintf_s (buf, sizeof (buf), "%d/ %d", pPlayer->data.iMP, pPlayer->data.iMPMax) ;
			pTA->setText (buf, 1, 1, 1) ;
		}else
		{	
			sprintf_s (buf, sizeof (buf), "%d/ %d", pPlayer->data.m_xp, pPlayer->data.m_xpMax) ;
			pTA->setText (buf, 1, 1, 1) ;
		}

		addChild (pTA) ;
	}
#endif
}

bool PlayerStatusWnd::canDrag (int tx, int ty)
{
	return false ;
}

void PlayerStatusWnd::onCommand (int id)
{
}

void PlayerStatusWnd::upDate ()
{
	int HP = pPlayer->getHP () ;

	for (int i = 0; i <BUTTON_COUNT; i++)
	{
		if (i == BUTTON_HP)
			pvBtn[i]->w = 200*HP/pPlayer->data.iHPMax ;		
	}
}


#ifdef _PROJECT_OGRE_3D_
void PlayerStatusWnd::onMove ()
{
	overlayUI.setPos (x, y) ;
}

void PlayerStatusWnd::setZOrder (int z)
{
	overlayUI.setZOrder (z) ;
}
#endif

/*
	void PlayerStatusWnd::draw (HDC hdc)
	{
		Window::draw (hdc, 0, 0) ;
		char buf[256] ;
		sprintf_s (buf, sizeof(buf), "hp:%d", pPlayer->data.hp) ;
		TextOut (hdc, x+2, y+2, buf, strlen (buf)) ;
		sprintf_s (buf, sizeof(buf), "mp:%d", pPlayer->data.mp) ;
		TextOut (hdc, x+2, y+2+20, buf, strlen (buf)) ;
	}
*/
