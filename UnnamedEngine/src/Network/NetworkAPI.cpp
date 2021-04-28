#include "uepch.h"
#include "Network/NetworkAPI.h"

#include "Platform/Winsock/WinsockNetworkAPI.h"

namespace UE
{
	NetworkAPI::API NetworkAPI::s_API = NetworkAPI::API::Winsock;

	Scope<NetworkAPI> NetworkAPI::Create()
	{
		switch (s_API)
		{
		case UE::NetworkAPI::API::None:
			UE_CORE_ASSERT(false, "NetworkAPI::None is currently not supported!");
			return nullptr;
		case UE::NetworkAPI::API::Winsock:
			return CreateScope<WinsockNetworkAPI>();
		}

		UE_CORE_ERROR("Unknown RendererAPI");
		return nullptr;
	}
}