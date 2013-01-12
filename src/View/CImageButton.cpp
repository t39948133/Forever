#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"

#include <OgreOverlayManager.h>

CImageButton::CImageButton() : m_pImage(NULL)
{
}

CImageButton::~CImageButton()
{
   if(m_pImage != NULL) {
      Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_pImage);
      m_pImage = NULL;
   }
}

void CImageButton::init(COverlayUI& ovl, 
			int _x, int _y, int _w, int _h, int _id)
{
	CButton::init (_x, _y, _w, _h, _id) ;

   Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

	static int in = 0 ;
	in ++ ;
	char name[256] ;
	sprintf (name, "CImageButton %d", in) ;

   m_pImage = (Ogre::OverlayContainer*)overlayManager.createOverlayElement("Panel", name) ;
	m_pImage->setMetricsMode(Ogre::GMM_PIXELS);
   m_pImage->setPosition((Ogre::Real)_x, (Ogre::Real)_y);
   m_pImage->setDimensions((Ogre::Real)_w, (Ogre::Real)_h);
	m_pImage->setMaterialName("Examples/RustySteel");
	m_pImage->show();

	ovl.addImage(this);
}

Ogre::OverlayContainer* CImageButton::getImage()
{
	return m_pImage ;
}

void CImageButton::setImage(std::string st)
{
	m_pImage->setMaterialName(st);
}

#endif  // #ifdef _GAMEENGINE_3D_