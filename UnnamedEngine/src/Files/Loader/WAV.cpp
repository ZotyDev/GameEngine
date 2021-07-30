#include "uepch.h"
#include "Files/Loader/WAV.h"

#include "Files/Loader/LoaderHelper.h"

namespace UE
{
	UEResult LoadWavFileHeader(
		std::ifstream& file,
		std::uint8_t& channels,
		std::uint32_t& sampleRate,
		std::uint8_t& bitsPerSample,
		std::uint32_t& size)
	{
		char Buffer[4];
		if (!file.is_open())
		{
			UE_CORE_ERROR("File is not currently open");
			return UEResult::Error;
		}

		// RIFF
		if (!file.read(Buffer, 4))
		{
			UE_CORE_ERROR("Could not read RIFF");
			return UEResult::Error;
		}
		if (std::strncmp(Buffer, "RIFF", 4) != 0)
		{
			UE_CORE_ERROR("File is not a valid WAVE file: header doesn't begin with RIFF");
			return UEResult::Error;
		}

		// The size of the entire file
		if (!file.read(Buffer, 4))
		{
			UE_CORE_ERROR("Could not read size of the file");
			return UEResult::Error;
		}

		// WAVE
		if (!file.read(Buffer, 4))
		{
			UE_CORE_ERROR("Could not read WAVE");
			return UEResult::Error;
		}
		if (std::strncmp(Buffer, "WAVE", 4) != 0)
		{
			UE_CORE_ERROR("File is not a valid WAVE file: header doesn't contain WAVE");
			return UEResult::Error;
		}

		// "fmt/0"
		if (!file.read(Buffer, 4))
		{
			UE_CORE_ERROR("Could not read \"fmt/0\"");
			return UEResult::Error;
		}

		// This is always 16, the size of the fmt data chunk
		if (!file.read(Buffer, 4))
		{
			UE_CORE_ERROR("Could not read the 16");
			return UEResult::Error;
		}

		// PCM should be 1?
		if (!file.read(Buffer, 2))
		{
			UE_CORE_ERROR("Could not read PCM");
			return UEResult::Error;
		}

		// The number of channels
		if (!file.read(Buffer, 2))
		{
			UE_CORE_ERROR("Could not read number of channels");
			return UEResult::Error;
		}
		channels = LoaderReadAndConvert(Buffer, 4);

		// Sample rate
		if (!file.read(Buffer, 4))
		{
			UE_CORE_ERROR("Could not read sample rate");
			return UEResult::Error;
		}
		sampleRate = LoaderReadAndConvert(Buffer, 4);

		// (SampleRate * BitsPerSample * Channels) / 8
		if (!file.read(Buffer, 4))
		{
			UE_CORE_ERROR("Could not read (SampleRate * BitsPerSample * Channels) / 8");
			return UEResult::Error;
		}

		// ?? wtf is this
		if (!file.read(Buffer, 2))
		{
			UE_CORE_ERROR("Could not read ?? wtf is this");
			return UEResult::Error;
		}

		// BitsPerSample
		if (!file.read(Buffer, 2))
		{
			UE_CORE_ERROR("Could not read bits per sample");
			return UEResult::Error;
		}
		bitsPerSample = LoaderReadAndConvert(Buffer, 2);

		// Data chunk header "data"
		if (!file.read(Buffer, 4))
		{
			UE_CORE_ERROR("Could not read data chunk header");
			return UEResult::Error;
		}
		if (std::strncmp(Buffer, "data", 4) != 0)
		{
			UE_CORE_ERROR("File is not a valid WAVE file: doesn't have \"data\" tag");
			return UEResult::Error;
		}

		// Size of data
		if (!file.read(Buffer, 4))
		{
			UE_CORE_ERROR("Could not read data size");
			return UEResult::Error;
		}
		size = LoaderReadAndConvert(Buffer, 4);

		// Cannot be at the end of the file
		if (file.eof())
		{
			UE_CORE_ERROR("Reached EOF of the file");
			return UEResult::Error;
		}
		if (file.fail())
		{
			UE_CORE_ERROR("Fail state set on the file");
			return UEResult::Error;
		}

		return UEResult::Success;
	}

	UEResult LoadWav(
		std::vector<char>& target,
		const std::string& filename,
		std::uint8_t& channels,
		std::uint32_t& sampleRate,
		std::uint8_t& bitsPerSample,
		std::uint32_t& size)
	{
		std::ifstream Input(filename, std::ios::binary);
		if (!Input.is_open())
		{
			UE_CORE_ERROR("Could not open {0}", filename);
			return UEResult::Error;
		}

		if (LoadWavFileHeader(Input, channels, sampleRate, bitsPerSample, size) == UEResult::Error)
		{
			UE_CORE_ERROR("Could not load WAV header of: {0}", filename);
			return UEResult::Error;
		}

		target.resize(size);
		Input.read(&target[0], size);

		return UEResult::Success;
	}
}