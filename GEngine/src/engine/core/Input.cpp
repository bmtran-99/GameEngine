#include "Engine_pch.h"
#include "Input.h"
#include "Application.h"

#include <GLFW\glfw3.h>

#define GET_GLFW_WINDOW() static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow())

namespace GEngine
{
	bool Input::IsKeyPressed(const KeyCode keycode)
	{
		auto window = GET_GLFW_WINDOW();
		auto state = glfwGetKey(window, static_cast<int>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMousePressed(const MouseCode button)
	{
		auto window = GET_GLFW_WINDOW();
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS || state == GLFW_RELEASE;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto window = GET_GLFW_WINDOW();
		double xpos;
		double ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
}