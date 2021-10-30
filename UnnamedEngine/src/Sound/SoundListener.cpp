#include "uepch.h"
#include "Sound/SoundListener.h"

#if defined(UE_PLATFORM_OPENAL)
	#include "OpenAL/OpenALSoundListener.h"
#endif

namespace UE
{
	Ref<SoundListener> SoundListener::Create()
	{
		switch (SoundAPI::GetAPI())
		{
		case SoundAPI::API::None:
			UE_CORE_ASSERT(false, "SoundAPI::None is currently not supported");
			return nullptr;

		#if defined(UE_PLATFORM_OPENAL)
		case SoundAPI::API::OpenAL:
			return CreateRef<OpenALSoundListener>();
		#endif
		}

		UE_CORE_ERROR("Unknown SoundAPI");
		return nullptr;
	}
}