#include "Window.h"

#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"
#include "ECS/Components.h"
#include "Input.h"

namespace Zote
{
	bool Window::openGLConsoleLogs = false;
	const int Window::glMinorVersion = 3;
	const int Window::glMajorVersion = 3;

	Window::Window()
		: name("Default Zote Window"), width(800), height(600), color(Color::Normalize(Color::grey)) {}

	Window::Window(const std::string name, int width, int height, const Color color)
		: name(name), width(width), height(height), color(color) {}

	Window::~Window()
	{
		glfwDestroyWindow(glfwWindow);
		glfwTerminate();
	}

	void Window::SetProperties()
	{
		//OpenGL version 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinorVersion);
		//Disables deprecated code
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//Enables new code
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
	}

	void Window::CalculateDeltaTime()
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
	}

	void Window::CalculateFrameRate()
	{
		frameRateTime += deltaTime;
		currentFrames++;
		if (frameRateTime < 1 || currentFrames == 0) return;
		frameRate = currentFrames;
		frameRateTime = 0;
		currentFrames = 0;
	}

	bool Window::Init()
	{
		if (!glfwInit())
		{
			LOG("GLFW initialisation failed!")
			return false;
		}

		SetProperties();

		glfwWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

		if (!glfwWindow)
		{
			LOG("GLFW window creation failed!")
			glfwTerminate();
			return false;
		}

		glfwGetFramebufferSize(glfwWindow, &bufferWidth, &bufferHeight);

		//Provides glfwWindow as open gl context.
		glfwMakeContextCurrent(glfwWindow);

		//INPUT ASSIGNEMENT
		Input::Init(glfwWindow);

		//Cursor settings
		glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glewExperimental = true;

		if (glewInit() != GLEW_OK)
		{
			LOG("GLEW initialisation failed!");
			glfwDestroyWindow(glfwWindow);
			glfwTerminate();
			return false;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageCallback(OnDebugMessage, nullptr);

		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, bufferWidth, bufferHeight);
		glfwSetWindowUserPointer(glfwWindow, this);

		initialized = true;
		return true;
	}

	void Window::StartLoop()
	{
		if (!initialized)
			return;

		while (!glfwWindowShouldClose(glfwWindow) && !close)
		{
			//Input events
			glfwPollEvents();

			glClearColor(color.r, color.g, color.b, color.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			CalculateDeltaTime();
			CalculateFrameRate();

			//DRAW STUFF
			OnRenderFrame.Invoke({ GetAspect(), deltaTime, frameRate });

			glfwSwapBuffers(glfwWindow);
		}
	}
	void Window::OnDebugMessage(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
	{
		if (openGLConsoleLogs)
			std::cout << message << std::endl;
	}
}