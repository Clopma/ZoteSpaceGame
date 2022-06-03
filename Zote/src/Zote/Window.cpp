#include "Window.h"

namespace Zote
{
	const int Window::glMinorVersion = 3;
	const int Window::glMajorVersion = 3;

	Window::Window()
		: name("Default Zote Window"), width(800), height(600), color(Color::grey) {}

	Window::Window(const std::string& name, int width, int height, const Color& color)
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
		//Limitador para no usar código deprecated
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//Permitir código nuevo.
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
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

		//Recuperamos Buffer size information (se explicará en el futuro).
		glfwGetFramebufferSize(glfwWindow, &bufferWidth, &bufferHeight);

		//Inicializamos el contexto para GLEW
		/* Le decimos a GLEW que esta será la ventana a la que
		estará conectada el contexto de Open GL.*/
		glfwMakeContextCurrent(glfwWindow);

		//ASIGNAR INPUTS

		//encapsulamos y desactivamos el cursor
		//glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glewExperimental = true;

		//Inciamos GLEW
		if (glewInit() != GLEW_OK)
		{
			LOG("GLEW initialisation failed!");
			glfwDestroyWindow(glfwWindow);
			glfwTerminate();
			return false;
		}

		glEnable(GL_DEPTH_TEST);

		//Elegimos el tamaño del Viewport
		glViewport(0, 0, bufferWidth, bufferHeight);

		glfwSetWindowUserPointer(glfwWindow, this);

		initialized = true;
		return true;
	}

	void Window::StartLoop()
	{
		if (!initialized)
			return;

		while (!glfwWindowShouldClose(glfwWindow))
		{
			//Eventos de Input
			glfwPollEvents();

			//Limpiar la ventana
			glClearColor(color.r, color.g, color.b, color.a);
			/* Cuando se pintan píxeles en la pantalla la información que contienen no sólo es de color.
			Con la siguiente función especifico qué datos de los pixeles se han de limpiar.
			(clear color buffer) */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//DRAW STUFF

			glfwSwapBuffers(glfwWindow);
		}
	}
}