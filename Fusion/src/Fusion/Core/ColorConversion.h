#pragma once

#include "Fusion/Core/Base.h"

#include <glm/glm.hpp>

namespace Fusion {

	static glm::vec4 RGBNormalize(const glm::vec4& color)
	{
		return glm::vec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a);
	}

	static glm::vec4 HexToRGB(const std::string& hex)
	{
		int r, g, b;
		int count = sscanf(hex.c_str(), "%02x%02x%02x", &r, &g, &b);
		F_CORE_ASSERT(count == 3, "Hex string must contain 3 pairs of hex characters, no spaces.");
		return RGBNormalize({ r,g,b, 1.0f });
	}
}
