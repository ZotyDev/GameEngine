#pragma once

#include "Network/NetworkAPI.h"

#include <winsock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

namespace UE
{
	class WinsockNetworkAPI : public NetworkAPI
	{
	public:
		virtual ~WinsockNetworkAPI();

		virtual void Init() override;
	private:
		WSADATA m_WsaData;
	};
}