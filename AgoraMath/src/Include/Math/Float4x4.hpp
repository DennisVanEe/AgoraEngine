#pragma once

#include "MathShared.hpp"
#include "float4.hpp"
#include "vec4.hpp"
#include "Float4Ops.hpp"
#include "FloatVecnConv.hpp"

namespace agora
{
	namespace math
	{
		class Float4x4
		{
		public:
			a_FORCEINLINE Float4x4();
			a_FORCEINLINE explicit Float4x4(const float* arr);
			a_FORCEINLINE explicit Float4x4(const Float4* arr);
			a_FORCEINLINE explicit Float4x4(Float4 r0, Float4 r1, Float4 r2, Float4 r3);

			a_FORCEINLINE void a_VCALL setRow0(Float4 r);
			a_FORCEINLINE void a_VCALL setRow1(Float4 c);
			a_FORCEINLINE void a_VCALL setRow2(Float4 c);
			a_FORCEINLINE void a_VCALL setRow3(Float4 c);

			a_FORCEINLINE Float4 a_VCALL getRow0() const;
			a_FORCEINLINE Float4 a_VCALL getRow1() const;
			a_FORCEINLINE Float4 a_VCALL getRow2() const;
			a_FORCEINLINE Float4 a_VCALL getRow3() const;

			a_FORCEINLINE Float4 operator*(Float4 v) const;
			a_FORCEINLINE Float4x4 a_VCALL operator*(float s) const;

			a_FORCEINLINE const float* data() const;
			a_FORCEINLINE float* data();

		private:
			Float4 m_rows[4];
		};
		static_assert(sizeof(Float4x4) == 16 * sizeof(float), "Float4x4 can't have any padding");
	}
}

#include "Float4x4.inl"