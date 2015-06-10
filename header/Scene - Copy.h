//-----------------------------------------------------------------------------
//@File:	Scene.h
//@Brief:	Defines a basic 3D scene with a light, a camera and a projectionM
//@Author:	Hector Morales Piloni
//@Date:	April 12, 2015
//-----------------------------------------------------------------------------
#pragma once
#define GLES_VERSION 2

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>

#include "Matrix.h"

using namespace MaliSDK;

class Scene
{
public:
	static void SetProjectionMatrix(Matrix m);
	static void SetLightPosition(float x, float y, float z);
	static void SetCameraPosition(float x, float y, float z);
	static void SetWindowWidth(int w);
	static void SetWindowHeight(int h);
	static Vec3f GetLightPosition();
	static Vec3f GetCameraPosition();
	static Matrix GetProjectionMatrix();
	static int GetWindowWidth();
	static int GetWindowHeight();

private:
	static int _mWindowHeight;
	static int _mWindowWidth;
	static Vec3f _mLightPosition;
	static Vec3f _mCameraPosition;
	static Matrix _mProjectionMatrix;
};

