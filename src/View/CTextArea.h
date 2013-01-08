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