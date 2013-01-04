#include "gp_canvas_layer.h"

#include <assert.h>

namespace GP
{

//##########################################

	Image* LayerNode::getImage ()
	{
		return &image ;
	}

	bool LayerNode::loadImage (const char* fname)
	{
		//先給個預設的大小
		size.set (100) ;
		set (0) ;//位置

		image.load (fname) ;

		return true ;
	}

	void LayerNode::setSize (const Point3F& s)
	{
		size = s ;//大小
	}

//##########################################
	void CanvasLayer::setGlobalLight (const Color& color)
	{
		globalLight = color ;
	}

	const Color& CanvasLayer::getGlobalLight ()
	{
		return globalLight ;
	}

	void CanvasLayer::sortNode ()
	{
	}

	V_LAYER_NODE& CanvasLayer::getAllNode ()
	{
		return vLayerNode ;
	}

	LayerNode* CanvasLayer::queryNodeImage (const char* fname)//配置一張圖片
	{
		vLayerNode.push_back (LayerNode ()) ;

		vLayerNode.back ().loadImage (fname) ;

		return &(vLayerNode.back ()) ;
	}

	void CanvasLayer::releaseNode (LayerNode* pn)
	{
		V_LAYER_NODE::iterator pi = vLayerNode.begin () ;
		while (pi != vLayerNode.end ())
		{
			if (&(*pi) == pn)
			{
				vLayerNode.erase (pi) ;//找到刪除
				return ;
			}
			++ pi ;
		}
		assert (0) ;
	}
	
	CanvasLayer::CanvasLayer ():globalLight(1, 1, 1, 1)
	{
	}

	/*
	CanvasLayer::~CanvasLayer ()
	{
	}
	*/

}