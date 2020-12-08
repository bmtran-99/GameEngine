#pragma once

#include "engine\renderer\RendererContext.h"

namespace GEngine
{
	class OpenGLContext : public RendererContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffer() override;
	private:
		GLFWwindow* m_Window;
	};
}


