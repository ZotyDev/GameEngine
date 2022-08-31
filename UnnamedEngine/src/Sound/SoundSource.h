#pragma once

#include "Sound/SoundAPI.h"
#include "Sound/Sound.h"

#include <glm/glm.hpp>

namespace UE
{
	class SoundSource
	{
	public:
		virtual ~SoundSource() = default;

		virtual UEResult<> Init() = 0;

		virtual UEResult<> SetSource(Ref<Sound> source) = 0;

		virtual UEResult<> Play() = 0;
		virtual UEResult<> Stop() = 0;
		virtual UEResult<> Pause() = 0;
		virtual UEResult<> Resume() = 0;

		virtual UEResult<> SetPitch(float pitch) = 0;
		virtual UEResult<> SetGain(float gain) = 0;
		virtual UEResult<> SetPosition(const glm::vec3& position) = 0;
		virtual UEResult<> SetVelocity(const glm::vec3& velocity) = 0;
		virtual UEResult<> SetDirection(const glm::vec3& direction) = 0;
		virtual UEResult<> SetLooping(bool looping) = 0;
		virtual UEResult<> SetBuffer(uint32_t bufferId) = 0;

		virtual UEResult<> GetPitch(float& pitch) = 0;
		virtual UEResult<> GetGain(float& gain) = 0;
		virtual UEResult<> GetPosition(glm::vec3& position) = 0;
		virtual UEResult<> GetVelocity(glm::vec3& velocity) = 0;
		virtual UEResult<> GetDirection(glm::vec3& direction) = 0;
		virtual UEResult<> GetLooping(bool& looping) = 0;
		virtual UEResult<> GetBuffer(uint32_t& bufferId) = 0;

		static Ref<SoundSource> Create();
	};
}