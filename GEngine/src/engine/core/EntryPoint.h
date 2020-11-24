#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern GEngine::Application* GEngine::CreateApplication();

int main(int argc, char** argv)
{
	GEngine::Log::Init();
	ENGINE_CORE_WARN("Initialized Log!");
	ENGINE_INFO("Hello!");

	auto app = GEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif
