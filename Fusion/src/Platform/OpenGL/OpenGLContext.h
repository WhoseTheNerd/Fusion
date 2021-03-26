#pragma once

#include "Fusion/Graphics/Context.h"

struct GLFWwindow;

namespace Fusion { namespace Graphics {

	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

} }
