#pragma once

#include <memory>

#include "Fusion/Base.h"
#include "spdlog/spdlog.h"

namespace Fusion {

	class F_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define F_CORE_TRACE(...)       ::Fusion::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define F_CORE_INFO(...)        ::Fusion::Log::GetCoreLogger()->info(__VA_ARGS__)
#define F_CORE_WARN(...)        ::Fusion::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define F_CORE_ERROR(...)       ::Fusion::Log::GetCoreLogger()->error(__VA_ARGS__)
#define F_CORE_CRITICAL(...)    ::Fusion::Log::GetCoreLogger()->critical(__VA_ARGS__)
                                
// Client log macros            
#define F_TRACE(...)	        ::Fusion::Log::GetClientLogger()->trace(__VA_ARGS__)
#define F_INFO(...)	            ::Fusion::Log::GetClientLogger()->info(__VA_ARGS__)
#define F_WARN(...)	            ::Fusion::Log::GetClientLogger()->warn(__VA_ARGS__)
#define F_ERROR(...)	        ::Fusion::Log::GetClientLogger()->error(__VA_ARGS__)
#define F_CRITICAL(...)	        ::Fusion::Log::GetClientLogger()->critical(__VA_ARGS__)