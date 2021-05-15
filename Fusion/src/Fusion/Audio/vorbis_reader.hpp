#pragma once

#include <fstream>
#include <cinttypes>
#include <optional>
#include <string>

#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

#include "Common.hpp"

#include "reader.hpp"

namespace Fusion {

	class VorbisReader : public Reader
	{
	public:
		VorbisReader(const char* filepath);

		virtual std::optional<std::vector<uint8_t>> Read(uint32_t length) override;

		virtual Audio::Duration GetDuration() const override { return m_Data.Duration; }
		virtual bool IsEOF() const override { return m_Data.IsEOF; }

		virtual uint32_t GetSampleRate() const override { return m_Data.SampleRate; }

		virtual Audio::Format GetAudioFormat() const override { return m_Data.Format; }
	private:
		static std::size_t read_ogg_callback(void* destination, std::size_t size1, std::size_t size2, void* fileHandle);
		static std::int32_t seek_ogg_callback(void* fileHandle, ogg_int64_t to, std::int32_t type);
		static long int tell_ogg_callback(void* fileHandle);
	private:
		struct Data
		{
			const char* FileName;
			std::ifstream File;
			uint32_t SizeConsumed;
			uint32_t Size;
			OggVorbis_File VorbisFile;
			int CurrentSection = 0;
			Audio::Format Format;
			uint32_t SampleRate;
			Audio::Duration Duration;
			bool IsEOF = false;
		};

		Data m_Data;
	};
}

