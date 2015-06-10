//-----------------------------------------------------------------------------
//@File:	Renderer.h
//@Brief:	Defines a renderer that has geometry to draw
//@Author:	Hector Morales Piloni
//@Date:	April 11, 2015
//-----------------------------------------------------------------------------
#pragma once
#define GLES_VERSION 2

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <string>

#include "Scene.h"
#include "Cube.h"
#include "Floor.h"
#include "Sphere.h"
#include "Shader.h"
#include "Texture.h"
#include "Matrix.h"
#include "Timer.h"
#include "Platform.h"
#include "EGLRuntime.h"

using namespace std;
using namespace MaliSDK;

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();
	bool Initialize();
	void Draw();

private:
	float _mLightRot;
	Floor *_mFloor;
	Cube *_mCube;
	Sphere *_mSphere;
	//Torus *_mTorus;
};
