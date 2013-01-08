/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CBackpackWnd.h
  * @author 林有良
  * @date   2012/12/21
  *         2013/01/05 整合與修正 by Darren Chen */
#ifndef _CBACKPACKWND_H_
#define _CBACKPACKWND_H_
#include "CWindow.h"
#include "CPlayer.h"
#include "CTextButton.h"
#include "CTextArea.h"

class CBackpackWnd : public CWindow
{
   public:
	   enum {BUTTON_COUNT = BACK_MAX, CELL_SIZE = 60, TEXT_COUNT = BACK_MAX + 2} ;
   	
	   CPlayer* pPlayer ;

#ifdef _GAMEENGINE_3D_	
	   ImageButton* vpBtn[BUTTON_COUNT] ;
#elif _GAMEENGINE_2D_
	   CTextButton* vpBtn[BUTTON_COUNT] ;
#endif
	   CTextArea* vpText[TEXT_COUNT];

	   ~CBackpackWnd () {};

      void init(int _x, int _y, CPlayer *pb);

	   bool canDrag (int tx, int ty) ;

	   void onRCommand (int) ;

#ifdef _GAMEENGINE_3D_	
	   void onMove () ;

	   void setZOrder (int z) ;
	   void onSwitch () ;
#endif
   //	void onClick (int tx, int ty) ;

   // Add by Darren on 2013/01/07 {
      WindowClassType getClassType();

#ifdef _GAMEENGINE_2D_
      void draw(HDC hdc, int ox, int oy);
#endif
   // } Add by Darren Chen on 2013/01/07
};

#endif  // #ifndef _CBACKPACKWND_H_