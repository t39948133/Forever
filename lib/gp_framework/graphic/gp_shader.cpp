#include "gp_shader.h"

#include "gp_matrix.h"
#include <stdio.h>
#include <assert.h>

namespace GP
{

//GLuint Shader::preProgramObject = NO_SHADER_ID ;

Shader::Shader ():uiFragShader(NULL),uiVertShader(NULL),uiProgramObject(NULL)
{
}

Shader::~Shader ()
{
	if (uiProgramObject != NULL)
		glDeleteProgram(uiProgramObject);
	if (uiFragShader != NULL)
		glDeleteShader(uiFragShader);
	GLuint loadShader (const char*) ;
	void loadProgram (const char*) ;
	if (uiVertShader != NULL)
		glDeleteShader(uiVertShader);
}

GLuint Shader::getShaderID ()
{
	return uiProgramObject ;
}

GLuint Shader::loadShader (const char* fileName, int type)
{
	GLuint curShaderID ;

	enum {SHADER_SIZE = 10240} ;
	char* pszSource = new char[SHADER_SIZE] ;

	//vertex shader
	FILE* pFile ;
	fopen_s (&pFile, fileName, "rb") ;
	if (pFile != NULL)
	{
		fseek (pFile, 0, SEEK_END) ;
		int size = ftell (pFile) ;
		assert (size < SHADER_SIZE) ;
		fseek (pFile, 0, SEEK_SET) ;

		fread (pszSource, size, 1, pFile) ;
		pszSource[size] = 0 ;
		fclose (pFile) ;
	}else
	{
		assert (0) ;
		goto cleanup ;
	}

	// Create the fragment shader object
	assert (uiFragShader == NULL) ;
	curShaderID = glCreateShader(type);

	// Load the source code into it
	glShaderSource(curShaderID, 1, (const char**)&pszSource, NULL);
	// Compile the source code
	glCompileShader(curShaderID);

	// Check if compilation succeeded
	GLint bShaderCompiled;
    glGetShaderiv(curShaderID, GL_COMPILE_STATUS, &bShaderCompiled);
	if (!bShaderCompiled)
	{
		// An error happened, first retrieve the length of the log message
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(curShaderID, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

		// Allocate enough space for the message and retrieve it
//		char* pszInfoLog = new char[i32InfoLogLength];
        glGetShaderInfoLog(curShaderID, i32InfoLogLength, &i32CharsWritten, pszSource);

		fopen_s (&pFile, "compile_shader.log", "wb") ;
		if (pFile != NULL)
		{
			fwrite (fileName, strlen (fileName), 1, pFile) ;
			fwrite ("\n", strlen ("\n"), 1, pFile) ;

			fwrite (pszSource, i32InfoLogLength, 1, pFile) ;
			fclose (pFile) ;
		}

		assert (0) ;
		goto cleanup ;
	}

cleanup:
	delete []pszSource ;

	return curShaderID ;
}

void Shader::loadProgram (const char* name)
{
	// Create the shader program
	assert (uiProgramObject == NULL) ;
    uiProgramObject = glCreateProgram();
	assert (uiProgramObject != NULL) ;

	char buf[256] ;
	sprintf_s (buf, sizeof (buf), "shader\\%s.vsh", name) ;
	assert (uiVertShader == NULL) ;
	uiVertShader = loadShader (buf, GL_VERTEX_SHADER) ;

	sprintf_s (buf, sizeof (buf), "shader\\%s.fsh", name) ;
	assert (uiFragShader == NULL) ;
	uiFragShader = loadShader (buf, GL_FRAGMENT_SHADER) ;
}

void Shader::useProgram ()
{
	enum {NO_SHADER_ID = NULL} ;
	static GLuint preProgramObject = NO_SHADER_ID ;
	if (preProgramObject != uiProgramObject)
	{
		// Actually use the created program
	    glUseProgram(uiProgramObject);
		preProgramObject= uiProgramObject ;
	}
}

void Shader::loadDeafault ()
{
	loadProgram ("default") ;

	// Attach the fragment and vertex shaders to it
    glAttachShader(uiProgramObject, uiFragShader);
    glAttachShader(uiProgramObject, uiVertShader);

	// Bind the custom vertex attribute "myVertex" to location VERTEX_ARRAY
    glBindAttribLocation(uiProgramObject, VERTEX_ARRAY, "vtxVertex");
    glBindAttribLocation(uiProgramObject, TEXCOORD_ARRAY, "vtxUV");

	// Link the program
    glLinkProgram(uiProgramObject);

	// Check if linking succeeded in the same way we checked for compilation success
    GLint bLinked;
    glGetProgramiv(uiProgramObject, GL_LINK_STATUS, &bLinked);
	if (!bLinked)
	{
		assert (0 && "CanvasGLES::initDefaultShader glLinkProgram") ;
	}

	// Actually use the created program
    glUseProgram(uiProgramObject);

	// Sets the sampler2D variable to the first texture unit
	glUniform1i(glGetUniformLocation(uiProgramObject, "sampler2d"), 0);

	addrMatrix = glGetUniformLocation(uiProgramObject, "myPMVMatrix");
	addrGlobalLight = glGetUniformLocation(uiProgramObject, "myGlobalLight");
	addrUseTexture = glGetUniformLocation(uiProgramObject, "bUseTexture");
}

void Shader::applyParamDefault (const Matrix4& mat, const Color& color, 
								bool bUseTexture)
{
	useProgram () ;

	static int in = 0 ;
	static Matrix4 preMat ;
	static Color preColor ;
	static bool preUsedTexture = false ;
	if (in == 0)
	{
		preColor.set (-1, -1, -1, -1) ;//完全不可能的顏色
		preMat.identity () ;
		in ++ ;
	}

	if (preMat != mat)
	{
		//矩陣變過
		glUniformMatrix4fv (addrMatrix, 1, GL_FALSE, mat);

		preMat = mat ;
	}

	//color
	if (preColor != color)
	{
		glUniform4f (addrGlobalLight, color.r,color.g, color.b, color.a) ;
		preColor = color ;
	}

	if (bUseTexture != preUsedTexture)
	{
		glUniform1i (addrUseTexture, bUseTexture) ;
		preUsedTexture = bUseTexture ;
	}
}

void Shader::loadText ()
{
	loadProgram ("text") ;

	// Attach the fragment and vertex shaders to it
    glAttachShader(uiProgramObject, uiFragShader);
    glAttachShader(uiProgramObject, uiVertShader);

	// Bind the custom vertex attribute "myVertex" to location VERTEX_ARRAY
    glBindAttribLocation(uiProgramObject, VERTEX_ARRAY, "vtxVertex");
    glBindAttribLocation(uiProgramObject, TEXCOORD_ARRAY, "vtxUV");

	// Link the program
    glLinkProgram(uiProgramObject);

	// Check if linking succeeded in the same way we checked for compilation success
    GLint bLinked;
    glGetProgramiv(uiProgramObject, GL_LINK_STATUS, &bLinked);
	if (!bLinked)
	{
		assert (0 && "CanvasGLES::initDefaultShader glLinkProgram") ;
	}

	// Actually use the created program
    glUseProgram(uiProgramObject);

	// Sets the sampler2D variable to the first texture unit
	glUniform1i(glGetUniformLocation(uiProgramObject, "sampler2d"), 0);

	addrMatrix = glGetUniformLocation(uiProgramObject, "myPMVMatrix");
	addrGlobalLight = glGetUniformLocation(uiProgramObject, "myGlobalLight");
	addrUseTexture = glGetUniformLocation(uiProgramObject, "bUseTexture");
}

void Shader::applyParamText (const Matrix4& mat, const Color& textColor, bool bUseTexture)
{
	useProgram () ;

	static int in = 0 ;
	static Matrix4 preMat ;
	static Color preColor ;
	static bool preUsedTexture = false ;
	if (in == 0)
	{
		preColor.set (-1, -1, -1, -1) ;//完全不可能的顏色
		preMat.identity () ;
		in ++ ;
	}

	if (preMat != mat)
	{
		//矩陣變過
		glUniformMatrix4fv (addrMatrix, 1, GL_FALSE, mat);

		preMat = mat ;
	}

	//color
	if (preColor != textColor)
	{
		glUniform4f (addrGlobalLight, textColor.r,textColor.g, textColor.b, textColor.a) ;
		preColor = textColor ;
	}

	if (bUseTexture != preUsedTexture)
	{
		glUniform1i (addrUseTexture, bUseTexture) ;
		preUsedTexture = bUseTexture ;
	}
}

void Shader::loadLine ()
{
	loadProgram ("line") ;

	// Attach the fragment and vertex shaders to it
    glAttachShader(uiProgramObject, uiFragShader);
    glAttachShader(uiProgramObject, uiVertShader);

	// Bind the custom vertex attribute "myVertex" to location VERTEX_ARRAY
    glBindAttribLocation(uiProgramObject, VERTEX_ARRAY, "vtxVertex");

	// Link the program
    glLinkProgram(uiProgramObject);

	// Check if linking succeeded in the same way we checked for compilation success
    GLint bLinked;
    glGetProgramiv(uiProgramObject, GL_LINK_STATUS, &bLinked);
	if (!bLinked)
	{
		assert (0 && "CanvasGLES::initDefaultShader glLinkProgram") ;
	}

	// Actually use the created program
    glUseProgram(uiProgramObject);

	addrMatrix = glGetUniformLocation(uiProgramObject, "myPMVMatrix");
	addrGlobalLight = glGetUniformLocation(uiProgramObject, "myGlobalLight");
}

void Shader::applyParamLine (const Matrix4& mat, const Color& textColor)
{
	useProgram () ;

	static int in = 0 ;
	static Matrix4 preMat ;
	static Color preColor ;
//	static bool preUsedTexture = false ;
	if (in == 0)
	{
		preColor.set (-1, -1, -1, -1) ;//完全不可能的顏色
		preMat.identity () ;
		in ++ ;
	}

	if (preMat != mat)
	{
		//矩陣變過
		glUniformMatrix4fv (addrMatrix, 1, GL_FALSE, mat);

		preMat = mat ;
	}

	//color
	if (preColor != textColor)
	{
		glUniform4f (addrGlobalLight, textColor.r,textColor.g, textColor.b, textColor.a) ;
		preColor = textColor ;
	}

	/*
	if (bUseTexture != preUsedTexture)
	{
		glUniform1i (addrUseTexture, bUseTexture) ;
		preUsedTexture = bUseTexture ;
	}
	*/
}

void Shader::loadRect ()
{
	loadProgram ("rect") ;

	// Attach the fragment and vertex shaders to it
    glAttachShader(uiProgramObject, uiFragShader);
    glAttachShader(uiProgramObject, uiVertShader);

	// Bind the custom vertex attribute "myVertex" to location VERTEX_ARRAY
    glBindAttribLocation(uiProgramObject, VERTEX_ARRAY, "vtxVertex");
    glBindAttribLocation(uiProgramObject, TEXCOORD_ARRAY, "vtxUV");

	// Link the program
    glLinkProgram(uiProgramObject);

	// Check if linking succeeded in the same way we checked for compilation success
    GLint bLinked;
    glGetProgramiv(uiProgramObject, GL_LINK_STATUS, &bLinked);
	if (!bLinked)
	{
		assert (0 && "CanvasGLES::initDefaultShader glLinkProgram") ;
	}

	// Actually use the created program
    glUseProgram(uiProgramObject);

	// Sets the sampler2D variable to the first texture unit
	glUniform1i(glGetUniformLocation(uiProgramObject, "sampler2d"), 0);

	addrMatrix = glGetUniformLocation(uiProgramObject, "myPMVMatrix");
	addrGlobalLight = glGetUniformLocation(uiProgramObject, "myGlobalLight");
	addrUseTexture = glGetUniformLocation(uiProgramObject, "bUseTexture");
}

void Shader::applyParamRect (const Matrix4& mat, const Color& textColor, bool bUseTexture)
{
	useProgram () ;

	static int in = 0 ;
	static Matrix4 preMat ;
	static Color preColor ;
	static bool preUsedTexture = false ;
	if (in == 0)
	{
		preColor.set (-1, -1, -1, -1) ;//完全不可能的顏色
		preMat.identity () ;
		in ++ ;
	}

	if (preMat != mat)
	{
		//矩陣變過
		glUniformMatrix4fv (addrMatrix, 1, GL_FALSE, mat);

		preMat = mat ;
	}

	//color
	if (preColor != textColor)
	{
		glUniform4f (addrGlobalLight, textColor.r,textColor.g, textColor.b, textColor.a) ;
		preColor = textColor ;
	}

	if (bUseTexture != preUsedTexture)
	{
		glUniform1i (addrUseTexture, bUseTexture) ;
		preUsedTexture = bUseTexture ;
	}
}

}
