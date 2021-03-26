#include "fpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Fusion { namespace Graphics {

	Scope<Context> Context::Create(void* window)
	{
		return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
	}

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_WindowHandle(window)
	{
		F_CORE_ASSERT(window, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		const int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		F_CORE_ASSERT(status, "Failed to initialize Glad!");

		F_CORE_INFO("OpenGL Info:");
		F_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		F_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		F_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		F_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
} }
