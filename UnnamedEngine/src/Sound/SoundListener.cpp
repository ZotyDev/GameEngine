#include "uepch.h"
#include "Sound/SoundListener.h"

#include "Platform/OpenAL/OpenALSoundListener.h"

namespace UE
{
	Ref<SoundListener> SoundListener::Create()
	{
		switch (SoundAPI::GetAPI())
		{
		case SoundAPI::API::None:
			UE_CORE_ASSERT(false, "SoundAPI::None is currently not supported");
			return nullptr;
		case SoundAPI::API::OpenAL:
			return CreateRef<OpenALSoundListener>();
		}

		UE_CORE_ERROR("Unknown SoundAPI");
		return nullptr;
	}
}