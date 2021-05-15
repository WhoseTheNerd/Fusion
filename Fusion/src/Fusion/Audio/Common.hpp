#pragma once

#include <cinttypes>
#include <vector>
#include <optional>
#include <memory>

#define MAX_SOUND_BUFFERS 8
#define SOUND_BUFFER_SIZE 4096

namespace Fusion { namespace Audio {

	enum class SourceState
	{
		Initial,
		Playing,
		Paused,
		Stopped
	};

	std::optional<SourceState> ToSourceState(uint32_t source_state);
	uint32_t FromSourceState(SourceState source_state);

	enum class Format
	{
		Stereo8,
		Stereo16,
		Mono8,
		Mono16
	};

	std::optional<Format> ToFormat(uint32_t format);
	std::optional<Format> ToFormat(uint8_t channels, uint8_t bits_per_sample);
	uint32_t FromFormat(Format format);

	struct Duration
	{
		uint8_t Hours;
		uint8_t Minutes;
		uint8_t Seconds;
	};
} }
