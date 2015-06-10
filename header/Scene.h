//-----------------------------------------------------------------------------
//@File:	Scene.h
//@Brief:	Defines a basic 3D scene with a light, a camera and a projectionM
//			It also defines geometry shapes to draw in it.
//@Author:	Hector Morales Piloni
//@Date:	April 12, 2015
//-----------------------------------------------------------------------------
#pragma once
#define GLES_VERSION 2

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <string>
#include <map>

#include "ShaderWrapper.h"
#include "Light.h"
#include "Camera.h"
#include "Cube.h"
#include "Floor.h"
#include "Sphere.h"
#include "Shader.h"
#include "Texture.h"
#include "Matrix.h"
#include "Timer.h"
#include "Platform.h"
#include "EGLRuntime.h"

using namespace MaliSDK;
using namespace std;

class Scene
{
public:
	Scene(int width, int height);
	~Scene();
	void SetProjectionMatrix(Matrix m);
	void SetLightPosition(float x, float y, float z);
	void SetCameraPosition(float x, float y, float z);
	void SetWindowWidth(int w);
	void SetWindowHeight(int h);
	bool Initialize();
	void Draw();

private:
	bool CreateShadowTexture();

	GLuint _mShadowTextureID;
	GLuint _mFBO;
	GLuint _mRBO;

	int _mWindowHeight;
	int _mWindowWidth;

	Camera *_mCamera;
	Light *_mLight;
	Floor *_mFloor;
	Cube *_mCube;
	Sphere *_mSphere;
	Sphere *_mSphere2;
	Sphere *_mSphere3;

	//Container that maps a shader technique with 
	//an actual ShaderWrapper object that can be
	//attached to different geometry
	map<string, ShaderWrapper*> _mShader;
};

