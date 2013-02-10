/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CObjectTitle.h
  * @author Darren Chen (陳盛仟)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/09 */
#ifndef _COBJECTTITLE_H_
#define _COBJECTTITLE_H_
#include "Common.h"

#include <OgreMovableObject.h>
#include <OgreCamera.h>
#include <OgreOverlay.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayContainer.h>
#include <OgreVector2.h>
#include <OgreFont.h>

class CObjectTitle
{
   public:
      CObjectTitle(Ogre::MovableObject *pObject,   // 要綁在哪個3D模型上
                   Ogre::Camera *pCamera,          // 攝影機
                   const std::string &fontName,    // 使用什麼字型
                   float fontSize,                 // 字型大小
                   const Ogre::ColourValue &color = Ogre::ColourValue::White);  // 顯示什麼顏色, default = 白色
 
      ~CObjectTitle();
    
      void setTitle(const std::string &title);
      std::string getTitle();
    
      void update();

   private:
      Ogre::Vector2 getTextDimensions(std::string text);

      const Ogre::MovableObject     *m_pObject;
      const Ogre::Camera            *m_pCamera;
      Ogre::Overlay                 *m_pOverlay;
      Ogre::TextAreaOverlayElement  *m_pTextArea;
      Ogre::OverlayContainer        *m_pContainer;
      Ogre::Vector2                  m_textDim;
      Ogre::Font                    *m_pFont;
      std::string                    m_title;
      std::string                    m_fontName;
};

#endif  // #ifndef _COBJECTTITLE_H_