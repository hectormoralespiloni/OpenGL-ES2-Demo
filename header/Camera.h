//-----------------------------------------------------------------------------
//@File:	Camera.h
//@Brief:	Defines a basic camera and projection matrix associated with it
//@Author:	Hector Morales Piloni
//@Date:	April 14, 2015
//-----------------------------------------------------------------------------
#pragma once

#include "Matrix.h"
using namespace MaliSDK;

class Camera
{
public:
	Camera();
	~Camera();

	//Static methods that can be accessed through the entire program
	//without having to instantiate e.g.: from shapes or other classes
	static Vec3f GetPosition();
	static Matrix GetProjectionMatrix();
	static Matrix GetLookAtMatrix();
	static void SetPosition(float x, float y, float z);
	static void SetProjectionMatrix(Matrix m);
	static void SetLookAtMatrix(Matrix m);

private:
	static Vec3f _mPosition;
	static Matrix _mProjectionMatrix;
	static Matrix _mLookAtMatrix;
};
