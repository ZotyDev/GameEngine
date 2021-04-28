#include "uepch.h"
#include "Platform/Winsock/WinsockNetworkAPI.h"

namespace UE
{
	WinsockNetworkAPI::~WinsockNetworkAPI()
	{
	}

	void WinsockNetworkAPI::Init()
	{
		int success = WSAStartup(MAKEWORD(2, 2), &m_WsaData);
		UE_CORE_ASSERT(!success, "Failed to start Winsock!");
	}
}