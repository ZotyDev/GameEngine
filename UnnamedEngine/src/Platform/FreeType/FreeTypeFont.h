#pragma once

#include "Interface/Text/Font.h"

#include "Platform/FreeType/FreeTypeTextAPI.h"

namespace UE
{
	class FreeTypeFont : public Font
	{
	public:
		virtual ~FreeTypeFont() override;

		virtual UEResult LoadFromFile(const std::string& filename) override;
	private:
		FT_Face FontFace;
	};
}