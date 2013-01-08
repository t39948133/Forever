/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPlayerInfoWnd.h
  * @author 林有良
  * @date   2012/12/21
  *         2013/01/05 整合與修正 by Darren Chen */
#ifndef _CPLAYERINFOWND_H_
#define _CPLAYERINFOWND_H_
#include "CWindow.h"
#include "CPlayer.h"
#include "CTextButton.h"
#include "CTextArea.h"

class CPlayerInfoWnd : public CWindow
{
   private:
	   CPlayer* pPlayer ;
   	
   public:
	   enum {BUTTON_SPAULDER, BUTTON_GLOVE, BUTTON_WEAPON, BUTTON_CLOTHES,
	   BUTTON_PANTS, BUTTON_SHIELD, BUTTON_SHOES, BUTTON_UI_NAME, BUTTON_PLAYER_NAME, 
	   BUTTON_LEVEL_EXP, BUTTON_ATTRIBUTE, BUTTON_PLAYER_IMAGE, BUTTON_COUNT} ;

	   enum {CELL_SIZE = 20, TEXT_COUNT = 21} ;

	   ~CPlayerInfoWnd () {};

#ifdef _GAMEENGINE_3D_	
	   ImageButton* vpBtn[BUTTON_COUNT] ;
#elif _GAMEENGINE_2D_
	   CTextButton* vpBtn[BUTTON_COUNT] ;
#endif
	   CTextArea* vpText[TEXT_COUNT];

	   void init (int _x, int _y, CPlayer* pPlr) ;

	   bool canDrag (int tx, int ty) ;

	   void onRCommand (int id) ;

#ifdef _GAMEENGINE_3D_	
	   void onMove () ;

	   void setZOrder (int z) ;
	   void onSwitch () ;
#endif

   // Add by Darren on 2013/01/07 {
      WindowClassType getClassType();

#ifdef _GAMEENGINE_2D_
      void draw(HDC hdc, int ox, int oy);
#endif
   // } Add by Darren Chen on 2013/01/07
};

#endif  // #ifndef _CPLAYERINFOWND_H_