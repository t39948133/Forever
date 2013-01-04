#include "gp_camera.h"

namespace GP
{

Camera::Camera ():pos(0,0,0),front(0,0,1),up(0,-1,0)
{
}

void Camera::setPos (const Point3F& p)
{
	pos = p ;
}

void Camera::setProjection (float cancasW, float cancasH, float aspect)//設定投影
{
}

const Matrix4& Camera::getFinalMatrix ()//取得矩陣
{
	return finalMatrix ;
}

void Camera::transformCanvas (Point3F& pnt)const//把一個座標做投影轉換,變成2D座標
{
}

}