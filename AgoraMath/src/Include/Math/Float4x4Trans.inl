static a_FORCEINLINE agora::math::Float4x4 a_VCALL a_rotate_normalized(float rad, float x, float y, float z)
{
	using namespace agora::math;

	// This is a helper function. This is the most efficient solution I can come up with at the momemnet.
	float c = std::cosf(rad);
	float s = std::sinf(rad);
	float minusc = 1 - c;

	float xy = x * y;
	float yz = y * z;
	float xz = x * z;

	float sx = s * x;
	float sy = s * y;
	float sz = s * z;

	return Float4x4(
		Float4((c + minusc * x * x), (minusc * xy - sz), (minusc * xz + sy), 0.f),
		Float4((minusc * xy + sz), (c + minusc * y * y), (minusc * yz - sx), 0.f),
		Float4((minusc * xz - sy), (minusc * yz + sx), (c + minusc * z * z), 0.f),
		Float4(0.f, 0.f, 0.f, 1.f));
}

agora::math::Float4x4 a_VCALL agora::math::rotate_f(float degrees, float x, float y, float z)
{
	float mag = 1 / sqrt(x * x + y * y + z * z);
	x *= mag;
	y *= mag;
	z *= mag;

	return a_rotate_normalized(radians(degrees), x, y, z);
}

agora::math::Float4x4 a_VCALL agora::math::rotate_f(float degrees, Float3 xyz)
{
	xyz = normalize_f(xyz);
	return a_rotate_normalized(radians(degrees), xyz.getX(), xyz.getY(), xyz.getZ());
}

agora::math::Float4x4 a_VCALL agora::math::rotateX_f(float degrees)
{
	float rad = radians(degrees);
	float c = std::cosf(rad);
	float s = std::sinf(rad);

	return Float4x4(
		Float4(1, 0, 0, 0),
		Float4(0, c, -s, 0),
		Float4(0, s, c, 0),
		Float4(0, 0, 0, 1));
}

agora::math::Float4x4 a_VCALL agora::math::rotateY_f(float degrees)
{
	float rad = radians(degrees);
	float c = std::cosf(rad);
	float s = std::sinf(rad);

	return Float4x4(
		Float4(c, 0, s, 0),
		Float4(0, 1, 0, 0),
		Float4(-s, 0, c, 0),
		Float4(0, 0, 0, 1));
}

agora::math::Float4x4 a_VCALL agora::math::rotateZ_f(float degrees)
{
	float rad = radians(degrees);
	float c = std::cosf(rad);
	float s = std::sinf(rad);

	return Float4x4(
		Float4(c, -s, 0, 0),
		Float4(s, c, 0, 0),
		Float4(0, 0, 1, 0),
		Float4(0, 0, 0, 1));
}

agora::math::Float4x4 a_VCALL agora::math::translate_f(float x, float y, float z)
{
	return Float4x4(
		Float4(1, 0, 0, x),
		Float4(0, 1, 0, y),
		Float4(0, 0, 1, z),
		Float4(0, 0, 0, 1));
}

agora::math::Float4x4 a_VCALL agora::math::translate_f(Float3 v)
{
	return Float4x4(
		Float4(1, 0, 0, v.getX()),
		Float4(0, 1, 0, v.getY()),
		Float4(0, 0, 1, v.getZ()),
		Float4(0, 0, 0, 1));
}

agora::math::Float4x4 a_VCALL agora::math::scale_f(float x, float y, float z)
{
	return Float4x4(
		Float4(x, 0, 0, 0),
		Float4(0, y, 0, 0),
		Float4(0, 0, z, 0),
		Float4(0, 0, 0, 1));
}

agora::math::Float4x4 a_VCALL agora::math::scale_f(float s)
{
	return Float4x4(
		Float4(s, 0, 0, 0),
		Float4(0, s, 0, 0),
		Float4(0, 0, s, 0),
		Float4(0, 0, 0, 1));
}

agora::math::Float4x4 a_VCALL agora::math::scale_f(Float3 v)
{
	// shuffling should be faster than vec (though it might not really be)
	return Float4x4(
		Float4(v.getX(), 0, 0, 0),
		Float4(0, v.getY(), 0, 0),
		Float4(0, 0, v.getZ(), 0),
		Float4(0, 0, 0, 1));
}

agora::math::Float4x4 a_VCALL agora::math::perspective_f(float fov, float aspect, float near, float far)
{
	float div0 = 1 / std::tanf(radians(fov * 0.5));
	float div1 = 1 / (far - near);

	return Float4x4(
		Float4(div0 / aspect, 0, 0, 0),
		Float4(0, div0, 0, 0),
		Float4(0, 0, -(far + near) * div1, -1),
		Float4(0, 0, -2 * far * near * div1, 0));
}

agora::math::Float4x4 a_VCALL agora::math::orthographic_f(float width, float height, float near, float far)
{
	return Float4x4(
		Float4(2.f / width, 0, 0, 0),
		Float4(0, 2.f / height, 0, 0),
		Float4(0, 0, -2 / (far - near), 0),
		Float4(0, 0, -(far + near) / (far - near), 1));
}

// TODO: figure out why some of the sings are off
agora::math::Float4x4 a_VCALL agora::math::lookAt_f(Float3 up, Float3 pos, Float3 target)
{
	Float3 newZ = normalize_f(target - pos);
	Float3 newX = normalize_f(cross_f(newZ, up));
	Float3 newY = cross_f(newX, newZ);

	return Float4x4(
		Float4(newX.getX(), newY.getX(), -newZ.getX(), 0),
		Float4(newX.getY(), newY.getY(), -newZ.getY(), 0),
		Float4(newX.getZ(), newY.getZ(), -newZ.getZ(), 0),
		Float4(-dot_f(newX, pos), -dot_f(newY, pos), dot_f(newZ, pos), 1.f));
}