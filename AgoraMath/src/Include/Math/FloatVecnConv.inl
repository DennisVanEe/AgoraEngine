agora::math::Float4 a_VCALL agora::math::cfloat4(Vec4 v)
{
	Float4 result;
	_mm_store_ps(result.data(), v.data());
	return result;
}

agora::math::Float4 a_VCALL agora::math::cfloat4(Vec3 v)
{
	Float4 result;
	_mm_store_ps(result.data(), v.data());
	return result;
}

agora::math::Float4 a_VCALL agora::math::cfloat4(Vec3 v, float w)
{
	Float4 result;
	_mm_store_ps(result.data(), v.data());
	result.setW(w);
	return result;
}

agora::math::Float3 a_VCALL agora::math::cfloat3(Vec4 v)
{
	float temp[4];
	_mm_store_ps(temp, v.data());
	return Float3(temp);
}

agora::math::Float3 a_VCALL agora::math::cfloat3(Vec3 v)
{
	float temp[4];
	_mm_store_ps(temp, v.data());
	return Float3(temp);
}

agora::math::Vec4 a_VCALL agora::math::Vec4(Float4 v)
{
	return Vec4(v.data());
}

agora::math::Vec4 a_VCALL agora::math::Vec4(Float3 v)
{
	return Vec4(v.getX(), v.getY(), v.getZ(), 0.f);
}

agora::math::Vec4 a_VCALL agora::math::Vec4(Float3 v, float w)
{
	return Vec4(v.getX(), v.getY(), v.getZ(), w);
}

agora::math::Vec3 a_VCALL agora::math::cvec3(Float4 v)
{
	return Vec3(v.data());
}

agora::math::Vec3 a_VCALL agora::math::cvec3(Float3 v)
{
	return Vec3(v.data());
}

agora::math::Vec4 a_VCALL agora::math::Vec4(__m128 vec)
{
	return Vec4(vec);
}