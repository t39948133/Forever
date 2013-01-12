#ifdef _GAMEENGINE_3D_
#include "COverlayUI.h"
#include "CImageButton.h"

#include <OgreOverlayManager.h>

COverlayUI::COverlayUI() : m_pOverlay(NULL),
                           m_pBackImage(NULL)
{
}

COverlayUI::~COverlayUI()
{
   if(m_pBackImage != NULL) {
      Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_pBackImage);
      m_pBackImage = NULL;
   }
   
   if(m_pOverlay != NULL) {
      Ogre::OverlayManager::getSingleton().destroy(m_pOverlay);
      m_pOverlay = NULL;
   }
}

void COverlayUI::init (int x, int y, int w, int h)
{
	static int in = 0 ;
	in ++ ;
	char buf[256] ;
	sprintf (buf, "COverlayUI %d", in) ;

   Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	m_pOverlay = overlayManager.create (buf);

	sprintf (buf, "COverlayUI BackImage %d", in) ;

   m_pBackImage = (Ogre::OverlayContainer*)(Ogre::OverlayManager::getSingleton().
                                          createOverlayElement("Panel", buf));
	m_pBackImage->setMetricsMode(Ogre::GMM_PIXELS);
   m_pBackImage->setPosition((Ogre::Real)x, (Ogre::Real)y);
   m_pBackImage->setDimensions((Ogre::Real)w, (Ogre::Real)h);
	m_pBackImage->setMaterialName("Examples/RustySteel");
	m_pBackImage->show();

	m_pOverlay->add2D(m_pBackImage);
	m_pOverlay->show();
}

void COverlayUI::setPos (int x, int y)
{
   m_pBackImage->setPosition((Ogre::Real)x, (Ogre::Real)y);
}

void COverlayUI::setZOrder(int z)
{
	m_pOverlay->setZOrder(z) ;
}

void COverlayUI::setBackImage(std::string st)
{
   m_pBackImage->setMaterialName(st) ;
}

void COverlayUI::addImage(CImageButton *pImgBtn)
{
	m_pBackImage->addChild(pImgBtn->getImage()) ;
}

/*void COverlayUI::addImage (TextArea& txtArea)
{
	m_pBackImage->addChild  (txtArea.getImage ()) ;
}*/

Ogre::Overlay* COverlayUI::getOverlay()
{
   return m_pOverlay;
}

Ogre::OverlayContainer* COverlayUI::getOverlayContainer()
{
   return m_pBackImage;
}

#endif  // #ifdef _GAMEENGINE_3D_