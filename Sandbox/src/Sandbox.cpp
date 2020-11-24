#include <GEngine.h>

class Sandbox : public GEngine::Application
{
public: 
	Sandbox()
	{
		PushOverlay(new GEngine::ImGuiLayer());
	}

	~Sandbox() {}

};

GEngine::Application* GEngine::CreateApplication()
{
	return new Sandbox();
}