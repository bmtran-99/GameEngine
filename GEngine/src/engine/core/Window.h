#pragma once

#include "Engine_pch.h"

#include "engine\core\Core.h"
#include "engine\events\Event.h"

#include "opengl\OpenGLContext.h"

namespace GEngine
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "GEngine", uint32_t width = 1600, uint32_t height = 900)
			: Title(title), Width(width), Height(height) {}
	};

	class ENGINE_API Window
	{
		typedef std::function<void(Event&)> EventCallbackfn;

	public:
		Window(const WindowProps& props = WindowProps());
		~Window();

		inline uint32_t GetWidth() const { return m_Data.Width; }
		inline uint32_t GetHeight() const { return m_Data.Height; }

		void OnUpdate();

		inline void* GetNativeWindow() const { return m_Window; }

		inline void SetEventCallback(const EventCallbackfn& callback) { m_Data.EventCallback = callback; }

	private:
		GLFWwindow* m_Window;

		void Init(const WindowProps& props);
		void Shutdown();

		struct WindowData
		{
			std::string Title;
			uint32_t Width;
			uint32_t Height;

			EventCallbackfn EventCallback;
		};

		WindowData m_Data;

		OpenGLContext* m_Context;

		bool b_glfwInit = false;
	};
}