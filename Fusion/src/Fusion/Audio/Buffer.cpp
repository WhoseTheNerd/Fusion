#include "fpch.h"
#include "Buffer.hpp"

#include <iostream>

#include <al.h>

#include "OpenAL.hpp"

namespace Fusion { namespace Audio {

	Buffer::Buffer()
		: m_PlaceHolder(false)
	{
		alGenBuffers(1, &m_BufferID);
	}

	Buffer::Buffer(uint32_t id)
		: m_BufferID(id), m_PlaceHolder(true)
	{
	}

	Buffer::Buffer(Buffer&& other)
		: m_BufferID(other.m_BufferID), m_PlaceHolder(other.m_PlaceHolder)
	{
		other.m_PlaceHolder = true;
	}

	Buffer::~Buffer()
	{
		if (m_PlaceHolder) return;

		alDeleteBuffers(1, &m_BufferID);
	}

	void Buffer::SetData(Format format, uint32_t sample_rate, const std::vector<uint8_t>& data)
	{
		if (data.size() == 0) {
			error_callback("Size must be greater than zero");
		}

		alBufferData(m_BufferID, static_cast<ALenum>(FromFormat(format)), &data[0], static_cast<ALsizei>(data.size()), static_cast<ALsizei>(sample_rate));
	}
} }
