#include "fpch.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace Fusion { namespace Graphics {

	Ref<VertexBuffer> VertexBuffer::Create(const std::vector<float>& vertices)
	{
		return CreateRef<OpenGLVertexBuffer>(vertices);
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		return CreateRef<OpenGLVertexBuffer>(size);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(const std::vector<float>& vertices)
		: m_Layout({})
	{
		glCreateBuffers(1, &m_BufferID);
		glNamedBufferData(m_BufferID, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
		: m_Layout({})
	{
		glCreateBuffers(1, &m_BufferID);
		glNamedBufferData(m_BufferID, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glNamedBufferSubData(m_BufferID, 0, size, data);
	}

} }
