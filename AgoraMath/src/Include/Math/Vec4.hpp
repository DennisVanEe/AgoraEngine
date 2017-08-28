#pragma once

#include "MathShared.hpp"

namespace agora
{
	namespace math
	{
		class Vec4
		{
		public:
			a_FORCEINLINE Vec4();
			a_FORCEINLINE explicit Vec4(const float* arr);
			a_FORCEINLINE explicit Vec4(float x, float y, float z, float w);
			a_FORCEINLINE explicit Vec4(float s);
			a_FORCEINLINE explicit Vec4(__m128 vec);

			a_FORCEINLINE float a_VCALL getX() const;
			a_FORCEINLINE float a_VCALL getY() const;
			a_FORCEINLINE float a_VCALL getZ() const;
			a_FORCEINLINE float a_VCALL getW() const;

			a_FORCEINLINE void a_VCALL setX(float x);
			a_FORCEINLINE void a_VCALL setY(float y);
			a_FORCEINLINE void a_VCALL setZ(float z);
			a_FORCEINLINE void a_VCALL setW(float w);

			// Some operators:
			a_FORCEINLINE Vec4 a_VCALL operator+(Vec4 v) const;
			a_FORCEINLINE Vec4 a_VCALL operator-(Vec4 v) const;
			a_FORCEINLINE Vec4 a_VCALL operator*(Vec4 v) const;
			a_FORCEINLINE Vec4 a_VCALL operator/(Vec4 v) const;
			a_FORCEINLINE Vec4 a_VCALL operator*(float s) const;
			a_FORCEINLINE Vec4 a_VCALL operator/(float s) const;

			a_FORCEINLINE Vec4& a_VCALL operator+=(Vec4 v);
			a_FORCEINLINE Vec4& a_VCALL operator-=(Vec4 v);
			a_FORCEINLINE Vec4& a_VCALL operator*=(Vec4 v);
			a_FORCEINLINE Vec4& a_VCALL operator/=(Vec4 v);
			a_FORCEINLINE Vec4& a_VCALL operator*=(float s);
			a_FORCEINLINE Vec4& a_VCALL operator/= (float s);

			a_FORCEINLINE __m128 a_VCALL data() const; // not gauranteed to be const, for pro use

			a_FORCEINLINE float& a_VCALL operator[](size_t i);
			a_FORCEINLINE const float& a_VCALL operator[](size_t i) const;

		private:
			__m128 m_vector;
		};
	}
}

#include "Vec4.inl"