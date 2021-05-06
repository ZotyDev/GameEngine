#pragma once

#define UE_IS_NATIVE_BIG_ENDIAN() __ue_is_native_big_endian()
#define UE_HTONS(number) __ue_htons(number)
#define UE_HTONL(number) __ue_htonl(number)
#define UE_HTONLL(number) __ue_htonll(number)

#define UE_NTOHS(number) __ue_ntohs(number)
#define UE_NTOHL(number) __ue_ntohl(number)
#define UE_NTOHLL(number) __ue_ntohll(number)

namespace UE
{
	bool __ue_is_native_big_endian();
	
	unsigned short __ue_htons(unsigned short number);
	unsigned long __ue_htonl(unsigned long number);
	unsigned long long __ue_htonll(unsigned long number);

	unsigned short __ue_ntohs(unsigned short number);
	unsigned long __ue_ntohl(unsigned long number);
	unsigned long long __ue_ntohll(unsigned long long number);
}