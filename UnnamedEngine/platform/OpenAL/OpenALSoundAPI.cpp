#include "uepch.h"
#include "OpenAL/OpenALSoundAPI.h"

namespace UE
{
	bool CheckAlcError(ALCdevice* device)
	{
		ALenum Error = alcGetError(device);
		if (Error != ALC_NO_ERROR)
		{
			switch (Error)
			{
			case ALC_INVALID_CONTEXT:
				UE_CORE_ERROR("ALC_INVALID_CONTEXT: a bad context was passed to an OpenAL function");
				break;
			case ALC_INVALID_DEVICE:
				UE_CORE_ERROR("ALC_INVALID_DEVICE: a bad device was passed to an OpenAL function");
				break;
			case ALC_INVALID_ENUM:
				UE_CORE_ERROR("ALC_INVALID_ENUM: a invalid enum value was passed to an OpenAL function");
				break;
			case ALC_INVALID_VALUE:
				UE_CORE_ERROR("ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function");
				break;
			case ALC_OUT_OF_MEMORY:
				UE_CORE_ERROR("ALC_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory");
				break;
			default:
				UE_CORE_ERROR("Unknwon OpenAL error: {0}", Error);
				break;
			}
			return true;
		}
		return false;
	}

	bool CheckAlError()
	{
		ALenum Error = alGetError();
		if (Error != AL_NO_ERROR)
		{
			switch (Error)
			{
			case AL_INVALID_NAME:
				UE_CORE_ERROR("AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function");
				break;
			case AL_INVALID_ENUM:
				UE_CORE_ERROR("AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function");
				break;
			case AL_INVALID_VALUE:
				UE_CORE_ERROR("AL_INVALID_VALUE: an invalid value was passed to an OpenAL function");
				break;
			case AL_INVALID_OPERATION:
				UE_CORE_ERROR("AL_INVALID_OPERATION: an invalid operation was passed to an OpenAL function");
				break;
			case AL_OUT_OF_MEMORY:
				UE_CORE_ERROR("AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory");
				break;
			default:
				UE_CORE_ERROR("Unknown OpenAL error: {0}", Error);
				break;
			}
			return true;
		}
		return false;
	}

	OpenALSoundAPI::OpenALSoundAPI()
		: m_SoundDevice(nullptr), m_SoundContext(nullptr)
	{}

	OpenALSoundAPI::~OpenALSoundAPI()
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(m_SoundContext);
		alcCloseDevice(m_SoundDevice);
	}

	UEResult OpenALSoundAPI::Init()
	{
		// Select the device to output sound to
		m_SoundDevice = alcOpenDevice(nullptr);
		if (m_SoundDevice == nullptr || CheckAlcError(m_SoundDevice))
		{
			UE_CORE_ERROR("Failed to select default audio output device");
			return UEResult::Error;
		}

		// Create context
		m_SoundContext = alcCreateContext(m_SoundDevice, nullptr);
		if (m_SoundContext == nullptr || CheckAlcError(m_SoundDevice))
		{
			UE_CORE_ERROR("Failed to create OpenAL context");
			return UEResult::Error;
		}

		// Make context current
		if (!alcMakeContextCurrent(m_SoundContext) || CheckAlcError(m_SoundDevice))
		{
			UE_CORE_ERROR("Failed to make OpenAL context current");
			return UEResult::Error;
		}

		UE_CORE_INFO("OpenAL info:\n Vendor: {0}\n Renderer: {1}\n Version: {2}",
			alGetString(AL_VENDOR),
			alGetString(AL_RENDERER),
			alGetString(AL_VERSION));

		return UEResult::Success;
	}
}