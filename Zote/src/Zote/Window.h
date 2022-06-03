#pragma once

#include<iostream>
#include <string>
#include<glew.h>
#include<glfw3.h>
#include"Maths/Color.h"
#include "Core.h"

#define LOG(a) std::cout << a << std::endl;

namespace Zote
{
	class ZOTE_API Window
	{
		const std::string name;
		int width, height;
		const Color color;
		
		GLFWwindow* glfwWindow = 0;
		int bufferWidth = 0;
		int bufferHeight = 0;
		bool initialized = false;

		static const int glMinorVersion;
		static const int glMajorVersion;

		void SetProperties();

	public:
		Window();
		Window(const std::string name, int width, int height, const Color color);
		~Window();

		bool Init();
		void StartLoop();

		int GetBufferWidth() const { return bufferWidth; }
		int GetBufferHeight() const { return bufferHeight; }
	};
}

