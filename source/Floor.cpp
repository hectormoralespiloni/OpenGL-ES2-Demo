//-----------------------------------------------------------------------------
//@File:	Floor.cpp
//@Brief:	Floor implementation file
//@Author:	Hector Morales Piloni
//@Date:	April 13, 2015
//-----------------------------------------------------------------------------
#include "Floor.h"

Floor::Floor()
{
}

Floor::~Floor()
{
}

bool Floor::Initialize()
{
	_mVertices = new vector<GLfloat>;
	_mNormals = new vector<GLfloat>;
	_mIndices = new vector<GLuint>;
	_mTexCoords = new vector<GLfloat>;
	_mColors = new vector<GLfloat>;

	_mVertices->push_back(-0.5); _mVertices->push_back(0.5); _mVertices->push_back( 0.5); //v0
	_mVertices->push_back( 0.5); _mVertices->push_back(0.5); _mVertices->push_back( 0.5); //v1
	_mVertices->push_back( 0.5); _mVertices->push_back(0.5); _mVertices->push_back(-0.5); //v2
	_mVertices->push_back(-0.5); _mVertices->push_back(0.5); _mVertices->push_back(-0.5); //v3
	
	_mNormals->push_back(0.0); _mNormals->push_back(1.0); _mNormals->push_back(0.0);
	_mNormals->push_back(0.0); _mNormals->push_back(1.0); _mNormals->push_back(0.0);
	_mNormals->push_back(0.0); _mNormals->push_back(1.0); _mNormals->push_back(0.0);
	_mNormals->push_back(0.0); _mNormals->push_back(1.0); _mNormals->push_back(0.0);

	_mIndices->push_back(0); _mIndices->push_back(1); _mIndices->push_back(2); _mIndices->push_back(3);
	
	_mTexCoords->push_back(0.0); _mTexCoords->push_back(0.0);
	_mTexCoords->push_back(4.0); _mTexCoords->push_back(0.0);
	_mTexCoords->push_back(4.0); _mTexCoords->push_back(4.0);
	_mTexCoords->push_back(0.0); _mTexCoords->push_back(4.0);

	//Define a white floor (4 vertices * 4 colors RGBA)
	for (int i = 0; i < 4*4; i++) {
		_mColors->push_back(1.0f);
	}

	//Create Vertex & Index buffer objects to avoid copying shape's data from host CPU memory each frame
	//VBO are defined as GL_ARRAY_BUFFER and IBO as GL_ELEMENT_ARRAY_BUFFER
	//Last parameter means that passed data is modified once and used many times
	glGenBuffers(1, &_mVBOVertices);
	glBindBuffer(GL_ARRAY_BUFFER, _mVBOVertices);
	glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(GLfloat), _mVertices->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_mVBONormals);
	glBindBuffer(GL_ARRAY_BUFFER, _mVBONormals);
	glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(GLfloat), _mNormals->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_mVBOColors);
	glBindBuffer(GL_ARRAY_BUFFER, _mVBOColors);
	glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(GLfloat), _mColors->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_mVBOTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER, _mVBOTexCoords);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(GLfloat), _mTexCoords->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_mIBOIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mIBOIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), _mIndices->data(), GL_STATIC_DRAW);

	//Unbind the buffers to avoid accidental writes to these buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//We can safely delete our shape data, since it has been transfered to GPU memory
	delete _mVertices;
	_mVertices = NULL;
	delete _mNormals;
	_mNormals = NULL;
	delete _mColors;
	_mColors = NULL;
	delete _mIndices;
	_mIndices = NULL;
	delete _mTexCoords;
	_mTexCoords = NULL;

	//load texture from file
	string texturePath = "assets/floor.raw";
	unsigned char *textureData = NULL;
	Texture::loadData(texturePath.c_str(), &textureData);

	//setup texturing	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		return false;

	return true;
}

void Floor::Draw()
{
	//Enable attributes for position, color and normals
	//because we're using VBO's, we pass as the last parameter an offset
	//instead of a pointer to the data buffer
	glBindBuffer(GL_ARRAY_BUFFER, _mVBOVertices);
	glEnableVertexAttribArray(_mShader->GetAttributeID("position"));
	glVertexAttribPointer(_mShader->GetAttributeID("position"), 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _mVBONormals);
	glEnableVertexAttribArray(_mShader->GetAttributeID("normal"));
	glVertexAttribPointer(_mShader->GetAttributeID("normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _mVBOColors);
	glEnableVertexAttribArray(_mShader->GetAttributeID("color"));
	glVertexAttribPointer(_mShader->GetAttributeID("color"), 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _mVBOTexCoords);
	glEnableVertexAttribArray(_mShader->GetAttributeID("texCoords"));
	glVertexAttribPointer(_mShader->GetAttributeID("texCoords"), 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Create our transformation matrices
	_mModelViewMatrix = Matrix::identityMatrix;
	_mRotationMatrix = Matrix::createRotationX(30.0) * Matrix::createRotationY(45.0);
	_mScaleMatrix = Matrix::createScaling(_mScaleX, _mScaleY, _mScaleZ);
	_mTranslationMatrix = Matrix::createTranslation(_mPosX, _mPosY, _mPosZ);
	_mModelViewMatrix = _mTranslationMatrix * _mScaleMatrix * _mRotationMatrix * _mModelViewMatrix;
	Matrix modelViewProjection = Camera::GetProjectionMatrix() * Camera::GetLookAtMatrix() * _mModelViewMatrix;

	glUniformMatrix4fv(_mShader->GetUniformID("modelViewProjectionMatrix"), 1, GL_FALSE, modelViewProjection.getAsArray());
	glUniformMatrix4fv(_mShader->GetUniformID("modelViewMatrix"), 1, GL_FALSE, _mModelViewMatrix.getAsArray());
	glUniform3f(_mShader->GetUniformID("lightPosition"), Light::GetPosition().x, Light::GetPosition().y, Light::GetPosition().z);

	//Here we enable texture unit 0 that contains our floor texture previously set
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(_mShader->GetUniformID("texture0"), 0);
	glUniform1i(_mShader->GetUniformID("useTexture"), 1);

	//Bind our IBO and instead of passing the indices buffer to glDrawElements
	//we pass an offset
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mIBOIndices);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}