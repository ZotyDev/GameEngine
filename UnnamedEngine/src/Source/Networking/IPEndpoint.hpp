#pragma once

#include "Core/Base.hpp"

namespace UE
{
    enum class IPVersion
    {
        IPv4,
        IPv6
    };

    class IPEndpoint
    {
    public:
        // TODO ZOTY
        // Make this work...
        enum class Version
        {
            IPv4,
            IPv6
        };

    public:
        IPEndpoint() = default;
        IPEndpoint(UEString ip, UEString port);
        IPEndpoint(UEString ip, UEUint16 port);

        void SetUPort(UEUint16 port) { Port = std::to_string(port); }
        UEUint16 GetUPort() const { return std::strtoul(Port.c_str(), NULL, 0); }

        UEString GetAddress() const { return IP + ":" + Port; }

    public:
        UEBool operator==(const IPEndpoint& other)
        {
            return (IP == other.IP && Port == other.Port);
        }

    public:
        UEString IP;
        UEString Port;
    };
}

namespace std
{
    template<>
    struct hash<UE::IPEndpoint>
    {
        std::size_t operator()(UE::IPEndpoint const& endpoint) const noexcept
        {
            return std::hash<UE::UEString>()(endpoint.IP) ^ std::hash<UE::UEString>()(endpoint.Port);
        }
    };
}