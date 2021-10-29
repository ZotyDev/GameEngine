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
	
	// type conversions
	unsigned long __ue_float_to_uint32(float number)
	{
		unsigned long newNumber = 0;
		float* newNumberPtr = reinterpret_cast<float*>(&newNumber);
		*newNumberPtr = static_cast<float>(number);

		return newNumber;
	}

	unsigned long long __ue_double_to_uint64(double number)
	{
		unsigned long long newNumber = 0;
		double* newNumberPtr = reinterpret_cast<double*>(&newNumber);
		*newNumberPtr = static_cast<double>(number);

		return newNumber;
	}


	float __ue_uint32_to_float(unsigned long number)
	{
		float newNumber = 0;
		unsigned long* newNumberPtr = reinterpret_cast<unsigned long*>(&newNumber);
		*newNumberPtr = static_cast<unsigned long>(number);

		return newNumber;
	}

	double __ue_uint64_to_double(unsigned long long number)
	{
		double newNumber = 0;
		unsigned long long* newNumberPtr = reinterpret_cast<unsigned long long*>(&newNumber);
		*newNumberPtr = static_cast<unsigned long long>(number);

		return newNumber;
	}

	// uint16 endianness conversions
	unsigned short __ue_uint16_big_endian_to_local_endian(unsigned short number)
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

	unsigned short __ue_uint16_little_endian_to_local_endian(unsigned short number)
	{
		if (!__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return UE_BYTESWAP_16(number);
		}
	}

	unsigned short __ue_uint16_local_endian_to_big_endian(unsigned short number)
	{
		return __ue_uint16_big_endian_to_local_endian(number);
	}

	unsigned short __ue_uint16_local_endian_to_little_endian(unsigned short number)
	{
		return __ue_uint16_little_endian_to_local_endian(number);
	}
	
	// uint32 endianness conversions
	unsigned long __ue_uint32_big_endian_to_local_endian(unsigned long number)
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

	unsigned long __ue_uint32_little_endian_to_local_endian(unsigned long number)
	{
		if (!__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return UE_BYTESWAP_32(number);
		}
	}

	unsigned long __ue_uint32_local_endian_to_big_endian(unsigned long number)
	{
		return __ue_uint32_big_endian_to_local_endian(number);
	}

	unsigned long __ue_uint32_local_endian_to_little_endian(unsigned long number)
	{
		return __ue_uint32_little_endian_to_local_endian(number);
	}

	// uint64 endianness conversions
	unsigned long long __ue_uint64_big_endian_to_local_endian(unsigned long long number)
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

	unsigned long long __ue_uint64_little_endian_to_local_endian(unsigned long long number)
	{
		if (!__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return UE_BYTESWAP_64(number);
		}
	}

	unsigned long long __ue_uint64_local_endian_to_big_endian(unsigned long long number)
	{
		return __ue_uint64_big_endian_to_local_endian(number);
	}

	unsigned long long __ue_uint64_local_endian_to_little_endian(unsigned long long number)
	{
		return __ue_uint64_little_endian_to_local_endian(number);
	}

	// int16 endianness conversions
	signed short __ue_int16_big_endian_to_local_endian(signed short number)
	{
		if (__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return (signed short)UE_BYTESWAP_16((unsigned short)number);
		}
	}

	signed short __ue_int16_little_endian_to_local_endian(signed short number)
	{
		if (!__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return (signed short)UE_BYTESWAP_16((unsigned short)number);
		}
	}

	signed short __ue_int16_local_endian_to_big_endian(signed short number)
	{
		return __ue_int16_big_endian_to_local_endian(number);
	}

	signed short __ue_int16_local_endian_to_little_endian(signed short number)
	{
		return __ue_int16_little_endian_to_local_endian(number);
	}

	// int32 endianness conversions
	signed long __ue_int32_big_endian_to_local_endian(signed long number)
	{
		if (__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return (signed long)UE_BYTESWAP_32((unsigned long)number);
		}
	}

	signed long __ue_int32_little_endian_to_local_endian(signed long number)
	{
		if (!__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return (signed long)UE_BYTESWAP_32((unsigned long)number);
		}
	}

	signed long __ue_int32_local_endian_to_big_endian(signed long number)
	{
		return __ue_int32_big_endian_to_local_endian(number);
	}

	signed long __ue_int32_local_endian_to_little_endian(signed long number)
	{
		return __ue_int32_little_endian_to_local_endian(number);
	}

	// int64 endainness conversions
	signed long long __ue_int64_big_endian_to_local_endian(signed long long number)
	{
		if (__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return (signed long long)UE_BYTESWAP_64((unsigned long long)number);
		}
	}

	signed long long __ue_int64_little_endian_to_local_endian(signed long long number)
	{
		if (!__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return (signed long long)UE_BYTESWAP_64((unsigned long long)number);
		}
	}

	signed long long __ue_int64_local_endian_to_big_endian(signed long long number)
	{
		return __ue_int64_big_endian_to_local_endian(number);
	}

	signed long long __ue_int64_local_endian_to_little_endian(signed long long number)
	{
		return __ue_int64_little_endian_to_local_endian(number);
	}

	// float endianness conversions
	float __ue_float_big_endian_to_local_endian(float number)
	{
		if (__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return __ue_uint32_to_float(UE_BYTESWAP_32(__ue_float_to_uint32(number)));
		}
	}

	float __ue_float_little_endian_to_local_endian(float number)
	{
		if (!__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return __ue_uint32_to_float(UE_BYTESWAP_32(__ue_float_to_uint32(number)));
		}
	}

	float __ue_float_local_endian_to_big_endian(float number)
	{
		return __ue_float_big_endian_to_local_endian(number);
	}

	float __ue_float_local_endian_to_little_endian(float number)
	{
		return __ue_float_little_endian_to_local_endian(number);
	}

	// double endianness conversions
	double __ue_double_big_endian_to_local_endian(double number)
	{
		if (__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return __ue_uint64_to_double(UE_BYTESWAP_64(__ue_double_to_uint64(number)));
		}
	}

	double __ue_double_little_endian_to_local_endian(double number)
	{
		if (!__ue_is_native_big_endian())
		{
			return number;
		}
		else
		{
			return __ue_uint64_to_double(UE_BYTESWAP_64(__ue_double_to_uint64(number)));
		}
	}

	double __ue_double_local_endian_to_big_endian(double number)
	{
		return __ue_double_big_endian_to_local_endian(number);
	}

	double __ue_double_local_endian_to_little_endian(double number)
	{
		return __ue_double_little_endian_to_local_endian(number);
	}

	// network endianness conversions
	unsigned short __ue_htons(unsigned short number)
	{
		return __ue_uint16_big_endian_to_local_endian(number);
	}
	
	unsigned long __ue_htonl(unsigned long number)
	{
		return __ue_uint32_big_endian_to_local_endian(number);
	}

	unsigned long long __ue_htonll(unsigned long number)
	{
		return __ue_uint64_big_endian_to_local_endian(number);
	}

	unsigned short __ue_ntohs(unsigned short number)
	{
		return __ue_uint16_local_endian_to_big_endian(number);
	}

	unsigned long __ue_ntohl(unsigned long number)
	{
		return __ue_uint32_local_endian_to_big_endian(number);
	}

	unsigned long long __ue_ntohll(unsigned long long number)
	{
		return __ue_uint64_local_endian_to_big_endian(number);
	}
}