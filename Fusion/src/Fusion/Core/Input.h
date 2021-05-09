#pragma once

#include "Fusion/Core/Base.h"

#include "Fusion/Core/KeyCodes.h"
#include "Fusion/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Fusion {

	class F_API Input
	{
	public:
		static bool IsKeyPressed(const KeyCode key);
		static bool IsMouseButtonPressed(const MouseCode button);

		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
