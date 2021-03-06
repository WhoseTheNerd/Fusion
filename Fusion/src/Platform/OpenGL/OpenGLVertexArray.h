#pragma once

#include "Fusion/Graphics/VertexArray.h"

namespace Fusion { namespace Graphics {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vb) override;
		virtual void AddIndexBuffer(const Ref<IndexBuffer>& ib) override;

		virtual Ref<IndexBuffer> GetIndexBuffer() override { return m_IndexBuffer; }
	private:
		uint32_t m_ArrayID;
		uint32_t m_VertexBufferIndex = 0;
		Ref<IndexBuffer> m_IndexBuffer;
	};

} }
