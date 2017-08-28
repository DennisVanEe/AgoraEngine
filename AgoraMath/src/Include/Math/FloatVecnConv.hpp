#pragma once

#include "Float4.hpp"
#include "Float3.hpp"
#include "Vec4.hpp"
#include "Vec3.hpp"

namespace agora
{
	namespace math
	{
		a_FORCEINLINE Float4 a_VCALL cfloat4(Vec4 v);
		a_FORCEINLINE Float4 a_VCALL cfloat4(Vec3 v);
		a_FORCEINLINE Float4 a_VCALL cfloat4(Vec3 v, float w);

		a_FORCEINLINE Float3 a_VCALL cfloat3(Vec4 v);
		a_FORCEINLINE Float3 a_VCALL cfloat3(Vec3 v);

		a_FORCEINLINE Vec4 a_VCALL Vec4(__m128 a);
		a_FORCEINLINE Vec4 a_VCALL Vec4(Float4 v);
		a_FORCEINLINE Vec4 a_VCALL Vec4(Float3 v);
		a_FORCEINLINE Vec4 a_VCALL Vec4(Float3 v, float w);

		a_FORCEINLINE Vec3 a_VCALL cvec3(Float4 v);
		a_FORCEINLINE Vec3 a_VCALL cvec3(Float3 v);
	}
}

#include "FloatVecnConv.inl"