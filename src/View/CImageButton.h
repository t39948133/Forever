/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CImageButton.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/03 */
#ifndef _CIMAGEBUTTON_H_
#define _CIMAGEBUTTON_H_
#ifdef _GAMEENGINE_3D_
#include "CFButton.h"
#include "COverlayUI.h"
#include "CTextAreaOgre.h"

#include <OgrePanelOverlayElement.h>

class CImageButton : public CFButton
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

	   CImageButton();
      virtual ~CImageButton();
   
	   virtual void init(COverlayUI *pUI, int _x, int _y, int _w, int _h, int _id);
      void setImage(std::string st);
      void setWidth(float width);
      void setTextVisible(bool visible);
      void setText(std::string text, float r, float g, float b);
      void setTextHorizontalAlignment(Alignment alignment);
      void setTextVerticalAlignment(Alignment alignment);
      void setPosition(int x, int y);
      void setSize(int width, int height);
      Ogre::PanelOverlayElement* getImage();

   protected:
      void addChild(Ogre::OverlayElement *pElement);

   private:
      bool m_bTextVisible;
      Ogre::PanelOverlayElement *m_pPanel;
      CTextAreaOgre *m_pTextArea;
      std::string m_materialName;
};

#endif  // #ifdef _GAMEENGINE_3D_
#endif  // #ifndef _CIMAGEBUTTON_H_