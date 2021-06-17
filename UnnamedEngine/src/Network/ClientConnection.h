#pragma once

#include "Network/Connection.h"

namespace UE
{
	class ClientConnection : public Connection
	{
	public:
		ClientConnection();
		virtual ~ClientConnection();

		virtual int Connect() override;
		virtual int Disconnect() override;
		virtual int OnUpdate() override;
		virtual int SendHeartbeat() override;
	};
}