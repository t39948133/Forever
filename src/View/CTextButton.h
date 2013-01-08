#ifndef _CTEXTBUTTON_H_
#define _CTEXTBUTTON_H_
#include "CButton.h"

class CTextButton : public CButton
{
   public:
      std::string str ;

	   void draw (HDC hdc, int ox, int oy) ;
};

#endif  // #ifndef _CTEXTBUTTON_H_