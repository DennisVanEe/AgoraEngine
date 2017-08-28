#pragma once

#include "MathShared.hpp"

namespace agora
{
	namespace math
	{
		class Float2
		{
		public:
			a_FORCEINLINE Float2();
			a_FORCEINLINE explicit Float2(const float* arr);
			a_FORCEINLINE explicit Float2(float x, float y);
			a_FORCEINLINE explicit Float2(float s);

			a_FORCEINLINE float getX() const;
			a_FORCEINLINE float getY() const;

			a_FORCEINLINE void setX(float x);
			a_FORCEINLINE void setY(float y);

			a_FORCEINLINE const float* data() const; // for those who want to just access the data
			a_FORCEINLINE float* data(); // for those who want to tweak the data

			a_FORCEINLINE Float2 operator+(Float2 v) const;
			a_FORCEINLINE Float2 operator-(Float2 v) const;
			a_FORCEINLINE Float2 operator*(Float2 v) const;
			a_FORCEINLINE Float2 operator/(Float2 v) const;
			a_FORCEINLINE Float2 operator*(float s) const;
			a_FORCEINLINE Float2 operator/(float s) const;

			a_FORCEINLINE Float2& operator+=(Float2 v);
			a_FORCEINLINE Float2& operator-=(Float2 v);
			a_FORCEINLINE Float2& operator*=(Float2 v);
			a_FORCEINLINE Float2& operator/=(Float2 v);
			a_FORCEINLINE Float2& operator*=(float s);
			a_FORCEINLINE Float2& operator/= (float s);

		private:
			float m_data[2];
		};
		static_assert(sizeof(Float2) == 2 * sizeof(float), "Float2 can't have any padding");
	}
}

#include "Float2.inl"