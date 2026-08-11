#ifndef SUMO_TYPES_H
#define SUMO_TYPES_H

typedef signed char SumoS8;
typedef unsigned char SumoU8;
typedef signed short SumoS16;
typedef unsigned short SumoU16;
typedef signed int SumoS32;
typedef unsigned int SumoU32;
#if !defined(_MSC_VER)
typedef signed long long SumoS64;
typedef unsigned long long SumoU64;
#else
typedef signed __int64 SumoS64;
typedef unsigned __int64 SumoU64;
#endif
typedef float SumoF32;
typedef double SumoF64;

#if (defined(_WIN64) ||                                                        \
     (defined(__SIZEOF_POINTER__) && __SIZEOF_POINTER__ == 8))
typedef SumoS64 SumoIntPtr;
typedef SumoU64 SumoUIntPtr;
#else
typedef SumoS32 SumoIntPtr;
typedef SumoU32 SumoUIntPtr;
#endif

typedef unsigned char undefined;
typedef unsigned short undefined2;
typedef unsigned int undefined4;

#endif
