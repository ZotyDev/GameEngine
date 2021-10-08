#pragma once

#define UE_IS_NATIVE_BIG_ENDIAN() __ue_is_native_big_endian()

#define UE_HTONS(number)		__ue_htons(number)
#define UE_HTONL(number)		__ue_htonl(number)
#define UE_HTONLL(number)		__ue_htonll(number)

#define UE_NTOHS(number)		__ue_ntohs(number)
#define UE_NTOHL(number)		__ue_ntohl(number)
#define UE_NTOHLL(number)		__ue_ntohll(number)

#define UE_UINT16_NTOH(number)	__ue_uint16_big_endian_to_local_endian(number)
#define UE_UINT16_HTON(number)	__ue_uint16_local_endian_to_big_endian(number)

#define UE_UINT32_NTOH(number)	__ue_uint32_big_endian_to_local_endian(number)
#define UE_UINT32_HTON(number)	__ue_uint32_local_endian_to_big_endian(number)

#define UE_UINT64_NTOH(number)	__ue_uint64_big_endian_to_local_endian(number)
#define UE_UINT64_HTON(number)	__ue_uint64_local_endian_to_big_endian(number)

#define UE_INT16_NTOH(number)	__ue_int16_big_endian_to_local_endian(number)
#define UE_INT16_HTON(number)	__ue_int16_local_endian_to_big_endian(number)

#define UE_INT32_NTOH(number)	__ue_int32_big_endian_to_local_endian(number)
#define UE_INT32_HTON(number)	__ue_int32_local_endian_to_big_endian(number)

#define UE_INT64_NTOH(number)	__ue_int64_big_endian_to_local_endian(number)
#define UE_INT64_HTON(number)	__ue_int64_local_endian_to_big_endian(number)

#define UE_FLOAT_NTOH(number)	__ue_float_big_endian_to_local_endian(number)
#define UE_FLOAT_HTON(number)	__ue_float_local_endian_to_big_endian(number)

#define UE_DOUBLE_NTOH(number)	__ue_double_big_endian_to_local_endian(number)
#define UE_DOUBLE_HTON(number)	__ue_double_local_endian_to_big_endian(number)

namespace UE
{
	constexpr bool __ue_is_native_big_endian();

	// type conversions
	unsigned long		__ue_float_to_uint32(float number);
	unsigned long long	__ue_double_to_uint64(double number);
	
	float				__ue_uint32_to_float(unsigned long number);
	double				__ue_uint64_to_double(unsigned long long number);

	// uint16 endianness conversions
	unsigned short		__ue_uint16_big_endian_to_local_endian(unsigned short number);
	unsigned short		__ue_uint16_little_endian_to_local_endian(unsigned short number);
	unsigned short		__ue_uint16_local_endian_to_big_endian(unsigned short number);
	unsigned short		__ue_uint16_local_endian_to_little_endian(unsigned short number);

	// uint32 endianness conversions
	unsigned long		__ue_uint32_big_endian_to_local_endian(unsigned long number);
	unsigned long		__ue_uint32_little_endian_to_local_endian(unsigned long number);
	unsigned long		__ue_uint32_local_endian_to_big_endian(unsigned long number);
	unsigned long		__ue_uint32_local_endian_to_little_endian(unsigned long number);

	// uint64 endainness conversions
	unsigned long long	__ue_uint64_big_endian_to_local_endian(unsigned long long number);
	unsigned long long	__ue_uint64_little_endian_to_local_endian(unsigned long long number);
	unsigned long long	__ue_uint64_local_endian_to_big_endian(unsigned long long number);
	unsigned long long	__ue_uint64_local_endian_to_little_endian(unsigned long long number);

	// int16 endianness conversions
	signed short		__ue_int16_big_endian_to_local_endian(signed short number);
	signed short		__ue_int16_little_endian_to_local_endian(signed short number);
	signed short		__ue_int16_local_endian_to_big_endian(signed short number);
	signed short		__ue_int16_local_endian_to_little_endian(signed short number);

	// int32 endianness conversions
	signed long			__ue_int32_big_endian_to_local_endian(signed long number);
	signed long			__ue_int32_little_endian_to_local_endian(signed long number);
	signed long			__ue_int32_local_endian_to_big_endian(signed long number);
	signed long			__ue_int32_local_endian_to_little_endian(signed long number);

	// int64 endainness conversions
	signed long long	__ue_int64_big_endian_to_local_endian(signed long long number);
	signed long long	__ue_int64_little_endian_to_local_endian(signed long long number);
	signed long long	__ue_int64_local_endian_to_big_endian(signed long long number);
	signed long long	__ue_int64_local_endian_to_little_endian(signed long long number);

	// float endianness conversions
	float				__ue_float_big_endian_to_local_endian(float number);
	float				__ue_float_little_endian_to_local_endian(float number);
	float				__ue_float_local_endian_to_big_endian(float number);
	float				__ue_float_local_endian_to_little_endian(float number);

	// double endianness conversions
	double				__ue_double_big_endian_to_local_endian(double number);
	double				__ue_double_little_endian_to_local_endian(double number);
	double				__ue_double_local_endian_to_big_endian(double number);
	double				__ue_double_local_endian_to_little_endian(double number);

	// network endianness conversions
	unsigned short		__ue_htons(unsigned short number);
	unsigned long		__ue_htonl(unsigned long number);
	unsigned long long	__ue_htonll(unsigned long number);

	unsigned short		__ue_ntohs(unsigned short number);
	unsigned long		__ue_ntohl(unsigned long number);
	unsigned long long	__ue_ntohll(unsigned long long number);
}