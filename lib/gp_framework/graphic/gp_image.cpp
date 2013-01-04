#include "gp_image.h"
#include "gp_vertex.h"

#include <assert.h>

#include <stdio.h>
#include <FreeImage.h>

namespace GP
{

//##########################################

Image::Image ():textureID(NO_TEXTURE_ID)
{
}

Image::~Image ()
{
	release () ;
}

GLuint Image::getTextureID ()const
{
	return textureID ;
}

void Image::createTestData ()
{
	release () ;
	assert (textureID == NO_TEXTURE_ID) ;

	// Creates the data as a 32bits integer array (8bits per component)
	enum {TEX_SIZE = 128} ;
	GLuint* pTexData = new GLuint[TEX_SIZE*TEX_SIZE];
	for (int i=0; i<TEX_SIZE; i++)
	for (int j=0; j<TEX_SIZE; j++)
	{
		// Fills the data with a fancy pattern
		GLuint col = (255L<<24) + ((255L-j*2)<<16) + ((255L-i)<<8) + (255L-i*2);
		if ( ((i*j)/8) % 2 ) col = (GLuint) (255L<<24) + (255L<<16) + (0L<<8) + (255L);
		pTexData[j*TEX_SIZE+i] = col;
	}

	// Allocates one texture handle
	glGenTextures(1, &textureID);

	// Binds this texture handle so we can load the data into it
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, pTexData);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glBindTexture(GL_TEXTURE_2D, 0);

	// Deletes the texture data, it's now in OpenGL memory
	delete [] pTexData;
}

void Image::setPixel (int w, int h, void* pPixel)
{
	if (textureID == NO_TEXTURE_ID)
	{
		//空的要先建立
		// Allocates one texture handle
		glGenTextures(1, &textureID);

		// Binds this texture handle so we can load the data into it
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	}

	assert (textureID != NO_TEXTURE_ID) ;

	// Binds this texture handle so we can load the data into it
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pPixel);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

//	glBindTexture(GL_TEXTURE_2D, 0);
}

void Image::release ()
{
	if (textureID != NO_TEXTURE_ID)
	{
		glDeleteTextures(1, &textureID);
		textureID = NO_TEXTURE_ID ;
	}
}

void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) 
{
	/*
	printf("\n*** "); 
	if(fif != FIF_UNKNOWN) {
		printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
	}
	printf(message);
	printf(" ***\n");
	*/
}

unsigned DLL_CALLCONV
myReadProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
	return fread(buffer, size, count, (FILE *)handle);
}

unsigned DLL_CALLCONV
myWriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
	return fwrite(buffer, size, count, (FILE *)handle);
}

int DLL_CALLCONV
mySeekProc(fi_handle handle, long offset, int origin) {
	return fseek((FILE *)handle, offset, origin);
}

long DLL_CALLCONV
myTellProc(fi_handle handle) {
	return ftell((FILE *)handle);
}

bool Image::load (const char* fname)
{
	release () ;

//	createTestData () ;
//	return true ;

	char buf[256] ;
	sprintf_s (buf, sizeof (buf), "image\\%s", fname) ;
//	fname = "image\\avatar000.png" ;

	FILE* pFile = NULL ;
	fopen_s (&pFile, buf, "rb") ;
	if (pFile == NULL)
		return false ;

	FreeImageIO io;

	io.read_proc  = myReadProc;
	io.write_proc = myWriteProc;
	io.seek_proc  = mySeekProc;
	io.tell_proc  = myTellProc;

	// find the buffer format
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromHandle(&io, (fi_handle)pFile, 0);

	if(fif == FIF_UNKNOWN) 
	{
	   /* Close the file */
		fclose(pFile);
		return false ;
	}

	// load from the file handle
	FIBITMAP *dib = FreeImage_LoadFromHandle(fif, &io, (fi_handle)pFile, 0);
		
	BYTE* pPixelData = FreeImage_GetBits(dib) ;

	int width, height,pitch  ;
	width =  FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	pitch = FreeImage_GetPitch(dib);
	int bpp = FreeImage_GetBPP(dib) ;
	assert (bpp == 32) ;

	FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib) ;
	assert (image_type == FIT_BITMAP) ;

//	/*
	//轉換rgba(因為rgba,的順序不同)
	RGBQUAD rgba ;
	BYTE* pBit = pPixelData ;
	for (int i = 0 ; i<height; i++)
	{
		BYTE* pPixel = pBit ;
		for (int m = 0; m<width; m++)
		{
			if (FreeImage_GetPixelColor(dib, m, i, &rgba))
			{
				BYTE tmp = rgba.rgbBlue ;
				rgba.rgbBlue = rgba.rgbRed ;
				rgba.rgbRed = tmp ;
				FreeImage_SetPixelColor (dib, m, i, &rgba) ;
			}
		}
		pBit += pitch ;
	}
//			*/

//---------------------------------------------------
   //把pixel copy給
   //最大記憶體
	if (pPixelData != NULL)
	{
		assert (textureID == NO_TEXTURE_ID) ;
		if (textureID == NO_TEXTURE_ID)
		{
			//空的要先建立
			// Allocates one texture handle
			glGenTextures(1, &textureID);
		}

		assert (textureID != NO_TEXTURE_ID) ;


		// Binds this texture handle so we can load the data into it
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pPixelData);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// free the loaded FIBITMAP
		FreeImage_Unload(dib);
	}


	return true ;
}

//##########################################

TextImage::TextImage ():bInit(false),hMemDC(NULL),hBMP(NULL)
{
}

TextImage::~TextImage ()
{
	if (hBMP != NULL)
		DeleteObject (hBMP) ;
	if (hMemDC != NULL)
		DeleteDC (hMemDC) ;
}

const Point2F& TextImage::buildText (const char* text, const Point2F&, 
								UV& getUV)//建立文字貼圖
{

	enum {MAX_TEXT_W = 512, MAX_TEXT_H = 32} ;
	if (bInit == false)
	{
		assert (hMemDC == NULL) ;
		assert (hBMP == NULL) ;
		bInit = true ;
		//建立mem dc, bitmap
		HDC screenDC = GetDC (NULL) ;
		hMemDC = CreateCompatibleDC (screenDC) ;
		ReleaseDC (NULL, screenDC) ;

		//背景色
//		SetBkColor (hMemDC, RGB (0, 0, 0)) ;

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

//		HPEN hPen = (HPEN)GetStockObject (WHITE_PEN) ;
//		SelectObject (hMemDC, hPen) ;

		SelectObject (hMemDC, hBMP) ;
	}

	//確保字串空間夠大
	assert (strlen (text) < sizeof (Text)-1) ;

	if ((strcmp (Text, text) == 0))
	{
		//相同,什麼都不做
		getUV = uv ;
		return textSize ;
	}
	//--------------------

	//複製字串
	strcpy_s (Text, sizeof (Text), text) ;

	SIZE txtSize ;
	//寫字
	BOOL bOK = TextOutA (hMemDC, 0, 0, Text, strlen (Text)) ;
	//取得大小
	GetTextExtentPointA (hMemDC, Text, strlen (Text), &txtSize) ;
	textSize.x = (float32)txtSize.cx ;
	textSize.y = (float32)txtSize.cy ;

	//取得uv
	uv.u = (float)txtSize.cx/MAX_TEXT_W ;
	uv.v = (float)txtSize.cy/MAX_TEXT_H ;

	assert (uv.u <= 1.0f) ;
	assert (uv.v <= 1.0f) ;

	setPixel (MAX_TEXT_W, MAX_TEXT_H, pPixel) ;

	getUV = uv ;
	return textSize ;
}

//################################################

TextImage2::TextImage2 ():curImage(-1)
{
}

TextImage& TextImage2::getCurImage ()
{
	return vImage[curImage] ;
}

const Point2F& TextImage2::buildText (const char* text, const Point2F& textSize, 
								UV& uv)//建立文字貼圖
{
	curImage ++ ;
	if (curImage >= BUFFER_COUNT)
		curImage = 0 ;
	return vImage[curImage].buildText (text, textSize, uv) ;
}

}