#include "fpch.h"
#include "Application.h"

#include "Fusion/Graphics/RenderCommand.h"

#include <GLFW/glfw3.h>

namespace Fusion {

	Application::Application()
	{
		m_Window = Window::Create();
		m_Window->SetEventCallback(F_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Ref<Layer> layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Ref<Layer> overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::PopLayer(Ref<Layer> layer)
	{
		m_LayerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Ref<Layer> overlay)
	{
		m_LayerStack.PopOverlay(overlay);
	}
	
	void Application::Run()
	{
		while (m_Running)
		{
			const float time = static_cast<float>(glfwGetTime());
			const Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Ref<Layer> layer : m_LayerStack)
				layer->OnUpdate(ts);

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(F_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(F_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		Graphics::RenderCommand::SetViewport(0, 0, e.GetWidth(), e.GetHeight());
		return true;
	}
}
