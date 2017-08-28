#include "vec4.hpp"
agora::math::Vec4::Vec4()
{
}

agora::math::Vec4::Vec4(const float* arr) :
	m_vector(_mm_load_ps(arr))
{
}

agora::math::Vec4::Vec4(float x, float y, float z, float w) :
	m_vector(_mm_set_ps(w, z, y, x))
{
}

agora::math::Vec4::Vec4(float s) :
	m_vector(_mm_set1_ps(s))
{
}

agora::math::Vec4::Vec4(__m128 vec) :
	m_vector(vec)
{
}

float a_VCALL agora::math::Vec4::getX() const
{
	return _mm_cvtss_f32(m_vector); // gets the lower float in the m_vector
}

float a_VCALL agora::math::Vec4::getY() const
{
	return _mm_cvtss_f32(_mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(1, 1, 1, 1)));
}

float a_VCALL agora::math::Vec4::getZ() const
{
	return _mm_cvtss_f32(_mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(2, 2, 2, 2)));
}

float a_VCALL agora::math::Vec4::getW() const
{
	return _mm_cvtss_f32(_mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(3, 3, 3, 3)));
}

void a_VCALL agora::math::Vec4::setX(float x)
{
	m_vector = _mm_move_ss(m_vector, _mm_set_ss(x));
}

void a_VCALL agora::math::Vec4::setY(float y)
{
	__m128 temp = _mm_move_ss(m_vector, _mm_set_ss(y)); // set y to be the first one in the m_vector
	temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 2, 0, 0)); // move x "or y in this case" to the beginning 
	m_vector = _mm_move_ss(temp, m_vector); // override temp, so original x is still there, but now with new y and old z (and w)
}

void a_VCALL agora::math::Vec4::setZ(float z)
{
	__m128 temp = _mm_move_ss(m_vector, _mm_set_ss(z));
	temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 0, 1, 2));
	m_vector = _mm_move_ss(temp, m_vector);
}

void a_VCALL agora::math::Vec4::setW(float w)
{
	__m128 temp = _mm_move_ss(m_vector, _mm_set_ss(w));
	temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(0, 2, 1, 0));
	m_vector = _mm_move_ss(temp, m_vector);
}

__m128 a_VCALL agora::math::Vec4::data() const
{
	return m_vector;
}

float& a_VCALL agora::math::Vec4::operator[](size_t i)
{
	return m_vector.m128_f32[i];
}

const float& a_VCALL agora::math::Vec4::operator[](size_t i) const
{
	return m_vector.m128_f32[i];
}

agora::math::Vec4 a_VCALL agora::math::Vec4::operator+(Vec4 v) const
{
	return Vec4(_mm_add_ps(m_vector, v.m_vector));
}

agora::math::Vec4 a_VCALL agora::math::Vec4::operator-(Vec4 v) const
{
	return Vec4(_mm_sub_ps(m_vector, v.m_vector));
}

agora::math::Vec4 agora::math::Vec4::operator*(Vec4 v2) const
{
	return Vec4(_mm_mul_ps(m_vector, v2.m_vector));
}

agora::math::Vec4 a_VCALL agora::math::Vec4::operator/(Vec4 v) const
{
	return Vec4(_mm_div_ps(m_vector, v.m_vector));
}

agora::math::Vec4 a_VCALL agora::math::Vec4::operator*(float s) const
{
	return Vec4(_mm_mul_ps(m_vector, _mm_set1_ps(s)));
}


agora::math::Vec4 a_VCALL agora::math::Vec4::operator/(float s) const
{
	s = 1 / s;
	return Vec4(_mm_mul_ps(m_vector, _mm_set1_ps(s)));;
}

agora::math::Vec4& a_VCALL agora::math::Vec4::operator+=(Vec4 v)
{
	(*this) = (*this) + v;
	return (*this);
}


agora::math::Vec4& a_VCALL agora::math::Vec4::operator-=(Vec4 v)
{
	(*this) = (*this) - v;
	return (*this);
}

agora::math::Vec4& a_VCALL agora::math::Vec4::operator*=(Vec4 v)
{
	(*this) = (*this) * v;
	return (*this);
}

agora::math::Vec4& a_VCALL agora::math::Vec4::operator/=(Vec4 v)
{
	(*this) = (*this) / v;
	return (*this);
}

agora::math::Vec4& a_VCALL agora::math::Vec4::operator*=(float s)
{
	(*this) = (*this) * s;
	return (*this);
}

agora::math::Vec4& a_VCALL agora::math::Vec4::operator/=(float s)
{
	(*this) = (*this) / s;
	return (*this);
}