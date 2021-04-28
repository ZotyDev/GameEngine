#include "uepch.h"
#include "Network/NetworkCommand.h"

namespace UE
{
	Scope<NetworkAPI> NetworkCommand::s_NetworkAPI = NetworkAPI::Create();
}