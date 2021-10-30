#include "uepch.h"
#include "Sound/SoundSource.h"

#if defined(UE_PLATFORM_OPENAL)
	#include "OpenAL/OpenALSoundSource.h"
#endif

namespace UE
{
	Ref<SoundSource> SoundSource::Create()
	{
		switch (SoundAPI::GetAPI())
		{
		case SoundAPI::API::None:
			UE_CORE_ASSERT(false, "SoundAPI::None is currently not supported");
			return nullptr;

		#if defined(UE_PLATFORM_OPENAL)
		case SoundAPI::API::OpenAL:
			return CreateRef<OpenALSoundSource>();
		#endif
		}

		UE_CORE_ASSERT(false, "Unknown SoundAPI");
		return nullptr;
	}
}