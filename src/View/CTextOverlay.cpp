#include "CTextOverlay.h"

#include <OgreOverlayManager.h>
#include <OgreTextureManager.h>
#include <OgreMaterialManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreTechnique.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreHardwareBuffer.h>
#include <OgrePixelFormat.h>
//#include <Strsafe.h>

HDC CTextOverlay::m_hMemDC = NULL;

CTextOverlay::CTextOverlay() : m_hBmp(NULL),
                               m_pPixel(NULL),
                               m_x(0),
                               m_y(0),
                               m_width(0),
                               m_height(0),
                               m_iHorizontalAlignment(CTextOverlay::H_LEFT),
                               m_iVerticalAlignment(CTextOverlay::V_TOP),
                               m_hFont(NULL),
                               m_pPanel(NULL)
{
}

CTextOverlay::~CTextOverlay()
{
   if(m_pPanel != NULL) {
      Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_pPanel);
      m_pPanel = NULL;
   }

   if(m_hFont != NULL) {
      DeleteObject(m_hFont);
	   m_hFont = NULL;
   }

   if(m_hBmp != NULL) {
      DeleteObject(m_hBmp);
      m_hBmp = NULL;
   }

   if(m_hMemDC != NULL) {
      DeleteDC(m_hMemDC);
      m_hMemDC = NULL;
   }

   m_pPixel = NULL;
}

void CTextOverlay::init(Ogre::OverlayContainer *pOverlayContainer, int x, int y, int width, int height)
{
   m_x = x;
   m_y = y;
   m_width = width;
   m_height = height;

   static int in12 = 0;
	if(in12 == 0) {
      HDC screenDC = GetDC(NULL);
      m_hMemDC = CreateCompatibleDC(screenDC);
      ReleaseDC(NULL, screenDC);
      in12++;
   }

   BITMAPINFO bmpInfo;
	memset(&bmpInfo, 0, sizeof (bmpInfo));
	bmpInfo.bmiHeader.biSize = sizeof(bmpInfo.bmiHeader);
	bmpInfo.bmiHeader.biWidth = m_width;
	bmpInfo.bmiHeader.biHeight = m_height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biSizeImage = 0;
	bmpInfo.bmiHeader.biXPelsPerMeter = 10;
	bmpInfo.bmiHeader.biYPelsPerMeter = 10;
	bmpInfo.bmiHeader.biClrUsed = 0;
	bmpInfo.bmiHeader.biClrImportant = 0;

   m_hBmp = CreateDIBSection(m_hMemDC, &bmpInfo, DIB_RGB_COLORS, &m_pPixel, NULL, 0);

   long lfHeight = -MulDiv(12, GetDeviceCaps(m_hMemDC, LOGPIXELSY), 72);
   m_hFont = CreateFont(lfHeight, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "MS Sans Serif");

	char buf[256];
   memset(buf, 0, sizeof(buf));
	static int in2 = 0;
	sprintf(buf, "CTextOverlay %d", in2++);

   m_pPanel = (Ogre::PanelOverlayElement*)Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", buf);
	m_pPanel->setMetricsMode(Ogre::GMM_PIXELS);
   m_pPanel->setPosition((Ogre::Real)m_x, (Ogre::Real)m_y);
	m_pPanel->setDimensions((Ogre::Real)m_width, (Ogre::Real)m_height);
	m_pPanel->show();

   if(pOverlayContainer != NULL)
	   pOverlayContainer->addChild(m_pPanel);

	//一開始建立一個簡單的texture與material準備使用
   m_pTexture = Ogre::TextureManager::getSingleton().createManual(buf, // name
                                                                  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                                  Ogre::TEX_TYPE_2D,    // type
                                                                  m_width, m_height,    // width & height
                                                                  0,                    // number of mipmaps
                                                                  Ogre::PF_BYTE_BGRA,   // pixel format
                                                                  Ogre::TU_DEFAULT);    // usage; should be TU_DYNAMIC_WRITE_ONLY_DISCARDABLE for
                                                                                        // textures updated very often (e.g. each frame)

	// Create a material using the texture
   m_pMaterial = Ogre::MaterialManager::getSingleton().create(buf, // name
                                                              Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	m_pMaterial->getTechnique(0)->getPass(0)->createTextureUnitState(buf);
   m_pMaterial->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

	m_pPanel->setMaterialName(buf);
}

void CTextOverlay::setText(std::string text, float r, float g, float b)
{
	int newColor;
   ((Ogre::uint8*)(&newColor))[0] = b * 255.0f;
   ((Ogre::uint8*)(&newColor))[1] = g * 255.0f;
   ((Ogre::uint8*)(&newColor))[2] = r * 255.0f;
   ((Ogre::uint8*)(&newColor))[3] = 255;

	if((m_text == text) && (m_color == newColor))
		return;  //相同,什麼都不做

	m_color = newColor;

	//複製字串
	m_text.clear();
   m_text = text;

   SelectObject(m_hMemDC, m_hBmp);

	//寫字
   HBRUSH hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
   HBRUSH hOldBrush = (HBRUSH)SelectObject(m_hMemDC, hBrush);

   HPEN hPen = (HPEN)GetStockObject(BLACK_PEN);
   HPEN hOldPen = (HPEN)SelectObject(m_hMemDC, hPen);

   HFONT hOldFont = (HFONT)SelectObject(m_hMemDC, m_hFont);

   RECT rect;
   rect.left = 0;
   rect.top = 0;
   rect.right = m_width;
   rect.bottom = m_height;
   FillRect(m_hMemDC, &rect, hBrush);
   SetTextColor(m_hMemDC, RGB(0, 0, 0));
   SetBkColor(m_hMemDC, RGB(255, 255, 255));
   DrawText(m_hMemDC, m_text.c_str(), (int)m_text.size(), &rect, m_iHorizontalAlignment | m_iVerticalAlignment | DT_WORDBREAK);

   SelectObject(m_hMemDC, hOldPen);
   SelectObject(m_hMemDC, hOldBrush);
   SelectObject(m_hMemDC, hOldFont);

	//複製點
	// Get the pixel buffer
   Ogre::HardwarePixelBufferSharedPtr pixelBuffer = m_pTexture->getBuffer();

	// Lock the pixel buffer and get a pixel box
   pixelBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL); // for best performance use HBL_DISCARD!
   const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock();

	int *pSource = (int *)m_pPixel;
	int *pDest = static_cast<int *>(pixelBox.data);

   for(size_t j = 0; j < (size_t)m_height; j++) {
      pSource = ((int *)m_pPixel) + (m_height - 1 - j) * m_width;
		pDest = static_cast<int *>(pixelBox.data) + j * m_width;

		for(size_t i = 0; i < (size_t)m_width; i++) {
			if(*pSource)
				*pDest = 0; // A
			else
				*pDest = m_color; // A

			pDest++;
			pSource++;
		}
	}

	// Unlock the pixel buffer
	pixelBuffer->unlock();
}

void CTextOverlay::setHorizontalAlignment(Alignment alignment)
{
   m_iHorizontalAlignment = alignment;
}

void CTextOverlay::setVerticalAlignment(Alignment alignment)
{
   if(alignment == V_CENTER || alignment == V_BOTTOM)
      m_iVerticalAlignment = alignment | DT_SINGLELINE;
   else
      m_iVerticalAlignment = alignment;
}

void CTextOverlay::setFont(int fontSize, bool bBold)
{
   if(m_hFont != NULL) {
      DeleteObject(m_hFont);
      m_hFont = NULL;

      long lfHeight = -MulDiv(fontSize, GetDeviceCaps(m_hMemDC, LOGPIXELSY), 72);
      if(bBold == true)
         m_hFont = CreateFont(lfHeight, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, "MS Sans Serif");
      else
         m_hFont = CreateFont(lfHeight, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "MS Sans Serif");
   }
}

void CTextOverlay::setPosition(float x, float y)
{
	m_pPanel->setPosition(x, y);
}

Ogre::PanelOverlayElement* CTextOverlay::getOverlayElement()
{
   return m_pPanel;
}