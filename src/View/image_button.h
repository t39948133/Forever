#ifndef _IMAGE_BUTTON_H_
#define _IMAGE_BUTTON_H_

#include "window.h"

#ifdef _PROJECT_OGRE_3D_

#include <OgreOverlayManager.h>

#include "overlayUI.h"

#include "text_overlay.h"

class ImageButton:public Button
{
private:
	Ogre::OverlayContainer* pImage ;

public:
	ImageButton ():pImage (NULL)
	{
	}
	void init (OverlayUI&, int _x, int _y, int _w, 
					int _h, int _id) ;

	Ogre::OverlayContainer* getImage () ;

	void setImage (const  Ogre::String& st) ;
} ;

class TextArea:public Window
{
private:
	TextOverlay textOverlay ;

public:
	void init (OverlayUI&, int _x, int _y, int _w, int _h) ;

	void setText (const char*, float, float, float) ;
	Ogre::OverlayContainer* getImage () ;
} ;

#endif

#endif