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

		static int SendServerMessage(Ref<Message> message)
		{
			return s_Server->SendMessage(message);
		}

		static void ShutdownServer()
		{
			s_Server->Shutdown();
			IsServer = false;
		}

		static void InitClient()
		{
			s_Client->Init();
			IsClient = true;
		}

		static int SendClientMessage(Ref<Message> message)
		{
			return s_Client->SendMessage(message);
		}

		static void ShutdownClient()
		{
			s_Client->Shutdown();
			IsClient = false;
		}

		static void Connect(IPEndpoint destination)
		{
			s_Client->Connect(destination);
		}

		static void Disconnect()
		{
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

		static void SetClientEventCallback(const EventCallbackFn& callback)
		{
			s_Client->SetEventCallback(callback);
		}
	public:
		static bool IsServer;
		static bool IsClient;
	private:
		static Scope<NetworkAPI> s_NetworkAPI;
		static Scope<Server> s_Server;
		static Scope<Client> s_Client;
	};
}