#include "uepch.h"
#include "Interface/Text/TextCommand.h"

namespace UE
{
	Scope<TextAPI> TextCommand::s_TextAPI = TextAPI::Create();
}