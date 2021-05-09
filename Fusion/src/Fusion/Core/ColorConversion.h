#pragma once

#include "Fusion/Core/Base.h"

#include <glm/glm.hpp>

namespace Fusion {

	F_API glm::vec4 RGBNormalize(const glm::vec4& color);

	F_API glm::vec4 HexToRGB(const std::string_view& hex);
}
