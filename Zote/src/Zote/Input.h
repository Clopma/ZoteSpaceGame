#pragma once

#include <glfw3.h>
#include "Core.h"
#include "Utils/Math.h"

namespace Zote
{
	class ZOTE_API Input
	{
	public:
		static void Init(GLFWwindow* window);
		static bool GetKeyPressed(int keycode);
		static bool GetMouseButtonPressed(int button);
		static vec2 GetMousePosition();

	private:
		static GLFWwindow* m_window;
	};
}