#include "uepch.h"
#include "Network/Socket.h"

#include "Network/NetworkAPI.h"

#include "Platform/Winsock/WinsockSocket.h"

namespace UE
{
	Scope<Socket> Socket::Create()
	{
		switch (NetworkAPI::GetAPI())
		{
		case UE::NetworkAPI::API::None:
			UE_CORE_ASSERT(false, "NetworkAPI::None is currently not supported!");
			return nullptr;
		case UE::NetworkAPI::API::Winsock:
			return CreateScope<WinsockSocket>();
		}

		UE_CORE_ERROR("Unknown NetworkAPI!");
		return nullptr;
	}
}