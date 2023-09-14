#pragma once

#include "Core/Base.hpp"
#include "Networking/IPEndpoint.hpp"

namespace UE
{
    struct Connection
    {
    public:
        enum class State
        {
            InitialDisconnected,
            Connecting,
            Connected,
            ConnectionFailed,
            Disconnecting,
            Disconnected
        };
    
        enum class Error
        {
            Timeout,
            WrongProtocol,
            AuthenticationFailed,
            Capacity,
            Unknown
        };
    public:
        UEBool IsConnected() const { return State == Connection::State::Connected; }

    public:
        Connection::State State = Connection::State::Disconnected;
        IPEndpoint Endpoint;
        UEUint64 ClientSalt;
        UEUint64 ServerSalt;
    };
}