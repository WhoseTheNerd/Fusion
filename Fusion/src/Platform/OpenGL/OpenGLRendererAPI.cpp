#include "fpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Fusion { namespace Graphics {

	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         F_CORE_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       F_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          F_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: F_CORE_TRACE(message); return;
		}

		F_CORE_ASSERT(false, "Unknown severity level!");
	}

	Scope<RendererAPI> RendererAPI::Create()
	{
		return CreateScope<OpenGLRendererAPI>();
	}

	void OpenGLRendererAPI::Init()
	{
#ifdef F_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(Ref<VertexArray> vao)
	{
		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	}

	void OpenGLRendererAPI::DrawIndexed(Ref<VertexArray> vao, uint32_t count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
	}

} }
