#include "fpch.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace Fusion { namespace Graphics {

	Scope<VertexBuffer> VertexBuffer::Create(const std::vector<float>& vertices)
	{
		return CreateScope<OpenGLVertexBuffer>(vertices);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(const std::vector<float>& vertices)
	{
		glCreateBuffers(1, &m_BufferID);
		glNamedBufferData(m_BufferID, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
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

} }
