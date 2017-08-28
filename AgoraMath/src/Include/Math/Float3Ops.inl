agora::math::Float3 agora::math::operator*(float s, Float3 v)
{
	return v * s;
}

agora::math::Float3 agora::math::operator/(float s, Float3 v)
{
	Float3 result;
	result.setX(s / v.getX());
	result.setX(s / v.getY());
	result.setX(s / v.getZ());
	return result;
}

agora::math::Float3 agora::math::cross_f(Float3 v1, Float3 v2)
{
	return Float3(
		v1.getY() * v2.getZ() - v1.getZ() * v2.getY(),
		v1.getZ() * v2.getX() - v1.getX() * v2.getZ(),
		v1.getX() * v2.getY() - v1.getY() * v2.getX());
}

agora::math::Float3 agora::math::dotVec_f(Float3 v1, Float3 v2)
{
	float d = dot_f(v1, v2);
	return Float3(d, d, d);
}

float agora::math::dot_f(Float3 v1, Float3 v2)
{
	return v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ();
}

agora::math::Float3 agora::math::normalize_f(Float3 v)
{
	float recip = 1 / sqrt(dot_f(v, v));
	return recip * v;
}