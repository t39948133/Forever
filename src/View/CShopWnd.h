#ifndef _CSHOPWND_H_
#define _CSHOPWND_H_

#include "CWindow.h"
#include "CPlayer.h"

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CShopWnd:public CWindow
{
private:
	enum {CLOSE_BUTTON = 10, BUTTON_COUNT = 11, 
		SHOP_TEXT = 10, TEXT_COUNT = 11, ICON_SIZE = 50} ;
	CPlayer       *m_pPlayer;

#ifdef _GAMEENGINE_3D_	
	CImageButton   *m_vpBtn[BUTTON_COUNT];
    CTextAreaOgre  *m_vpText[TEXT_COUNT];
    COverlayUI      m_overlay;  //ºÞ²zoverlay
#elif _GAMEENGINE_2D_
	CTextButton    *m_vpBtn[BUTTON_COUNT];
    CTextArea      *m_vpText[TEXT_COUNT];
#endif
	 
public:
	CShopWnd () ;
	~CShopWnd () ;

	void init(int _x, int _y, CPlayer* pb);

	// CWindow
	/* virtual */ bool canDrag(int tx, int ty);
	/* virtual */ void onLCommand(int btnID);
	/* virtual */ void onRCommand(int btnID);
	/* virtual */ void show(bool bShow);
#ifdef _GAMEENGINE_3D_
	/* virtual */ void onDrag();
	/* virtual */ void setZOrder(int order);
#endif
//	void draw (HDC hdc, int ox, int oy) ;
} ;

#endif
