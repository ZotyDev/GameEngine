#pragma once

#include "Network/NetworkAPI.h"
#include "Network/NetworkServer.h"

#include <string>

namespace UE
{
	class NetworkCommand
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		static void Init()
		{
			s_NetworkAPI->Init();
		}

		static void InitServer(std::string port)
		{
			s_NetworkServer->Init(port);
		}

		static void ShutdownServer()
		{
			s_NetworkServer->Shutdown();
		}

		static void OnServerUpdate()
		{
			s_NetworkServer->OnUpdate();
		}

		static void SetServerEventCallback(const EventCallbackFn& callback)
		{
			s_NetworkServer->SetEventCallback(callback);
		}

	private:
		static Scope<NetworkAPI> s_NetworkAPI;
		static Scope<NetworkServer> s_NetworkServer;
	};
}