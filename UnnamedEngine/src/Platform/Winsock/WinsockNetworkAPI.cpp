#include "Networking/NetworkAPI.hpp"

#include "Winsock/WinsockData.hpp"

#include <winsock2.h>
#include <WS2tcpip.h>

namespace UE
{
    void NetworkAPI::Init()
    {
        UEInt32 Success = WSAStartup(MAKEWORD(2, 2), &WinsockData.WSAData);
        UE_ASSERT_CORE(!Success, "Failed to start Winsock");
    }

    void NetworkAPI::Shutdown()
    {
        UEInt32 Success = WSACleanup();
        UE_ASSERT_CORE(!Success, "Failed to cleanup Winsock");
    }
}
