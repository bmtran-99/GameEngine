#pragma once

#include <iostream>
#include <sstream>
#include <memory>
#include <functional>
#include <algorithm>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "engine\core\KeyCodes.h"
#include "engine\core\MouseCodes.h"

#ifdef ENGINE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
