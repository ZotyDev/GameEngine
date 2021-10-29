#include "uepch.h"
#include "OpenAL/OpenALSoundListener.h"

namespace UE
{
	OpenALSoundListener* OpenALSoundListener::s_CurrentContext = nullptr;

	OpenALSoundListener::OpenALSoundListener() :
		m_Gain(1.0f),
		m_Position(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_Velocity(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_Orientation(glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)))
	{}

	OpenALSoundListener::~OpenALSoundListener()
	{}

	UEResult OpenALSoundListener::MakeCurrent()
	{
		s_CurrentContext = this;

		if (SetGain(m_Gain) == UEResult::Error)
		{
			return UEResult::Error;
		}

		if (SetPosition(m_Position) == UEResult::Error)
		{
			return UEResult::Error;
		}
		
		if (SetVelocity(m_Velocity) == UEResult::Error)
		{
			return UEResult::Error;
		}

		if (SetOrientation(m_Orientation) == UEResult::Error)
		{
			return UEResult::Error;
		}

		return UEResult::Success;
	}

	UEResult OpenALSoundListener::SetGain(float gain)
	{
		if (s_CurrentContext == this)
		{
			alListenerf(AL_GAIN, gain);
			if (CheckAlError())
			{
				UE_CORE_ERROR("Failed to set listener gain");
				return UEResult::Error;
			}
		}

		m_Gain = gain;

		return UEResult::Success;
	}

	UEResult OpenALSoundListener::SetPosition(const glm::vec3& position)
	{
		if (s_CurrentContext == this)
		{
			alListener3f(AL_POSITION, position.x, position.y, position.z);
			if (CheckAlError())
			{
				UE_CORE_ERROR("Failed to set listener position");
				return UEResult::Error;
			}
		}

		m_Position = position;

		return UEResult::Success;
	}

	UEResult OpenALSoundListener::SetVelocity(const glm::vec3& velocity)
	{
		if (s_CurrentContext == this)
		{
			alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
			if (CheckAlError())
			{
				UE_CORE_ERROR("Failed to set listener velocity");
				return UEResult::Error;
			}
		}

		m_Position = velocity;

		return UEResult::Success;
	}

	UEResult OpenALSoundListener::SetOrientation(const glm::quat& orientation)
	{
		if (s_CurrentContext == this)
		{
			glm::vec3 Forward = glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f));
			glm::vec3 Up = glm::rotate(orientation, glm::vec3(0.0f, 1.0f, 0.0f));
			float ListenerOrientation[] =
			{
				Forward.x, Forward.y, Forward.z,
				Up.x, Up.y, Up.z
			};
			alListenerfv(AL_ORIENTATION, ListenerOrientation);
			if (CheckAlError())
			{
				UE_CORE_ERROR("Failed to set listener orientation");
				return UEResult::Error;
			}
		}

		m_Orientation = orientation;

		return UEResult::Success;
	}
}