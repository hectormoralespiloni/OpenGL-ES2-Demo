//-----------------------------------------------------------------------------
//@File:	Light.cpp
//@Brief:	Light implementation file
//@Author:	Hector Morales Piloni
//@Date:	April 14, 2015
//-----------------------------------------------------------------------------
#include "Light.h"

//In order to avoid Linkage problems
//we need to define static members in the implementation file
//since in the header (.h) file, we only declare them...
 Vec3f Light::_mPosition;
 Vec3f Light::_mRotPosition;

Light::Light()
{
	_mRotationAngle = 0.0;
	_mPosition.x = 0.0;
	_mPosition.y = 0.0;
	_mPosition.z = 0.0;
}

Light::~Light()
{
}

Vec3f Light::GetPosition()
{
	return _mRotPosition;
}

void Light::SetPosition(float x, float y, float z)
{
	//We use an original position (fixed, set by user)  and a rotation position
	//which is going to be calculated in real-time based on the user specified position
	//and the rotation calculations
	_mPosition.x = _mRotPosition.x = x;
	_mPosition.y = _mRotPosition.y = y;
	_mPosition.z = _mRotPosition.z = z;
}

float Light::GetRotation()
{
	return _mRotationAngle;
}

void Light::SetRotation(float angle)
{
	//Set angle of rotation and rotate the light around a given radius (r)
	_mRotationAngle = angle;
	float r = 3.0f;

	float x = r*cos(angle);
	float z = r*sin(angle);

	_mRotPosition.x = _mPosition.x + x;
	_mRotPosition.z = _mPosition.z + z;
}
