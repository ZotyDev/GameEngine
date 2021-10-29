#include "uepch.h"
#include "Interface/Text/Font.h"

#if defined(UE_PLATFORM_WINDOWS)
	#include "FreeType/FreeTypeFont.h"
#endif

namespace UE
{
	Ref<Font> Font::Create()
	{
		switch (TextAPI::GetAPI())
		{
		case UE::TextAPI::API::None:
			UE_CORE_ASSERT(false, "TextAPI::None is currently not supported");
			return nullptr;

		#if defined(UE_PLATFORM_WINDOWS)
		case UE::TextAPI::API::FreeType:
			return CreateRef<FreeTypeFont>();
		#endif
		}

		UE_CORE_ERROR("Unknown TextAPI");
		return nullptr;
	}
}