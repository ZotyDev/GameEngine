#pragma once

#include "Sound/SoundSource.h"

#include "Platform/OpenAL/OpenALSoundAPI.h"

namespace UE
{
	class OpenALSoundSource : public SoundSource
	{
	public:
		OpenALSoundSource();
		virtual ~OpenALSoundSource() override;

		virtual UEResult Init() override;

		virtual UEResult Play() override;
		virtual UEResult Stop() override;
		virtual UEResult Pause() override;
		virtual UEResult Resume() override;

		virtual UEResult SetSource(Ref<Sound> source) override;

		virtual UEResult SetPitch(float pitch) override;
		virtual UEResult SetGain(float gain) override;
		virtual UEResult SetPosition(const glm::vec3& position) override;
		virtual UEResult SetVelocity(const glm::vec3& velocity) override;
		virtual UEResult SetDirection(const glm::vec3& direction) override;
		virtual UEResult SetLooping(bool looping) override;
		virtual UEResult SetBuffer(uint32_t bufferId) override;

		virtual UEResult GetPitch(float& pitch) override;
		virtual UEResult GetGain(float& gain) override;
		virtual UEResult GetPosition(glm::vec3& position) override;
		virtual UEResult GetVelocity(glm::vec3& velocity) override;
		virtual UEResult GetDirection(glm::vec3& direction) override;
		virtual UEResult GetLooping(bool& looping) override;
		virtual UEResult GetBuffer(uint32_t& bufferId) override;
	private:

	private:
		ALuint m_ID;
	};
}