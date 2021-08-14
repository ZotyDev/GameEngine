#pragma once

#include "Interface/Text/Character.h"

namespace UE
{
	class Font
	{
	public:
		virtual ~Font() = default;

		virtual UEResult LoadFromFile(const std::string& filename) = 0;

		static Ref<Font> Create();
	};
}