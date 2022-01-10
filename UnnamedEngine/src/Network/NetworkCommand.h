#pragma once

#include "Network/NetworkAPI.h"

namespace UE
{
	class NetworkCommand
	{
	public:

		static void Init()
		{
			s_NetworkAPI->Init();
		}

		static void Shutdown()
		{
			s_NetworkAPI->Shutdown();
		}

	private:
		static Scope<NetworkAPI> s_NetworkAPI;
	};
}