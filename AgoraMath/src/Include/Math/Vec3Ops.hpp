#pragma once

#include "MathShared.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"

namespace agora
{
	namespace math
	{
		a_FORCEINLINE Vec3 a_VCALL operator*(float, Vec3);
		a_FORCEINLINE Vec3 a_VCALL operator/(float, Vec3);

		a_FORCEINLINE Vec3 a_VCALL cross_v(Vec3 v1, Vec3 v2);
		a_FORCEINLINE Vec4 a_VCALL dotVec_v(Vec3 v1, Vec3 v2);
		a_FORCEINLINE float a_VCALL dot_v(Vec3 v1, Vec3 v2);
		
		a_FORCEINLINE Vec3 a_VCALL negate_v(Vec3 v);

		a_FORCEINLINE Vec3 a_VCALL normalize_v(Vec3 v);
		a_FORCEINLINE Vec4 a_VCALL lengthVec_v(Vec3 v);
		a_FORCEINLINE float a_VCALL length_v(Vec3 v);
	}
}

#include "Vec3Ops.inl"