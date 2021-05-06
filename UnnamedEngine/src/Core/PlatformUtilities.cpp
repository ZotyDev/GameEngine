#include "uepch.h"
#include "Core/PlatformUtilities.h"

namespace UE
{
	bool __ue_is_native_big_endian()
	{
		int num = 1;
		if (*(char*)&num == 1)
		{
			return false;
		}
		else
		{
			return true;
		} 
	}
	
	unsigned short __ue_htons(unsigned short number)
	{
		if (__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return UE_BYTESWAP_16(number);
		}
	}
	
	unsigned long __ue_htonl(unsigned long number)
	{
		if (__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return UE_BYTESWAP_32(number);
		}
	}

	unsigned long long __ue_htonll(unsigned long number)
	{
		if (__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return UE_BYTESWAP_64(number);
		}
	}

	unsigned short __ue_ntohs(unsigned short number)
	{
		if (__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return UE_BYTESWAP_16(number);
		}
	}

	unsigned long __ue_ntohl(unsigned long number)
	{
		if (__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return UE_BYTESWAP_32(number);
		}
	}

	unsigned long long __ue_ntohll(unsigned long long number)
	{
		if (__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return UE_BYTESWAP_64(number);
		}
	}
}