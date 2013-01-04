#ifndef _GP_CANVANS_LAYER_H
#define _GP_CANVANS_LAYER_H

#include "gp_draw_info.h"
#include "gp_image.h"

namespace GP
{

class LayerNode:public DrawInfo
{
private:
	Image image ;//圖片

	//不許複製
	LayerNode& operator= (const LayerNode&) {}

public:
	Image* getImage () ;

	bool loadImage (const char*) ;
	void setSize (const Point3F&)  ;
} ;

typedef std::list <LayerNode> V_LAYER_NODE ;

class CanvasLayer
{
private:
	friend class Canvas ;
	V_LAYER_NODE vLayerNode ;

	Color globalLight ;

public:
	void setGlobalLight (const Color&) ;
	const Color& getGlobalLight () ;

	void sortNode () ;
	V_LAYER_NODE& getAllNode () ;

	LayerNode* queryNodeImage (const char*) ;//配置一張圖片
	void releaseNode (LayerNode*) ;//歸還

//	void draw () ;

	CanvasLayer () ;
//	~CanvasLayer () ;
} ;

}

#endif