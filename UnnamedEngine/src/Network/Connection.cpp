#include "uepch.h"
#include "Network/Connection.h"

namespace UE
{
	Connection::Connection(Ref<Socket> socket)
	{
		m_Socket = socket;
	}

	void Connection::Close()
	{
		m_Socket->Close();
	}
}