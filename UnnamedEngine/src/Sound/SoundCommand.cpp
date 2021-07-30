#include "uepch.h"
#include "Sound/SoundCommand.h"

namespace UE
{
	Scope<SoundAPI> SoundCommand::s_SoundAPI = SoundAPI::Create();
}