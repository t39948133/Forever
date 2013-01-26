#ifdef _PROJECT_OGRE_3D_

#include "overlayUI.h"
#include "image_button.h"

using namespace Ogre ;

void OverlayUI::init (int x, int y, int w, int h)
{
	static int in = 0 ;
	in ++ ;
	char buf[256] ;
	sprintf (buf, "overylay %d", in) ;

	OverlayManager& overlayManager = OverlayManager::getSingleton();

	pOverlay = overlayManager.create (buf);

	sprintf (buf, "overylay back image%d", in) ;

	pBackImage = (OverlayContainer*)
                                (OverlayManager::getSingleton().
                                createOverlayElement("Panel", buf));
	pBackImage->setMetricsMode(Ogre::GMM_PIXELS);
	pBackImage->setPosition(x, y);
	pBackImage->setDimensions(w, h);
	pBackImage->setMaterialName ("") ;

	pBackImage->show () ;
	pOverlay->add2D (pBackImage) ;

	pOverlay->show () ;
}
void OverlayUI::show (bool bS)
{
	if (bS)
		pBackImage->show () ;
	else
		pBackImage->hide () ;
}


void OverlayUI::setPos (int x, int y)
{
	pBackImage->setPosition(x, y);
}

void OverlayUI::setZOrder (int z)
{
	pOverlay->setZOrder (z) ;
}

void OverlayUI::setImage (const Ogre::String& st)
{
	pBackImage->setMaterialName (st) ;
}

void OverlayUI::addImage (ImageButton& img)
{
	pBackImage->addChild  (img.getImage ()) ;

//	pOverlay->add2D (img.getImage ()) ;
//	pOverlay->show () ;
}

void OverlayUI::addImage (TextArea& txtArea)
{
	pBackImage->addChild  (txtArea.getImage ()) ;	
}

#endif
