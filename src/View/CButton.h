/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CButton.h
  * @author 林有良
  * @date   2012/12/21
  * @version
  *         2013/01/05 Darren Chen - 整合與修正 */
#ifndef _CBUTTON_H_
#define _CBUTTON_H_
#include "CWindow.h"

class CButton : public CWindow
{
   public:
	   int id ;

	   void init (int _x, int _y, int _w, int _h, int _id) ;
	   virtual void onLClick (int tx, int ty) ;
      virtual void onRClick (int tx, int ty) ;
};

#endif  // #ifndef _CBUTTON_H_