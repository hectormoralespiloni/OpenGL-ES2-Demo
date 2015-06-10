//-----------------------------------------------------------------------------
//@File:	Scene.cpp
//@Brief:	Scene implementation file
//@Author:	Hector Morales Piloni
//@Date:	April 12, 2015
//-----------------------------------------------------------------------------
#include "Scene.h"

//In order to avoid Linkage problems
//we need to define static members in the implementation file
//since in the header (.h) file, we only declare them...
Vec3f Scene::_mLightPosition;
Vec3f Scene::_mCameraPosition;
Matrix Scene::_mProjectionMatrix;

void Scene::SetProjectionMatrix(Matrix m)
{
	_mProjectionMatrix = m;
}

void Scene::SetLightPosition(float x, float y, float z)
{
	_mLightPosition.x = x;
	_mLightPosition.y = y;
	_mLightPosition.z = z;
}

void Scene::SetCameraPosition(float x, float y, float z)
{
	_mCameraPosition.x = x;
	_mCameraPosition.y = y;
	_mCameraPosition.z = z;
}

void Scene::SetWindowHeight(int h)
{
	_mWindowHeight = h;
}

void Scene::SetWindowWidth(int w)
{
	_mWindowWidth = w;
}

Vec3f Scene::GetLightPosition()
{
	return _mLightPosition;
}

Vec3f Scene::GetCameraPosition()
{
	return _mCameraPosition;
}


Matrix Scene::GetProjectionMatrix()
{
	return _mProjectionMatrix;
}
