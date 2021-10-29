#include "uepch.h"
#include "Network/Socket.h"

#include "Network/NetworkAPI.h"

#if defined(UE_PLATFORM_WINDOWS)
	#include "Winsock/WinsockSocket.h"
#endif

namespace UE
{
	Scope<Socket> Socket::Create()
	{
		switch (NetworkAPI::GetAPI())
		{
		case UE::NetworkAPI::API::None:
			UE_CORE_ASSERT(false, "NetworkAPI::None is currently not supported!");
			return nullptr;

		#if defined(UE_PLATFORM_WINDOWS)
		case UE::NetworkAPI::API::Winsock:
			return CreateScope<WinsockSocket>();
		#endif
		}

		UE_CORE_ERROR("Unknown NetworkAPI!");
		return nullptr;
	}
}