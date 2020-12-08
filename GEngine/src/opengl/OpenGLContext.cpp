#include "Engine_pch.h"
#include "OpenGLContext.h"

#define ASSERT(x, ...) { if (!(x))  {ENGINE_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }

namespace GEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window(window)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ASSERT(status, "Failed to initialize Glad!");

		ENGINE_CORE_INFO("OpenGL Info:");
		ENGINE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		ENGINE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		ENGINE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Engine requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_Window);
	}
}