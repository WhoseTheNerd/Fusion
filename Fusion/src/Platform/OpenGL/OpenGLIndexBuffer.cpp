#include "fpch.h"
#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Fusion { namespace Graphics {

	Ref<IndexBuffer> IndexBuffer::Create(const std::vector<uint32_t>& indices)
	{
		return CreateRef<OpenGLIndexBuffer>(indices);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(const std::vector<uint32_t>& indices)
	{
		glCreateBuffers(1, &m_BufferID);
		glNamedBufferData(m_BufferID, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}
	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	}

} }
