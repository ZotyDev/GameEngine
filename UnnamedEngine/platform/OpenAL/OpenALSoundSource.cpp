#include "uepch.h"
#include "OpenAL/OpenALSoundSource.h"

namespace UE
{
	OpenALSoundSource::OpenALSoundSource() :
		m_ID(0)
	{}

	OpenALSoundSource::~OpenALSoundSource()
	{
		Stop();
		alDeleteSources(1, &m_ID);
	}

	UEResult<> OpenALSoundSource::Init()
	{
		alGenSources(1, &m_ID);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Could not create OpenAL sound source");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::SetSource(Ref<Sound> source)
	{
		if (!SetBuffer(source->GetID()))
		{
			UE_CORE_ERROR("Could not set data source of OpenAL sound source");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::Play()
	{
		alSourcePlay(m_ID);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to play OpenAL sound source");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::Stop()
	{
		alSourceStop(m_ID);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to stop OpenAL sound source");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::Pause()
	{
		alSourcePause(m_ID);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to pause OpenAL sound source");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	// Todo: warn about the incorrect usage of resume
	UEResult<> OpenALSoundSource::Resume()
	{
		alSourcePlay(m_ID);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to resume OpenAL sound source");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::SetPitch(float pitch)
	{
		alSourcef(m_ID, AL_PITCH, pitch);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to set pitch of OpenAL sound source: value = {0}", pitch);
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::SetGain(float gain)
	{
		alSourcef(m_ID, AL_GAIN, gain);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to set gain of OpenAL sound source: value = {0}", gain);
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::SetPosition(const glm::vec3& position)
	{
		alSource3f(m_ID, AL_POSITION, position.x, position.y, position.z);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to set position of OpenAL sound source: values = x: {0}, y: {1}, z: {2}", position.x, position.y, position.z);
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::SetVelocity(const glm::vec3& velocity)
	{
		alSource3f(m_ID, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to set velocity of OpenAL sound source: values = x: {0}, y: {1}, z: {2}", velocity.x, velocity.y, velocity.z);
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::SetDirection(const glm::vec3& direction)
	{
		alSource3f(m_ID, AL_DIRECTION, direction.x, direction.y, direction.z);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to set direction of OpenAL sound source: values = x: {0}, y: {1}, z: {2}", direction.x, direction.y, direction.z);
			return UEResult<>::Error;
		}
		
		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::SetLooping(bool looping)
	{
		alSourcei(m_ID, AL_LOOPING, looping ? AL_TRUE : AL_FALSE);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to set OpenAL sound source to {0}", looping ? "looping" : "non-looping");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::SetBuffer(uint32_t bufferId)
	{
		alSourcei(m_ID, AL_BUFFER, (ALint)bufferId);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to attach buffer to OpenAL sound source");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::GetPitch(float& pitch)
	{
		alGetSourcef(m_ID, AL_PITCH, &pitch);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to get pitch of OpenAL sound source");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::GetGain(float& gain)
	{
		alGetSourcef(m_ID, AL_GAIN, &gain);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to get gain of OpenAL sound source");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::GetPosition(glm::vec3& position)
	{
		alGetSource3f(m_ID, AL_POSITION, &position.x, &position.y, &position.z);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to get position of OpenAL sound source");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::GetVelocity(glm::vec3& velocity)
	{
		alGetSource3f(m_ID, AL_VELOCITY, &velocity.x, &velocity.y, &velocity.z);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to get velocity of OpenAL sound source");
			return UEResult<>::Error;
		}
		
		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::GetDirection(glm::vec3& direction)
	{
		alGetSource3f(m_ID, AL_DIRECTION, &direction.x, &direction.y, &direction.z);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to get direction of OpenAL sound source");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::GetLooping(bool& looping)
	{
		ALint IsLooping;
		alGetSourcei(m_ID, AL_LOOPING, &IsLooping);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to check if OpenAL sound source is looping");
			return UEResult<>::Error;
		}
		
		looping = IsLooping == AL_TRUE ? true : false;
		return UEResult<>::Success;
	}

	UEResult<> OpenALSoundSource::GetBuffer(uint32_t& bufferId)
	{
		alGetSourcei(m_ID, AL_BUFFER, (ALint*)&bufferId);
		if (CheckAlError())
		{
			UE_CORE_ERROR("Failed to get the attached buffer of OpenAL sound source");
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}
}