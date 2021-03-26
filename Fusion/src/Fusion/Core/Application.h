#pragma once

#include "Fusion/Core/Base.h"
#include "Fusion/Core/Window.h"
#include "Fusion/Events/Event.h"
#include "Fusion/Events/ApplicationEvent.h"
#include "Fusion/Core/LayerStack.h"

namespace Fusion {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		Scope<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	};

	// Client defines this!
	Scope<Application> CreateApplication();
}
