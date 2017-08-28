agora::math::Float2 agora::math::operator*(float s, Float2 v)
{
	return v * s;
}

agora::math::Float2 agora::math::operator/(float s, Float2 v)
{
	Float2 result;
	result.setX(s / v.getX());
	result.setX(s / v.getY());
	return result;
}

agora::math::Float2 agora::math::dotVec_f(Float2 v1, Float2 v2)
{
	float d = dot_f(v1, v2);
	return Float2(d, d);
}

float agora::math::dot_f(Float2 v1, Float2 v2)
{
	return v1.getX() * v2.getX() + v1.getY() * v2.getY();
}

agora::math::Float2 agora::math::normalize_f(Float2 v)
{
	float recip = 1 / sqrt(dot_f(v, v));
	return recip * v;
}