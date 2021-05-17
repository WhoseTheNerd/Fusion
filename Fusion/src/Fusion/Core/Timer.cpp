#include "fpch.h"
#include "Timer.h"

namespace Fusion {

	Timer::Timer(const char* name)
		: m_Name(name)
	{
	}

	Timer::~Timer()
	{
		auto end = std::chrono::high_resolution_clock::now();
		int64_t elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - m_Now).count();
		printf("%s took %lld microseconds\n", m_Name, elapsed);
	}
}
