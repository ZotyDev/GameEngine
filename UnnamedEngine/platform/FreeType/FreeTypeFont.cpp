#include "uepch.h"
#include "FreeType/FreeTypeFont.h"

#include "Interface/Text/TextCommand.h"

namespace UE
{
	FreeTypeFont::~FreeTypeFont()
	{}

	UEResult<> FreeTypeFont::LoadFromFile(const std::string& filename)
	{
		if (FT_New_Face((FT_Library)TextCommand::GetUserPtr(), filename.c_str(), 0, &FontFace))
		{
			UE_CORE_ERROR("FreeType failed to load font: {0}", filename);
			return UEResult<>::Error;
		}

		return UEResult<>::Success;
	}
}