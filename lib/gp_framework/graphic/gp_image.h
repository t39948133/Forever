#ifndef _GP_IMAGE_H_
#define _GP_IMAGE_H_

#include "gp_geometry.h"
#include "gp_vertex.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>

namespace GP
{
//一張圖片
class Image
{
public:
	enum {NO_TEXTURE_ID = 0} ;

protected:
	GLuint textureID ;
	Point2F textSize ;
	UV uv ;

public:
	Image () ;
	~Image () ;

	//不許複製
	Image& operator= (const Image&) {}

	GLuint getTextureID ()const ;
	void createTestData () ;

protected:
	void setPixel (int, int, void*) ;

public:

	void release () ;
	bool load (const char*) ;
} ;

class TextImage:public Image
{
private:
	int bInit ;
	HDC hMemDC ;
//	HPEN hPen ;
	HBITMAP hBMP ;
	void* pPixel ;
	char Text[256] ;//上次的文字內容

public:
	TextImage () ;
	~TextImage () ;
	const Point2F& buildText (const char*, const Point2F&, UV&) ;//建立文字貼圖
} ;

class TextImage2
{
private:
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//這個class不要用,因為切換texture反而造成效能變慢
	enum {BUFFER_COUNT = 1} ;
	TextImage vImage[BUFFER_COUNT] ;
	int curImage ;

public:
	TextImage2 () ;

	TextImage& getCurImage () ;
	const Point2F& buildText (const char*, const Point2F&, UV&) ;//建立文字貼圖
} ;

} ;

#endif