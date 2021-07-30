#include "uepch.h"
#include "Sound/SoundAPI.h"

#include "Platform/OpenAL/OpenALSoundAPI.h"

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
		case UE::SoundAPI::API::OpenAL:
			return CreateScope<OpenALSoundAPI>();
		}

		UE_CORE_ERROR("Unknown SoundAPI");
		return nullptr;
	}
}