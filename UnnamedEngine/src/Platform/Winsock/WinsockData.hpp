#pragma once

#include "Core/Base.hpp"

#include <WinSock2.h>
#include <WS2tcpip.h>

namespace UE
{
    struct
    {
        WSADATA WSAData;
    } WinsockData;
}
