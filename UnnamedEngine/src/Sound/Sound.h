#pragma once

#include "Sound/SoundAPI.h"

namespace UE
{
	class Sound
	{
	public:
		virtual ~Sound() = default;

		virtual UEResult LoadFromFile(const std::string& filename) = 0;

		virtual const uint8_t& GetChannels() const = 0;
		virtual const uint32_t& GetSampleRate() const = 0;
		virtual const uint8_t& GetBitsPerSample() const = 0;
		virtual const uint32_t& GetSize() const = 0;
		virtual const uint32_t& GetNumberOfSamples() const = 0;
		virtual const uint32_t& GetDuration() const = 0;

		virtual const uint32_t& GetID() const = 0;

		static Ref<Sound> Create();
	};
}