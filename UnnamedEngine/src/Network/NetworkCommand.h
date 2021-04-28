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

	private:
		static Scope<NetworkAPI> s_NetworkAPI;
	};
}
