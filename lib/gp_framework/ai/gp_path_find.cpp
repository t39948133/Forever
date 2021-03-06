#include "gp_path_find.h"
#include <graphic\gp_canvas.h>

#include <math.h>
#include <stdio.h>


namespace GP
{

	/*
bool lineSegmentIntersection(
                                 float Ax, float Ay,
                                 float Bx, float By,
                                 float Cx, float Cy,
                                 float Dx, float Dy,
                                 float *X, float *Y) 
{
    float  distAB, theCos, theSin, newX, ABpos ;
    
    //  Fail if either line segment is zero-length.
    if (((Ax==Bx) && (Ay==By)) || ((Cx==Dx) && (Cy==Dy))) return false;
    
    //  Fail if the segments share an end-point.
    if (((Ax==Cx) && (Ay==Cy)) || ((Bx==Cx) && (By==Cy))
        ||  ((Ax==Dx) && (Ay==Dy)) || ((Bx==Dx) && (By==Dy))) {
        return false; }
    
    //  (1) Translate the system so that point A is on the origin.
    Bx-=Ax; By-=Ay;
    Cx-=Ax; Cy-=Ay;
    Dx-=Ax; Dy-=Ay;
    
    //  Discover the length of segment A-B.
    distAB=sqrtf(Bx*Bx+By*By);
    
    //  (2) Rotate the system so that point B is on the positive X axis.
    theCos=Bx/distAB;
    theSin=By/distAB;
    newX=Cx*theCos+Cy*theSin;
    Cy  =Cy*theCos-Cx*theSin; Cx=newX;
    newX=Dx*theCos+Dy*theSin;
    Dy  =Dy*theCos-Dx*theSin; Dx=newX;
    
    //  Fail if segment C-D doesn't cross line A-B.
    if (((Cy<0.) && (Dy<0.)) || ((Cy>=0.) && (Dy>=0.))) return false;
    
    //  (3) Discover the position of the intersection point along line A-B.
    ABpos=Dx+(Cx-Dx)*Dy/(Dy-Cy);
    
    //  Fail if segment C-D crosses line A-B outside of segment A-B.
    if (ABpos<0. || ABpos>distAB) return false;
    
    //  (4) Apply the discovered position to line A-B in the original coordinate system.
    *X=Ax+ABpos*theCos;
    *Y=Ay+ABpos*theSin;
    
    //  Success.
    return true; 
}

bool lineSegmentIntersectionXZ(const Point3F& p0, const Point3F& p1,
				const Point3F& p2, const Point3F& p3,
				Point3F& pr)
{
    return lineSegmentIntersection (p0.x, p0.z, p1.x, p1.z, p2.x, p2.z, p3.x, p3.z, &pr.x, &pr.z) ;
}
   */
//######################################
//######################################
//######################################

const Point3F& MoveNode::getPos ()const
{
	return pos ;
}

void MoveNode::setPos (const Point3F& p)
{
	pos = p ;
}

bool MoveNode::isCollide (const Point3F& pnt, float sz)const
{
	return pos.isShorterXY (pnt, (size+sz)) ;
}

void MoveNode::getFrontPos (const Point3F& target, Point3F& frontPos)
{
	frontPos.makeVector (pos, target) ;//向前的向量
	frontPos.normalizeXY (size*2.0f) ;

	frontPos += pos ;
}

void MoveNode::setData (float sz)
{
	size = sz ;
}

bool MoveNode::work (const Point3F& target, float keepDistance, 
						float moveSpeed, MoveScene& scene)
{
	bool bReach ;


	//先直接往目標前進
	bReach = pos.shiftKeepDistance (target, keepDistance, moveSpeed) ;

	//畫前方的圓
	Point3F frontPos ;
	getFrontPos (target, frontPos) ;

	Point3F turnVector ;
	if (scene.calcTurnVector (this, pos, frontPos, size, turnVector))
	{
		//有撞到
	}

	return bReach ;
}

void MoveNode::draw (const Point3F* pTarget, Canvas& canvas)
{
	GP::VertexC vtx ;
	vtx.pos = pos ;
	vtx.color.set (1, 1, 1, 1) ;

	//畫自己
	canvas.drawCircle (vtx, size) ;

	if (pTarget != NULL)
	{
		//畫前方的圓
		getFrontPos (*pTarget, vtx.pos) ;
		canvas.drawCircle (vtx, size) ;

		//畫目標
		vtx.pos = *pTarget ;
		canvas.drawCircle (vtx, size) ;
	}
}

//##############################
	bool MoveScene::calcTurnVector (const MoveNode* pNode, 
										const Point3F& pos, const Point3F& frontPos, 
										float size, Point3F& turnVector)
	{
		V_MOVE_NODE::iterator pi = vMoveNode.begin () ;
		while (pi != vMoveNode.end ())
		{
			if (&(*pi) == pNode)
			{
				//跳過自己
			}else
			{
				//檢查有沒有重疊
				if (pi->isCollide (frontPos, size))
				{
					//有重疊
					int x = 0;
					 x++ ;

					 return true ;
				}else
				{
				}
			}

			++ pi ;
		}

		return false ;
	}

	MoveNode* MoveScene::queryMoveNode ()
	{
		vMoveNode.push_back (MoveNode ()) ;
		return &(vMoveNode.back ()) ;
	}

	void MoveScene::release (MoveNode* pNode)
	{
		//刪除
		V_MOVE_NODE::iterator pi = vMoveNode.begin () ;
		while (pi != vMoveNode.end ())
		{
			if (&(*pi) == pNode)
			{
				vMoveNode.erase (pi) ;
				return ;
			}
			++ pi ;
		}
	}

	/*
	void MoveScene::work (float32)
	{
		V_MOVE_NODE::iterator pi = vMoveNode.begin () ;
		while (pi != vMoveNode.end ())
		{
			pi->work (*this) ;
			++ pi ;
		}
	}
	*/

}//namespace

