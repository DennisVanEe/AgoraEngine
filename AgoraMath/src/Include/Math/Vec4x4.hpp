#pragma once

#include "MathShared.hpp"
#include "Vec4.hpp"

namespace agora
{
	namespace math
	{
		// Row-Major Matrices
		class Vec4x4
		{
		public:
			a_FORCEINLINE Vec4x4();
			a_FORCEINLINE explicit Vec4x4(const float* arr); // row-major order
			a_FORCEINLINE explicit Vec4x4(const Vec4* vec);
			a_FORCEINLINE explicit Vec4x4(Vec4 r0, Vec4 r1, Vec4 r2, Vec4 r3);

			a_FORCEINLINE Vec4 a_VCALL operator*(Vec4 v) const;
			a_FORCEINLINE Vec4x4 a_VCALL operator*(Vec4x4 m) const;
			a_FORCEINLINE Vec4x4 a_VCALL operator*(float s) const;
			
			a_FORCEINLINE Vec4x4 a_VCALL operator+(Vec4x4 m) const;
			a_FORCEINLINE Vec4x4 a_VCALL operator+(float s) const;
			a_FORCEINLINE Vec4x4 a_VCALL operator-(Vec4x4 m) const;
			a_FORCEINLINE Vec4x4 a_VCALL operator-(float s) const;

			a_FORCEINLINE Vec4 a_VCALL getRow0() const;
			a_FORCEINLINE Vec4 a_VCALL getRow1() const;
			a_FORCEINLINE Vec4 a_VCALL getRow2() const;
			a_FORCEINLINE Vec4 a_VCALL getRow3() const;

			a_FORCEINLINE void a_VCALL setRow0(Vec4 r);
			a_FORCEINLINE void a_VCALL setRow1(Vec4 r);
			a_FORCEINLINE void a_VCALL setRow2(Vec4 r);
			a_FORCEINLINE void a_VCALL setRow3(Vec4 r);

			a_FORCEINLINE __m128* a_VCALL data();
			a_FORCEINLINE const __m128* a_VCALL data() const;

		private:
			Vec4 m_rows[4];
		};
		static_assert(sizeof(Vec4x4) == 4 * sizeof(__m128), "Vec4x4 can't have any padding");
	}
}

#include "Vec4x4.inl"