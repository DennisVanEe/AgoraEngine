agora::math::Float3::Float3()
{
}

agora::math::Float3::Float3(const float* arr)
{
	m_data[0] = arr[0];
	m_data[1] = arr[1];
	m_data[2] = arr[2];
}

agora::math::Float3::Float3(float x, float y, float z)
{
	m_data[0] = x;
	m_data[1] = y;
	m_data[2] = z;
}

agora::math::Float3::Float3(float s)
{
	m_data[0] = m_data[1] = m_data[2] = s;
}

float agora::math::Float3::getX() const
{
	return m_data[0];
}

float agora::math::Float3::getY() const
{
	return m_data[1];
}

float agora::math::Float3::getZ() const
{
	return m_data[2];
}

void agora::math::Float3::setX(float x)
{
	m_data[0] = x;
}

void agora::math::Float3::setY(float y)
{
	m_data[1] = y;
}

void agora::math::Float3::setZ(float z)
{
	m_data[2] = z;
}

const float* agora::math::Float3::data() const
{
	return m_data;
}

float* agora::math::Float3::data()
{
	return m_data;
}

agora::math::Float3 agora::math::Float3::operator+(Float3 v) const
{
	return Float3(
		m_data[0] + v.getX(),
		m_data[1] + v.getY(),
		m_data[2] + v.getZ());
}

agora::math::Float3 agora::math::Float3::operator-(Float3 v) const
{
	return Float3(
		m_data[0] - v.getX(),
		m_data[1] - v.getY(),
		m_data[2] - v.getZ());
}

agora::math::Float3 agora::math::Float3::operator*(Float3 v) const
{
	return Float3(
		m_data[0] * v.getX(),
		m_data[1] * v.getY(),
		m_data[2] * v.getZ());
}

agora::math::Float3 agora::math::Float3::operator/(Float3 v) const
{
	return Float3(
		m_data[0] / v.getX(),
		m_data[1] / v.getY(),
		m_data[2] / v.getZ());
}

agora::math::Float3 agora::math::Float3::operator*(float s) const
{
	return Float3(
		m_data[0] * s,
		m_data[1] * s,
		m_data[2] * s);
}

agora::math::Float3 agora::math::Float3::operator/(float s) const
{
	s = 1 / s;
	return operator*(s);
}

agora::math::Float3& agora::math::Float3::operator+=(Float3 v)
{
	m_data[0] += v.getX();
	m_data[1] += v.getY();
	m_data[2] += v.getZ();
	return *this;
}

agora::math::Float3& agora::math::Float3::operator-=(Float3 v)
{
	m_data[0] -= v.getX();
	m_data[1] -= v.getY();
	m_data[2] -= v.getZ();
	return *this;
}

agora::math::Float3& agora::math::Float3::operator*=(Float3 v)
{
	m_data[0] *= v.getX();
	m_data[1] *= v.getY();
	m_data[2] *= v.getZ();
	return *this;
}

agora::math::Float3& agora::math::Float3::operator/=(Float3 v)
{
	m_data[0] /= v.getX();
	m_data[1] /= v.getY();
	m_data[2] /= v.getZ();
	return *this;
}

agora::math::Float3& agora::math::Float3::operator*=(float s)
{
	m_data[0] *= s;
	m_data[1] *= s;
	m_data[2] *= s;
	return *this;
}

agora::math::Float3& agora::math::Float3::operator/= (float s)
{
	s = 1 / s;
	operator*=(s);
	return *this;
}