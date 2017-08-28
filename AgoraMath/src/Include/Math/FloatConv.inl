#include "float_conv.hpp"
agora::math::Float3 a_VCALL agora::math::cfloat3(Float4 v)
{
	return Float3(v.getX(), v.getY(), v.getZ());
}

agora::math::Float4 a_VCALL agora::math::cfloat4_0(Float3 v)
{
	return Float4(v.getX(), v.getY(), v.getZ(), 0.f);
}

agora::math::Float4 a_VCALL agora::math::cfloat4_1(Float3 v)
{
	return Float4(v.getX(), v.getY(), v.getZ(), 1.f);
}

agora::math::Float4 a_VCALL agora::math::cfloat4(Float3 v, float w)
{
	return Float4(v.getX(), v.getY(), v.getZ(), w);
}

agora::math::Float4 a_VCALL agora::math::zfloat4()
{
	return Float4(0.f);
}

agora::math::Float3 a_VCALL agora::math::zfloat3()
{
	return Float3(0.f);
}