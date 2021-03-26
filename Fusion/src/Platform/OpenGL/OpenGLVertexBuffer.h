#pragma once

#include "Fusion/Graphics/VertexBuffer.h"

namespace Fusion { namespace Graphics {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const std::vector<float>& vertices);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual const VertexBufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const VertexBufferLayout& layout) override { m_Layout = layout; }

		virtual uint32_t GetBufferHandle() const override { return m_BufferID; }
	private:
		uint32_t m_BufferID;
		VertexBufferLayout m_Layout;
	};

} }
