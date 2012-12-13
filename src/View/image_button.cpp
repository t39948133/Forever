#include "image_button.h"


#ifdef _PROJECT_OGRE_3D_

#include <OgreOverlayContainer.h>

using namespace Ogre ;

void ImageButton::init (OverlayUI& ovl, 
			int _x, int _y, int _w, int _h, int _id)
{
	Button::init (_x, _y, _w, _h, _id) ;


	OverlayManager& overlayManager = 
			OverlayManager::getSingleton();

	static int in = 0 ;
	in ++ ;
	char name[256] ;
	sprintf (name, "ImageButton %d", in) ;

	pImage = (OverlayContainer*)overlayManager.createOverlayElement(
				"Panel", name) ;


	pImage->setMetricsMode(Ogre::GMM_PIXELS);
	pImage->setPosition( _x, _y);
	pImage->setDimensions( _w, _h);
	pImage->setMaterialName ("drbunsen_head");
	pImage->show () ;

	ovl.addImage (*this) ;
}

Ogre::OverlayContainer* ImageButton::getImage ()
{
	return pImage ;
}

void ImageButton::setImage (const Ogre::String& st)
{
	pImage->setMaterialName (st);
	
}

void TextArea::init (OverlayUI& ui, int _x, int _y, int _w, int _h)
{
	x = _x ;
	y = _y ;
	w = _w ;
	h = _h ;

	textOverlay.Init (ui.getOverlayContainer ()) ;
	textOverlay.SetPos (x, y) ;
}

void TextArea::setText (const char* text, float r, float g, float b)
{
	textOverlay.SetText (text, r, g, b) ;
}

Ogre::OverlayContainer* TextArea::getImage ()
{
	return textOverlay.getImage () ;
}


#endif
