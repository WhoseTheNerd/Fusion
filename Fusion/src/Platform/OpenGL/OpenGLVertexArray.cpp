#include "fpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Fusion { namespace Graphics {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		F_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Ref<VertexArray> VertexArray::Create()
	{
		return CreateRef<OpenGLVertexArray>();
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_ArrayID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_ArrayID);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_ArrayID);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(NULL);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vb)
	{
		F_CORE_ASSERT(vb->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		const auto& layout = vb->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexArrayAttrib(m_ArrayID, m_VertexBufferIndex);
			glVertexArrayVertexBuffer(m_ArrayID, m_VertexBufferIndex,
				vb->GetBufferHandle(),
				element.Offset, layout.GetStride());
			glVertexArrayAttribFormat(m_ArrayID, m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				0);

			glVertexArrayAttribBinding(m_ArrayID, m_VertexBufferIndex, m_VertexBufferIndex);
			m_VertexBufferIndex++;
		}
	}

	void OpenGLVertexArray::AddIndexBuffer(const Ref<IndexBuffer>& ib)
	{
		glVertexArrayElementBuffer(m_ArrayID, ib->GetBufferHandle());
	}

} }
