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
	static int inOverlayUI = 0;
	char buf[256];
   memset(buf, 0, sizeof(buf));
   sprintf(buf, "COverlayUI::%d", inOverlayUI++);
   std::string objName = buf;

   Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	m_pOverlay = overlayManager.create(objName);

   m_pBackImage = (Ogre::OverlayContainer*)(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", objName + "::BackImage"));
	m_pBackImage->setMetricsMode(Ogre::GMM_PIXELS);
   m_pBackImage->setPosition((Ogre::Real)x, (Ogre::Real)y);
   m_pBackImage->setDimensions((Ogre::Real)w, (Ogre::Real)h);
	m_pBackImage->show();

	m_pOverlay->add2D(m_pBackImage);
	m_pOverlay->show();
}

void COverlayUI::setPosition(int x, int y)
{
   m_pBackImage->setPosition((Ogre::Real)x, (Ogre::Real)y);
}

void COverlayUI::setSize(int width, int height)
{
   m_pBackImage->setDimensions((Ogre::Real)width, (Ogre::Real)height);
}

void COverlayUI::setZOrder(int z)
{
	m_pOverlay->setZOrder(z) ;
}

int COverlayUI::getZOrder()
{
   return m_pOverlay->getZOrder();
}

void COverlayUI::setBackImage(std::string st)
{
   m_pBackImage->setMaterialName(st) ;
}

Ogre::Overlay* COverlayUI::getOverlay()
{
   return m_pOverlay;
}

Ogre::OverlayContainer* COverlayUI::getOverlayContainer()
{
   return m_pBackImage;
}

#endif  // #ifdef _GAMEENGINE_3D_