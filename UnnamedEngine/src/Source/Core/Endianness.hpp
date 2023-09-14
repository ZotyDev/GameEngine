////////////////////////////////////////////////////////////
// - Endianness Check
// Big-Endian Targets:
// > Sending Data over Network
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// - Big-Endian
////////////////////////////////////////////////////////////
#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN                      || \
    defined(__FLOAT_WORD_ORDER) && __FLOAT_WORD_ORDER == __ORDER_BIG_ENDIAN    || \
    defined(__BIG_ENDIAN)                                                      || \
    defined(__ARMEB__)                                                         || \
    defined(__THUMBEB__)                                                       || \
    defined(__AARCH64EB__)                                                     || \
    defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)               || \
    defined(_M_PPC)

    #define UE_BIG_ENDIAN
////////////////////////////////////////////////////////////
// - Little-Endian
////////////////////////////////////////////////////////////
#elif defined(__BYTE_ORDER) && __BYTE_ORDER == LITTLE_ENDIAN                   || \
    defined(__FLOAT_WORD_ORDER) && __FLOAT_WORD_ORDER == __ORDER_LITTLE_ENDIAN || \
    defined(__LITTLE_ENDIAN__)                                                 || \
    defined(__ARMEL__)                                                         || \
    defined(__THUMBEL__)                                                       || \
    defined(__AARCH64EL__)                                                     || \
    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)               || \
    defined(_M_IX86) || defined(_M_X64) || defined(_M_IA64) || defined(_M_ARM)

    #define UE_LITTLE_ENDIAN
#else
    #error "Unknown architecture endianness!"
#endif
