#include "fpch.h"
#include "Application.h"

namespace Fusion {

	Application::Application()
	{
		m_Window = Window::Create();
		m_Window->SetEventCallback(F_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}
	
	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(F_BIND_EVENT_FN(Application::OnWindowClose));

		F_CORE_TRACE("{0}", e.ToString());
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
