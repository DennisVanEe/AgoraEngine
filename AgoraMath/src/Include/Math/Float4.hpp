#pragma once

#include "MathShared.hpp"

#include <string>

namespace agora
{
	namespace math
	{
		class Float4
		{
		public:
			a_FORCEINLINE Float4();
			a_FORCEINLINE explicit Float4(const float* arr);
			a_FORCEINLINE explicit Float4(float x, float y, float z, float w);
			a_FORCEINLINE explicit Float4(float s);

			a_FORCEINLINE float getX() const;
			a_FORCEINLINE float getY() const;
			a_FORCEINLINE float getZ() const;
			a_FORCEINLINE float getW() const;

			a_FORCEINLINE void setX(float x);
			a_FORCEINLINE void setY(float y);
			a_FORCEINLINE void setZ(float z);
			a_FORCEINLINE void setW(float w);

			a_FORCEINLINE const float* data() const;
			a_FORCEINLINE float* data();

			// Some operators:
			a_FORCEINLINE Float4 operator+(Float4 v) const;
			a_FORCEINLINE Float4 operator-(Float4 v) const;
			a_FORCEINLINE Float4 operator*(Float4 v) const;
			a_FORCEINLINE Float4 operator/(Float4 v) const;
			a_FORCEINLINE Float4 operator*(float s) const;
			a_FORCEINLINE Float4 operator/(float s) const;

			a_FORCEINLINE Float4& operator+=(Float4 v);
			a_FORCEINLINE Float4& operator-=(Float4 v);
			a_FORCEINLINE Float4& operator*=(Float4 v);
			a_FORCEINLINE Float4& operator/=(Float4 v);
			a_FORCEINLINE Float4& operator*=(float s);
			a_FORCEINLINE Float4& operator/= (float s);

		private:
			float m_data[4];
		};
		static_assert(sizeof(Float4) == 4 * sizeof(float), "Float4 can't have any padding");
	}
}

#include "Float4.inl"