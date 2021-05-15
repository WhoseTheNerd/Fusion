#pragma once

#include "Common.hpp"
#include "Listener.hpp"
#include "Source.hpp"
#include "Buffer.hpp"

#include <vector>
#include <string>

struct ALCdevice;
struct ALCcontext;

namespace Fusion { namespace Audio {

	typedef void(*error_cb_t)(const char* message);

	extern error_cb_t error_callback;

	// RAII
	class System
	{
	public:
		System();
		~System();

		const std::vector<std::string_view>& GetExtensions() const { return m_Extensions; }
	private:
		ALCdevice* m_Device;
		ALCcontext* m_Context;
		std::vector<std::string_view> m_Extensions;
	};
} }
