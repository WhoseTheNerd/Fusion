#pragma once

#include "Fusion/Core/Base.h"

namespace Fusion {
	
	class F_API Timestep
	{
	public:
		Timestep(const float time = 0.0f)
			: m_Time(time)
		{}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};
}
