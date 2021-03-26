#pragma once

#include "Fusion/Core/Base.h"

namespace Fusion { namespace Graphics {

	class Context
	{
	public:
		virtual ~Context() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<Context> Create(void* window);
	};

} }
