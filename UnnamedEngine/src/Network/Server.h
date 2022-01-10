#pragma once

#include "Network/IPEndpoint.h"
#include "Network/Socket.h"
#include "Core/Timestep.h"

namespace UE
{
	class Server
	{
	public:

		UEResult Start(IPEndpoint listeningIP);
		UEResult Shutdown();

		UEResult OnUpdate(Timestep dt);

	private:
		IPEndpoint m_ListeningIP;
		Ref<Socket> m_ListeningSocket;
	};
}