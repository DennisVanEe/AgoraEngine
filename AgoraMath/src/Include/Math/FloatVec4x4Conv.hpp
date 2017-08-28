#pragma once

#include "MathShared.hpp"

#include "Float4x4Ops.hpp"
#include "Vec4x4Ops.hpp"
#include "FloatVecnConv.hpp"

namespace agora
{
	namespace math
	{
		a_FORCEINLINE Float4x4 a_VCALL cfloat4x4(Vec4x4 m);
		a_FORCEINLINE Vec4x4 a_VCALL cvec4x4(Float4x4 m);
	}
}

#include "FloatVec4x4Conv.inl"