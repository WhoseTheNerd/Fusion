#include "fpch.h"
#include "Application.h"

namespace Fusion {

	Application::Application()
	{
		m_Window = Window::Create();
	}

	Application::~Application()
	{
	}
	
	void Application::Run()
	{
		while (true)
		{
			m_Window->OnUpdate();
		}
	}
}
