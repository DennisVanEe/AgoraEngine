agora::math::Float2::Float2()
{
}

agora::math::Float2::Float2(const float* arr)
{
	m_data[0] = arr[0];
	m_data[1] = arr[1];
	m_data[2] = arr[2];
}

agora::math::Float2::Float2(float x, float y)
{
	m_data[0] = x;
	m_data[1] = y;
}

agora::math::Float2::Float2(float s)
{
	m_data[0] = m_data[1] = s;
}

float agora::math::Float2::getX() const
{
	return m_data[0];
}

float agora::math::Float2::getY() const
{
	return m_data[1];
}

void agora::math::Float2::setX(float x)
{
	m_data[0] = x;
}

void agora::math::Float2::setY(float y)
{
	m_data[1] = y;
}

const float* agora::math::Float2::data() const
{
	return m_data;
}

float* agora::math::Float2::data()
{
	return m_data;
}

agora::math::Float2 agora::math::Float2::operator+(Float2 v) const
{
	return Float2(
		m_data[0] + v.getX(),
		m_data[1] + v.getY());
}

agora::math::Float2 agora::math::Float2::operator-(Float2 v) const
{
	return Float2(
		m_data[0] - v.getX(),
		m_data[1] - v.getY());
}

agora::math::Float2 agora::math::Float2::operator*(Float2 v) const
{
	return Float2(
		m_data[0] * v.getX(),
		m_data[1] * v.getY());
}

agora::math::Float2 agora::math::Float2::operator/(Float2 v) const
{
	return Float2(
		m_data[0] / v.getX(),
		m_data[1] / v.getY());
}

agora::math::Float2 agora::math::Float2::operator*(float s) const
{
	return Float2(
		m_data[0] * s,
		m_data[1] * s);
}

agora::math::Float2 agora::math::Float2::operator/(float s) const
{
	s = 1 / s;
	return operator*(s);
}

agora::math::Float2& agora::math::Float2::operator+=(Float2 v)
{
	m_data[0] += v.getX();
	m_data[1] += v.getY();
	return *this;
}

agora::math::Float2& agora::math::Float2::operator-=(Float2 v)
{
	m_data[0] -= v.getX();
	m_data[1] -= v.getY();
	return *this;
}

agora::math::Float2& agora::math::Float2::operator*=(Float2 v)
{
	m_data[0] *= v.getX();
	m_data[1] *= v.getY();
	return *this;
}

agora::math::Float2& agora::math::Float2::operator/=(Float2 v)
{
	m_data[0] /= v.getX();
	m_data[1] /= v.getY();
	return *this;
}

agora::math::Float2& agora::math::Float2::operator*=(float s)
{
	m_data[0] *= s;
	m_data[1] *= s;
	return *this;
}

agora::math::Float2& agora::math::Float2::operator/= (float s)
{
	s = 1 / s;
	operator*=(s);
	return *this;
}