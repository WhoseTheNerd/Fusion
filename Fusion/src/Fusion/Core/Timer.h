#pragma once

#include "Fusion/Core/Base.h"

#include <chrono>

namespace Fusion {

	class F_API Timer
	{
	public:
		Timer(const char* name);
		~Timer();
	private:
		const char* m_Name;
		std::chrono::high_resolution_clock::time_point m_Now = std::chrono::high_resolution_clock::now();
	};
}
