#include "Shader.h"

namespace Zote
{
	string Shader::ReadFile(c_str fileLocation)
	{
		string content;
		std::ifstream fileStream(fileLocation, std::ios::in);

		if (!fileStream.is_open())
		{
			printf("Failed to read %s! File doesn't exist.", fileLocation);
			return "";
		}

		string line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			content.append(line + "\n");
		}

		fileStream.close();
		return content;
	}
	bool Shader::Compile(int shaderID, c_str shaderCode, int shaderType, int theShader)
	{
		c_str theCode[1];
		theCode[0] = shaderCode;

		int codeLength[1];
		codeLength[0] = strlen(shaderCode);

		glShaderSource(theShader, 1, theCode, codeLength);
		glCompileShader(theShader);

		int result = 0;
		char eLog[1024] = { 0 };
		glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
			printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
			return false;
		}
		
		glAttachShader(shaderID, theShader);
		return true;
	}
	void Shader::LinkAndValidate(c_str vertexCode, c_str fragmentCode)
	{
		shaderID = glCreateProgram();

		if (!shaderID)
		{
			printf("Error creating shader program!");
			return;
		}

		int vertex = glCreateShader(GL_VERTEX_SHADER);

		if (!Compile(shaderID, vertexCode, GL_VERTEX_SHADER, vertex))
		{
			printf("Error compiling vertex shader!");
			return;
		}

		int fragment = glCreateShader(GL_FRAGMENT_SHADER);
		
		if (!Compile(shaderID, fragmentCode, GL_FRAGMENT_SHADER, fragment))
		{
			printf("Error compiling fragment shader!");
			return;
		}
			
		int result = 0;
		char eLog[1024] = { 0 };

		glLinkProgram(shaderID);
		glGetProgramiv(shaderID, GL_LINK_STATUS, &result);

		if (!result)
		{
			glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
			printf("Error linking program '%s'\n", eLog);
			return;
		}

		glValidateProgram(shaderID);
		glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);

		if (!result)
		{
			glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
			printf("Error validating program '%s'\n", eLog);
			return;
		}

		glDetachShader(shaderID, vertex);
		glDetachShader(shaderID, fragment);
		
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	void Shader::Create(c_str vertexLocation, c_str fragmentLocation)
	{
		string vertexString = ReadFile(vertexLocation);
		string fragmentString = ReadFile(fragmentLocation);
		LinkAndValidate(vertexString.c_str(), fragmentString.c_str());
	}
	Shader::Shader(c_str vertexLocation, c_str fragmentLocation)
		: shaderID(0), modelLocation(0), viewLocation(0), projectionLocation(0)
	{
		Create(vertexLocation, fragmentLocation);
	}
	Shader::Shader()
		: shaderID(0), modelLocation(0), viewLocation(0), projectionLocation(0)
	{
		Create(defaultVertexLocation, defaultFragmentLocation);
	}
	Shader::~Shader()
	{
		Clear();
	}
	void Shader::SetUnfiformMat4(c_str name, mat4 value)
	{
		int location = GetUniform(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
	void Shader::SetUniformVec4(c_str name, vec4 value)
	{
		int location = GetUniform(name);
		glUniform4fv(location, 1, glm::value_ptr(value));
	}
	void Shader::Use()
	{
		glUseProgram(shaderID);
	}
	void Shader::Unbind()
	{
		glUseProgram(0);
	}
	void Shader::Clear()
	{
		if (shaderID == 0) return;
		glDeleteProgram(shaderID);
		shaderID = 0;
		modelLocation = 0;
		viewLocation = 0;
		projectionLocation = 0;
	}
}