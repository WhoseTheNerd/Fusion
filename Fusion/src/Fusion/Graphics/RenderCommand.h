#pragma once

#include "Fusion/Core/Base.h"

#include "Fusion/Graphics/RendererAPI.h"

#include <glm/glm.hpp>

namespace Fusion { namespace Graphics {

	class F_API RenderCommand
	{
	public:
		static void Init()
		{
			s_RendererAPI->Init();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(float r, float g, float b, float a)
		{
			s_RendererAPI->SetClearColor(r, g, b, a);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		static void Clear()
		{
			s_RendererAPI->Clear();
		}

		static void DrawIndexed(Ref<VertexArray> vao)
		{
			s_RendererAPI->DrawIndexed(vao);
		}

		static void DrawIndexed(Ref<VertexArray> vao, uint32_t count)
		{
			s_RendererAPI->DrawIndexed(vao, count);
		}
	private:
		static inline Scope<RendererAPI> s_RendererAPI{ RendererAPI::Create() };
	};

} }
