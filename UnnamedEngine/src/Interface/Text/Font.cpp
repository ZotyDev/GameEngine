#include "uepch.h"
#include "Interface/Text/Font.h"

#include "Platform/FreeType/FreeTypeFont.h"

namespace UE
{
	Ref<Font> Font::Create()
	{
		switch (TextAPI::GetAPI())
		{
		case UE::TextAPI::API::None:
			UE_CORE_ASSERT(false, "TextAPI::None is currently not supported");
			return nullptr;
		case UE::TextAPI::API::FreeType:
			return CreateRef<FreeTypeFont>();
		}

		UE_CORE_ERROR("Unknown TextAPI");
		return nullptr;
	}
}