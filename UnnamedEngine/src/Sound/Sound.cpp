#include "uepch.h"
#include "Sound/Sound.h"

#if defined(UE_PLATFORM_OPENAL)
	#include "OpenAL/OpenALSound.h"
#endif

namespace UE
{
	Ref<Sound> Sound::Create()
	{
		switch (SoundAPI::GetAPI())
		{
		case SoundAPI::API::None:
			UE_CORE_ASSERT(false, "SoundAPI::None is currently not supported");
			return nullptr;

		#if defined(UE_PLATFORM_OPENAL)
		case SoundAPI::API::OpenAL:
			return CreateRef<OpenALSound>();
		#endif
		}

		UE_CORE_ASSERT(false, "Unknown SoundAPI");
		return nullptr;
	}
}