#pragma once

#include "MathShared.hpp"
#include "Float4.hpp"

#include <string>
#include <sstream>
#include <iostream>

namespace agora
{
	namespace math
	{
		a_FORCEINLINE Float4 operator*(float s, Float4 v);
		a_FORCEINLINE Float4 operator/(float s, Float4 v);

		a_FORCEINLINE Float4 cross_f(Float4 v1, Float4 v2);

		a_FORCEINLINE float dot_f(Float4 v1, Float4 v2);
		a_FORCEINLINE Float4 dotVec_f(Float4 v1, Float4 v2);

		a_FORCEINLINE Float4 normalize_f(Float4 v);
	}
}

#include "Float4Ops.inl"