agora::math::Float4 agora::math::operator*(float s, Float4 v)
{
	return v * s;
}

agora::math::Float4 agora::math::operator/(float s, Float4 v)
{
	Float4 result;
	result.setX(s / v.getX());
	result.setY(s / v.getY());
	result.setZ(s / v.getZ());
	result.setW(s / v.getW());
	return result;
}

agora::math::Float4 agora::math::cross_f(Float4 v1, Float4 v2)
{
	return Float4(
		v1.getY() * v2.getZ() - v1.getZ() * v2.getY(),
		v1.getZ() * v2.getX() - v1.getX() * v2.getZ(),
		v1.getX() * v2.getY() - v1.getY() * v2.getX(),
		0.f); // the result has to be a vector
}

agora::math::Float4 agora::math::dotVec_f(Float4 v1, Float4 v2)
{
	float d = dot_f(v1, v2);
	return Float4(d, d, d, d);
}

float agora::math::dot_f(Float4 v1, Float4 v2)
{
	return v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ() +
		v1.getW() * v2.getW();
}

agora::math::Float4 agora::math::normalize_f(Float4 v)
{
	float recip = 1 / sqrt(dot_f(v, v));
	return recip * v;
}