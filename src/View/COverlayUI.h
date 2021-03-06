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

      void init(int, int, int, int);  //�إ�overlay
	   void setPosition(int x, int y);
      void setSize(int width, int height);
	   void setZOrder(int);
      int getZOrder();
      void setBackImage(std::string st);

      Ogre::Overlay* getOverlay();
      Ogre::OverlayContainer* getOverlayContainer();

   private:
	   Ogre::Overlay          *m_pOverlay;   //overlay
	   Ogre::OverlayContainer *m_pBackImage; //����
};

#endif  // #ifdef _GAMEENGINE_3D_
#endif  // #ifndef _COVERLAYUI_H_