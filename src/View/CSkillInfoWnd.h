#ifndef _SKILLINFOWND_H_
#define _SKILLINFOWND_H_

#include "CWindow.h"
#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"
#include "CTextAreaOgre.h"
#include "COverlayUI.h"
#elif _GAMEENGINE_2D_
#include "CTextButton.h"
#include "CTextArea.h"
#endif  // #ifdef _GAMEENGINE_3D_ && #elif _GAMEENGINE_2D_

class CSkillInfoWnd:public CWindow
{
private:
	enum {TEXT_COUNT = 3} ;
	
#ifdef _GAMEENGINE_3D_	
      CTextAreaOgre  *m_vpText[TEXT_COUNT];
      COverlayUI      m_overlay;  //ºÞ²zoverlay
#elif _GAMEENGINE_2D_
      CTextArea      *m_vpText[TEXT_COUNT];
#endif

public:
	CSkillInfoWnd () ;
	~CSkillInfoWnd () ;

	void init (int _x, int _y) ;
	void setItem (std::string) ;
	void setPos (int _x, int _y) ;
	void show (bool bs) ;
	void draw (HDC hdc, int ox, int oy) ;
	void setZOrder(int order) ;
} ;

#endif