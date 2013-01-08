#ifndef _CSKILLWND_H_
#define _CSKILLWND_H_
#include "CWindow.h"
#include "CPlayer.h"
#include "CTextArea.h"

class CSkillWnd : public CWindow
{
   public:
	   enum {BUTTON_COUNT = 7, CELL_SIZE = 60, TEXT_COUNT = 7} ;
   	
#ifdef _GAMEENGINE_3D_
		OverlayUI overlaySK ;//ºÞ²zoverlay
#endif
	 
	   CPlayer* pPlayer ;

	   ~CSkillWnd () {};

	   void init (int _x, int _y, CPlayer* pb) ;

	   bool canDrag (int tx, int ty) ;
	   void onCommand (int) ;

#ifdef _GAMEENGINE_3D_
	   void onMove () ;

	   void setZOrder (int z) ;
#endif

   //	void onClick (int tx, int ty) ;

      // Add by Darren Chen on 2013/01/07 {
      CTextArea* vpText[TEXT_COUNT];

      WindowClassType getClassType();

#ifdef _GAMEENGINE_2D_
      void draw(HDC hdc, int ox, int oy);
#endif
      // } Add by Darren Chen on 2013/01/07
};

#endif  // #ifndef _CSKILLWND_H_