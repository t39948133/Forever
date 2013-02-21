#ifndef _CMAPWND_H_
#define _CMAPWND_H_

#include "CWindow.h"

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CMapWnd:public CWindow
{
private:
#ifdef _GAMEENGINE_3D_	
	CImageButton   *m_vpBtn;
	CTextAreaOgre  *m_vpText;
	COverlayUI      m_overlay;  //ºÞ²zoverlay
#elif _GAMEENGINE_2D_
	CTextButton    *m_pBtn;
	CTextArea      *m_pText;
#endif

public:
	enum {CELL_SIZE = 800} ;

	CMapWnd () {};
	~CMapWnd () {};

	void init(int _x, int _y);

	// CWindow
	/* virtual */ bool canDrag(int tx, int ty);    
	/* virtual */ void show(bool bShow);
#ifdef _GAMEENGINE_3D_
	/* virtual */ void onDrag();
	/* virtual */ void setZOrder(int order);
#endif
} ;

#endif