#pragma once

#include <cinttypes>
#include <vector>
#include <optional>

#include "Common.hpp"

namespace Fusion {

	class F_API Reader
	{
	public:
		virtual ~Reader() = default;

		virtual std::optional<std::vector<uint8_t>> Read(uint32_t length) = 0;

		virtual Audio::Duration GetDuration() const = 0;
		virtual uint32_t GetSampleRate() const = 0;

		virtual bool IsEOF() const = 0;

		virtual Audio::Format GetAudioFormat() const = 0;
	};

}
