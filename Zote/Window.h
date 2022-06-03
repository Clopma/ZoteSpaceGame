#pragma once

#include<iostream>

#include<glew.h>
#include<glfw3.h>

namespace Zote
{
	class Window
	{
		int width = 800;
		int height = 600;
		

	public:
		Window();
		Window(int width, int height);

	};
}

