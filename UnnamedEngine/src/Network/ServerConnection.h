#pragma once

#include "Network/Connection.h"

namespace UE
{
	class ServerConnection : public Connection
	{
	public:
		ServerConnection();
		virtual ~ServerConnection();

		virtual UEResult<> Connect() override;
		virtual UEResult<> Disconnect() override;
		virtual UEResult<> OnUpdate() override;
		virtual UEResult<> SendHeartbeat() override;
	};
}