#include "uepch.h"
#include "Sound/SoundAPI.h"

#if defined(UE_PLATFORM_OPENAL)
	#include "OpenAL/OpenALSoundAPI.h"
#endif

namespace UE
{
	SoundAPI::API SoundAPI::s_API = SoundAPI::API::OpenAL;

	Scope<SoundAPI> SoundAPI::Create()
	{
		switch (s_API)
		{
		case UE::SoundAPI::API::None:
			UE_CORE_ASSERT(false, "SoundAPI::None is currently not supported");
			return nullptr;

		#if defined(UE_PLATFORM_OPENAL)
		case UE::SoundAPI::API::OpenAL:
			return CreateScope<OpenALSoundAPI>();
		#endif
		}

		UE_CORE_ERROR("Unknown SoundAPI");
		return nullptr;
	}
}