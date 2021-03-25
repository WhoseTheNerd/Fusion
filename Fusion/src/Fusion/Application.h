#pragma once

#include "Fusion/Base.h"

namespace Fusion {

	class F_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Client defines this!
	Application* CreateApplication();
}