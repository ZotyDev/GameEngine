#include "uepch.h"
#include "Network/NetworkServer.h"

#include "Platform/Winsock/WinsockNetworkServer.h"

namespace UE
{
	Scope<NetworkServer> NetworkServer::Create()
	{
		switch (NetworkAPI::GetAPI())
		{
		case UE::NetworkAPI::API::None:
			UE_CORE_ASSERT(false, "NetworkAPI::None is currently not supported!");
			return nullptr;
		case UE::NetworkAPI::API::Winsock:
			return CreateScope<WinsockNetworkServer>();
		}

		UE_CORE_ERROR("Unknown NetworkAPI!");
		return nullptr;
	}
}