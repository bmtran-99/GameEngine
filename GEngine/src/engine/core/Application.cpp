#include "Engine_pch.h"
#include "Application.h"
#include "Log.h"
#include "Input.h"
#include "engine\renderer\Primitives.h"

#include <glm.hpp>

namespace GEngine
{
	Cube cube;

	Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		m_Instance = this;
		m_Window = std::make_unique<Window>();
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_RendererLayer = new Renderer();
		PushLayer(m_RendererLayer);

		m_RendererLayer->Bind(cube.getNrOfVertices(), cube.getVertices(), cube.getNrOfIndices(), cube.getIndices());
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
			m_RendererLayer->Draw(cube.getNrOfVertices());

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

