#ifdef _GAMEENGINE_3D_
#include "CTextAreaOgre.h"

CTextAreaOgre::CTextAreaOgre()
{
   m_pTextOverlay = new CTextOverlay();
}

CTextAreaOgre::~CTextAreaOgre()
{
   if(m_pTextOverlay != NULL) {
      delete m_pTextOverlay;
      m_pTextOverlay = NULL;
   }
}

void CTextAreaOgre::init (COverlayUI *pUI, int _x, int _y, int _w, int _h)
{
	x = _x ;
	y = _y ;
	w = _w ;
	h = _h ;

   if(pUI != NULL)
      m_pTextOverlay->init(pUI->getOverlayContainer(), x, y, w, h);
   else
      m_pTextOverlay->init(NULL, x, y, w, h);
}

void CTextAreaOgre::setPosition(int x, int y)
{
   m_pTextOverlay->setPosition((Ogre::Real)x, (Ogre::Real)y);
}

void CTextAreaOgre::setText(std::string text, float r, float g, float b)
{
   m_pTextOverlay->setText(text, r, g, b);
}

void CTextAreaOgre::setHorizontalAlignment(Alignment alignment)
{
   switch(alignment) {
      case H_LEFT:
         m_pTextOverlay->setHorizontalAlignment(CTextOverlay::H_LEFT);
         break;

      case H_CENTER:
         m_pTextOverlay->setHorizontalAlignment(CTextOverlay::H_CENTER);
         break;

      case H_RIGHT:
         m_pTextOverlay->setHorizontalAlignment(CTextOverlay::H_RIGHT);
         break;
   }
}

void CTextAreaOgre::setVerticalAlignment(Alignment alignment)
{
   switch(alignment) {
      case V_TOP:
         m_pTextOverlay->setVerticalAlignment(CTextOverlay::V_TOP);
         break;

      case V_CENTER:
         m_pTextOverlay->setVerticalAlignment(CTextOverlay::V_CENTER);
         break;

      case V_BOTTOM:
         m_pTextOverlay->setVerticalAlignment(CTextOverlay::V_BOTTOM);
         break;
   }
}

void CTextAreaOgre::setFont(int fontSize, bool bBold)
{
   m_pTextOverlay->setFont(fontSize, bBold);
}

Ogre::OverlayElement* CTextAreaOgre::getOverlayElement()
{
   return m_pTextOverlay->getOverlayElement();
}
#endif  // #ifdef _GAMEENGINE_3D_