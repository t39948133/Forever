#ifndef _OVERLAY_UI_H_
#define _OVERLAY_UI_H_

#ifdef _PROJECT_OGRE_3D_

#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgrePanelOverlayElement.h> 
#include "Ogre.h"


class ImageButton ;
class TextArea ;
//自己寫的overlay
//提供overlay的管理機制
class OverlayUI
{
private:
	Ogre::Overlay* pOverlay ;//overlay
	Ogre::OverlayContainer* pBackImage ;//底圖

public:
	OverlayUI ():pBackImage (NULL)
	{
	}
	Ogre::Overlay* getOverlay ()
	{
		return pOverlay ;
	}

	Ogre::OverlayContainer* getOverlayContainer ()
	{
		return pBackImage ;
	}

	void init (int, int, int, int) ;//建立overlay
	void show (bool) ;
	void setPos (int, int) ;
	void setZOrder (int) ;
	void setImage (const Ogre::String& st) ;
	void addImage (ImageButton&) ;
	void addImage (TextArea&) ;
} ;

#endif

#endif