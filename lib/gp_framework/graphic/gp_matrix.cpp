#include "gp_matrix.h"
#include <math.h>

namespace GP
{

bool Matrix4::operator!= (const Matrix4& mat)const
{
	return memcmp (this, &mat, sizeof (Matrix4)) != 0 ;
}

Matrix4::operator const float32* ()const
{
	return e ;
}

/*
Matrix4:: operator float32* ()
{
	return e[0] ;
}
*/

void Matrix4::operator= (const float32* pf)
{
	memcpy (this, pf, sizeof (Matrix4)) ;
}

void Matrix4::identity ()
{
	e[0] = 1 ; e[4] = 0 ; e[8] = 0 ; e[12] = 0 ;
	e[1] = 0 ; e[5] = 1 ; e[9] = 0 ; e[13] = 0 ;
	e[2] = 0 ; e[6] = 0 ; e[10] = 1 ; e[14] = 0 ;
	e[3] = 0 ; e[7] = 0 ; e[11] = 0 ; e[15] = 1 ;
}

void Matrix4::setTranslate (float32 dx, float32 dy, float32 dz)
{
	e[0] = 1 ; e[4] = 0 ; e[8] = 0 ; e[12] = dx ;
	e[1] = 0 ; e[5] = 1 ; e[9] = 0 ; e[13] = dy ;
	e[2] = 0 ; e[6] = 0 ; e[10] = 1 ; e[14] = dz ;
	e[3] = 0 ; e[7] = 0 ; e[11] = 0 ; e[15] = 1 ;
}

void Matrix4::setScale (float32 sx, float32 sy, float32 sz)
{
	e[0] = sx ; e[4] = 0 ; e[8] = 0 ; e[12] = 0 ;
	e[1] = 0 ; e[5] = sy ; e[9] = 0 ; e[13] = 0 ;
	e[2] = 0 ; e[6] = 0 ; e[10] = sz ; e[14] = 0 ;
	e[3] = 0 ; e[7] = 0 ; e[11] = 0 ; e[15] = 1 ;
}

void Matrix4::setRotationZ (float32 rz)
{
	float		fCosine, fSine;

	/* Precompute cos and sin */
	/*
#if defined(BUILD_DX9) || defined(BUILD_D3DM) || defined(BUILD_DX10)
	fCosine =	(float)PVRTFCOS(-fAngle);
    fSine =		(float)PVRTFSIN(-fAngle);
#else
	fCosine =	(float)PVRTFCOS(fAngle);
    fSine =		(float)PVRTFSIN(fAngle);
#endif
	*/

	fCosine =	(float)cos (-rz);
    fSine =		(float)sin (-rz);

	/* Create the trigonometric matrix corresponding to Z Rotation */
	e[ 0]=fCosine;		e[ 4]=fSine;	e[ 8]=0.0f;	e[12]=0.0f;
	e[ 1]=-fSine;		e[ 5]=fCosine;	e[ 9]=0.0f;	e[13]=0.0f;
	e[ 2]=0.0f;		e[ 6]=0.0f;	e[10]=1.0f;	e[14]=0.0f;
	e[ 3]=0.0f;		e[ 7]=0.0f;	e[11]=0.0f;	e[15]=1.0f;
}

void Matrix4::addTranslate (float32 dx, float32 dy, float32 dz)
{
	Matrix4 tmp ;
	tmp.setTranslate (dx, dy, dz) ;

	operator*= (tmp) ;
}

void Matrix4::addRotateZ (float32 rz)
{
	Matrix4 tmp ;
	tmp.setRotationZ (rz) ;

	operator*= (tmp) ;
}

void Matrix4::addScale (float32 sx, float32 sy, float32 sz)
{
	Matrix4 tmp ;
	tmp.setScale (sx, sy, sz) ;

	operator*= (tmp) ;
}

void Matrix4::operator*= (const Matrix4& mat)
{
	Matrix4 tmp ;

	tmp.e[ 0] = e[ 0]*mat.e[ 0] + e[ 1]*mat.e[ 4] + e[ 2]*mat.e[ 8] + e[ 3]*mat.e[12];
	tmp.e[ 1] = e[ 0]*mat.e[ 1] + e[ 1]*mat.e[ 5] + e[ 2]*mat.e[ 9] + e[ 3]*mat.e[13];
	tmp.e[ 2] = e[ 0]*mat.e[ 2] + e[ 1]*mat.e[ 6] + e[ 2]*mat.e[10] + e[ 3]*mat.e[14];
	tmp.e[ 3] = e[ 0]*mat.e[ 3] + e[ 1]*mat.e[ 7] + e[ 2]*mat.e[11] + e[ 3]*mat.e[15];

	tmp.e[ 4] = e[ 4]*mat.e[ 0] + e[ 5]*mat.e[ 4] + e[ 6]*mat.e[ 8] + e[ 7]*mat.e[12];
	tmp.e[ 5] = e[ 4]*mat.e[ 1] + e[ 5]*mat.e[ 5] + e[ 6]*mat.e[ 9] + e[ 7]*mat.e[13];
	tmp.e[ 6] = e[ 4]*mat.e[ 2] + e[ 5]*mat.e[ 6] + e[ 6]*mat.e[10] + e[ 7]*mat.e[14];
	tmp.e[ 7] = e[ 4]*mat.e[ 3] + e[ 5]*mat.e[ 7] + e[ 6]*mat.e[11] + e[ 7]*mat.e[15];

	tmp.e[ 8] = e[ 8]*mat.e[ 0] + e[ 9]*mat.e[ 4] + e[10]*mat.e[ 8] + e[11]*mat.e[12];
	tmp.e[ 9] = e[ 8]*mat.e[ 1] + e[ 9]*mat.e[ 5] + e[10]*mat.e[ 9] + e[11]*mat.e[13];
	tmp.e[10] = e[ 8]*mat.e[ 2] + e[ 9]*mat.e[ 6] + e[10]*mat.e[10] + e[11]*mat.e[14];
	tmp.e[11] = e[ 8]*mat.e[ 3] + e[ 9]*mat.e[ 7] + e[10]*mat.e[11] + e[11]*mat.e[15];

	tmp.e[12] = e[12]*mat.e[ 0] + e[13]*mat.e[ 4] + e[14]*mat.e[ 8] + e[15]*mat.e[12];
	tmp.e[13] = e[12]*mat.e[ 1] + e[13]*mat.e[ 5] + e[14]*mat.e[ 9] + e[15]*mat.e[13];
	tmp.e[14] = e[12]*mat.e[ 2] + e[13]*mat.e[ 6] + e[14]*mat.e[10] + e[15]*mat.e[14];
	tmp.e[15] = e[12]*mat.e[ 3] + e[13]*mat.e[ 7] + e[14]*mat.e[11] + e[15]*mat.e[15];

	*this = tmp ;
}

void Matrix4::mul (Point3F& pnt)const
{

}

}