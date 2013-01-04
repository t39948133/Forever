#ifndef _GP_CANVAS_H_
#define _GP_CANVAS_H_

#include <graphic\gp_geometry.h>
#include <graphic\gp_draw_info.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

namespace GP
{

class CanvasLayer ;
class Image ;
class Canvas
{
public:
	enum {MODE_PIXEL, MODE_RELATIVE} ;//
	enum {COORDINATE_SCREEN, COORDINATE_2D} ;
private:
	int mode ;//顯示模式
protected:
	int coordinateSystem ;

protected:
	float32 w, h ;

public:
	virtual void setMode (int) = 0 ;//顯示模式

	void setCoordinateSystem (int  cs)
	{	coordinateSystem = cs ;	}
	int getCoordinateSystem ()
	{	return coordinateSystem ;	}

	float getWidth () {return w ;}
	float getHeight () {return h ;}

	virtual void setBrushColor (const Color&) = 0;
	virtual void setGlobalLight (const Color&) = 0 ;//設定環境光(作日夜)

	virtual void clear (const Color&) = 0 ;

	enum {AUTO_LEN = -1} ;
//	virtual void drawText (const char*, float, float, int = AUTO_LEN) = 0 ;//顯示文字

	virtual void drawEllipse (const RectF&) = 0 ;
	virtual void drawRect (const RectF&, Image*) = 0 ;
	virtual void drawImage (const Point3F&, const Point2F&, Image* = NULL, float32 = 0) = 0 ;
	virtual void drawRect (const VertexC&, const Point2F&, float32 = 0) = 0 ;
	virtual void drawLine (const Point3F&, const Point3F&, const Color&) = 0 ;
	virtual void drawCircle (const VertexC&, float) = 0 ;
	virtual void drawGridLine (const Point3F&, const Point2F&, const Point2I&, const Color&) = 0 ;
	//pos, width&height, align
	virtual void drawText (const char*, const VertexC&, const Point2F&, int) = 0 ;


	virtual void drawLayer (CanvasLayer&) = 0 ;
	virtual void drawAllLayer () = 0;

	virtual CanvasLayer* queryLayer () = 0 ;
	virtual void releaseLayer (CanvasLayer*) = 0 ;

	virtual void update () = 0 ;//把背景頁更新到視窗或螢幕
} ;

class CanvasDC:public Canvas
{
private:
	HWND hWnd ;
	HDC hDC ;

	HBITMAP hBMP ;
	HDC memDC ;

	Color brushColor ;//目前筆刷的顏色
	HBRUSH hBrush ;

public:
	CanvasDC (const CanvasDC&) {} //no copy construct

	CanvasDC (HWND) ;
	~CanvasDC () ;

	void setMode (int) ;//顯示模式

private:
	void releaseBrush () ;

public:
//	void setScreenPixelMode () ;//把矩陣設定為螢幕,左上角是(0,0),右下角是(w-1,h)
//	void set2DPixelMode ()  ;//把矩陣設定為笛卡兒座標
										//畫面中間是(0,0)
										//左上角是(-寬/2,高/2)
										//右上角是(寬/2,高/2)

	void setBrushColor (const Color&) ;

	void clear (const Color&) ;
	void drawDefault () {} ;//顯示測試用的畫面

//	void drawText (const char*, float, float, int = AUTO_LEN) ;//顯示文字

	void drawEllipse (const RectF&) ;
	void drawRect (const RectF&, Image*) ;
//	void drawLine (const VertexC&, const VertexC&) = 0 ;
	void drawCircle (const VertexC&, float) {};
	//pos, width&height, align
	void drawText (const char*, const VertexC&, const Point2F&, int) {} ;

	void update () ;//把背景頁更新到視窗或螢幕
} ;

//#################################

//opengl es
typedef std::list <CanvasLayer> V_CANVAS_LAYER ;

}

#endif