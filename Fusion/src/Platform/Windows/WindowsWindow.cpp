#include "fpch.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>

namespace Fusion {

	static bool s_GLFWInitialized = false;

	Scope<Window> Window::Create(const WindowProps& props)
	{
		return CreateScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
		: m_Data(props)
	{
		if (!s_GLFWInitialized)
		{
			int status = glfwInit();
			F_CORE_ASSERT(status, "Failed to initialize GLFW!");
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(props.Width, props.Height, m_Data.Title.c_str(), NULL, NULL);
		F_CORE_ASSERT(m_Window, "Failed to create Window");

		glfwMakeContextCurrent(m_Window);
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

}
