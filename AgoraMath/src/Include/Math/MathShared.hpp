#pragma once

#include <cmath>
#include <cstdint>
#include <cassert>

#if defined(_MSC_VER)
#	include <intrin.h>
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
#	include <x86intrin.h>
#else
static_assert(false, "The agora math library only supports x86-64 architectures.");
#endif

#if defined(_MSC_VER)
#	define a_FORCEINLINE __forceinline
#	define a_VCALL __vectorcall
#	define a_ALIGN16 __declspec(align(16))
#elif defined(__GNUC__)
#	define a_FORCEINLINE __attribute__((always_inline))
#	define a_ALING16 __attribute__((__aligned__(16)))
#	if defined (__clang__)
#		define a_VCALL __vectorcall
#	else
#		define a_VCALL
#	endif
#endif

namespace agora
{
	namespace math
	{
		const float A_PI = 3.14159265359f;

        a_FORCEINLINE float degrees(float rads);
        a_FORCEINLINE float radians(float deg);
	}
}

float agora::math::degrees(float rads)
{
	return rads * (180.f / A_PI);
}

float agora::math::radians(float deg)
{
	return deg * (A_PI / 180.f);
}