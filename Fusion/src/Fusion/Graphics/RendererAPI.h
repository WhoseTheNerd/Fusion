#pragma once

#include "Fusion/Core/Base.h"

#include "Fusion/Graphics/VertexArray.h"

#include <glm/glm.hpp>

namespace Fusion { namespace Graphics {

	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vao) = 0;
		
		static Scope<RendererAPI> Create();
	};

} }
