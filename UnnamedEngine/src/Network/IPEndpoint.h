#pragma once

namespace UE
{
	class IPEndpoint
	{
	public:
		IPEndpoint() = default;
		IPEndpoint(std::string ip, std::string port);
		IPEndpoint(std::string ip, unsigned short port);

		void SetIp(const std::string& ip) { m_IP = ip; }
		std::string GetIp() const { return m_IP; }
		void SetPort(const std::string& port) { m_Port = port; }
		void SetPort(unsigned short port) { m_Port = std::to_string(port); }
		std::string GetPort() const { return m_Port; }
		unsigned short GetUPort() const { return std::strtoul(m_Port.c_str(), NULL, 0); }

		std::string GetAddress() { return m_IP + ":" + m_Port; }

	public:
		// For use alongside std::unordered_map
		bool operator==(const IPEndpoint& other) const
		{
			return (m_IP == other.m_IP && m_Port == other.m_Port);
		}
	private:
		std::string m_IP;
		std::string m_Port;
	};
}

namespace std
{
	template<>
	struct hash<UE::IPEndpoint>
	{
		std::size_t operator()(UE::IPEndpoint const& ipEndpoint) const noexcept
		{
			return std::hash<std::string>()(ipEndpoint.GetIp()) ^ std::hash<std::string>()(ipEndpoint.GetPort());
		}
	};
}