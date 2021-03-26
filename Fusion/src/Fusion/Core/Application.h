#pragma once

#include "Fusion/Core/Base.h"
#include "Fusion/Core/Window.h"
#include "Fusion/Events/Event.h"
#include "Fusion/Events/ApplicationEvent.h"

namespace Fusion {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		Scope<Window> m_Window;
		bool m_Running = true;
	};

	// Client defines this!
	Scope<Application> CreateApplication();
}
