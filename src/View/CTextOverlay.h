/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CTextOverlay.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/03 */
#ifndef _CTEXTOVERLAY_H_
#define _CTEXTOVERLAY_H_
#ifdef _GAMEENGINE_3D_
#include "Common.h"

#include <OgrePanelOverlayElement.h>
#include <OgreTexture.h>
#include <OgreMaterial.h>
#include <windows.h>

class CTextOverlay
{
   public:
      enum Alignment {
         H_LEFT   = DT_LEFT, 
         H_CENTER = DT_CENTER, 
         H_RIGHT  = DT_RIGHT,
         V_TOP    = DT_TOP,
         V_CENTER = DT_VCENTER,
         V_BOTTOM = DT_BOTTOM
      };

      CTextOverlay();
      ~CTextOverlay();

	   void init(Ogre::OverlayContainer *pOverlayContainer, int x, int y, int width, int height);
      void setText(std::string text, float r, float g, float b);
      void setHorizontalAlignment(Alignment alignment);
      void setVerticalAlignment(Alignment alignment);
      void setFont(int fontSize, bool bBold = false);
	   void setPosition(float x, float y);

      Ogre::PanelOverlayElement* getOverlayElement();

   private:
      static HDC   m_hMemDC;

      int          m_x;
      int          m_y;
      int          m_width;
      int          m_height;
      HBITMAP      m_hBmp;
      void        *m_pPixel;
	   int          m_color;
      std::string  m_text;
      int          m_iHorizontalAlignment;
      int          m_iVerticalAlignment;
      HFONT        m_hFont;

      Ogre::TexturePtr  m_pTexture;
      Ogre::MaterialPtr m_pMaterial;
      Ogre::PanelOverlayElement *m_pPanel;
};

#endif  // #ifdef _GAMEENGINE_3D_
#endif  // #ifndef _CTEXTOVERLAY_H_