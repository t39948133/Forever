#ifndef _GP_DRAW_INFO_H_
#define _GP_DRAW_INFO_H_

#include "gp_geometry.h"

#include <list>


#include "gp_vertex.h"

namespace GP
{

//畫物件的資訊
class DrawInfo:public Point3F
{
private:
	//blending
	enum {NO_BLEND, //一般繪圖
			BLEND_MODULATE, BLEND_ADD //alpha blend
			} ;
	int blendType ;
	float32 alpha ;//半透明

	bool bFillColor ;
	Color fillColor ;//參考用的填色

	int drawOrder ;//繪圖排序用

public:
	Point3F size ;//大小

	float time ;//動畫時間

	DrawInfo () ;

	void setFillColor (bool, const Color&) ;//填色
	void setBlend (int, float32) ;
} ;

//###############################



}

#endif