#pragma once

#include "Network/NetworkAPI.h"

#include "Events/Event.h"

namespace UE
{
	class NetworkServer
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~NetworkServer() = default;

		virtual void Init(std::string port) = 0;
		virtual void Shutdown() = 0;

		virtual void OnUpdate() = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		static Scope<NetworkServer> Create();
	};
}