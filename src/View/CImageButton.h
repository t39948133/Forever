#ifndef _CIMAGEBUTTON_H_
#define _CIMAGEBUTTON_H_
#ifdef _GAMEENGINE_3D_
#include "CFButton.h"
#include "COverlayUI.h"

class CImageButton : public CFButton
{
   public:
	   CImageButton();
      ~CImageButton();
   
	   void init(COverlayUI&, int _x, int _y, int _w, 
					   int _h, int _id) ;

	   Ogre::OverlayContainer* getImage();
      void setImage(std::string st);

   private:
	   Ogre::OverlayContainer *m_pImage;
};

#endif  // #ifdef _GAMEENGINE_3D_
#endif  // #ifndef _CIMAGEBUTTON_H_