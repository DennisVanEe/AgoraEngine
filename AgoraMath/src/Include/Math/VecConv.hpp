#pragma once

#include "Vec4.hpp"
#include "Vec3.hpp"

namespace agora
{
	namespace math
	{
		a_FORCEINLINE Vec3 a_VCALL cvec3(Vec4 v);
		a_FORCEINLINE Vec4 a_VCALL cvec4_0(Vec3 v);
		a_FORCEINLINE Vec4 a_VCALL cvec4_1(Vec3 v);
		a_FORCEINLINE Vec4 a_VCALL cvec4(Vec3 v, float w);
		
		a_FORCEINLINE Vec4 a_VCALL zvec4();
		a_FORCEINLINE Vec3 a_VCALL zvec3();
	}
}

#include "VecConv.inl"