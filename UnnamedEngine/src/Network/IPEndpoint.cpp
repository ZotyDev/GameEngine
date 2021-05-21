#include "uepch.h"
#include "Network/IPEndpoint.h"

namespace UE
{
	IPEndpoint::IPEndpoint(std::string ip, std::string port)
		: m_IP(ip), m_Port(port)
	{}

	IPEndpoint::IPEndpoint(std::string ip, unsigned short port)
		: m_IP(ip), m_Port(std::to_string(port))
	{}
}