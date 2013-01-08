#include "tool_bar_wnd.h"
#include "item.h"

#ifdef _PROJECT_OGRE_3D_
	#include "image_button.h"
#endif

//背包視窗
void ToolBarWnd::init (Window* pw0,  Window* pw1, 
					   Window* pw2, Window* pw3,
					   int _x, int _y)
{
	pTA = NULL ;

	vpWnd[0] = pw0 ;
	vpWnd[1] = pw1 ;
	vpWnd[2] = pw2 ;
	vpWnd[3] = pw3 ;

	x = _x ;
	y = _y ;

	w = UI_COUNT*CELL_SIZE ;
	h = CELL_SIZE ;

#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;

	for (int i = 0; i<UI_COUNT; i++)
	{
		ImageButton* pBtn = new ImageButton ;
		pBtn->init (overlayUI, i*CELL_SIZE, 0, CELL_SIZE, CELL_SIZE, i) ;
		pBtn->setImage ("droplet_x") ;
		addChild (pBtn) ;
	}
#else _PROJECT_GDI_
	for (int i = 0; i<UI_COUNT; i++)
	{
		TextButton* pBtn = new TextButton ;
		pBtn->init (i*CELL_SIZE, 0, CELL_SIZE, CELL_SIZE, i) ;
		addChild (pBtn) ;		
	}	
#endif

	for (int i = 0; i<UI_COUNT; i++)
	{
		pTA = new TextArea ;

#ifdef _PROJECT_OGRE_3D_
		pTA->init (overlayUI, i*CELL_SIZE, 0, CELL_SIZE, CELL_SIZE) ;
		
#else _PROJECT_GDI_
		pTA->init (i*CELL_SIZE, 0, CELL_SIZE, CELL_SIZE) ;		

#endif
		if (i == 0)
			pTA->setText ("背包", 1, 1, 1) ;
		else if (i == 1)
			pTA->setText ("主角", 1, 1, 1) ;
		else if (i == 2)
			pTA->setText ("技能", 1, 1, 1) ;
		else if (i == 3)
			pTA->setText ("地圖", 1, 1, 1) ;
		
		addChild (pTA) ;
	}
}

bool ToolBarWnd::canDrag (int tx, int ty)
{
	return false ;
}

void ToolBarWnd::onCommand (int btnID)
{
//	pTA->setText ("???", 1, 1, 1) ;


	vpWnd[btnID]->bVisible = 
		!(vpWnd[btnID]->bVisible) ;

	vpWnd[btnID]->onSwitch () ;
}

void ToolBarWnd::onMove ()
{
#ifdef _PROJECT_OGRE_3D_
	overlayUI.setPos (x, y) ;
#endif
}

void ToolBarWnd::setZOrder (int z)
{
#ifdef _PROJECT_OGRE_3D_
	overlayUI.setZOrder (z) ;
#endif
}

/*
void ToolBarWnd::onClick (int tx, int ty)
{
	int offset = (tx/CELL_SIZE)-1 ;
	if (offset >= 0)
	{
		vpWnd[offset]->bVisible = 
			!(vpWnd[offset]->bVisible) ;
	}

//	pPlayer->useItem (offset) ;
}
*/

	/*
	void ToolBarWnd::draw (HDC hdc)
	{
		Window::draw (hdc) ;

		for (int i = 0; i<UI_COUNT; i++)
		{
			Rectangle (hdc, x+((i+1)*CELL_SIZE),
							y, x+((i+2)*CELL_SIZE),
							y+CELL_SIZE) ;
		}

	}
	*/
