#pragma once
#include <glew.h>
#include "Core.h"

#include "Utils/Math.h"
#include "Utils/Log.h"
#include "Utils/CustomTypes.h"
#include "Utils/String.h"
#include "Utils/GlobalStrings.h"

namespace Zote
{
	class ZOTE_API Shader
	{
		int shaderID, modelLocation, projectionLocation, viewLocation;

		str ReadFile(cstr fileLocation);
		bool Compile(int shaderID, cstr shaderCode, int shaderType, int theShader);
		void LinkAndValidate(cstr vertexCode, cstr fragmentCode);
		void Create(cstr vertexLocation, cstr fragmentLocation);

	public:
		Shader(cstr vertexLocation, cstr fragmentLocation);
		Shader();
		~Shader();

		const int GetUniform(cstr name) const { return glGetUniformLocation(shaderID, name); }
		
		void SetUniformFloat(cstr name, float value);
		void SetUnfiformMat4(cstr name, mat4 value);
		void SetUniformVec4(cstr name, vec4 value);
		void SetUniformVec3(cstr name, vec3 value);

		void Use();
		void Unbind();
		void Clear();
	};
}



