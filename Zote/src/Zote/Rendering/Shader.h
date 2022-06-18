#pragma once
#include <iostream>
#include <glew.h>
#include <fstream>
#include <string>
#include "Core.h"
#include "Maths/GlmCommon.h"

using c_str = const char*;
using string = std::string;

namespace Zote
{
	class ZOTE_API Shader
	{
		int shaderID, modelLocation, projectionLocation, viewLocation;

		c_str defaultFragmentLocation = "Shaders/shader.frag";
		c_str defaultVertexLocation = "Shaders/shader.vert";

		c_str modelUniformName = "model";
		c_str viewUniformName = "view";
		c_str projectionUniformName = "projection";

		string ReadFile(c_str fileLocation);
		bool Compile(int shaderID, c_str shaderCode, int shaderType, int theShader);
		void LinkAndValidate(c_str vertexCode, c_str fragmentCode);
		void Create(c_str vertexLocation, c_str fragmentLocation);

	public:
		Shader(c_str vertexLocation, c_str fragmentLocation);
		Shader();
		~Shader();

		const int GetUniform(c_str name) const { return glGetUniformLocation(shaderID, name); }
		
		int GetModelLocation() { return modelLocation; }
		int GetViewLocation() { return viewLocation; }
		int GetProjectionLocation() { return projectionLocation; }
		
		void SetUnfiformMat4(int location, mat4 value);
		void SetUniformVec4(c_str name, vec4 value);

		void Use();
		void Unbind();
		void Clear();
	};
}



