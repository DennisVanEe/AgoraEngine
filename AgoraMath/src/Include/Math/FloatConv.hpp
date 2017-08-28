#pragma once

#include "Float3.hpp"
#include "Float4.hpp"

namespace agora
{
	namespace math
	{
		a_FORCEINLINE Float3 a_VCALL cfloat3(Float4 v);
		a_FORCEINLINE Float4 a_VCALL cfloat4_0(Float3 v);
		a_FORCEINLINE Float4 a_VCALL cfloat4_1(Float3 v);
		a_FORCEINLINE Float4 a_VCALL cfloat4(Float3 v, float w);

		a_FORCEINLINE Float4 a_VCALL zfloat4();
		a_FORCEINLINE Float3 a_VCALL zfloat3();
	}
}

#include "FloatConv.inl"