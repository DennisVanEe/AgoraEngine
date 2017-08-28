#pragma once

#include "Float3.hpp"

namespace agora
{
	namespace math
	{
		a_FORCEINLINE Float3 operator*(float s, Float3 v);
		a_FORCEINLINE Float3 operator/(float s, Float3 v);

		a_FORCEINLINE Float3 cross_f(Float3 v1, Float3 v2);

		a_FORCEINLINE float dot_f(Float3 v1, Float3 v2);
		a_FORCEINLINE Float3 dotVec_f(Float3 v1, Float3 v2);

		a_FORCEINLINE Float3 normalize_f(Float3 v);
	}
}

#include "Float3Ops.inl"