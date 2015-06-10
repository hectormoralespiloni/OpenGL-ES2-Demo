//-----------------------------------------------------------------------------
//@File:	Camera.cpp
//@Brief:	Camera implementation file
//@Author:	Hector Morales Piloni
//@Date:	April 14, 2015
//-----------------------------------------------------------------------------
#include "Camera.h"

//In order to avoid Linkage problems
//we need to define static members in the implementation file
//since in the header (.h) file, we only declare them...
Vec3f Camera::_mPosition;
Matrix Camera::_mProjectionMatrix;
Matrix Camera::_mLookAtMatrix;

Camera::Camera()
{
}

Camera::~Camera()
{
}

Vec3f Camera::GetPosition()
{
	return _mPosition;
}

Matrix Camera::GetProjectionMatrix()
{
	return _mProjectionMatrix;
}

Matrix Camera::GetLookAtMatrix()
{
	return _mLookAtMatrix;
}

void Camera::SetPosition(float x, float y, float z)
{
	_mPosition.x = x;
	_mPosition.y = y;
	_mPosition.z = z;
}

void Camera::SetProjectionMatrix(Matrix m)
{
	_mProjectionMatrix = m;
}

void Camera::SetLookAtMatrix(Matrix m)
{
	_mLookAtMatrix = m;
}
