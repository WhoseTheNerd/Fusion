#pragma once

#include "Fusion/Core/Base.h"

#include "Fusion/Graphics/VertexBufferLayout.h"

namespace Fusion { namespace Graphics {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetBufferHandle() const = 0;

		virtual const VertexBufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const VertexBufferLayout& layout) = 0;

		static Ref<VertexBuffer> Create(const std::vector<float>& vertices);
	};

} }
