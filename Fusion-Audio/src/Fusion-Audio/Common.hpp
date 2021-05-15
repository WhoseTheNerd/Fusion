#pragma once

#include <cinttypes>
#include <vector>
#include <optional>
#include <memory>

#include "PlatformDetection.h"

#define MAX_SOUND_BUFFERS 8
#define SOUND_BUFFER_SIZE 4096

#ifdef F_DEBUG
#if defined(F_PLATFORM_WINDOWS)
#define F_DEBUGBREAK() __debugbreak()
#if defined(F_BUILD_DLL)
#define F_API __declspec(dllexport)
#elif defined(F_DLL)
#define F_API __declspec(dllimport)
#else
#define F_API
#endif
#elif defined(F_PLATFORM_LINUX)
#include <signal.h>
#define F_DEBUGBREAK() raise(SIGTRAP)
#if defined(F_BUILD_DLL)
#define F_API __attribute__((visibility("default")))
#elif defined(F_DLL)
#define F_API
#else
#define F_API
#endif
#else
#error "Platform doesn't support debugbreak yet"
#endif
#define F_ENABLE_ASSERTS
#else
#define F_DEBUGBREAK()
#endif

namespace Fusion { namespace Audio {

	enum class F_API SourceState
	{
		Initial,
		Playing,
		Paused,
		Stopped
	};

	F_API std::optional<SourceState> ToSourceState(uint32_t source_state);
	F_API uint32_t FromSourceState(SourceState source_state);

	enum class F_API Format
	{
		Stereo8,
		Stereo16,
		Mono8,
		Mono16
	};

	F_API std::optional<Format> ToFormat(uint32_t format);
	F_API std::optional<Format> ToFormat(uint8_t channels, uint8_t bits_per_sample);
	F_API uint32_t FromFormat(Format format);

	struct F_API Duration
	{
		uint8_t Hours;
		uint8_t Minutes;
		uint8_t Seconds;
	};
} }
