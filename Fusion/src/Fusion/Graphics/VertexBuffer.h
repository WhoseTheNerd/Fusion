#pragma once

#include "Fusion/Core/Base.h"

namespace Fusion { namespace Graphics {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetBufferHandle() const = 0;

		static Scope<VertexBuffer> Create(const std::vector<float>& vertices);
	};

} }
