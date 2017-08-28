#pragma once

#include "MathShared.hpp"
#include "Vec4x4.hpp"

#include <string>
#include <sstream>

namespace agora
{
	namespace math
	{
		a_FORCEINLINE Vec4x4 a_VCALL identity_v();
		a_FORCEINLINE Vec4x4 a_VCALL transpose_v(Vec4x4 m);
		a_FORCEINLINE Vec4x4 a_VCALL inverse_v(Vec4x4 m);

		a_FORCEINLINE Vec4x4 a_VCALL operator*(float s, Vec4x4 m);
		a_FORCEINLINE Vec4x4 a_VCALL operator+(float s, Vec4x4 m);
		a_FORCEINLINE Vec4x4 a_VCALL operator-(float s, Vec4x4 m);
	}
}

#include "Vec4x4Ops.inl"