#include "uepch.h"
#include "Network/NetworkAPI.h"

#if defined(UE_PLATFORM_WINDOWS)
	#include "Winsock/WinsockNetworkAPI.h"
#endif

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

		#if defined(UE_PLATFORM_WINDOWS)
		case UE::NetworkAPI::API::Winsock:
			return CreateScope<WinsockNetworkAPI>();
		#endif
		}

		UE_CORE_ERROR("Unknown RendererAPI");
		return nullptr;
	}
}