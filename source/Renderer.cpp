//-----------------------------------------------------------------------------
//@File:	Renderer.cpp
//@Brief:	Renderer class implementaion
//@Author:	Hector Morales Piloni
//@Date:	April 11, 2015
//-----------------------------------------------------------------------------
#include "Renderer.h"

Renderer::Renderer(int width, int height)
{
	//Scene::SetWindowHeight(height);
	//Scene::SetWindowWidth(width);	
	//Scene::SetLightPosition(2.0f, 2.0f, 2.0f);
}

Renderer::~Renderer()
{
	delete _mCube;
	delete _mFloor;
	delete _mSphere;

	_mCube = NULL;
	_mFloor = NULL;
	_mSphere = NULL;
}

//Use an initialize method instead of default constructor
//this helps debugging and it's better since when we call
//this method, it means the object has been fully created
bool Renderer::Initialize()
{
	_mLightRot = 0.0;

	_mCube = new Cube();
	_mCube->Initialize();	

	_mFloor = new Floor();
	_mFloor->Initialize();

	_mSphere = new Sphere();
	_mSphere->Initialize();
	
	//Initialize OpenGL ES
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glViewport(0, 0, Scene::GetWindowWidth(), Scene::GetWindowHeight());

	//Matrix projectionMatrix = Matrix::matrixPerspective(45.0f, Scene::GetWindowWidth() / (float)Scene::GetWindowHeight(), 0.01f, 100.0f);
	//Scene::SetProjectionMatrix(projectionMatrix);

	return true;
}

void Renderer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Rotate the light circulary
	_mLightRot += 0.05f;
	if (_mLightRot >= 360) _mLightRot -= 360;
	//Scene::SetLightPosition(2.0f*cos(_mLightRot), 2.0f, 2.0f*sin(_mLightRot));

	//Draw the geometry
	_mFloor->Draw();
	_mCube->Draw();
	_mSphere->Draw();
}
