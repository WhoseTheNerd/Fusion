#pragma once

#include <stdio.h>
#include <cstdint>

#include <vector>
#include <string>
#include <optional>

#include "Common.hpp"

#include "reader.hpp"

namespace Fusion { namespace Audio {
	class Buffer;
} }

namespace RIFF {
	struct chunk
	{
		char ID[4];
		uint32_t length;
	};

	struct riff_chunk
	{
		struct chunk chunk;
		char format[4];
	};

	struct fmt_chunk
	{
		struct chunk chunk;
		uint16_t format_type;
		uint16_t num_channels;
		uint32_t sample_rate;
		uint32_t byte_rate; /* (Sample Rate * BitsPerSample * Channels) / 8. */
		uint16_t block_align; /* (BitsPerSample * Channels) / 8.1 - 8 bit mono2 - 8 bit stereo/16 bit mono4 - 16 bit stereo */
		uint16_t bits_per_sample;
	};

	struct data_chunk
	{
		struct chunk chunk;
		uint8_t* data_ptr;
	};

	struct wave_data
	{
		struct riff_chunk riff;
		struct fmt_chunk fmt;
		struct data_chunk data;
	};

	struct wave_header
	{
		struct riff_chunk riff;
		struct fmt_chunk fmt;
		uint32_t data_size;
	};
}

namespace Fusion {

	class WaveReader : public Reader
	{
	public:
		WaveReader(const char* filepath);
		virtual ~WaveReader() override;

		virtual std::optional<std::vector<uint8_t>> Read(uint32_t length) override;

		virtual Audio::Format GetAudioFormat() const override { return m_Format; }
		const RIFF::wave_header& GetHeader() const { return m_Header; }
		virtual bool IsEOF() const override { return m_FileIndex >= m_FileSize; }
		virtual uint32_t GetSampleRate() const override { return m_Header.fmt.sample_rate; }

		virtual Audio::Duration GetDuration() const override { return m_Duration; }
	private:
		void ReadWaveFile(const char* filepath);
	private:
		FILE* m_File = nullptr;
		uint32_t m_FileSize = 0;
		uint32_t m_FileIndex = 0;
		Audio::Duration m_Duration;
		Audio::Format m_Format;

		RIFF::wave_header m_Header{};
	};

	std::unique_ptr<Fusion::Audio::Buffer> LoadWaveToBuffer(const char* filepath);

}

