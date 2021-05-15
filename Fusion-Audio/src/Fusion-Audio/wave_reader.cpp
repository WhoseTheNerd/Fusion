#include "wave_reader.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Buffer.hpp"

namespace Fusion {

	WaveReader::WaveReader(const char* filepath)
	{
		ReadWaveFile(filepath);

		const double total_duration = m_Header.data_size / m_Header.fmt.byte_rate;

		const uint32_t minutes = static_cast<uint32_t>(total_duration / 60);
		m_Duration.Hours = static_cast<uint8_t>(minutes / 60);
		m_Duration.Seconds = static_cast<uint8_t>(total_duration - (minutes * 60));
		m_Duration.Minutes = static_cast<uint8_t>(minutes % 60);

		m_Format = Audio::ToFormat(static_cast<uint8_t>(m_Header.fmt.num_channels), static_cast<uint8_t>(m_Header.fmt.bits_per_sample)).value_or(Audio::Format::Stereo16);
	}

	WaveReader::~WaveReader()
	{
		fclose(m_File);
	}

	void WaveReader::ReadWaveFile(const char* filepath)
	{
		m_File = fopen(filepath, "rb");
		if (!m_File) {
			fprintf(stderr, "Couldn't open '%s' file!\n", filepath);
			return;
		}

		while (!feof(m_File)) {
			RIFF::chunk chunk;
			fread(&chunk, sizeof(RIFF::chunk), 1, m_File);

			if (strncmp(chunk.ID, "RIFF", 4) == 0) {
				RIFF::riff_chunk riff;
				riff.chunk = chunk;
				fread(&riff.format, sizeof(char), 4, m_File);

				m_Header.riff = riff;
			}
			else if (strncmp(chunk.ID, "fmt ", 4) == 0) {
				RIFF::fmt_chunk fmt;
				fmt.chunk = chunk;
				fread(&fmt.format_type, sizeof(char), fmt.chunk.length, m_File);

				m_Header.fmt = fmt;
			}
			else if (strncmp(chunk.ID, "data", 4) == 0) {
				m_Header.data_size = chunk.length;
				m_FileSize = chunk.length;
				break;
			}
			else {
				// Read variable length chunk to avoid problems with finding data chunk
				char* buf = new char[chunk.length];
				fread(buf, sizeof(char), chunk.length, m_File);
				delete[] buf;
			}
		}
	}

	std::optional<std::vector<uint8_t>> WaveReader::Read(const uint32_t length)
	{
		std::vector<uint8_t> data(length);

		size_t read = fread(&data[0], sizeof(uint8_t), length, m_File);
		m_FileIndex += length;

		if (read != length) {
			fprintf(stderr, "Requested to read %d but read %d\n", length, read);
			return {};
		}

		return std::move(data);
	}

	std::unique_ptr<Audio::Buffer> LoadWaveToBuffer(const char* filepath)
	{
		WaveReader reader(filepath);

		const std::vector<uint8_t> data = reader.Read(reader.GetHeader().data_size).value_or(std::vector<uint8_t>{});

		std::unique_ptr<Audio::Buffer> buffer = std::make_unique<Audio::Buffer>();
		buffer->SetData(reader.GetAudioFormat(), reader.GetSampleRate(), data);

		return buffer;
	}

}
