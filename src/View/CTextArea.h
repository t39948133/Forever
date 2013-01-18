/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CTextArea.h
  * @author 林有良
  * @date   2012/12/21
  * @version
  *         2013/01/05 Darren Chen - 整合與修正 */
#ifndef _CTEXTAREA_H_
#define _CTEXTAREA_H_
#include "CWindow.h"

class CTextArea : public CWindow
{
   private:
      std::string str ;

   public:
	   void init (int _x, int _y, int _w, int _h) ;

      void setText (std::string, float, float, float) ;
	   void draw (HDC hdc, int ox, int oy) ;
};

#endif  // #ifndef _CTEXTAREA_H_