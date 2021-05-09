#pragma once

#include "Fusion/Core/Base.h"

#include "Fusion/Graphics/VertexBuffer.h"
#include "Fusion/Graphics/IndexBuffer.h"

namespace Fusion { namespace Graphics {

	class F_API VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vb) = 0;
		virtual void AddIndexBuffer(const Ref<IndexBuffer>& ib) = 0;

		virtual Ref<IndexBuffer> GetIndexBuffer() = 0;

		static Ref<VertexArray> Create();
	};

} }
