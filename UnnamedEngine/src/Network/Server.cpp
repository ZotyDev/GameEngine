#include "uepch.h"
#include "Network/Server.h"

namespace UE
{
	UEResult<> Server::Start(IPEndpoint listeningIP)
	{
		m_ListeningIP = listeningIP;

		m_ListeningSocket = Socket::Create();
		m_ListeningSocket->Init();

		if (m_ListeningSocket->Bind(listeningIP))
		{
			UE_CORE_ERROR("Failed to start server: failed to bind listening socket");
			return UEResult<>::Error;
		}

		if (m_ListeningSocket->Block(false))
		{
			UE_CORE_ERROR("Failed to start server: failed to set listening socket to non-blocking");
			return UEResult<>::Error;
		}

		UE_CORE_INFO("Server started and listening on: {0}", listeningIP.GetAddress());

		return UEResult<>::Success;
	}

	UEResult<> Server::Shutdown()
	{
		return UEResult<>::Success;
	}

	UEResult<> Server::OnUpdate(Timestep dt)
	{
		return UEResult<>::Success;
	}
}