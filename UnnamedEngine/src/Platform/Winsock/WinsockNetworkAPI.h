#pragma once

#include "Network/NetworkAPI.h"

#include <winsock2.h>
#include <WS2tcpip.h>

namespace UE
{
	class WinsockNetworkAPI : public NetworkAPI
	{
	public:
		virtual ~WinsockNetworkAPI();

		virtual void Init() override;
		virtual void Shutdown() override;
	private:
		WSADATA m_WsaData;
	};
}