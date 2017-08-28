#include "vec3.hpp"
agora::math::Vec3::Vec3()
{
}

agora::math::Vec3::Vec3(const float* arr) :
	m_vector(_mm_setr_ps(arr[0], arr[1], arr[2], 0.f))
{
}

agora::math::Vec3::Vec3(float x, float y, float z) :
	m_vector(_mm_setr_ps(x, y, z, 0.f))
{
}

agora::math::Vec3::Vec3(float s) :
	m_vector(_mm_setr_ps(s, s, s, 0.f))
{
}

agora::math::Vec3::Vec3(__m128 vec) :
	m_vector(vec)
{
}

float a_VCALL agora::math::Vec3::getX() const
{
	return _mm_cvtss_f32(m_vector);
}

float a_VCALL agora::math::Vec3::getY() const
{
	return _mm_cvtss_f32(_mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(1, 1, 1, 1)));
}

float a_VCALL agora::math::Vec3::getZ() const
{
	return _mm_cvtss_f32(_mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(2, 2, 2, 2)));
}

void a_VCALL agora::math::Vec3::setX(float x)
{
	m_vector = _mm_move_ss(m_vector, _mm_set_ss(x));
}

void a_VCALL agora::math::Vec3::setY(float y)
{
	__m128 temp = _mm_move_ss(m_vector, _mm_set_ss(y)); // set y to be the first one in the m_vector
	temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 2, 0, 0)); // move x "or y in this case" to the beginning 
	m_vector = _mm_move_ss(temp, m_vector); // override temp, so original x is still there, but now with new y and old z (and w)
}

void a_VCALL agora::math::Vec3::setZ(float z)
{
	__m128 temp = _mm_move_ss(m_vector, _mm_set_ss(z));
	temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 0, 1, 2));
	m_vector = _mm_move_ss(temp, m_vector);
}

__m128 a_VCALL agora::math::Vec3::data() const
{
	return m_vector;
}

agora::math::Vec3 a_VCALL agora::math::Vec3::operator+(Vec3 v) const
{
	return Vec3(_mm_add_ps(m_vector, v.m_vector));
}

agora::math::Vec3 a_VCALL agora::math::Vec3::operator-(Vec3 v) const
{
	return Vec3(_mm_sub_ps(m_vector, v.m_vector));
}

agora::math::Vec3 agora::math::Vec3::operator*(Vec3 v2) const
{
	return Vec3(_mm_mul_ps(m_vector, v2.m_vector));
}

agora::math::Vec3 a_VCALL agora::math::Vec3::operator/(Vec3 v) const
{
	return Vec3(_mm_div_ps(m_vector, v.m_vector));
}

agora::math::Vec3 a_VCALL agora::math::Vec3::operator*(float s) const
{
	return Vec3(_mm_mul_ps(m_vector, _mm_set1_ps(s)));
}


agora::math::Vec3 a_VCALL agora::math::Vec3::operator/(float s) const
{
	s = 1 / s;
	return Vec3(_mm_mul_ps(m_vector, _mm_set1_ps(s)));;
}

agora::math::Vec3& a_VCALL agora::math::Vec3::operator+=(Vec3 v)
{
	(*this) = (*this) + v;
	return (*this);
}

agora::math::Vec3& a_VCALL agora::math::Vec3::operator-=(Vec3 v)
{
	(*this) = (*this) - v;
	return (*this);
}


agora::math::Vec3& a_VCALL agora::math::Vec3::operator*=(Vec3 v)
{
	(*this) = (*this) * v;
	return (*this);
}


agora::math::Vec3& a_VCALL agora::math::Vec3::operator/=(Vec3 v)
{
	(*this) = (*this) / v;
	return (*this);
}


agora::math::Vec3& a_VCALL agora::math::Vec3::operator*=(float s)
{
	(*this) = (*this) * s;
	return (*this);
}


agora::math::Vec3& a_VCALL agora::math::Vec3::operator/=(float s)
{
	(*this) = (*this) / s;
	return (*this);
}

float& agora::math::Vec3::operator[](size_t i)
{
	return m_vector.m128_f32[i];
}

const float& agora::math::Vec3::operator[](size_t i) const
{
	return m_vector.m128_f32[i];
}
