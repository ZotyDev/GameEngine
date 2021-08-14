#include "uepch.h"
#include "Interface/Text/TextAPI.h"

#include "Platform/FreeType/FreeTypeTextAPI.h"

namespace UE
{
	TextAPI::API TextAPI::s_API = TextAPI::API::FreeType;

	Scope<TextAPI> TextAPI::Create()
	{
		switch (s_API)
		{
		case UE::TextAPI::API::None:
			UE_CORE_ASSERT(false, "TextAPI::None is currently not supported");
			return nullptr;
		case UE::TextAPI::API::FreeType:
			return CreateScope<FreeTypeTextAPI>();
		}

		UE_CORE_ERROR("Unknown TextAPI");
		return nullptr;
	}
}