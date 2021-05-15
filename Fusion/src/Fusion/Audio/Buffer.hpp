#pragma once

#include <cinttypes>
#include <vector>

#include "Common.hpp"

namespace Fusion { namespace Audio {

	class Buffer
	{
	public:
		Buffer();
		Buffer(uint32_t id);

		/* The class doesn't store buffer data and we can't query it from OpenAL so it cannot be copied. */
		Buffer(const Buffer& other) = delete;

		Buffer(Buffer&& other);
		~Buffer();

		void SetData(Format format, uint32_t sample_rate, const std::vector<uint8_t>& data);

		operator uint32_t() const
		{
			return m_BufferID;
		}

		uint32_t GetBufferHandle() const { return m_BufferID; }
	private:
		uint32_t m_BufferID;
		bool m_PlaceHolder;
	};
} }
