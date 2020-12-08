#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

#include "engine\events\ApplicationEvent.h"
#include "engine\renderer\Renderer.h"

namespace GEngine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *m_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool m_Running = true;

		static Application* m_Instance;

		std::unique_ptr<Window> m_Window;

		LayerStack m_LayerStack;

		Renderer* m_RendererLayer;
	};

	Application* CreateApplication();

}

