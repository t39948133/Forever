/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CImageButton.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/03 */
#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"

#include <OgreOverlayManager.h>

CImageButton::CImageButton() : m_pPanel(NULL),
                               m_pTextArea(NULL),
                               m_bTextVisible(false)
{
}

CImageButton::~CImageButton()
{
   if(m_pTextArea != NULL) {
      delete m_pTextArea;
      m_pTextArea = NULL;
   }

   if(m_pPanel != NULL) {
      Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_pPanel);
      m_pPanel = NULL;
   }
}

void CImageButton::init(COverlayUI *pUI, int _x, int _y, int _w, int _h, int _id)
{
	CFButton::init (_x, _y, _w, _h, _id) ;

	static int inImageButton = 0;
	char name[256];
   memset(name, 0, sizeof(name));
   sprintf(name, "CImageButton::%d", inImageButton++);

   m_pPanel = (Ogre::PanelOverlayElement *)Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", name);
   m_pPanel->setMetricsMode(Ogre::GMM_PIXELS);
   m_pPanel->setPosition((Ogre::Real)_x, (Ogre::Real)_y);
   m_pPanel->setDimensions((Ogre::Real)_w, (Ogre::Real)_h);
   m_pPanel->show();

   if(pUI != NULL)
      pUI->getOverlayContainer()->addChild(m_pPanel);
}

void CImageButton::setImage(std::string st)
{
   if(m_materialName != st) {
      m_materialName = st;
      m_pPanel->setMaterialName(st);
   }
}

void CImageButton::setWidth(float width)
{
   m_pPanel->setWidth(width);
}

void CImageButton::setTextVisible(bool visible)
{
   m_bTextVisible = visible;

   if(m_bTextVisible == true) {
      m_pTextArea = new CTextAreaOgre();
      m_pTextArea->init(NULL, 0, 0, w, h);
      m_pTextArea->setFont(10);
      m_pPanel->addChild(m_pTextArea->getOverlayElement());
   }
   else {
      if(m_pTextArea != NULL) {
         m_pPanel->removeChild(m_pTextArea->getOverlayElement()->getName());
         delete m_pTextArea;
         m_pTextArea = NULL;
      }
   }
}

void CImageButton::setText(std::string text, float r, float g, float b)
{
   if(m_pTextArea != NULL)
      m_pTextArea->setText(text, r, g, b);
}

void CImageButton::setTextHorizontalAlignment(Alignment alignment)
{
   if(m_pTextArea != NULL) {
      switch(alignment) {
         case H_LEFT:
            m_pTextArea->setHorizontalAlignment(CTextAreaOgre::H_LEFT);
            break;

         case H_CENTER:
            m_pTextArea->setHorizontalAlignment(CTextAreaOgre::H_CENTER);
            break;

         case H_RIGHT:
            m_pTextArea->setHorizontalAlignment(CTextAreaOgre::H_RIGHT);
            break;
      }
   }
}

void CImageButton::setTextVerticalAlignment(Alignment alignment)
{
   if(m_pTextArea != NULL) {
      switch(alignment) {
         case V_TOP:
            m_pTextArea->setVerticalAlignment(CTextAreaOgre::V_TOP);
            break;

         case V_CENTER:
            m_pTextArea->setVerticalAlignment(CTextAreaOgre::V_CENTER);
            break;

         case V_BOTTOM:
            m_pTextArea->setVerticalAlignment(CTextAreaOgre::V_BOTTOM);
            break;
      }
   }
}

void CImageButton::addChild(Ogre::OverlayElement *pElement)
{
   if(pElement != NULL)
      m_pPanel->addChild(pElement);
}

#endif  // #ifdef _GAMEENGINE_3D_