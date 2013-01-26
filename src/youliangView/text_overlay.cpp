#ifdef _PROJECT_OGRE_3D_

#include "text_overlay.h"

//#include "unique_id.h"

HDC TextOverlay::hMemDC ;
HBITMAP TextOverlay::hBMP ;
void* TextOverlay::pPixel ;

void TextOverlay::Init (Ogre::OverlayContainer* pContainer)
{
	static int in = 0 ;
	if (in == 0)
	{
		//建立mem dc, bitmap
		HDC screenDC = GetDC (NULL) ;
		hMemDC = CreateCompatibleDC (screenDC) ;
		ReleaseDC (NULL, screenDC) ;

		BITMAPINFO bmpInfo ;
		memset (&bmpInfo, 0, sizeof (bmpInfo)) ;
		bmpInfo.bmiHeader.biSize = sizeof (bmpInfo.bmiHeader) ;
		bmpInfo.bmiHeader.biWidth = MAX_TEXT_W ;
		bmpInfo.bmiHeader.biHeight = MAX_TEXT_H ;
		bmpInfo.bmiHeader.biPlanes = 1 ;
		bmpInfo.bmiHeader.biBitCount = 32 ;
		bmpInfo.bmiHeader.biCompression = BI_RGB ;
		bmpInfo.bmiHeader.biSizeImage = 0 ;
		bmpInfo.bmiHeader.biXPelsPerMeter = 10 ;
		bmpInfo.bmiHeader.biYPelsPerMeter = 10 ;
		bmpInfo.bmiHeader.biClrUsed = 0 ;
		bmpInfo.bmiHeader.biClrImportant = 0 ;

		hBMP = CreateDIBSection (hMemDC, &bmpInfo, DIB_RGB_COLORS, &pPixel,
									NULL, 0) ;

		SelectObject (hMemDC, hBMP) ;
/*
		HFONT font = CreateFont(20,0,0,0,FW_NORMAL,
              FALSE,FALSE,FALSE,DEFAULT_CHARSET,
              OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
              VARIABLE_PITCH|PROOF_QUALITY,FF_DONTCARE,"a") ;

		SelectObject (hMemDC, font) ;
*/
		/*
		HFONT CreateFont(
  _In_  int nHeight,
  _In_  int nWidth,
  _In_  int nEscapement,
  _In_  int nOrientation,
  _In_  int fnWeight,
  _In_  DWORD fdwItalic,
  _In_  DWORD fdwUnderline,
  _In_  DWORD fdwStrikeOut,
  _In_  DWORD fdwCharSet,
  _In_  DWORD fdwOutputPrecision,
  _In_  DWORD fdwClipPrecision,
  _In_  DWORD fdwQuality,
  _In_  DWORD fdwPitchAndFamily,
  _In_  LPCTSTR lpszFace
);
		*/


		in ++ ;
	}

	Text[0] = 0 ;

	char buf[256] ;
	static int in2 = 0 ;
	in2 ++ ;
	sprintf (buf, "text overlay %d", in2) ;

	pEel = (PanelOverlayElement*)OverlayManager::getSingleton().createOverlayElement("Panel", buf) ;
		
	pEel->setMetricsMode(Ogre::GMM_PIXELS);
	pEel->setPosition(100, 100);
	pEel->setDimensions(300, 300);
	pEel->show () ;

	pContainer->addChild (pEel) ;

	//一開始建立一個簡單的texture與material準備使用
	pTexture = TextureManager::getSingleton().createManual(
    buf, // name
    ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    TEX_TYPE_2D,      // type
    MAX_TEXT_W, MAX_TEXT_H,         // width & height
    0,                // number of mipmaps
    PF_BYTE_BGRA,     // pixel format
    TU_DEFAULT);      // usage; should be TU_DYNAMIC_WRITE_ONLY_DISCARDABLE for
                      // textures updated very often (e.g. each frame)

	// Create a material using the texture
	pMaterial = MaterialManager::getSingleton().create(
    buf, // name
    ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	pMaterial->getTechnique(0)->getPass(0)->createTextureUnitState(buf);
	pMaterial->getTechnique(0)->getPass(0)->setSceneBlending(SBT_TRANSPARENT_ALPHA);

	pEel->setMaterialName (buf) ;
}

void TextOverlay::SetText (const char* text, float r, float g, float b)
{
	//確保字串空間夠大
	assert (strlen (text) < sizeof (Text)) ;

	int newColor ;
	((uint8*)(&newColor))[0] = b*255 ;
	((uint8*)(&newColor))[1] = g*255 ;
	((uint8*)(&newColor))[2] = r*255 ;
	((uint8*)(&newColor))[3] = 255 ;

	if ((strcmp (Text, text) == 0) &&
		(Color == newColor))
	{
		//相同,什麼都不做
		return ;
	}

	Color = newColor ;

	//複製字串
	strcpy (Text, text) ;

	SIZE txtSize ;
	//寫字
	BOOL bOK = TextOut (hMemDC, 0, 0, Text, strlen (Text)) ;
	//取得大小
	GetTextExtentPoint (hMemDC, Text, strlen (Text), &txtSize) ;

	//取得uv
	float u = (float)txtSize.cx/MAX_TEXT_W ;
	float v = (float)txtSize.cy/MAX_TEXT_H ;

	assert (u <= 1.0f) ;
	assert (v <= 1.0f) ;

	//複製點
	// Get the pixel buffer
	HardwarePixelBufferSharedPtr pixelBuffer = pTexture->getBuffer();

	// Lock the pixel buffer and get a pixel box
	pixelBuffer->lock(HardwareBuffer::HBL_NORMAL); // for best performance use HBL_DISCARD!
	const PixelBox& pixelBox = pixelBuffer->getCurrentLock();

	int* pSource = (int*)pPixel ;
	int* pDest = static_cast<int*>(pixelBox.data) ;

//	int newColor ;
//	((uint8*)(&color))[0] = b*255 ;
//	((uint8*)(&color))[1] = g*255 ;
//	((uint8*)(&color))[2] = r*255 ;
//	((uint8*)(&color))[3] = 255 ;

	for (size_t j = 0; j < txtSize.cy; j++)
	{
		pSource = ((int*)pPixel)+(MAX_TEXT_H-j-1)*MAX_TEXT_W ;
		pDest = static_cast<int*>(pixelBox.data)+j*MAX_TEXT_W ;

		for(size_t i = 0; i < txtSize.cx; i++)
		{
			if (*pSource)
				*pDest = 0; // A
			else
				*pDest = Color; // A

			pDest++ ;
			pSource ++ ;
		}
	}

	// Unlock the pixel buffer
	pixelBuffer->unlock();

	pEel->setUV (0, 0, u, v) ;
	pEel->setDimensions (txtSize.cx, txtSize.cy) ;
}

void TextOverlay::SetPos (float x, float y)
{
	pEel->setPosition (x, y) ;
}
#endif
