#include "fpch.h"
#include "Common.hpp"

#include <al.h>

#include <exception>

namespace Fusion { namespace Audio {

	std::optional<SourceState> ToSourceState(uint32_t source_state)
	{
		switch (source_state)
		{
		case AL_INITIAL: return SourceState::Initial;
		case AL_PLAYING: return SourceState::Playing;
		case AL_PAUSED: return SourceState::Paused;
		case AL_STOPPED: return SourceState::Stopped;
		default: return {};
		}
	}

	uint32_t FromSourceState(SourceState source_state)
	{
		switch (source_state)
		{
		case SourceState::Initial: return AL_INITIAL;
		case SourceState::Playing: return AL_PLAYING;
		case SourceState::Paused: return AL_PAUSED;
		case SourceState::Stopped: return AL_STOPPED;
		}

		throw std::exception("Unknown SourceState enumeration value!");
	}

	std::optional<Format> ToFormat(uint32_t format)
	{
		switch (format)
		{
		case AL_FORMAT_MONO8: return Format::Mono8;
		case AL_FORMAT_MONO16: return Format::Mono16;
		case AL_FORMAT_STEREO8: return Format::Stereo8;
		case AL_FORMAT_STEREO16: return Format::Stereo16;
		default: return {};
		}
	}

	std::optional<Format> ToFormat(uint8_t channels, uint8_t bits_per_sample)
	{
		bool stereo = channels > 1;
		switch (bits_per_sample)
		{
		case 8: return stereo ? Format::Stereo8 : Format::Mono8;
		case 16: return stereo ? Format::Stereo16 : Format::Mono16;
		default: return {};
		}
	}

	uint32_t FromFormat(Format format)
	{
		switch (format)
		{
		case Format::Stereo8: return AL_FORMAT_STEREO8;
		case Format::Stereo16: return AL_FORMAT_STEREO16;
		case Format::Mono8: return AL_FORMAT_MONO8;
		case Format::Mono16: return AL_FORMAT_MONO16;
		}

		throw std::exception("Unknown Format enumeration value!");
	}
} }
