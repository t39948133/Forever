#ifndef _CTEXTAREAOGRE_H_
#define _CTEXTAREAOGRE_H_
#ifdef _GAMEENGINE_3D_
#include "CWindow.h"
#include "COverlayUI.h"
//#include "text_overlay.h"

#include <OgreTextAreaOverlayElement.h>

class CTextAreaOgre : public CWindow
{
   public:
      CTextAreaOgre();
      ~CTextAreaOgre();

	   void init (COverlayUI&, int _x, int _y, int _w, int _h) ;

      void setText (std::string, float, float, float) ;
	   //Ogre::OverlayContainer* getImage() ;

   private:
	   //TextOverlay textOverlay ;
      Ogre::TextAreaOverlayElement *m_pTextArea;
};

#endif  // #ifdef _GAMEENGINE_3D_
#endif  // #ifndef _CTEXTAREAOGRE_H_