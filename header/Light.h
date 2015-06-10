//-----------------------------------------------------------------------------
//@File:	Light.h
//@Brief:	Defines a basic light that can be attached to a scene
//@Author:	Hector Morales Piloni
//@Date:	April 14, 2015
//-----------------------------------------------------------------------------
#pragma once

#include "Matrix.h"
using namespace MaliSDK;

class Light
{
public:
	Light();
	~Light();

	//Static methods that can be accessed through the entire program
	//without having to instantiate e.g.: from shapes or other classes
	static Vec3f GetPosition();
	static void SetPosition(float x, float y, float z);

	void SetRotation(float angle);
	float GetRotation();

private:
	static Vec3f _mPosition;	//Fixed position, set by user
	static Vec3f _mRotPosition;	//In case of rotational light, we need to calculate this new position
	float _mRotationAngle;
};
