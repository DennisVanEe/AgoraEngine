#include "vec_conv.hpp"
agora::math::Vec3 a_VCALL agora::math::cvec3(Vec4 v)
{
	__m128 temp = _mm_setzero_ps(); // zero the register (not really necessary, but VS will give error if unititalized, and zeros it regardless (if sdl is turned off)
	temp = _mm_cmpeq_ps(temp, temp); // set to all 1s
	temp = _mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(temp), 4)); // shift it by 4 (so last is 0)
	return Vec3(_mm_and_ps(temp, v.data())); // and it and return this result
}

agora::math::Vec4 a_VCALL agora::math::cvec4_0(Vec3 v)
{
	return Vec4(v.data());
}

agora::math::Vec4 a_VCALL agora::math::cvec4_1(Vec3 v)
{
	__m128i temp0 = _mm_setzero_si128(); // set to all zero
	temp0 = _mm_cmpeq_epi32(temp0, temp0); // set to all 1
	temp0 = _mm_slli_si128(temp0, 12); // shift left by 12 bytes (will be needed later)
	__m128i temp1 = _mm_slli_epi32(temp0, 25); // create 1.f
	temp1 = _mm_srli_epi32(temp1, 2);
	temp1 = _mm_and_si128(temp0, temp1);
	return Vec4(_mm_or_ps(v.data(), _mm_castsi128_ps(temp1)));
}

agora::math::Vec4 a_VCALL agora::math::cvec4(Vec3 v, float w)
{
	__m128 temp = _mm_move_ss(v.data(), _mm_set_ss(w));
	temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(0, 2, 1, 0));
	return Vec4(_mm_move_ss(temp, v.data()));
}

agora::math::Vec4 a_VCALL agora::math::zvec4()
{
	return Vec4(_mm_setzero_ps());
}

agora::math::Vec3 a_VCALL agora::math::zvec3()
{
	return Vec3(_mm_setzero_ps());
}