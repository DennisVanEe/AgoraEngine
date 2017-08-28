#pragma once

#include "MathShared.hpp"
#include "Float4.hpp"
#include "Float4x4.hpp"
#include "Float4Ops.hpp"
#include "Float3Ops.hpp"
#include "VecConv.hpp"

namespace agora
{
	namespace math
	{
		a_FORCEINLINE Float4x4 a_VCALL rotate_f(float degrees, float x, float y, float z);
		a_FORCEINLINE Float4x4 a_VCALL rotate_f(float degrees, Float3 xyz);
		a_FORCEINLINE Float4x4 a_VCALL rotateX_f(float degrees);
		a_FORCEINLINE Float4x4 a_VCALL rotateY_f(float degrees);
		a_FORCEINLINE Float4x4 a_VCALL rotateZ_f(float degrees);

		a_FORCEINLINE Float4x4 a_VCALL translate_f(float x, float y, float z);
		a_FORCEINLINE Float4x4 a_VCALL translate_f(Float3 v);

		a_FORCEINLINE Float4x4 a_VCALL scale_f(float x, float y, float z);
		a_FORCEINLINE Float4x4 a_VCALL scale_f(float s);
		a_FORCEINLINE Float4x4 a_VCALL scale_f(Float3 v);

		a_FORCEINLINE Float4x4 a_VCALL perspective_f(float fov, float aspect, float near, float far);
		a_FORCEINLINE Float4x4 a_VCALL orthographic_f(float width, float height, float near, float far);
		a_FORCEINLINE Float4x4 a_VCALL lookAt_f(Float3 up, Float3 pos, Float3 target);
	}
}

#include "float4x4_trans.inl"