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