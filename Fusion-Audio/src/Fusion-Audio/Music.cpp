#include "Music.hpp"

#include "wave_reader.hpp"
#include "vorbis_reader.hpp"

#include <chrono>
#include <thread>

namespace Fusion {namespace Audio {

	Music::Music(std::string_view filepath)
	{
		m_Source.SetPitch(1.0f);
		m_Source.SetGain(1.0f);
		m_Source.SetPosition(0.0f, 0.0f, 0.0f);
		m_Source.SetVelocity(0.0f, 0.0f, 0.0f);
		m_Source.SetLooping(false);

		if (filepath.substr(filepath.find_last_of('.') + 1) == "wav") {
			m_Reader = std::make_unique<WaveReader>(filepath.data());
		}
		else if (filepath.substr(filepath.find_last_of('.') + 1) == "ogg") {
			m_Reader = std::make_unique<VorbisReader>(filepath.data());
		}
		else {
			error_callback("Unknown file format!\n");
			return;
		}

		for (uint32_t i = 0; i < MAX_SOUND_BUFFERS; i++) {
			const std::vector<uint8_t> data = m_Reader->Read(SOUND_BUFFER_SIZE).value_or(std::vector<uint8_t>{});
			m_Buffers[i] = std::make_unique<Buffer>();
			m_Buffers[i]->SetData(m_Reader->GetAudioFormat(), m_Reader->GetSampleRate(), data);
		}

		m_Source.QueueBuffers(m_Buffers);

		m_Thread = std::thread([this]() {
			this->MusicPlayerThread();
			});
	}

	Music::~Music()
	{
		m_Running = false;
		m_Thread.join();
	}

	void Music::Play()
	{
		std::lock_guard lock(m_Mutex);

		m_Source.Play();
	}

	void Music::Stop()
	{
		std::lock_guard lock(m_Mutex);

		m_Source.Stop();
	}

	void Music::Pause()
	{
		std::lock_guard lock(m_Mutex);

		m_Source.Pause();
	}

	void Music::SetPitch(float pitch)
	{
		std::lock_guard lock(m_Mutex);

		m_Source.SetPitch(pitch);
	}

	void Music::SetGain(float gain)
	{
		std::lock_guard lock(m_Mutex);

		m_Source.SetGain(gain);
	}

	void Music::SetPosition(float x, float y, float z)
	{
		std::lock_guard lock(m_Mutex);

		m_Source.SetPosition(x, y, z);
	}

	void Music::SetVelocity(float x, float y, float z)
	{
		std::lock_guard lock(m_Mutex);

		m_Source.SetVelocity(x, y, z);
	}

	void Music::SetLooping(bool loop)
	{
		std::lock_guard lock(m_Mutex);

		m_Source.SetLooping(loop);
	}

	void Music::Wait()
	{
		SourceState state;
		do
		{
			std::this_thread::sleep_for(std::chrono::microseconds(1));
			std::lock_guard lock(m_Mutex);
			state = m_Source.GetSourceState();
		} 		while (state == SourceState::Playing);
	}

	void Music::MusicPlayerThread()
	{
		while (m_Running) {

			{
				std::lock_guard lock(m_Mutex);

				if (m_Source.GetSourceState() == SourceState::Playing) {

					uint32_t processed_buffers = m_Source.GetProcessedBuffers();
					while (processed_buffers-- && !m_Reader->IsEOF()) {
						Buffer buffer = m_Source.UnqueueBuffer();

						auto data = m_Reader->Read(SOUND_BUFFER_SIZE);
						if (data)
							buffer.SetData(m_Reader->GetAudioFormat(), m_Reader->GetSampleRate(), data.value());
						else
							printf("Read returned empty result\n");

						m_Source.QueueBuffer(buffer);
					}
				}
			}
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}

	}
} }
