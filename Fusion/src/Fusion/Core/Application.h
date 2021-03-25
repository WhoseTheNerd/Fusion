#pragma once

#include "Fusion/Core/Base.h"
#include "Fusion/Core/Window.h"

namespace Fusion {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		Scope<Window> m_Window;
	};

	// Client defines this!
	Scope<Application> CreateApplication();
}
