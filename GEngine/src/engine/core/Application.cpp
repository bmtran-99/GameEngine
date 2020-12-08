#include "Engine_pch.h"
#include "Application.h"
#include "Log.h"
#include "Input.h"

#include <glm.hpp>

namespace GEngine
{
	typedef glm::vec3 Vertex;

	Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		m_Instance = this;
		m_Window = std::make_unique<Window>();
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_RendererLayer = new Renderer();
		PushLayer(m_RendererLayer);

		float vertices[] = {
			-0.5f,  0.5f,  0.5f,          
			-0.5f, -0.5f,  0.5f,		 
			 0.5f, -0.5f,  0.5f,		 
			 0.5f,  0.5f,  0.5f,		 
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f
		};

		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3,

			7, 6, 1,
			7, 1, 0,

			4, 5, 6,
			4, 6, 7,

			3, 2, 5,
			3, 5, 4
		};

		m_RendererLayer->Bind(sizeof(vertices), vertices, sizeof(indices), indices);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			/* Render here */
			m_RendererLayer->Clear();
			m_RendererLayer->Draw(8);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
}

