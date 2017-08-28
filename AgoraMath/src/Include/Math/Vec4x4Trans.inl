static a_FORCEINLINE agora::math::Vec4x4 a_VCALL a_rotate_normalized(float rad, float x, float y, float z)
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

	return Vec4x4(
		Vec4((c + minusc * x * x), (minusc * xy - sz), (minusc * xz + sy), 0.f),
		Vec4((minusc * xy + sz), (c + minusc * y * y), (minusc * yz - sx), 0.f),
		Vec4((minusc * xz - sy), (minusc * yz + sx), (c + minusc * z * z), 0.f),
		Vec4(0.f, 0.f, 0.f, 1.f));
}

agora::math::Vec4x4 a_VCALL agora::math::rotate_v(float degrees, float x, float y, float z)
{
	float mag = 1 / sqrt(x * x + y * y + z * z);
	x *= mag;
	y *= mag;
	z *= mag;

	return a_rotate_normalized(radians(degrees), x, y, z);
}

agora::math::Vec4x4 a_VCALL agora::math::rotate_v(float degrees, Vec3 xyz)
{
	Float4 fl = cfloat4(normalize_v(xyz));
	return a_rotate_normalized(radians(degrees), fl.getX(), fl.getY(), fl.getZ());
}

agora::math::Vec4x4 a_VCALL agora::math::rotateX_v(float degrees)
{
	float rad = radians(degrees);
	float c = std::cosf(rad);
	float s = std::sinf(rad);

	return Vec4x4(
		Vec4(1, 0, 0, 0),
		Vec4(0, c, -s, 0),
		Vec4(0, s, c, 0),
		Vec4(0, 0, 0, 1));
}

agora::math::Vec4x4 a_VCALL agora::math::rotateY_v(float degrees)
{
	float rad = radians(degrees);
	float c = std::cosf(rad);
	float s = std::sinf(rad);

	return Vec4x4(
		Vec4(c, 0, s, 0),
		Vec4(0, 1, 0, 0),
		Vec4(-s, 0, c, 0),
		Vec4(0, 0, 0, 1));
}

agora::math::Vec4x4 a_VCALL agora::math::rotateZ_v(float degrees)
{
	float rad = radians(degrees);
	float c = std::cosf(rad);
	float s = std::sinf(rad);

	return Vec4x4(
		Vec4(c, -s, 0, 0),
		Vec4(s, c, 0, 0),
		Vec4(0, 0, 1, 0),
		Vec4(0, 0, 0, 1));
}

agora::math::Vec4x4 a_VCALL agora::math::translate_v(float x, float y, float z)
{
	return Vec4x4(
		Vec4(1, 0, 0, x),
		Vec4(0, 1, 0, y),
		Vec4(0, 0, 1, z),
		Vec4(0, 0, 0, 1));
}

agora::math::Vec4x4 a_VCALL agora::math::translate_v(Vec3 v)
{
	Float4 fl = cfloat4(v);
	return Vec4x4(
		Vec4(1, 0, 0, fl.getX()),
		Vec4(0, 1, 0, fl.getY()),
		Vec4(0, 0, 1, fl.getZ()),
		Vec4(0, 0, 0, 1));
}

agora::math::Vec4x4 a_VCALL agora::math::scale_v(float x, float y, float z)
{
	return Vec4x4(
		Vec4(x, 0, 0, 0),
		Vec4(0, y, 0, 0),
		Vec4(0, 0, z, 0),
		Vec4(0, 0, 0, 1));
}

agora::math::Vec4x4 a_VCALL agora::math::scale_v(float s)
{
	return Vec4x4(
		Vec4(s, 0, 0, 0),
		Vec4(0, s, 0, 0),
		Vec4(0, 0, s, 0),
		Vec4(0, 0, 0, 1));
}

agora::math::Vec4x4 a_VCALL agora::math::scale_v(Vec3 v)
{
	// shuffling should be faster than vec (though it might not really be)
	return Vec4x4(
		Vec4(_mm_shuffle_ps(v.data(), v.data(), _MM_SHUFFLE(3, 3, 3, 0))),
		Vec4(_mm_shuffle_ps(v.data(), v.data(), _MM_SHUFFLE(3, 3, 1, 3))),
		Vec4(_mm_shuffle_ps(v.data(), v.data(), _MM_SHUFFLE(3, 2, 3, 3))),
		Vec4(1, 0, 0, 0));
}

agora::math::Vec4x4 a_VCALL agora::math::perspective_v(float fov, float aspect, float near, float far)
{
	float div0 = 1 / std::tanf(radians(fov * 0.5));
	float div1 = 1 / (far - near);

	return Vec4x4(
		Vec4(div0 / aspect, 0, 0, 0),
		Vec4(0, div0, 0, 0),
		Vec4(0, 0, -(far + near) * div1, -1),
		Vec4(0, 0, -2 * far * near * div1, 0));
}

agora::math::Vec4x4 a_VCALL agora::math::orthographic_v(float width, float height, float near, float far)
{
	return Vec4x4(
		Vec4(2.f / width, 0, 0, 0),
		Vec4(0, 2.f / height, 0, 0),
		Vec4(0, 0, -2 / (far - near), 0),
		Vec4(0, 0, -(far + near) / (far - near), 1));
}

// TODO: figure out why some of the sings are off
agora::math::Vec4x4 a_VCALL agora::math::lookAt_v(Vec3 up, Vec3 pos, Vec3 target)
{
	Vec3 newZ = normalize_v(target - pos);
	Vec3 newX = normalize_v(cross_v(newZ, up));
	Vec3 newY = cross_v(newX, newZ);

	Vec3 newZneg = negate_v(newZ);

	Vec4x4 result(
		cvec4_0(newX),
		cvec4_0(newY),
		cvec4_0(newZneg),
		Vec4(0, 0, 0, 1));

	result = transpose_v(result); // transpose than do look at calculations:
	result.setRow3(Vec4(-dot_v(newX, pos), -dot_v(newY, pos), dot_v(newZ, pos), 1.f));
	return result;
}