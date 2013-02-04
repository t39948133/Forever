/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CHotKeyButton.cpp
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/04 */
#ifdef _GAMEENGINE_3D_
#include "CHotKeyButton.h"

#include <OgreOverlayManager.h>

CHotKeyButton::CHotKeyButton() : CImageButton()
{
   m_pTextArea = NULL;
}

CHotKeyButton::~CHotKeyButton()
{
   if(m_pTextArea != NULL) {
      delete m_pTextArea;
      m_pTextArea = NULL;
   }
}

void CHotKeyButton::init(COverlayUI *pUI, int _x, int _y, int _w, int _h, int _id)
{
   CImageButton::init(pUI, _x, _y, _w, _h, _id);

   m_pTextArea = new CTextAreaOgre();
   m_pTextArea->init(NULL, 0, 0, w, h);
   m_pTextArea->setFont(10, false);
   this->addChild(m_pTextArea->getOverlayElement());
}

void CHotKeyButton::setHotKeyText(std::string text, float r, float g, float b)
{
   if(m_pTextArea != NULL)
      m_pTextArea->setText(text, r, g, b);
}

void CHotKeyButton::setHotKeyTextHorizontalAlignment(Alignment alignment)
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

void CHotKeyButton::setHotKeyTextVerticalAlignment(Alignment alignment)
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

#endif  // #ifdef _GAMEENGINE_3D_