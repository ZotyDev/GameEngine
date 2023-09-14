#include "Networking/IPEndpoint.hpp"

namespace UE
{
    IPEndpoint::IPEndpoint(UEString ip, UEString port)
    : IP(ip), Port(port)
    {}

    IPEndpoint::IPEndpoint(UEString ip, UEUint16 port)
    : IP(ip), Port(std::to_string(port))
    {}
}