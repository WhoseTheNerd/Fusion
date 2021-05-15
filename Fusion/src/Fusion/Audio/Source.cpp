#include "fpch.h"
#include "Source.hpp"

#include <al.h>

namespace Fusion { namespace Audio {

	Source::Source()
	{
		alGenSources(1, &m_SourceID);
	}

	Source::~Source()
	{
		alDeleteSources(1, &m_SourceID);
	}

	void Source::Play()
	{
		alSourcePlay(m_SourceID);
	}

	void Source::Stop()
	{
		alSourceStop(m_SourceID);
	}

	void Source::Pause()
	{
		alSourcePause(m_SourceID);
	}

	void Source::SetPitch(float pitch)
	{
		alSourcef(m_SourceID, AL_PITCH, pitch);
	}

	void Source::SetGain(float gain)
	{
		alSourcef(m_SourceID, AL_GAIN, gain);
	}

	void Source::SetPosition(float x, float y, float z)
	{
		alSource3f(m_SourceID, AL_POSITION, x, y, z);
	}

	void Source::SetVelocity(float x, float y, float z)
	{
		alSource3f(m_SourceID, AL_VELOCITY, x, y, z);
	}

	void Source::SetLooping(bool loop)
	{
		alSourcei(m_SourceID, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
	}

	void Source::QueueBuffer(const Buffer& buffer)
	{
		uint32_t raw_buffer = buffer.GetBufferHandle();
		alSourceQueueBuffers(m_SourceID, 1, &raw_buffer);
	}

	Buffer Source::UnqueueBuffer()
	{
		ALuint buffer;
		alSourceUnqueueBuffers(m_SourceID, 1, &buffer);
		return Buffer(buffer);
	}

	void Source::SetBuffer(std::unique_ptr<Buffer> buffer)
	{
		alSourcei(m_SourceID, AL_BUFFER, static_cast<ALint>(buffer->GetBufferHandle()));
		m_Buffer = std::move(buffer);
	}

	SourceState Source::GetSourceState() const
	{
		ALint source_state;
		alGetSourcei(m_SourceID, AL_SOURCE_STATE, &source_state);

		return ToSourceState(static_cast<uint32_t>(source_state)).value_or(SourceState::Initial);
	}

	uint32_t Source::GetProcessedBuffers() const
	{
		ALint processed_buffers;
		alGetSourcei(m_SourceID, AL_BUFFERS_PROCESSED, &processed_buffers);
		return static_cast<uint32_t>(processed_buffers);
	}

} }

namespace OpenAL {
	void SourceQueueBuffers(unsigned int sid, int numEntries, const unsigned int* bids)
	{
		alSourceQueueBuffers(sid, numEntries, bids);
	}

	void SourceUnqueueBuffers(unsigned int sid, int numEntries, unsigned int* bids)
	{
		alSourceUnqueueBuffers(sid, numEntries, bids);
	}

}
