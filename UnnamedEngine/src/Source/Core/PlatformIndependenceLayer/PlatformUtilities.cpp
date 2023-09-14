#include "Core/PlatformIndependenceLayer/PlatformUtilities.hpp"

namespace UE
{
    UEBool PlatformUtilities::s_IsBigEndian = false;

    void PlatformUtilities::Setup()
    {
        int num = 1;
        if (*(char*)&num == 1)
        {
            PlatformUtilities::s_IsBigEndian = false;
        }
        else
        {
            PlatformUtilities::s_IsBigEndian = true;
        }
    }

    UEUint32 PlatformUtilities::FloatToUint32(UEFloat value)
    {
        UEUint32 NewValue = 0;
        UEFloat* NewValuePtr = reinterpret_cast<UEFloat*>(&NewValue);
        *NewValuePtr = static_cast<UEFloat>(value);

        return NewValue;
    }

    UEUint64 PlatformUtilities::DoubleToUint64(UEDouble value)
    {
        UEUint64 NewValue = 0;
        UEDouble* NewValuePtr = reinterpret_cast<UEDouble*>(&NewValue);
        *NewValuePtr = static_cast<UEDouble>(value);

        return NewValue;
    }

    UEFloat PlatformUtilities::Uint32ToFloat(UEUint32 value)
    {
        UEFloat NewValue = 0;
        UEUint32* NewValuePtr = reinterpret_cast<UEUint32*>(&NewValue);
        *NewValuePtr = static_cast<UEUint32>(value);

        return NewValue;
    }

    UEDouble PlatformUtilities::Uint64ToDouble(UEUint64 value)
    {
        UEDouble NewValue = 0;
        UEUint64* NewValuePtr = reinterpret_cast<UEUint64*>(&NewValue);
        *NewValuePtr = static_cast<UEUint64>(value);

        return NewValue;
    }

    UEUint16 PlatformUtilities::BigEndianLocalEndian16(UEUint16 value)
    {
        return PlatformUtilities::s_IsBigEndian ? value : UE_BYTESWAP_16(value);
    }

    UEUint32 PlatformUtilities::BigEndianLocalEndian32(UEUint32 value)
    {
        return PlatformUtilities::s_IsBigEndian ? value : UE_BYTESWAP_32(value);
    }

    UEUint64 PlatformUtilities::BigEndianLocalEndian64(UEUint64 value)
    {
        return PlatformUtilities::s_IsBigEndian ? value : UE_BYTESWAP_64(value);
    }

    UEFloat PlatformUtilities::BigEndianLocalEndianFloat(UEFloat value)
    {
        return PlatformUtilities::s_IsBigEndian ? value : Uint32ToFloat(UE_BYTESWAP_32(FloatToUint32(value)));
    }

    UEDouble PlatformUtilities::BigEndianLocalEndianDouble(UEDouble value)
    {
        return PlatformUtilities::s_IsBigEndian ? value : Uint64ToDouble(UE_BYTESWAP_64(DoubleToUint64(value)));
    }

    UEUint16 PlatformUtilities::LittleEndianLocalEndian16(UEUint16 value)
    {
        return PlatformUtilities::s_IsBigEndian ? UE_BYTESWAP_16(value) : value;
    }

    UEUint32 PlatformUtilities::LittleEndianLocalEndian32(UEUint32 value)
    {
        return PlatformUtilities::s_IsBigEndian ? UE_BYTESWAP_32(value) : value;
    }

    UEUint64 PlatformUtilities::LittleEndianLocalEndian64(UEUint64 value)
    {
        return PlatformUtilities::s_IsBigEndian ? UE_BYTESWAP_64(value) : value;
    }

    UEFloat PlatformUtilities::LittleEndianLocalEndianFloat(UEFloat value)
    {
        return PlatformUtilities::s_IsBigEndian ? Uint32ToFloat(UE_BYTESWAP_32(FloatToUint32(value))) : value;
    }

    UEDouble PlatformUtilities::LittleEndianLocalEndianDouble(UEDouble value)
    {
        return PlatformUtilities::s_IsBigEndian ? Uint64ToDouble(UE_BYTESWAP_64(DoubleToUint64(value))) : value;
    }

    UEUint16 PlatformUtilities::LocalEndianBigEndian16(UEUint16 value)
    {
        return PlatformUtilities::s_IsBigEndian ? value : UE_BYTESWAP_16(value);
    }

    UEUint32 PlatformUtilities::LocalEndianBigEndian32(UEUint32 value)
    {
        return PlatformUtilities::s_IsBigEndian ? value : UE_BYTESWAP_32(value);
    }

    UEUint64 PlatformUtilities::LocalEndianBigEndian64(UEUint64 value)
    {
        return PlatformUtilities::s_IsBigEndian ? value : UE_BYTESWAP_64(value);
    }

    UEFloat PlatformUtilities::LocalEndianBigEndianFloat(UEFloat value)
    {
        return PlatformUtilities::s_IsBigEndian ? value : Uint32ToFloat(UE_BYTESWAP_32(FloatToUint32(value)));
    }

    UEDouble PlatformUtilities::LocalEndianBigEndianDouble(UEDouble value)
    {
        return PlatformUtilities::s_IsBigEndian ? value : Uint64ToDouble(UE_BYTESWAP_64(DoubleToUint64(value)));
    }

    UEUint16 PlatformUtilities::LocalEndianLittleEndian16(UEUint16 value)
    {
        return PlatformUtilities::s_IsBigEndian ? UE_BYTESWAP_16(value) : value;
    }

    UEUint32 PlatformUtilities::LocalEndianLittleEndian32(UEUint32 value)
    {
        return PlatformUtilities::s_IsBigEndian ? UE_BYTESWAP_32(value) : value;
    }

    UEUint64 PlatformUtilities::LocalEndianLittleEndian64(UEUint64 value)
    {
        return PlatformUtilities::s_IsBigEndian ? UE_BYTESWAP_64(value) : value;
    }

    UEFloat PlatformUtilities::LocalEndianLittleEndianFloat(UEFloat value)
    {
        return PlatformUtilities::s_IsBigEndian ? Uint32ToFloat(UE_BYTESWAP_32(FloatToUint32(value))) : value;
    }

    UEDouble PlatformUtilities::LocalEndianLittleEndianDouble(UEDouble value)
    {
        return PlatformUtilities::s_IsBigEndian ? Uint64ToDouble(UE_BYTESWAP_64(DoubleToUint64(value))) : value;
    }

    UEUint16 PlatformUtilities::HostToNetwork16(UEUint16 value)
    {
        return PlatformUtilities::LocalEndianBigEndian16(value);
    }

    UEUint32 PlatformUtilities::HostToNetwork32(UEUint32 value)
    {
        return PlatformUtilities::LocalEndianBigEndian32(value);
    }

    UEUint64 PlatformUtilities::HostToNetwork64(UEUint64 value)
    {
        return PlatformUtilities::LocalEndianBigEndian64(value);
    }

    UEFloat PlatformUtilities::HostToNetworkFloat(UEFloat value)
    {
        return PlatformUtilities::LocalEndianBigEndianFloat(value);
    }

    UEDouble PlatformUtilities::HostToNetworkDouble(UEDouble value)
    {
        return PlatformUtilities::LocalEndianBigEndianDouble(value);
    }

    UEUint16 PlatformUtilities::NetworkToHost16(UEUint16 value)
    {
        return PlatformUtilities::BigEndianLocalEndian16(value);
    }

    UEUint32 PlatformUtilities::NetworkToHost32(UEUint32 value)
    {
        return PlatformUtilities::BigEndianLocalEndian32(value);
    }

    UEUint64 PlatformUtilities::NetworkToHost64(UEUint64 value)
    {
        return PlatformUtilities::BigEndianLocalEndian64(value);
    }

    UEFloat PlatformUtilities::NetworkToHostFloat(UEFloat value)
    {
        return PlatformUtilities::BigEndianLocalEndianFloat(value);
    }

    UEDouble PlatformUtilities::NetworkToHostDouble(UEDouble value)
    {
        return PlatformUtilities::BigEndianLocalEndianDouble(value);
    }
}
