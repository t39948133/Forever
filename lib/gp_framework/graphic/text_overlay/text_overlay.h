#ifndef _TEXT_OVERLAY_H_
#define _TEXT_OVERLAY_H_

#include "Ogre.h"
using namespace Ogre ;

#include <OgrePanelOverlayElement.h> 
#include <windows.h>

class TextOverlay
{
private:
	TexturePtr pTexture ;
	MaterialPtr pMaterial ;

	enum {MAX_TEXT_W = 512, MAX_TEXT_H = 32} ;
	static HDC hMemDC ;
	static HBITMAP hBMP ;
	static void* pPixel ;

	int Color ;
	char Text[256] ;
	PanelOverlayElement* pEel ;

public:
	void Init (Ogre::Overlay*) ;
	void SetText (const char*, float, float, float) ;
	void SetPos (float, float) ;
} ;

#endif