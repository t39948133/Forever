#ifndef _GP_MATRIX_H_
#define _GP_MATRIX_H_

#include "gp_geometry.h"

namespace GP
{

class Matrix4
{
private:
	float32 e[16] ;

public:

	bool operator!= (const Matrix4&)const ;
	operator const float32* ()const ; 
//	operator float32* () ; 

	void operator= (const float32*) ;
	void identity () ;
	void setTranslate (float32, float32, float32) ;
	void setScale (float32, float32, float32) ;
//	void setRotation (float32, float32, float32) ;
	void setRotationZ (float32) ;
	void setPos (float32, float32, float32) ;

	void addTranslate (float32, float32, float32) ;
	void addRotateZ (float32) ;
	void addScale (float32, float32, float32) ;

	void operator*= (const Matrix4&) ;
	void mul (Point3F&)const ;
} ;

}

#endif