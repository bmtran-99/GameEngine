#include "Engine_pch.h"
#include "Window.h"
#include "Log.h"

#include "engine\events\ApplicationEvent.h"
#include "engine\events\KeyEvent.h"
#include "engine\events\MouseEvent.h"

#define ASSERT(x, ...) { if (!(x))  {ENGINE_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }

namespace GEngine
{	
	Window::Window(const WindowProps& props)
	{
		Init(props);
	}

	Window::~Window()
	{
		Shutdown();
	}

	static void GLFWErrorCallback(int error, const char* context)
	{
		ENGINE_CORE_ERROR("GLFW Error ({0}): {1}", error, context);
	}

	void Window::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		ENGINE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		/* Initialize GLFW lib */
		if (!b_glfwInit)
		{
			b_glfwInit = glfwInit();
			ASSERT(b_glfwInit, "Failed to Initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}
		
		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			return;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);

		/* set up GLAD */
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ASSERT(status, "Failed to Initialize GLAD!");

		/* sets the user-defined pointer of the specified window */
		glfwSetWindowUserPointer(m_Window, &m_Data);

		/* set GLFW callbacks */
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		}
		);

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
					
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
				case GLFW_PRESS:
				{
					MousePressedEvent event(button);
					data.EventCallback(event);
					break;
				}
		
				case GLFW_RELEASE:
				{
					MouseReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		}
		);

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(xOffset, yOffset);
			data.EventCallback(event);
		}
		);

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPosition, double yPosition)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event(xPosition, yPosition);
			data.EventCallback(event);
		}
		);
	}

	void Window::OnUpdate()
	{
		/* Swap front and back buffers */
		glfwSwapBuffers(m_Window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	void Window::Shutdown()
	{
		glfwTerminate();
	}
}

