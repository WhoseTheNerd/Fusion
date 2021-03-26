#pragma once

#include "Fusion/Core/Base.h"

namespace Fusion { namespace Graphics {

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		
		virtual uint32_t GetBufferHandle() const = 0;

		static Scope<IndexBuffer> Create(const std::vector<uint32_t>& indices);
	};

} }
