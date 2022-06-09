#pragma once

#include <glm/glm.hpp>
#include <glfw3.h>
#include "Core.h"

namespace Zote
{
	class ZOTE_API Input
	{
	public:
		static void Init(GLFWwindow* window);
		static bool GetKeyPressed(int keycode);
		static bool GetMouseButtonPressed(int button);
		static glm::vec2 GetMousePosition();

	private:
		static GLFWwindow* m_window;
	};
}