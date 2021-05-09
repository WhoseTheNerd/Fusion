#pragma once

#include "Fusion/Core/Base.h"
#include "Fusion/Core/Window.h"
#include "Fusion/Events/Event.h"
#include "Fusion/Events/ApplicationEvent.h"
#include "Fusion/Core/LayerStack.h"

namespace Fusion {

	class F_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Ref<Layer> layer);
		void PushOverlay(Ref<Layer> overlay);
		void PopLayer(Ref<Layer> layer);
		void PopOverlay(Ref<Layer> overlay);

		void OnEvent(Event& e);

		static Application* Get() { return s_Instance; }
		Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	// Client defines this!
	Scope<Application> CreateApplication();
}
