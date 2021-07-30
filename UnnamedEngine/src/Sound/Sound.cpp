#include "uepch.h"
#include "Sound/Sound.h"

#include "Platform/OpenAL/OpenALSound.h"

namespace UE
{
	Ref<Sound> Sound::Create()
	{
		switch (SoundAPI::GetAPI())
		{
		case SoundAPI::API::None:
			UE_CORE_ASSERT(false, "SoundAPI::None is currently not supported");
			return nullptr;
		case SoundAPI::API::OpenAL:
			return CreateRef<OpenALSound>();
		}

		UE_CORE_ASSERT(false, "Unknown SoundAPI");
		return nullptr;
	}
}