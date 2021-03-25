#pragma once

#include "Fusion/Base.h"

namespace Fusion {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Client defines this!
	Scope<Application> CreateApplication();
}
