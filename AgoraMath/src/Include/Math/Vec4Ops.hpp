#pragma once

#include "MathShared.hpp"
#include "Vec4.hpp"

namespace agora
{
	namespace math
	{
		a_FORCEINLINE Vec4 a_VCALL operator*(float, Vec4);
		a_FORCEINLINE Vec4 a_VCALL operator/(float, Vec4);

		a_FORCEINLINE Vec4 a_VCALL cross_v(Vec4 v1, Vec4 v2);
		a_FORCEINLINE Vec4 a_VCALL dotVec_v(Vec4 v1, Vec4 v2);
		a_FORCEINLINE float a_VCALL dot_v(Vec4 v1, Vec4 v2);

		a_FORCEINLINE Vec4 a_VCALL negate_v(Vec4 v);

		a_FORCEINLINE Vec4 a_VCALL normalize_v(Vec4 v);
		a_FORCEINLINE Vec4 a_VCALL lengthVec_v(Vec4 v);
		a_FORCEINLINE float a_VCALL length_v(Vec4 v);
	}
}

#include "Vec4Ops.inl"