#include "uepch.h"
#include "Sound/SoundSource.h"

#include "Platform/OpenAL/OpenALSoundSource.h"

namespace UE
{
	Ref<SoundSource> SoundSource::Create()
	{
		switch (SoundAPI::GetAPI())
		{
		case SoundAPI::API::None:
			UE_CORE_ASSERT(false, "SoundAPI::None is currently not supported");
			return nullptr;
		case SoundAPI::API::OpenAL:
			return CreateRef<OpenALSoundSource>();
		}

		UE_CORE_ASSERT(false, "Unknown SoundAPI");
		return nullptr;
	}
}