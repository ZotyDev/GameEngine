#pragma once

#include "Sound/Sound.h"

#include "OpenAL/OpenALSoundAPI.h"

namespace UE
{
	class OpenALSound : public Sound
	{
	public:
		OpenALSound();
		virtual ~OpenALSound() override;

		virtual UEResult<> LoadFromFile(const std::string& filename) override;

		virtual const uint8_t& GetChannels() const override { return m_Channels; }
		virtual const uint32_t& GetSampleRate() const override { return m_SampleRate; }
		virtual const uint8_t& GetBitsPerSample() const override { return m_BitsPerSample; }
		virtual const uint32_t& GetSize() const override { return m_Size; }
		virtual const uint32_t& GetNumberOfSamples() const override { return m_NumberOfSamples; }
		virtual const uint32_t& GetDuration() const override { return m_Duration; }

		virtual const uint32_t& GetID() const override { return (uint32_t)m_Buffer; }
	private:
		std::uint8_t m_Channels;
		std::uint32_t m_SampleRate;
		std::uint8_t m_BitsPerSample;
		std::uint32_t m_Size;
		std::uint32_t m_NumberOfSamples;
		std::uint32_t m_Duration;
	private:
		ALuint m_Buffer;
	};
}