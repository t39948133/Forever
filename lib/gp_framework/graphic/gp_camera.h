#ifndef _GP_CAMERA_H_
#define _GP_CAMERA_H_

#include "gp_geometry.h"
#include "gp_matrix.h"

namespace GP
{

class Matrix4 ;

class Camera
{
private:
	Point3F pos, front, up ;
	Matrix4 finalMatrix ;

public:
	Camera () ;

	void setPos (const Point3F&) ;
	void setProjection (float, float, float) ;//設定投影

	const Matrix4& getFinalMatrix () ;//取得矩陣

	void transformCanvas (Point3F&)const ;//把一個座標做投影轉換,變成2D座標
} ;

}

#endif