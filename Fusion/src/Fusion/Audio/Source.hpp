#pragma once

#include <cinttypes>

#include <array>

#include "Buffer.hpp"

#include "Common.hpp"

#include <type_traits>

namespace OpenAL {
	void SourceQueueBuffers(unsigned int sid, int numEntries, const unsigned int* bids);
	void SourceUnqueueBuffers(unsigned int sid, int numEntries, unsigned int* bids);
}

namespace Fusion { namespace Audio {

	class Source
	{
	public:
		Source();
		~Source();

		void Play();
		void Stop();
		void Pause();

		void SetPitch(float pitch);
		void SetGain(float gain);
		void SetPosition(float x, float y, float z);
		void SetVelocity(float x, float y, float z);
		void SetLooping(bool loop);

		template<uint32_t N>
		void QueueBuffers(const std::array<std::unique_ptr<Buffer>, N>& buffers)
		{
			std::array<uint32_t, N> raw_buffers;
			for (uint32_t i = 0; i < N; i++) {
				raw_buffers[i] = buffers[i]->GetBufferHandle();
			}
			OpenAL::SourceQueueBuffers(m_SourceID, N, &raw_buffers[0]);
		}

		void QueueBuffer(const Buffer& buffer);

		template<uint32_t N>
		void UnqueueBuffers(std::array<std::unique_ptr<Buffer>, N>& buffers)
		{
			std::array<uint32_t, N> raw_buffers;
			OpenAL::SourceUnqueueBuffers(m_SourceID, N, &raw_buffers[0]);
			for (uint32_t i = 0; i < N; i++) {
				buffers[i] = std::make_unique<Buffer>(raw_buffers[i]);
			}
		}

		Buffer UnqueueBuffer();

		void SetBuffer(std::unique_ptr<Buffer> buffer);

		SourceState GetSourceState() const;
		uint32_t GetProcessedBuffers() const;
	private:
		uint32_t m_SourceID;
		std::unique_ptr<Buffer> m_Buffer;
	};

} }
