/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CHotKeyButton.h
  * @author Darren Chen (³¯²±¥a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/04 */
#ifndef _CHOTKEYBUTTON_H_
#define _CHOTKEYBUTTON_H_
#ifdef _GAMEENGINE_3D_
#include "CImageButton.h"

class CHotKeyButton : public CImageButton
{
   public:
      CHotKeyButton();
      ~CHotKeyButton();

      // CImageButton
      /* virtual */ void init(COverlayUI *pUI, int _x, int _y, int _w, int _h, int _id);

      void setHotKeyText(std::string text, float r, float g, float b);
      void setHotKeyTextHorizontalAlignment(Alignment alignment);
      void setHotKeyTextVerticalAlignment(Alignment alignment);

   private:
      CTextAreaOgre *m_pTextArea;
};

#endif  // #ifdef _GAMEENGINE_3D_
#endif  // #ifndef _CHOTKEYBUTTON_H_