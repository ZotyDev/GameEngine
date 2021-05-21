#pragma once

#include "Network/NetworkAPI.h"
#include "Network/Server.h"
#include "Network/Client.h"
#include "Core/Timestep.h"

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

		static void Shutdown()
		{
			s_NetworkAPI->Shutdown();
		}

		static void InitServer(std::string port)
		{
			s_Server->Init(port);
			IsServer = true;
		}

		static void ShutdownServer()
		{
			s_Server->Shutdown();
			IsServer = false;
		}

		static void InitClient()
		{
			s_Client->Init();
		}

		static void ShutdownClient()
		{
			IsConnected = false;
			s_Client->Shutdown();
		}

		static void Connect(IPEndpoint destination)
		{
			s_Client->Connect(destination);
			IsConnected = true;
		}

		static void Disconnect()
		{
			IsConnected = false;
		}

		static void OnServerUpdate(Timestep timestep)
		{
			s_Server->OnUpdate();
		}

		static void OnClientUpdate(Timestep timestep)
		{
			s_Client->OnUpdate();
		}

		static void SetServerEventCallback(const EventCallbackFn& callback)
		{
			s_Server->SetEventCallback(callback);
		}
	public:
		static bool IsServer;
		static bool IsConnected;
	private:
		static Scope<NetworkAPI> s_NetworkAPI;
		static Scope<Server> s_Server;
		static Scope<Client> s_Client;
	};
}