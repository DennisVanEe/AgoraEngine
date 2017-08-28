#pragma once

#include "Float2.hpp"

namespace agora
{
	namespace math
	{
		a_FORCEINLINE Float2 operator*(float s, Float2 v);
		a_FORCEINLINE Float2 operator/(float s, Float2 v);

		a_FORCEINLINE float dot_f(Float2 v1, Float2 v2);
		a_FORCEINLINE Float2 dotVec_f(Float2 v1, Float2 v2);

		a_FORCEINLINE Float2 normalize_f(Float2 v);
	}
}

#include "Float2Ops.inl"