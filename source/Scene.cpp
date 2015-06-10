//-----------------------------------------------------------------------------
//@File:	Scene.cpp
//@Brief:	Scene implementation file
//@Author:	Hector Morales Piloni
//@Date:	April 12, 2015
//-----------------------------------------------------------------------------
#include "Scene.h"

Scene::Scene(int w, int h)
{
	_mWindowHeight = h;
	_mWindowWidth = w;
}

Scene::~Scene()
{
	delete _mCamera;
	delete _mLight;
	delete _mCube;
	delete _mFloor;
	delete _mSphere;

	_mCamera = NULL;
	_mLight = NULL;
	_mCube = NULL;
	_mFloor = NULL;
	_mSphere = NULL;
}

void Scene::SetProjectionMatrix(Matrix m)
{
	_mCamera->SetProjectionMatrix(m);
}

void Scene::SetLightPosition(float x, float y, float z)
{
	_mLight->SetPosition(x, y, z);
}

void Scene::SetCameraPosition(float x, float y, float z)
{
	_mCamera->SetPosition(x, y, z);
}

void Scene::SetWindowHeight(int h)
{
	_mWindowHeight = h;
}

void Scene::SetWindowWidth(int w)
{
	_mWindowWidth = w;
}

//Use an initialize method instead of default constructor
//this helps debugging and it's better since when we call
//this method, it means the object has been fully created
bool Scene::Initialize()
{
	_mLight = new Light();
	_mLight->SetPosition(0.0f, 10.0f, 0.0f);

	_mCube = new Cube();
	_mCube->Initialize();
	_mCube->SetPosition(1.0, 1.5, 0.0);

	_mFloor = new Floor();
	_mFloor->Initialize();
	_mFloor->SetScale(4.0, 1.0, 4.0);

	_mSphere = new Sphere(3);
	_mSphere->Initialize();
	_mSphere->SetPosition(-1.0f, 1.5f, -3.0f);
	_mSphere->SetScale(0.8f, 0.8f, 0.8f);

	_mSphere2 = new Sphere(1);
	_mSphere2->Initialize();
	_mSphere2->SetPosition(1.5f, 1.0f, 2.0f);
	_mSphere2->SetScale(0.6f, 0.6f, 0.6f);

	_mSphere3 = new Sphere(0);
	_mSphere3->Initialize();
	_mSphere3->SetPosition(-1.5f, 1.0f, 2.0f);
	_mSphere3->SetScale(0.5f, 0.5f, 0.5f);

	//Initialize OpenGL ES
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, _mWindowWidth, _mWindowHeight);

	//Initialize the camera
	_mCamera = new Camera();
	_mCamera->SetPosition(0.0f, 0.5f, 5.0f);	

	Vec3f center, up;
	up.x = up.z = center.x = center.y = center.z = 0.0f;
	up.y = 1.0f;

	Matrix projectionMatrix = Matrix::matrixPerspective(45.0f, (float)_mWindowWidth / _mWindowHeight, 0.01f, 100.0f);
	Matrix lookAtMatrix = Matrix::matrixCameraLookAt(_mCamera->GetPosition(), center, up);		
	_mCamera->SetProjectionMatrix(projectionMatrix);
	_mCamera->SetLookAtMatrix(lookAtMatrix);

	//Initialize shader techniques and define all attribute & uniforms they use	
	ShaderWrapper *shader;

	//Define Gouraud shading or flat shading (per vexter lighting)
	shader = new ShaderWrapper();
	shader->SetTechnique("Gouraud");
	shader->SetAttribute("position");
	shader->SetAttribute("color");
	shader->SetAttribute("normal");
	shader->SetAttribute("texCoords");
	shader->SetUniform("modelViewProjectionMatrix");
	shader->SetUniform("modelViewMatrix");
	shader->SetUniform("lightPosition");
	shader->SetUniform("texture0");
	shader->SetUniform("useTexture");
	_mShader["Gouraud"] = shader;
	_mCube->AttachShader(_mShader["Gouraud"]);
	_mFloor->AttachShader(_mShader["Gouraud"]);

	//Define Phong shading (per pixel lighting)
	shader = new ShaderWrapper();
	shader->SetTechnique("Phong");
	shader->SetAttribute("position");
	shader->SetAttribute("color");
	shader->SetAttribute("normal");
	shader->SetUniform("modelViewProjectionMatrix");
	shader->SetUniform("modelViewMatrix");
	shader->SetUniform("lightPosition");
	_mShader["Phong"] = shader;
	_mSphere->AttachShader(_mShader["Phong"]);
	_mSphere2->AttachShader(_mShader["Phong"]);
	_mSphere3->AttachShader(_mShader["Phong"]);

	/*
	//Define Shadow Map shader
	shader = new ShaderWrapper();
	shader->SetTechnique("ShadowMap");
	shader->SetAttribute("position");
	shader->SetAttribute("color");
	shader->SetAttribute("normal");
	shader->SetAttribute("texCoords");
	shader->SetUniform("modelViewProjectionMatrix");
	shader->SetUniform("modelViewMatrix");
	shader->SetUniform("lightViewMatrix");
	shader->SetUniform("lightProjectionMatrix");
	shader->SetUniform("lightPosition");
	shader->SetUniform("texture0");
	shader->SetUniform("shadowMap");
	shader->SetUniform("useTexture");
	_mShader["ShadowMap"] = shader;

	//Define Depth shader
	shader = new ShaderWrapper();
	shader->SetTechnique("Depth");
	shader->SetAttribute("position");
	shader->SetUniform("modelViewProjectionMatrix");
	_mShader["Depth"] = shader;
	*/

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		return false;

	if (!CreateShadowTexture())
		return false;

	return true;
}

void Scene::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Rotate the light circulary
	float angle = _mLight->GetRotation() + 0.05f;
	if (angle >= 360) angle -= 360;
	_mLight->SetRotation(angle);

	//Draw the geometry
	//Note that we could be able to change each shape shader technique
	//in real time, by processing user input... e.g.:
	//string technique = GetUserDesiredTechnique();
	//_mCube->AttachShader(_mShader[technique]);
	_mShader["Gouraud"]->UseTechnique();
	_mCube->Draw();
	_mFloor->Draw();

	_mShader["Phong"]->UseTechnique();
	_mSphere->Draw();	//sphere with 3 levels of refinement
	_mSphere2->Draw();	//sphere with 1 level of refinement
	_mSphere3->Draw();	//sphere without refinement (Icosahedron)

	/* 
	//SHADOW MAPPING HERE
	//Needs more setup... not working now
	Vec3f center, up;
	up.x = up.z = center.x = center.y = center.z = 0.0f;
	up.y = 1.0f;
	Matrix lookAtMatrix = Matrix::matrixCameraLookAt(_mLight->GetPosition(), center, up);
	_mCamera->SetLookAtMatrix(lookAtMatrix);

	CreateShadowTexture();
	glBindFramebuffer(GL_FRAMEBUFFER, _mFBO);

	_mCube->AttachShader(_mShader["Depth"]);
	_mFloor->AttachShader(_mShader["Depth"]);
	_mSphere->AttachShader(_mShader["Depth"]);
	_mShader["Depth"]->UseTechnique();
	_mCube->Draw();
	_mFloor->Draw();
	_mSphere->Draw();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	lookAtMatrix = Matrix::matrixCameraLookAt(_mCamera->GetPosition(), center, up);
	_mCamera->SetLookAtMatrix(lookAtMatrix);

	_mCube->AttachShader(_mShader["ShadowMap"]);
	_mFloor->AttachShader(_mShader["ShadowMap"]);
	_mSphere->AttachShader(_mShader["ShadowMap"]);
	_mShader["ShadowMap"]->UseTechnique();
	_mCube->Draw();
	_mFloor->Draw();
	_mSphere->Draw();
	*/
}

//This method sets up a shadow texture using a Frame Buffer Object FBO
bool Scene::CreateShadowTexture()
{
	//Here we generate the texture name and bind it to a TEXTURE 2D object
	//this texture is going to be used as a render target later
	glGenTextures(1, &_mShadowTextureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _mShadowTextureID);

	//Specify the 2D shadow texture options
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Render Buffer Objects (RBO) are used along with FBOs as render targets for offline rendering
	//We don't need colors stored in RBO, only the depth component which is an internal type
	//we specify the type of storage in glRenderbufferStorage
	glGenFramebuffers(1, &_mFBO);
	glGenRenderbuffers(1, &_mRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, _mRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 512, 512);

	//Here we attach both the RBO and texture object to the FBO
	//FBOs have different attachment points, this allows to write 
	//to multiple destinations at the same time0 
	glBindFramebuffer(GL_FRAMEBUFFER, _mFBO);
	glBindTexture(GL_TEXTURE_2D, _mShadowTextureID);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _mRBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _mShadowTextureID, 0);

	//Unbind FBO, otherwise we won't be able to render to the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;
	else
		return true;
}
