#ifndef _GP_GEOMETRY_H_
#define _GP_GEOMETRY_H_

#include <system\gp_variable_type.h>

namespace GP
{

const float32 GP_PI = 3.141592f ;
const float32 GP_PI_360 = GP_PI ;
const float32 GP_PI_270 = GP_PI*3/4 ;
const float32 GP_PI_180 = GP_PI/2 ;
const float32 GP_PI_90 = GP_PI/4 ;

//座標系統
//不同螢幕尺寸

template <class T> class Point2
{
public:
	T x, y ;

	void shift (T dx, T dy)
	{
		x += dx ;
		y += dy ;
	}

	void shift (const Point2& target, T len)
	{
		T dx = (target.x-x) ;
		T dy = (target.y-y) ;
		float dist = sqrt (dx*dx+dy*dy) ;
		if (dist > len)
		{
			//太遠
			if (dist > 0.00000001)
			{
				//不能除零
				x += dx*len/dist ;
				y += dy*len/dist ;
			}
		}else
		{
			//夠近
			x = target.x ;
			y = target.y ;
		}
	}

	bool operator == (const Point2& pnt)const
	{
		return (x == pnt.x) && (y == pnt.y) ;
	}

	bool operator != (const Point2& pnt)const
	{
		return (x != pnt.x) || (y != pnt.y) ;
	}

	Point2 (T _x, T _y):x(_x),y(_y)
	{
	}

	Point2 ()
	{
	}
} ;

typedef Point2<float32> Point2F ;
typedef Point2<int> Point2I ;
//###########################################

template <class T> class Point3
{
public:
	T x, y, z ;

	void set (T _x, T _y, T _z)
	{
		x = _x ; y = _y ; z = _z ;
	}

	void set (T t)
	{
		x = t ;	y = t ;	z = t ;
	}

	void shift (T dx, T dy, T dz)
	{
		x += dx ;	y += dy ;	z += dz ;
	}

	void operator += (const Point3& pnt)
	{
		x += pnt.x ;	y += pnt.y ;	z += pnt.z ;
	}

	bool shiftKeepDistance (const Point3& target, T keepDist, T len)
	{
		//回傳true代表到了
		//要保持一段距離,不用走到底
		T dx = (target.x-x) ;
		T dy = (target.y-y) ;
		T dz = (target.z-z) ;
		float dist = sqrt (dx*dx+dy*dy+dz*dz) ;
		if (dist > keepDist)
		{
			//目前距離 > 保持距離
			//可以再近一點
			if (dist > 0.00000001)//不能除零
			{
				if (dist <= len)
				{
					//到了,直接跳過去
					x = target.x ;
					y = target.y ;
					z = target.z ;
					return true ;
				}else
				{
					x += dx*len/dist ;
					y += dy*len/dist ;
					z += dz*len/dist ;
					return false ;
				}
			}else
			{
				return false ;
			}
		}else
		{
			//目前距離 < 保持距離
			//夠近,不要再往前
			return true ;
		}
	}

	bool shift (const Point3& target, T len)
	{
		//回傳true代表到了
		T dx = (target.x-x) ;
		T dy = (target.y-y) ;
		T dz = (target.z-z) ;
		float dist = sqrt (dx*dx+dy*dy+dz*dz) ;
		if (dist > len)
		{
			//太遠
			if (dist > 0.00000001)//不能除零
			{
				x += dx*len/dist ;
				y += dy*len/dist ;
				z += dz*len/dist ;
				return false ;
			}else
			{
				return false ;
			}
		}else
		{
			//夠近
			x = target.x ;
			y = target.y ;
			z = target.z ;
			return true ;
		}
	}

	bool operator == (const Point3& pnt)const
	{
		return (x == pnt.x) && (y == pnt.y) && (z == pnt.z) ;
	}

	bool operator != (const Point3& pnt)const
	{
		return (x != pnt.x) || (y != pnt.y) || (z != pnt.z) ;
	}

	void makeVector (const Point3& p0, const Point3& p1)
	{
		x = p1.x-p0.x ;
		y = p1.y-p0.y ;
		z = p1.z-p0.z ;
	}

	void normalizeXY (float scale)
	{
		float dist = sqrt (x*x+y*y) ;
		dist /= scale ;
		x /= dist ;
		y /= dist ;
	}

	bool isShorterXY (const Point3& pos, float len)const
	{
		return ((pos.x-x)*(pos.x-x)+(pos.y-y)*(pos.y-y)) < len*len ;
	}

	Point3 (T _x, T _y, T _z):x(_x),y(_y),z(_z)
	{
	}

	Point3 (const Point3& p0, const Point3& p1)
	{
		makeVector (p0, p1) ;
	}

	Point3 ()
	{
	}
} ;

typedef Point3<float32> Point3F ;

//###########################################

template <class T>
class Rect
{
public:
	T left, top, right, bottom ;

	void shift (T dx, T dy)
	{
		left += dx ;
		top += dy ;
		right += dx ;
		bottom += dy ;
	}

	Rect (T l, T t, T r, T b):left(t),top(t),right(r),bottom(b)
	{
	}

	Rect ()
	{
	}
} ;

typedef Rect <float32> RectF ;

}

#endif
