#pragma once

#include "Fusion/Graphics/RendererAPI.h"

namespace Fusion { namespace Graphics {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor(float r, float g, float b, float a) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(Ref<VertexArray> vao) override;
		virtual void DrawIndexed(Ref<VertexArray> vao, uint32_t count) override;
	};

} }
