#include "vorbis_reader.hpp"

#include <iostream>

namespace Fusion {

	VorbisReader::VorbisReader(const char* filepath)
	{
		m_Data.FileName = filepath;

		m_Data.File.open(filepath, std::ios::binary);
		if (!m_Data.File.is_open()) {
			fprintf(stderr, "Couldn't open '%s' file\n", filepath);
			return;
		}

		m_Data.File.seekg(0, std::ios_base::beg);
		m_Data.File.ignore(std::numeric_limits<std::streamsize>::max());
		m_Data.Size = static_cast<uint32_t>(m_Data.File.gcount());
		m_Data.File.clear();
		m_Data.File.seekg(0, std::ios_base::beg);
		m_Data.SizeConsumed = 0;

		ov_callbacks oggCallbacks;
		oggCallbacks.read_func = read_ogg_callback;
		oggCallbacks.close_func = nullptr;
		oggCallbacks.seek_func = seek_ogg_callback;
		oggCallbacks.tell_func = tell_ogg_callback;

		if (ov_open_callbacks(reinterpret_cast<void*>(&m_Data), &m_Data.VorbisFile, nullptr, -1, oggCallbacks) < 0)
		{
			fputs("Call to ov_open_callbacks failed", stderr);
			return;
		}

		vorbis_info* vorbisInfo = ov_info(&m_Data.VorbisFile, -1);
		if (!vorbisInfo) {
			fputs("vorbisInfo was null", stderr);
			return;
		}

		m_Data.Format = Audio::ToFormat(static_cast<uint8_t>(vorbisInfo->channels), 16).value_or(Audio::Format::Stereo16);
		m_Data.SampleRate = static_cast<uint32_t>(vorbisInfo->rate);

		const double total_duration = ov_time_total(&m_Data.VorbisFile, -1);

		const uint32_t minutes = static_cast<uint32_t>(total_duration) / 60;
		m_Data.Duration.Hours = static_cast<uint8_t>(minutes / 60);
		m_Data.Duration.Seconds = static_cast<uint8_t>(total_duration - (minutes * 60));
		m_Data.Duration.Minutes = static_cast<uint8_t>(minutes % 60);
	}

	std::optional<std::vector<uint8_t>> VorbisReader::Read(uint32_t length)
	{
		std::vector<uint8_t> data(length);

		uint32_t sizeRead = 0;

		while (sizeRead < length)
		{
			const int32_t result = ov_read(&m_Data.VorbisFile, reinterpret_cast<char*>(&data[sizeRead]), static_cast<int>(SOUND_BUFFER_SIZE - sizeRead), 0, 2, 1, &m_Data.CurrentSection);
			if (result == OV_HOLE)
			{
				fputs("ERROR: OV_HOLE found in update of buffer", stderr);
				return {};
			}
			else if (result == OV_EBADLINK)
			{
				fputs("ERROR: OV_EBADLINK found in update of buffer ", stderr);
				return {};
			}
			else if (result == OV_EINVAL)
			{
				fputs("ERROR: OV_EINVAL found in update of buffer ", stderr);
				return {};
			}
			else if (result == 0)
			{
				const int seekResult = ov_raw_seek(&m_Data.VorbisFile, 0);
				if (seekResult == OV_ENOSEEK)
					fputs("ERROR: OV_ENOSEEK found when trying to loop", stderr);
				else if (seekResult == OV_EINVAL)
					fputs("ERROR: OV_EINVAL found when trying to loop", stderr);
				else if (seekResult == OV_EREAD)
					fputs("ERROR: OV_EREAD found when trying to loop", stderr);
				else if (seekResult == OV_EFAULT)
					fputs("ERROR: OV_EFAULT found when trying to loop", stderr);
				else if (seekResult == OV_EOF) {
					fputs("ERROR: OV_EOF found when trying to loop", stderr);
					m_Data.IsEOF = true;
				}
				else if (seekResult == OV_EBADLINK)
					fputs("ERROR: OV_EBADLINK found when trying to loop", stderr);

				return {};
			}
			sizeRead += static_cast<uint32_t>(result);
		}

		return std::move(data);
	}

	std::size_t VorbisReader::read_ogg_callback(void* destination, std::size_t size1, std::size_t size2, void* fileHandle)
	{
		Data* audioData = reinterpret_cast<Data*>(fileHandle);

		std::size_t length = size1 * size2;

		if (audioData->SizeConsumed >= audioData->Size) {
			audioData->IsEOF = true;
			return 0;
		}

		if (audioData->SizeConsumed + length > audioData->Size)
			length = audioData->Size - audioData->SizeConsumed;

		if (!audioData->File.is_open())
		{
			audioData->File.open(audioData->FileName, std::ios::binary);
			if (!audioData->File.is_open())
			{
				fprintf(stderr, "Couldn't reopen '%s' file while streaming\n", audioData->FileName);
				return 0;
			}
		}

		std::vector<char> moreData(length);

		audioData->File.clear();
		audioData->File.seekg(audioData->SizeConsumed);
		if (!audioData->File.read(&moreData[0], length))
		{
			if (audioData->File.eof())
			{
				audioData->File.clear(); // just clear the error, we will resolve it later
				audioData->IsEOF = true;
			}
			else if (audioData->File.fail())
			{
				fprintf(stderr, "ERROR: Read failed, because fail bit was set. Filename = '%s'\n", audioData->FileName);
				audioData->File.clear();
				return 0;
			}
			else if (audioData->File.bad())
			{
				fprintf(stderr, "File '%s' has bad bit set\n", audioData->FileName);
				audioData->File.clear();
				return 0;
			}
		}
		audioData->SizeConsumed += length;

		std::memcpy(destination, &moreData[0], length);

		audioData->File.clear();

		return length;
	}

	std::int32_t VorbisReader::seek_ogg_callback(void* fileHandle, ogg_int64_t to, std::int32_t type)
	{
		Data* audioData = reinterpret_cast<Data*>(fileHandle);

		if (type == SEEK_CUR)
		{
			audioData->SizeConsumed += to;
		}
		else if (type == SEEK_END)
		{
			audioData->SizeConsumed = static_cast<uint32_t>(audioData->Size - to);
		}
		else if (type == SEEK_SET)
		{
			audioData->SizeConsumed = static_cast<uint32_t>(to);
		}
		else
			return -1; // what are you trying to do vorbis?

		if (audioData->SizeConsumed > audioData->Size)
		{
			audioData->SizeConsumed = audioData->Size;
			return -1;
		}

		return 0;
	}

	long int VorbisReader::tell_ogg_callback(void* fileHandle)
	{
		Data* audioData = reinterpret_cast<Data*>(fileHandle);
		return static_cast<long int>(audioData->SizeConsumed);
	}

}
