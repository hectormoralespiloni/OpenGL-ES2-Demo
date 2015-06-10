//-----------------------------------------------------------------------------
//@File:	Shape.h
//@Brief:	Defines a basic geometric shape and properties common to all
//@Author:	Hector Morales Piloni
//@Date:	April 12, 2015
//-----------------------------------------------------------------------------
#pragma once
#define GLES_VERSION 2

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <string>
#include <vector>

#include "ShaderWrapper.h"
#include "Shader.h"
#include "Matrix.h"

using namespace std;
using namespace MaliSDK;

class Shape
{
public:
	Shape();
	virtual ~Shape();
	virtual void Draw() = 0;
	virtual bool Initialize() = 0;

	void AttachShader(ShaderWrapper *shader);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetPosition(float x, float y, float z);

protected:
	Matrix _mModelViewMatrix;
	Matrix _mRotationMatrix;
	Matrix _mTranslationMatrix;
	Matrix _mScaleMatrix;

	GLfloat _mRotAngleX;
	GLfloat _mRotAngleY;
	GLfloat _mRotAngleZ;

	GLfloat _mScaleX;
	GLfloat _mScaleY;
	GLfloat _mScaleZ;

	GLfloat _mPosX;
	GLfloat _mPosY;
	GLfloat _mPosZ;

	//To hold data
	vector<GLfloat> *_mVertices;
	vector<GLfloat> *_mNormals;
	vector<GLfloat> *_mColors;
	vector<GLuint> *_mIndices;

	//Common VBO and IBO stuff
	GLuint _mVBOVertices;
	GLuint _mVBONormals;
	GLuint _mVBOColors;	
	GLuint _mIBOIndices;	

	ShaderWrapper *_mShader;

	//Common shader variables
	GLuint _mShaderProgramID;
	GLint _mLocPosition;
	GLint _mLocColor;
	GLint _mLocModelViewProjectionMatrix;
	GLint _mLocModelViewMatrix;	
	GLint _mLocNormal;
	GLint _mLocLightPosition;
};

