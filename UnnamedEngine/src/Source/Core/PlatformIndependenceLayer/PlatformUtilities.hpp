#pragma once

#include "Core/PlatformIndependenceLayer/PlatformDetection.hpp"
#include "Core/PlatformIndependenceLayer/Types.hpp"

namespace UE
{
    class PlatformUtilities
    {
    public:
        static void Setup();

        static UEUint32 FloatToUint32(UEFloat value);
        static UEUint64 DoubleToUint64(UEDouble value);
        static UEFloat  Uint32ToFloat(UEUint32 value);
        static UEDouble Uint64ToDouble(UEUint64 value);

        static UEUint16 BigEndianLocalEndian16(UEUint16 value);
        static UEUint32 BigEndianLocalEndian32(UEUint32 value);
        static UEUint64 BigEndianLocalEndian64(UEUint64 value);
        static UEFloat  BigEndianLocalEndianFloat(UEFloat value);
        static UEDouble BigEndianLocalEndianDouble(UEDouble value);

        static UEUint16 LittleEndianLocalEndian16(UEUint16 value);
        static UEUint32 LittleEndianLocalEndian32(UEUint32 value);
        static UEUint64 LittleEndianLocalEndian64(UEUint64 value);
        static UEFloat  LittleEndianLocalEndianFloat(UEFloat value);
        static UEDouble LittleEndianLocalEndianDouble(UEDouble value);

        static UEUint16 LocalEndianBigEndian16(UEUint16 value);
        static UEUint32 LocalEndianBigEndian32(UEUint32 value);
        static UEUint64 LocalEndianBigEndian64(UEUint64 value);
        static UEFloat  LocalEndianBigEndianFloat(UEFloat value);
        static UEDouble LocalEndianBigEndianDouble(UEDouble value);

        static UEUint16 LocalEndianLittleEndian16(UEUint16 value);
        static UEUint32 LocalEndianLittleEndian32(UEUint32 value);
        static UEUint64 LocalEndianLittleEndian64(UEUint64 value);
        static UEFloat  LocalEndianLittleEndianFloat(UEFloat value);
        static UEDouble LocalEndianLittleEndianDouble(UEDouble value);

        static UEUint16 HostToNetwork16(UEUint16 value);
        static UEUint32 HostToNetwork32(UEUint32 value);
        static UEUint64 HostToNetwork64(UEUint64 value);
        static UEFloat  HostToNetworkFloat(UEFloat value);
        static UEDouble HostToNetworkDouble(UEDouble value);

        static UEUint16 NetworkToHost16(UEUint16 value);
        static UEUint32 NetworkToHost32(UEUint32 value);
        static UEUint64 NetworkToHost64(UEUint64 value);
        static UEFloat  NetworkToHostFloat(UEFloat value);
        static UEDouble NetworkToHostDouble(UEDouble value);
    public:
        static UEBool s_IsBigEndian;
    };
}
