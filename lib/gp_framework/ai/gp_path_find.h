#ifndef _GP_PATH_FIND_H_
#define _GP_PATH_FIND_H_

#include <vector>
#include <list>

#include <graphic\gp_geometry.h>

//#include <resource\gp_share_pointer.h>

namespace GP
{

//移動的單位
class MoveScene ;
class Canvas ;
class MoveNode
{
private:
	Point3F pos/*, target*/ ;//座標
	float size ;//size是半徑

public:
	const Point3F& getPos ()const ;
	void setPos (const Point3F&) ;

//	void setTarget (const Point3F&) ;
	bool isCollide (const Point3F&, float)const ;

	void getFrontPos (const Point3F&, Point3F&) ;

	void setData (float) ;
	bool work (const Point3F&, float, float, MoveScene&) ;

	void draw (const Point3F*, Canvas&) ;

} ;

//typedef SHARE_POINTER <MoveNode> SP_MOVE_NODE ;

//##############################

class MoveScene
{
private:
	typedef std::list <MoveNode> V_MOVE_NODE ;
	V_MOVE_NODE vMoveNode ;

public:
	bool calcTurnVector (const MoveNode*, const Point3F&, const Point3F&, 
						float, Point3F&) ;

	MoveNode* queryMoveNode () ;
	void release (MoveNode*) ;

//	void draw (Canvas&) ;

//	void work (float32) ;
} ;

}//namespace

#endif//header
