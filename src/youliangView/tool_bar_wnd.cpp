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
	pText = NULL ;

	vpWnd[0] = pw0 ;
	vpWnd[1] = pw1 ;
	vpWnd[2] = pw2 ;
	vpWnd[3] = pw3 ;

	x = _x ;
	y = _y ;

	w = 300 ;
	h = 71 ;

#ifdef _PROJECT_OGRE_3D_
	overlayUI.init (x, y, w, h) ;
	overlayUI.setImage ("toolbar") ;

	for (int i = 0; i<UI_COUNT; i++)
	{
		ImageButton* pBtn = new ImageButton ;
		pBtn->init (overlayUI, (i*49)+60, 17, ICON_SIZE, ICON_SIZE, i) ;
		if (i == 0)
			pBtn->setImage ("") ;
		else if (i == 1)
			pBtn->setImage ("") ;
		else if (i == 2)
			pBtn->setImage ("") ;
		else if (i == 3)
			pBtn->setImage ("") ;
		addChild (pBtn) ;
	}
#else _PROJECT_GDI_
	for (int i = 0; i<UI_COUNT; i++)
	{
		TextButton* pBtn = new TextButton ;
		pBtn->init (i*ICON_SIZE, 0, ICON_SIZE, ICON_SIZE, i) ;
		addChild (pBtn) ;		
	}	

	for (int i = 0; i<UI_COUNT; i++)
	{
		pText = new TextArea ;
		pText->init (i*ICON_SIZE, 0, ICON_SIZE, ICON_SIZE) ;
		if (i == 0)
			pText->setText ("背包", 1, 1, 1) ;
		else if (i == 1)
			pText->setText ("主角", 1, 1, 1) ;
		else if (i == 2)
			pText->setText ("技能", 1, 1, 1) ;
		else if (i == 3)
			pText->setText ("地圖", 1, 1, 1) ;
		
		addChild (pText) ;
	}
#endif
}

bool ToolBarWnd::canDrag (int tx, int ty)
{
	return false ;
}

void ToolBarWnd::onCommand (int btnID)
{
	vpWnd[btnID]->bVisible = 
		!(vpWnd[btnID]->bVisible) ;

#ifdef _PROJECT_OGRE_3D_
	vpWnd[btnID]->onSwitch () ;
#endif
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
