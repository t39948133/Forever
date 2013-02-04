/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CTextAreaOgre.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/03 */
#ifndef _CTEXTAREAOGRE_H_
#define _CTEXTAREAOGRE_H_
#ifdef _GAMEENGINE_3D_
#include "CWindow.h"
#include "COverlayUI.h"
#include "CTextOverlay.h"

#include <OgreOverlayElement.h>

class CTextAreaOgre : public CWindow
{
   public:
      enum Alignment {
         H_LEFT = 0, 
         H_CENTER, 
         H_RIGHT,
         V_TOP,
         V_CENTER,
         V_BOTTOM
      };


      CTextAreaOgre();
      ~CTextAreaOgre();

	   void init(COverlayUI *pUI, int _x, int _y, int _w, int _h);

      void setText(std::string, float, float, float);
      void setHorizontalAlignment(Alignment alignment);
      void setVerticalAlignment(Alignment alignment);
      void setFont(int fontSize, bool bBold = false);
      Ogre::OverlayElement* getOverlayElement();

   private:
	   CTextOverlay *m_pTextOverlay;
};

#endif  // #ifdef _GAMEENGINE_3D_
#endif  // #ifndef _CTEXTAREAOGRE_H_