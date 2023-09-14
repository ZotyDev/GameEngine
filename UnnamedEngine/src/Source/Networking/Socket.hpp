#pragma once

#include "Core/Base.hpp"

#include "Networking/IPEndpoint.hpp"

namespace UE
{
    class Socket
    {
    public:
        Socket();
        ~Socket();

        UEResult<> Init();
        UEResult<> Shutdown();
        UEResult<> Bind(IPEndpoint endpoint);
        UEResult<> Block(UEBool block);
        UEResult<> SendTo(IPEndpoint destination, const void* data, UEUint32 numberOfBytes, UEUint32& bytesSent);
        UEResult<> ReceiveFrom(IPEndpoint& sender, void* data, UEUint32 numberOfBytes, UEUint32& bytesReceived);
        UEResult<> SendAllTo(IPEndpoint destination, const void* data, UEUint32 numberOfBytes);
        UEResult<> ReceiveAllFrom(IPEndpoint& sender, void* data, UEUint32 numberOfBytes);

        UEResult<UEInt32> Poll();

        const UEBool IsReceivingPackets() const { return m_IsReceivingPackets; }
        const UEBool IsReceivingErrors() const { return m_IsReceivingErrors; }
    private:
        UEBool m_IsBlocking = false;
    private:
        UEBool m_IsReceivingPackets = false;
        UEBool m_IsReceivingErrors = false;
    private:
        void* m_NativeSocket = nullptr;
    };
}
