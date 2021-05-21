#pragma once

#include "Network/ConnectionManager.h"

#include <winsock2.h>
#include <WS2tcpip.h>

namespace UE
{
	class WinsockConnectionManager : public ConnectionManager
	{
	public:
		WinsockConnectionManager();
		virtual ~WinsockConnectionManager();

		virtual int Init(Ref<Socket> listeningSocket) override;
		virtual int Poll() override;
	private:
		void CloseConnection(int connectionIndex);
	private:
		WSAPOLLFD m_ListeningSocketFD[1];
		int m_ConnectionIndex = 0;
	};
}