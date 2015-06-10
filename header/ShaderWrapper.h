//-----------------------------------------------------------------------------
//@File:	ShaderWrapper.h
//@Brief:	Shader wrapper class declaration
//@Author:	Hector Morales Piloni
//@Date:	April 15, 2015
//-----------------------------------------------------------------------------
#pragma once
#define GLES_VERSION 2

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <string>
#include <map>

#include "Shader.h"

using namespace std;
using namespace MaliSDK;

class ShaderWrapper
{
public:
	ShaderWrapper();
	~ShaderWrapper();
	void SetTechnique(string technique);
	void UseTechnique();
	void SetAttribute(string name);
	void SetUniform(string name);
	GLint GetAttributeID(string name);
	GLint GetUniformID(string name);

private:
	GLuint _mShaderProgramID;

	//These maps are going to hold all the attribute and uniform
	//variables, we can have different number/name of these per shader
	map<string,int> _mAttribute;
	map<string,int> _mUniform;
};

