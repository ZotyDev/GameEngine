#include "uepch.h"
#include "Network/ConnectionManager.h"

#include "Platform/Winsock/WinsockConnectionManager.h"

namespace UE
{
	Scope<ConnectionManager> ConnectionManager::Create()
	{
		switch (NetworkAPI::GetAPI())
		{
		case UE::NetworkAPI::API::None:
			UE_CORE_ASSERT(false, "NetworkAPI::None is currently not supported!");
			return nullptr;
		case UE::NetworkAPI::API::Winsock:
			return CreateScope<WinsockConnectionManager>();
		}

		UE_CORE_ERROR("Unknown NetworkAPI!");
		return nullptr;
	}
}