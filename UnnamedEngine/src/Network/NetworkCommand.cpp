#include "uepch.h"
#include "Network/NetworkCommand.h"

namespace UE
{
	bool NetworkCommand::IsServer = false;
	bool NetworkCommand::IsConnected = false;
	Scope<NetworkAPI> NetworkCommand::s_NetworkAPI = NetworkAPI::Create();
	Scope<Server> NetworkCommand::s_Server = CreateScope<Server>();
	Scope<Client> NetworkCommand::s_Client = CreateScope<Client>();
}