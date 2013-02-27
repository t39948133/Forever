#include "CObjectTitle.h"

#include <OgreOverlayManager.h>
#include <OgreFontManager.h>
#include <OgrePlane.h>
#include <OgreStringConverter.h>
#include <OgreResourceGroupManager.h>
#include <OgreViewport.h>

CObjectTitle::CObjectTitle()
{
}

CObjectTitle::~CObjectTitle()
{
   Ogre::OverlayManager *pOverlayManager = Ogre::OverlayManager::getSingletonPtr();
   m_pContainer->removeChild(m_pTextArea->getName());
   m_pOverlay->remove2D(m_pContainer);
   pOverlayManager->destroyOverlayElement(m_pTextArea);
   pOverlayManager->destroyOverlayElement(m_pContainer);
   pOverlayManager->destroy(m_pOverlay);
}

void CObjectTitle::init(Ogre::MovableObject *pObject, Ogre::Camera *pCamera,
                        const std::string &fontName, float fontSize, const Ogre::ColourValue &color)
{
   static int inObjectTitle = 0;
	char buf[256];
   memset(buf, 0, sizeof(buf));
   sprintf(buf, "CObjectTitle::%d", inObjectTitle++);
   std::string objName = buf;

   m_pOverlay = Ogre::OverlayManager::getSingleton().create(objName);

   m_pContainer = (Ogre::OverlayContainer *)Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", objName + "::Container");
   m_pOverlay->add2D(m_pContainer);
   m_pOverlay->setZOrder(0);

   Ogre::FontManager::getSingleton().load(fontName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
   m_pFont = (Ogre::Font *)Ogre::FontManager::getSingleton().getByName(fontName).getPointer();
   m_pFont->setTrueTypeSize(fontSize);
   m_fontName = m_pFont->getName();

   m_pTextArea = (Ogre::TextAreaOverlayElement *)Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", objName + "::TextArea");
   m_pTextArea->setDimensions(1.0f, 1.0f);
   m_pTextArea->setMetricsMode(Ogre::GMM_PIXELS);
   m_pTextArea->setPosition(0.0f, 0.0f);
   m_pTextArea->setFontName(fontName);
   m_pTextArea->setCharHeight(fontSize);
   m_pTextArea->setParameter("horz_align", "left");
   m_pTextArea->setColour(color);

   m_pContainer->addChild(m_pTextArea);
   m_pOverlay->hide();

   m_pContainer->setDimensions(1.0f, 1.0f);

   m_pObject = pObject;
   m_pCamera = pCamera;
   m_title.clear();
}

void CObjectTitle::setTitle(const std::string &title)
{
   if(m_title != title) {
      m_title = title;
      Ogre::UTFString utfText = ConvertToUTFString(m_title);
      m_pTextArea->setCaption(utfText);
      m_textDim = getTextDimensions(utfText);
      m_pContainer->setDimensions(m_textDim.x, m_textDim.y);
   }
}

std::string CObjectTitle::getTitle()
{
   return m_title;
}

void CObjectTitle::update(Ogre::SceneNode *pUnitObjectNode, Ogre::SceneNode *pCameraNode)
{
   
   float distance = getDistance(pUnitObjectNode->getPosition().x, pUnitObjectNode->getPosition().z,
                                pCameraNode->getPosition().x, pCameraNode->getPosition().z);
   if(distance > 50) {
      m_pOverlay->hide();
      return;
   }

   if(!m_pObject->isInScene()) {
      m_pOverlay->hide();
      return;
   }

   // Derive the average point between the top-most corners of the object's bounding box
   const Ogre::AxisAlignedBox &AABB = m_pObject->getWorldBoundingBox(true);
   Ogre::Vector3 point = (AABB.getCorner(Ogre::AxisAlignedBox::FAR_LEFT_TOP)
                        + AABB.getCorner(Ogre::AxisAlignedBox::FAR_RIGHT_TOP)
                        + AABB.getCorner(Ogre::AxisAlignedBox::NEAR_LEFT_TOP)
                        + AABB.getCorner(Ogre::AxisAlignedBox::NEAR_RIGHT_TOP)) / 4;

   // Is the camera facing that point? If not, hide the overlay and return.
   Ogre::Plane cameraPlane = Ogre::Plane(Ogre::Vector3(m_pCamera->getDerivedOrientation().zAxis()), m_pCamera->getDerivedPosition());
   if(cameraPlane.getSide(point) != Ogre::Plane::NEGATIVE_SIDE) {
      m_pOverlay->hide();
      return;
   }

   // Derive the 2D screen-space coordinates for that point
   point = m_pCamera->getProjectionMatrix() * (m_pCamera->getViewMatrix() * point);

   // Transform from coordinate space [-1, 1] to [0, 1]
   Ogre::Real x = (point.x / 2) + 0.5f;
   Ogre::Real y = 1 - ((point.y / 2) + 0.5f);

   // Update the position (centering the text)
   m_pContainer->setPosition(x - (m_textDim.x / 6), y - 0.05f);
   m_pOverlay->show();
}

Ogre::Vector2 CObjectTitle::getTextDimensions(std::string text)
{
   Ogre::Real charHeight = m_pTextArea->getCharHeight();
 
   Ogre::Vector2 result(0, 0);

   std::string::iterator it = text.begin(); 
   while(it != text.end()) {   
      if ((*it) == 0x0020)  // ªÅ¥Õ¦r¤¸
         result.x += m_pFont->getGlyphAspectRatio(0x0030);
      else
         result.x += m_pFont->getGlyphAspectRatio((*it));

      it++;
   }

   result.x = (result.x * charHeight) / (Ogre::Real)Ogre::OverlayManager::getSingleton().getViewportWidth();
   result.y = charHeight / (Ogre::Real)Ogre::OverlayManager::getSingleton().getViewportHeight();

   return result;
}