#pragma once

#include "MathShared.hpp"

#include <string>

namespace agora
{
	namespace math
	{
		class Float3
		{
		public:
			a_FORCEINLINE Float3();
			a_FORCEINLINE explicit Float3(const float* arr);
			a_FORCEINLINE explicit Float3(float x, float y, float z);
			a_FORCEINLINE explicit Float3(float s);

			a_FORCEINLINE float getX() const;
			a_FORCEINLINE float getY() const;
			a_FORCEINLINE float getZ() const;

			a_FORCEINLINE void setX(float x);
			a_FORCEINLINE void setY(float y);
			a_FORCEINLINE void setZ(float z);

			a_FORCEINLINE const float* data() const; // for those who want to just access the data
			a_FORCEINLINE float* data(); // for those who want to tweak the data

			a_FORCEINLINE Float3 operator+(Float3 v) const;
			a_FORCEINLINE Float3 operator-(Float3 v) const;
			a_FORCEINLINE Float3 operator*(Float3 v) const;
			a_FORCEINLINE Float3 operator/(Float3 v) const;
			a_FORCEINLINE Float3 operator*(float s) const;
			a_FORCEINLINE Float3 operator/(float s) const;

			a_FORCEINLINE Float3& operator+=(Float3 v);
			a_FORCEINLINE Float3& operator-=(Float3 v);
			a_FORCEINLINE Float3& operator*=(Float3 v);
			a_FORCEINLINE Float3& operator/=(Float3 v);
			a_FORCEINLINE Float3& operator*=(float s);
			a_FORCEINLINE Float3& operator/= (float s);

		private:
			float m_data[3];
		};
		static_assert(sizeof(Float3) == 3 * sizeof(float), "Float3 can't have any padding");
	}
}

#include "Float3.inl"