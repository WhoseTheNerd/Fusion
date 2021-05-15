#include "fpch.h"
#include "Sound.hpp"

#include <chrono>
#include <thread>

namespace Fusion { namespace Audio {

	Sound::Sound(const char* filepath)
	{
		std::unique_ptr<Buffer> buffer = LoadWaveToBuffer(filepath);

		m_Source.SetBuffer(std::move(buffer));

		m_Source.SetPitch(1.0f);
		m_Source.SetGain(1.0f);
		m_Source.SetPosition(0.0f, 0.0f, 0.0f);
		m_Source.SetVelocity(0.0f, 0.0f, 0.0f);
		m_Source.SetLooping(false);
	}

	void Sound::Play()
	{
		m_Source.Play();
	}

	void Sound::SetPitch(float pitch)
	{
		m_Source.SetPitch(pitch);
	}

	void Sound::SetGain(float gain)
	{
		m_Source.SetGain(gain);
	}

	void Sound::SetPosition(float x, float y, float z)
	{
		m_Source.SetPosition(x, y, z);
	}

	void Sound::SetVelocity(float x, float y, float z)
	{
		m_Source.SetVelocity(x, y, z);
	}

	void Sound::SetLooping(bool loop)
	{
		m_Source.SetLooping(loop);
	}

	void Sound::Wait()
	{
		while (m_Source.GetSourceState() == SourceState::Playing) {
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}
} }
