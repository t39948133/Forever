/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPlayerInfoWnd.h
  * @author 林有良
  * @date   2012/12/21
  * @version
  *         2013/01/05 Darren Chen - 整合與修正 */
#ifndef _CTOOLBARWND_H_
#define _CTOOLBARWND_H_
#include "CWindow.h"

#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CToolBarWnd:public CWindow
{
public:
	enum {BUTTON_COUNT = 4, TEXT_COUNT = 4, ICON_SIZE = 38} ;
	CWindow* vpWnd[BUTTON_COUNT] ;//指向按鈕對應的UI

	CToolBarWnd ();
	~CToolBarWnd ();

	void init (CWindow*, CWindow*, CWindow*, CWindow*, int _x, int _y) ;
	// CWindow
	  /* virtual */ bool canDrag(int tx, int ty);
	  /* virtual */ void onLCommand(int btnID);
      /* virtual */ void onDrag();
	  /* virtual */ void setZOrder(int order) ;

private:
  	
#ifdef _GAMEENGINE_3D_	
	  CImageButton   *m_vpBtn[BUTTON_COUNT];
      CTextAreaOgre  *m_vpTextName[TEXT_COUNT];
      CTextAreaOgre  *m_vpText[TEXT_COUNT];
      COverlayUI      m_overlay;  //管理overlay
#elif _GAMEENGINE_2D_
	  CTextButton    *m_vpBtn[BUTTON_COUNT];
      CTextArea      *m_vpTextName[TEXT_COUNT];
      CTextArea      *m_vpText[TEXT_COUNT];
#endif
} ;

#endif  // #ifndef _CTOOLBARWND_H_