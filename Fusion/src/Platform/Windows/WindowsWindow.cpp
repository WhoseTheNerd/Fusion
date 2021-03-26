#include "fpch.h"
#include "WindowsWindow.h"

#include "Fusion/Events/KeyEvent.h"
#include "Fusion/Events/MouseEvent.h"
#include "Fusion/Events/ApplicationEvent.h"

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
			const int status = glfwInit();
			F_CORE_ASSERT(status, "Failed to initialize GLFW!");
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(props.Width, props.Height, m_Data.Title.c_str(), NULL, NULL);
		F_CORE_ASSERT(m_Window, "Failed to create Window");

		m_Context = Graphics::Context::Create(static_cast<void*>(m_Window));
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
			case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

}
