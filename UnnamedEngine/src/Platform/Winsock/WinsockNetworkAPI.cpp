#include "uepch.h"
#include "Platform/Winsock/WinsockNetworkAPI.h"

#include <winsock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

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

	void WinsockNetworkAPI::Shutdown()
	{
		WSACleanup();
	}
}