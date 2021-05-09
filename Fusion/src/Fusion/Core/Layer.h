#pragma once

#include "Fusion/Core/Base.h"
#include "Fusion/Core/Timestep.h"
#include "Fusion/Events/Event.h"

namespace Fusion {

	class F_API Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(const Timestep ts) {}
		virtual void OnEvent(Event& event) {}
	};
}
