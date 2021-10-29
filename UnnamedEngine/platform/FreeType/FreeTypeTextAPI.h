#pragma once

#include "Interface/Text/TextAPI.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace UE
{
	class FreeTypeTextAPI : public TextAPI
	{
	public:
		virtual ~FreeTypeTextAPI() override;

		virtual UEResult Init() override;

		virtual void* GetRawLibrary() override;
	private:
		FT_Library FreeType;
	};
}