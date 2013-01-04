#ifndef _GP_SHADER_H_
#define _GP_SHADER_H_

#include "gp_vertex.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>

namespace GP
{

#define VERTEX_ARRAY	0
#define TEXCOORD_ARRAY	1

class Matrix4 ;
class Shader
{
private:
	int addrMatrix, addrGlobalLight, addrUseTexture ;
	GLuint uiFragShader, uiVertShader;
	GLuint uiProgramObject;

//	static GLuint preProgramObject ;

private:
	Shader (const Shader&) {} ;
public:

	Shader () ;
	~Shader () ;

	GLuint getShaderID ()  ;

private:
	GLuint loadShader (const char*, int) ;
	void loadProgram (const char*) ;

private:
	void useProgram () ;

public:
	void loadDeafault () ;
	void applyParamDefault (const Matrix4&, const Color&, bool) ;

	void loadText () ;
	void applyParamText (const Matrix4&, const Color&, bool) ;

	void loadLine () ;
	void applyParamLine (const Matrix4&, const Color&) ;

	void loadRect () ;
	void applyParamRect (const Matrix4&, const Color&, bool) ;
} ;

}

#endif