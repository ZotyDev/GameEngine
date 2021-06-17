#pragma once

#include "Network/Connection.h"

namespace UE
{
	class ServerConnection : public Connection
	{
	public:
		ServerConnection();
		virtual ~ServerConnection();

		virtual int Connect() override;
		virtual int Disconnect() override;
		virtual int OnUpdate() override;
		virtual int SendHeartbeat() override;
	};
}