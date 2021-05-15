#pragma once

#include "OpenAL.hpp"

#include <mutex>
#include <thread>
#include <memory>
#include <string>

#include "reader.hpp"

namespace Fusion { namespace Audio {

	class Music
	{
	public:
		Music(std::string_view filepath);
		~Music();

		void Play();
		void Stop();
		void Pause();

		void SetPitch(float pitch);
		void SetGain(float gain);
		void SetPosition(float x, float y, float z);
		void SetVelocity(float x, float y, float z);
		void SetLooping(bool loop);

		void Wait();

		Duration GetDuration() const { return m_Reader->GetDuration(); }
	private:
		void MusicPlayerThread();
	private:
		Source m_Source;
		std::array<std::unique_ptr<Buffer>, MAX_SOUND_BUFFERS> m_Buffers;
		std::unique_ptr<Reader> m_Reader;

		std::mutex m_Mutex;
		std::thread m_Thread;
		bool m_Running = true;
	};
} }
