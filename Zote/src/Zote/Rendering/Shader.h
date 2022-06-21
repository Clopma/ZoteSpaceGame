#pragma once
#include <iostream>
#include <glew.h>
#include <fstream>
#include <string>
#include "Core.h"
#include "Maths/GlmCommon.h"
#include "Utils/GlobalStrings.h"

using c_str = const char*;
using string = std::string;

namespace Zote
{
	class ZOTE_API Shader
	{
		int shaderID, modelLocation, projectionLocation, viewLocation;

		string ReadFile(c_str fileLocation);
		bool Compile(int shaderID, c_str shaderCode, int shaderType, int theShader);
		void LinkAndValidate(c_str vertexCode, c_str fragmentCode);
		void Create(c_str vertexLocation, c_str fragmentLocation);

	public:
		Shader(c_str vertexLocation, c_str fragmentLocation);
		Shader();
		~Shader();

		const int GetUniform(c_str name) const { return glGetUniformLocation(shaderID, name); }
		
		void SetUniformFloat(c_str name, float value);
		void SetUnfiformMat4(c_str name, mat4 value);
		void SetUniformVec4(c_str name, vec4 value);

		void Use();
		void Unbind();
		void Clear();
	};
}



