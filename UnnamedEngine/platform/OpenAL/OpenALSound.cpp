#include "uepch.h"
#include "OpenAL/OpenALSound.h"

#include "Files/Loader/WAV.h"

namespace UE
{
	OpenALSound::OpenALSound() : 
		m_Channels(0),
		m_SampleRate(0),
		m_BitsPerSample(0),
		m_Size(0),
		m_NumberOfSamples(0),
		m_Duration(0),
		m_Buffer(0)
	{}

	OpenALSound::~OpenALSound()
	{
		alDeleteBuffers(1, &m_Buffer);
	}

	UEResult<> OpenALSound::LoadFromFile(const std::string& filename)
	{
		std::string FileType = filename.substr(filename.find_first_of(".") + 1);

		std::vector<char> FileBuffer;

		if (FileType == "wav" || FileType == "WAV")
		{
			if (!LoadWav(FileBuffer, filename, m_Channels, m_SampleRate, m_BitsPerSample, m_Size))
			{
				UE_CORE_ERROR("Failed to load sound data from: {0}", filename);
				return UEResult<>::Error;
			}
		}
		else
		{
			UE_CORE_ERROR("Filename not supported");
			return UEResult<>::Error;
		}

		alGenBuffers(1, &m_Buffer);

		ALenum Format;
		if (m_Channels == 1 && m_BitsPerSample == 8)
		{
			Format = AL_FORMAT_MONO8;
		}
		else if (m_Channels == 1 && m_BitsPerSample == 16)
		{
			Format = AL_FORMAT_MONO16;
		}
		else if (m_Channels == 2 && m_BitsPerSample == 8)
		{
			Format = AL_FORMAT_STEREO8;
		}
		else if (m_Channels == 2 && m_BitsPerSample == 16)
		{
			Format = AL_FORMAT_STEREO16;
		}
		else
		{
			UE_CORE_ERROR("Unknwon WAVE format:\n Channels: {0}\n Bps: {1}", m_Channels, m_BitsPerSample);
			return UEResult<>::Error;
		}

		alBufferData(m_Buffer, Format, FileBuffer.data(), m_Size, m_SampleRate);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to buffer data into sound");
			return UEResult<>::Error;
		}
		FileBuffer.clear();

		m_NumberOfSamples = m_Size / (m_Channels * (m_BitsPerSample) / 8);
		m_Duration = m_NumberOfSamples / m_SampleRate;

		return UEResult<>::Success;
	}
}