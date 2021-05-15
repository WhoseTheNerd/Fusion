#pragma once

#include <array>

namespace Fusion { namespace Audio {

	class Listener
	{
	public:
		static void SetPosition(float x, float y, float z);
		static void SetVelocity(float x, float y, float z);
		static void SetOrientation(const std::array<float, 6>& orientation);
	};
} }
