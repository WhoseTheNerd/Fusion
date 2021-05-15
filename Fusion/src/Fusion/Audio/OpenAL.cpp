#include "fpch.h"
#include "OpenAL.hpp"

#include <al.h>
#include <alc.h>

#include <cstdlib>

namespace Fusion { namespace Audio {

	static void default_callback(const char* message) {}

	error_cb_t error_callback = default_callback;

	static std::vector<std::string_view> split(std::string_view str, char token) {
		std::vector<std::string_view> result;
		while (str.size()) {
			const size_t index = str.find(token);
			if (index != std::string::npos) {
				result.push_back(str.substr(0, index));
				str = str.substr(index + 1);
				if (str.size() == 0) result.push_back(str);
			}
			else {
				result.push_back(str);
				str = "";
			}
		}
		return result;
	}

	System::System()
	{
		ALboolean enumeration = alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT");
		if (!enumeration) {
			error_callback("Enumeration extension is not available!");
			return;
		}

		const ALCchar* default_device = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);

		m_Device = alcOpenDevice(default_device);
		if (!m_Device) {
			error_callback("Cannot open OpenAL Device");
			return;
		}

		m_Context = alcCreateContext(m_Device, nullptr);
		if (!alcMakeContextCurrent(m_Context)) {
			error_callback("Cannot make default OpenAL context");
			return;
		}

		const char* extensions = alcGetString(m_Device, ALC_EXTENSIONS);

		m_Extensions = split(extensions, ' ');
	}

	System::~System()
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(m_Context);
		alcCloseDevice(m_Device);
	}
} }
