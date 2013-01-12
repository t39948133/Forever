#ifndef _COVERLAYUI_H_
#define _COVERLAYUI_H_
#ifdef _GAMEENGINE_3D_
#include "Common.h"

#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>

class CImageButton;
class COverlayUI
{
   public:
      COverlayUI();
      ~COverlayUI();

      void init(int, int, int, int);  //«Ø¥ßoverlay
	   void setPos(int, int);
	   void setZOrder(int);
      void setBackImage(std::string st);

	   void addImage(CImageButton *pImgBtn);
	   //void addImage(TextArea&);

      Ogre::Overlay* getOverlay();
      Ogre::OverlayContainer* getOverlayContainer();

   private:
	   Ogre::Overlay          *m_pOverlay;   //overlay
	   Ogre::OverlayContainer *m_pBackImage; //©³¹Ï
};

#endif  // #ifdef _GAMEENGINE_3D_
#endif  // #ifndef _COVERLAYUI_H_