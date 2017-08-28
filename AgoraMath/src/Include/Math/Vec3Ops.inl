agora::math::Vec3 a_VCALL agora::math::operator*(float s, Vec3 v)
{
	return v * s;
}

agora::math::Vec3 a_VCALL agora::math::operator/(float s, Vec3 v)
{
	__m128 ssss = _mm_set1_ps(s);
	return Vec3(_mm_div_ps(ssss, v.data()));
}

agora::math::Vec3 a_VCALL agora::math::cross_v(Vec3 v1, Vec3 v2)
{
	__m128 v1_yzx = _mm_shuffle_ps(v1.data(), v1.data(), _MM_SHUFFLE(3, 0, 2, 1));
	__m128 v2_yzx = _mm_shuffle_ps(v2.data(), v2.data(), _MM_SHUFFLE(3, 0, 2, 1));
	__m128 result0 = _mm_sub_ps(_mm_mul_ps(v1.data(), v2_yzx), _mm_mul_ps(v1_yzx, v2.data()));
	return Vec3(_mm_shuffle_ps(result0, result0, _MM_SHUFFLE(3, 0, 2, 1)));
}

agora::math::Vec4 a_VCALL agora::math::dotVec_v(Vec3 v1, Vec3 v2)
{
#if defined(__AVX__) || defined(__AVX2__)
	return Vec4(_mm_dp_ps(v1.data(), v2.data(), 0xff));
#else
	__m128 temp0 = _mm_mul_ps(v1.data(), v2.data());
	__m128 temp1 = _mm_hadd_ps(temp0, temp0);
	return Vec4(_mm_hadd_ps(temp1, temp1));
#endif
}

float a_VCALL agora::math::dot_v(Vec3 v1, Vec3 v2)
{
	return dotVec_v(v1, v2).getX();
}

agora::math::Vec3 a_VCALL agora::math::negate_v(Vec3 v)
{
	return Vec3(_mm_sub_ps(_mm_setzero_ps(), v.data()));
}

agora::math::Vec3 a_VCALL agora::math::normalize_v(Vec3 v)
{
	__m128 recip = _mm_rsqrt_ps(dotVec_v(v, v).data());
	return Vec3(_mm_mul_ps(recip, v.data()));
}

agora::math::Vec4 a_VCALL agora::math::lengthVec_v(Vec3 v)
{
	return Vec4(_mm_sqrt_ps(dotVec_v(v, v).data()));
}

float a_VCALL agora::math::length_v(Vec3 v)
{
	return lengthVec_v(v).getX();
}