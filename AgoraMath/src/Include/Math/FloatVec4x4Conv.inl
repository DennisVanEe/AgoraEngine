agora::math::Float4x4 a_VCALL agora::math::cfloat4x4(Vec4x4 m)
{
	return Float4x4(
		cfloat4(m.getRow0()),
		cfloat4(m.getRow1()),
		cfloat4(m.getRow2()),
		cfloat4(m.getRow3()));
}

agora::math::Vec4x4 a_VCALL agora::math::cvec4x4(Float4x4 m)
{
	// faster to store first than transpose using simd
	// one expects the result in row-major order, the other in col-major order
	return Vec4x4(m.data());
}