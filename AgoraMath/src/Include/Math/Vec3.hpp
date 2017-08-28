#pragma once

#include "MathShared.hpp"
#include "Vec4.hpp"

namespace agora
{
	namespace math
	{
		class Vec3
		{
		public:
			a_FORCEINLINE Vec3();
			a_FORCEINLINE explicit Vec3(const float* arr);
			a_FORCEINLINE explicit Vec3(float s);
			a_FORCEINLINE explicit Vec3(float x, float y, float z);

			a_FORCEINLINE float a_VCALL getX() const;
			a_FORCEINLINE float a_VCALL getY() const;
			a_FORCEINLINE float a_VCALL getZ() const;

			a_FORCEINLINE void a_VCALL setX(float x);
			a_FORCEINLINE void a_VCALL setY(float y);
			a_FORCEINLINE void a_VCALL setZ(float z);

			a_FORCEINLINE __m128 a_VCALL data() const; // not gauranteed to be const, for pro use

			a_FORCEINLINE Vec3 a_VCALL operator+(Vec3 v) const;
			a_FORCEINLINE Vec3 a_VCALL operator-(Vec3 v) const;
			a_FORCEINLINE Vec3 a_VCALL operator*(Vec3 v) const;
			a_FORCEINLINE Vec3 a_VCALL operator/(Vec3 v) const;
			a_FORCEINLINE Vec3 a_VCALL operator*(float s) const;
			a_FORCEINLINE Vec3 a_VCALL operator/(float s) const;

			a_FORCEINLINE Vec3& a_VCALL operator+=(Vec3 v);
			a_FORCEINLINE Vec3& a_VCALL operator-=(Vec3 v);
			a_FORCEINLINE Vec3& a_VCALL operator*=(Vec3 v);
			a_FORCEINLINE Vec3& a_VCALL operator/=(Vec3 v);
			a_FORCEINLINE Vec3& a_VCALL operator*=(float s);
			a_FORCEINLINE Vec3& a_VCALL operator/= (float s);

			a_FORCEINLINE float& operator[](size_t i);
			a_FORCEINLINE const float& operator[](size_t i) const;

		private:
			__m128 m_vector;
			a_FORCEINLINE explicit Vec3(__m128 vec); // gaurantees last element is always 0

			friend Vec3 a_VCALL cvec3(Vec4);
			friend Vec3 a_VCALL operator/(float, Vec3);
			friend Vec3 a_VCALL cross_v(Vec3 v1, Vec3 v2);
			friend Vec3 a_VCALL normalize_v(Vec3 v);
			friend Vec3 a_VCALL negate_v(Vec3 v);
			friend Vec3 a_VCALL zvec3();
		};
	}
}

#include "Vec3.inl"