//-----------------------------------------------------------------------------
//@File:	ShaderWrapper.cpp
//@Brief:	Shader wrapper class implementation
//@Author:	Hector Morales Piloni
//@Date:	April 15, 2015
//-----------------------------------------------------------------------------
#include "ShaderWrapper.h"

ShaderWrapper::ShaderWrapper()
{
}

ShaderWrapper::~ShaderWrapper()
{
}

void ShaderWrapper::UseTechnique()
{
	glUseProgram(_mShaderProgramID);
}

void ShaderWrapper::SetTechnique(string name)
{
	//Clear every attribute & uniform previoulsy defined so we can start over
	_mAttribute.clear();
	_mUniform.clear();

	//Full paths to the shader files
	string vertexShaderPath = "assets/" + name + ".vert";
	string fragmentShaderPath = "assets/" + name + ".frag";

	//Create unique ID and process shaders
	GLuint vertexShaderID, fragmentShaderID;
	Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
	Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
	_mShaderProgramID = glCreateProgram();
	glAttachShader(_mShaderProgramID, vertexShaderID);
	glAttachShader(_mShaderProgramID, fragmentShaderID);
	glLinkProgram(_mShaderProgramID);
	glUseProgram(_mShaderProgramID);
}

void ShaderWrapper::SetAttribute(string name)
{
	//Get attribute location and store its ID in our attributes map
	_mAttribute[name] = glGetAttribLocation(_mShaderProgramID, name.c_str());
}

void ShaderWrapper::SetUniform(string name)
{
	//Get uniform location and store its ID in our uniforms map
	_mUniform[name] = glGetUniformLocation(_mShaderProgramID, name.c_str());
}

GLint ShaderWrapper::GetAttributeID(string name)
{
	return _mAttribute[name];
}

GLint ShaderWrapper::GetUniformID(string name)
{
	return _mUniform[name];
}