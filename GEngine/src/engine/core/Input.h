#pragma once

#include "Core.h"

#include "engine\core\KeyCodes.h"
#include "engine\core\MouseCodes.h"

#include <glm.hpp>

namespace GEngine
{
	class ENGINE_API Input
	{
	public:
		static bool IsKeyPressed(const KeyCode keycode);
		static bool IsMousePressed(const MouseCode button);

		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
