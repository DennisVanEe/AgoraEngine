#include "vec4x4.hpp"
agora::math::Vec4x4::Vec4x4()
{
}

agora::math::Vec4x4::Vec4x4(const float* arr)
{
	m_rows[0] = Vec4(_mm_load_ps(arr));
	m_rows[1] = Vec4(_mm_load_ps(arr + 4));
	m_rows[2] = Vec4(_mm_load_ps(arr + 8));
	m_rows[4] = Vec4(_mm_load_ps(arr + 12));
}

agora::math::Vec4x4::Vec4x4(const Vec4* vec)
{
	m_rows[0] = vec[0];
	m_rows[1] = vec[1];
	m_rows[2] = vec[2];
	m_rows[3] = vec[3];
}

agora::math::Vec4x4::Vec4x4(Vec4 r0, Vec4 r1, Vec4 r2, Vec4 r3)
{
	m_rows[0] = r0;
	m_rows[1] = r1;
	m_rows[2] = r2;
	m_rows[3] = r3;
}

agora::math::Vec4 a_VCALL agora::math::Vec4x4::operator*(Vec4 v) const
{
	__m128 res0 = _mm_mul_ps(_mm_shuffle_ps(v.data(), v.data(), _MM_SHUFFLE(0, 0, 0, 0)), m_rows[0].data());
	__m128 res1 = _mm_mul_ps(_mm_shuffle_ps(v.data(), v.data(), _MM_SHUFFLE(1, 1, 1, 1)), m_rows[1].data());
	__m128 res2 = _mm_mul_ps(_mm_shuffle_ps(v.data(), v.data(), _MM_SHUFFLE(2, 2, 2, 2)), m_rows[2].data());
	__m128 res3 = _mm_mul_ps(_mm_shuffle_ps(v.data(), v.data(), _MM_SHUFFLE(3, 3, 3, 3)), m_rows[3].data());

	__m128 result = _mm_add_ps(res0, res1);
	result = _mm_add_ps(result, res2);
	return Vec4(_mm_add_ps(result, res3));
}

agora::math::Vec4x4 a_VCALL agora::math::Vec4x4::operator*(Vec4x4 m) const
{
	Vec4x4 result;

	{
		__m128 res0 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[0].data(), m.m_rows[0].data(), _MM_SHUFFLE(0, 0, 0, 0)), m_rows[0].data());
		__m128 res1 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[0].data(), m.m_rows[0].data(), _MM_SHUFFLE(1, 1, 1, 1)), m_rows[1].data());
		__m128 res2 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[0].data(), m.m_rows[0].data(), _MM_SHUFFLE(2, 2, 2, 2)), m_rows[2].data());
		__m128 res3 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[0].data(), m.m_rows[0].data(), _MM_SHUFFLE(3, 3, 3, 3)), m_rows[3].data());

		result.m_rows[0] = Vec4(_mm_add_ps(res0, res1));
		result.m_rows[0] = Vec4(_mm_add_ps(result.m_rows[0].data(), res2));
		result.m_rows[0] = Vec4(_mm_add_ps(result.m_rows[0].data(), res3));
	}

	{
		__m128 res0 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[1].data(), m.m_rows[1].data(), _MM_SHUFFLE(0, 0, 0, 0)), m_rows[0].data());
		__m128 res1 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[1].data(), m.m_rows[1].data(), _MM_SHUFFLE(1, 1, 1, 1)), m_rows[1].data());
		__m128 res2 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[1].data(), m.m_rows[1].data(), _MM_SHUFFLE(2, 2, 2, 2)), m_rows[2].data());
		__m128 res3 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[1].data(), m.m_rows[1].data(), _MM_SHUFFLE(3, 3, 3, 3)), m_rows[3].data());

		result.m_rows[0] = Vec4(_mm_add_ps(res0, res1));
		result.m_rows[0] = Vec4(_mm_add_ps(result.m_rows[1].data(), res2));
		result.m_rows[0] = Vec4(_mm_add_ps(result.m_rows[1].data(), res3));
	}

	{
		__m128 res0 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[2].data(), m.m_rows[2].data(), _MM_SHUFFLE(0, 0, 0, 0)), m_rows[0].data());
		__m128 res1 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[2].data(), m.m_rows[2].data(), _MM_SHUFFLE(1, 1, 1, 1)), m_rows[1].data());
		__m128 res2 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[2].data(), m.m_rows[2].data(), _MM_SHUFFLE(2, 2, 2, 2)), m_rows[2].data());
		__m128 res3 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[2].data(), m.m_rows[2].data(), _MM_SHUFFLE(3, 3, 3, 3)), m_rows[3].data());

		result.m_rows[2] = Vec4(_mm_add_ps(res0, res1));
		result.m_rows[2] = Vec4(_mm_add_ps(result.m_rows[0].data(), res2));
		result.m_rows[2] = Vec4(_mm_add_ps(result.m_rows[0].data(), res3));
	}

	{
		__m128 res0 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[3].data(), m.m_rows[3].data(), _MM_SHUFFLE(0, 0, 0, 0)), m_rows[0].data());
		__m128 res1 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[3].data(), m.m_rows[3].data(), _MM_SHUFFLE(1, 1, 1, 1)), m_rows[1].data());
		__m128 res2 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[3].data(), m.m_rows[3].data(), _MM_SHUFFLE(2, 2, 2, 2)), m_rows[2].data());
		__m128 res3 = _mm_mul_ps(_mm_shuffle_ps(m.m_rows[3].data(), m.m_rows[3].data(), _MM_SHUFFLE(3, 3, 3, 3)), m_rows[3].data());

		result.m_rows[3] = Vec4(_mm_add_ps(res0, res1));
		result.m_rows[3] = Vec4(_mm_add_ps(result.m_rows[3].data(), res2));
		result.m_rows[3] = Vec4(_mm_add_ps(result.m_rows[3].data(), res3));
	}

	return result;
}

agora::math::Vec4x4 a_VCALL agora::math::Vec4x4::operator*(float s) const
{
	Vec4 ssss(_mm_set1_ps(s));

	return Vec4x4(
		m_rows[0] * ssss,
		m_rows[1] * ssss,
		m_rows[2] * ssss,
		m_rows[3] * ssss);
}

agora::math::Vec4x4 a_VCALL agora::math::Vec4x4::operator+(Vec4x4 m) const
{
	return Vec4x4(
		m_rows[0] + m.m_rows[0],
		m_rows[1] + m.m_rows[1],
		m_rows[2] + m.m_rows[2],
		m_rows[3] + m.m_rows[3]);
}

agora::math::Vec4x4 a_VCALL agora::math::Vec4x4::operator+(float s) const
{
	Vec4 ssss = Vec4(_mm_set1_ps(s));

	return Vec4x4(
		m_rows[0] + ssss,
		m_rows[1] + ssss,
		m_rows[2] + ssss,
		m_rows[3] + ssss);
}

agora::math::Vec4x4 a_VCALL agora::math::Vec4x4::operator-(Vec4x4 m) const
{
	return Vec4x4(
		m_rows[0] - m.m_rows[0],
		m_rows[1] - m.m_rows[1],
		m_rows[2] - m.m_rows[2],
		m_rows[3] - m.m_rows[3]);
}

agora::math::Vec4x4 a_VCALL agora::math::Vec4x4::operator-(float s) const
{
	Vec4 ssss(s);

	return Vec4x4(
		m_rows[0] - ssss,
		m_rows[1] - ssss,
		m_rows[2] - ssss,
		m_rows[3] - ssss);
}

agora::math::Vec4 a_VCALL agora::math::Vec4x4::getRow0() const
{
	return m_rows[0];
}

agora::math::Vec4 a_VCALL agora::math::Vec4x4::getRow1() const
{
	return m_rows[1];
}

agora::math::Vec4 a_VCALL agora::math::Vec4x4::getRow2() const
{
	return m_rows[2];
}

agora::math::Vec4 a_VCALL agora::math::Vec4x4::getRow3() const
{
	return m_rows[3];
}

void a_VCALL agora::math::Vec4x4::setRow0(Vec4 r)
{
	m_rows[0] = r;
}

void a_VCALL agora::math::Vec4x4::setRow1(Vec4 r)
{
	m_rows[1] = r;
}

void a_VCALL agora::math::Vec4x4::setRow2(Vec4 r)
{
	m_rows[2] = r;
}

void a_VCALL agora::math::Vec4x4::setRow3(Vec4 r)
{
	m_rows[3] = r;
}

__m128 *a_VCALL agora::math::Vec4x4::data()
{
	return reinterpret_cast<__m128*>(&m_rows[0]);
}

const __m128 *a_VCALL agora::math::Vec4x4::data() const
{
	return reinterpret_cast<const __m128*>(&m_rows[0]);
}
