#pragma once

#include "MathShared.hpp"
#include "Float4.hpp"
#include "Vec4x4Ops.hpp"
#include "Vec4Ops.hpp"
#include "Vec3Ops.hpp"
#include "VecConv.hpp"
#include "FloatVecnConv.hpp"

namespace agora
{
	namespace math
	{
		a_FORCEINLINE Vec4x4 a_VCALL rotate_v(float degrees, float x, float y, float z);
		a_FORCEINLINE Vec4x4 a_VCALL rotate_v(float degrees, Vec3 xyz);
		a_FORCEINLINE Vec4x4 a_VCALL rotateX_v(float degrees);
		a_FORCEINLINE Vec4x4 a_VCALL rotateY_v(float degrees);
		a_FORCEINLINE Vec4x4 a_VCALL rotateZ_v(float degrees);
		
		a_FORCEINLINE Vec4x4 a_VCALL translate_v(float x, float y, float z);
		a_FORCEINLINE Vec4x4 a_VCALL translate_v(Vec3 v);
	
		a_FORCEINLINE Vec4x4 a_VCALL scale_v(float x, float y, float z);
		a_FORCEINLINE Vec4x4 a_VCALL scale_v(float s);
		a_FORCEINLINE Vec4x4 a_VCALL scale_v(Vec3 v);

		a_FORCEINLINE Vec4x4 a_VCALL perspective_v(float fov, float aspect, float near, float far);
		a_FORCEINLINE Vec4x4 a_VCALL orthographic_v(float width, float height, float near, float far);
		a_FORCEINLINE Vec4x4 a_VCALL lookAt_v(Vec3 up, Vec3 pos, Vec3 target);
	}
}

#include "Vec4x4Trans.inl"