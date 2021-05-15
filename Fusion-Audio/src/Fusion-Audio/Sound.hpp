#pragma once

#include "Source.hpp"
#include "wave_reader.hpp"

namespace Fusion { namespace Audio {

	class F_API Sound
	{
	public:
		Sound(const char* filepath);

		void Play();

		void SetPitch(float pitch);
		void SetGain(float gain);
		void SetPosition(float x, float y, float z);
		void SetVelocity(float x, float y, float z);
		void SetLooping(bool loop);

		void Wait();
	private:
		Source m_Source;
	};
} }
