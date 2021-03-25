#pragma once

#include <memory>

#include "Fusion/Core/PlatformDetection.h"

#ifdef F_DEBUG
	#if defined(F_PLATFORM_WINDOWS)
		#define F_DEBUGBREAK() __debugbreak()
	#elif defined(F_PLATFORM_LINUX)
		#include <signal.h>
		#define F_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet"
	#endif
	#define F_ENABLE_ASSERTS
#else
	#define F_DEBUGBREAK()
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Fusion {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "Fusion/Core/Log.h"

#ifdef F_ENABLE_ASSERTS
	#define F_ASSERT(x, ...) { if(!(x)) { F_ERROR("Assertion Failed: {0}", __VA_ARGS__); F_DEBUGBREAK(); } }
	#define F_CORE_ASSERT(x, ...) { if(!(x)) { F_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); F_DEBUGBREAK(); } }
#else
	#define F_ASSERT(x, ...)
	#define F_CORE_ASSERT(x, ...)
#endif
