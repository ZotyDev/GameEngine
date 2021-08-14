#pragma once

#include "Interface/Text/TextAPI.h"
#include "Interface/Text/Character.h"
#include "Interface/Text/Font.h"

#include "Events/event.h"

namespace UE
{
	class TextCommand
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		static void Init()
		{
			s_TextAPI->Init();
		}

		static void* GetUserPtr()
		{
			return s_TextAPI->GetRawLibrary();
		}

	private:
		static Scope<TextAPI> s_TextAPI;
	};
}