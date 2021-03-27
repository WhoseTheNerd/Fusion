#pragma once

#include "Fusion/Graphics/IndexBuffer.h"

namespace Fusion { namespace Graphics {

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const std::vector<uint32_t>& indices);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetBufferHandle() const override { return m_BufferID; }
		virtual uint32_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_BufferID;
		uint32_t m_Count;
	};

} }
