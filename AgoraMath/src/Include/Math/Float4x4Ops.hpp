#pragma once

#include "MathShared.hpp"
#include "Float4x4.hpp"

#include <string>
#include <sstream>

namespace agora
{
	namespace math
	{
		a_FORCEINLINE Float4x4 identity_f();

		a_FORCEINLINE Float4x4 a_VCALL transpose_f(Float4x4 m);
		a_FORCEINLINE Float4x4 a_VCALL inverse_f(Float4x4 m);

		a_FORCEINLINE Float4x4 a_VCALL operator*(float s, Float4x4 m);
		a_FORCEINLINE Float4x4 a_VCALL operator*(Float4x4 m0, Float4x4 m1);
	}
}

#include "Float4x4Ops.inl"