#ifndef _WINDOW_OGRE_H_
#define _WINDOW_OGRE_H_


#include "window.h"

class ImageButton ;
//自己寫的overlay
//提供overlay的管理機制
class OverlayUI
{
private:
	Ogre::Overlay* pOverlay ;

public:
	void init () ;//建立overlay
	void addImage (ImageButton&) ;
} ;


#endif