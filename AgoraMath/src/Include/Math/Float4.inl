agora::math::Float4::Float4()
{
}

agora::math::Float4::Float4(const float* arr)
{
	m_data[0] = arr[0];
	m_data[1] = arr[1];
	m_data[2] = arr[2];
	m_data[3] = arr[3];
}

agora::math::Float4::Float4(float x, float y, float z, float w)
{
	m_data[0] = x;
	m_data[1] = y;
	m_data[2] = z;
	m_data[3] = w;
}

agora::math::Float4::Float4(float s)
{
	m_data[0] = m_data[1] = m_data[2] = m_data[3] = s;
}

float agora::math::Float4::getX() const
{
	return m_data[0];
}

float agora::math::Float4::getY() const
{
	return m_data[1];
}

float agora::math::Float4::getZ() const
{
	return m_data[2];
}

float agora::math::Float4::getW() const
{
	return m_data[3];
}

void agora::math::Float4::setX(float x)
{
	m_data[0] = x;
}

void agora::math::Float4::setY(float y)
{
	m_data[1] = y;
}

void agora::math::Float4::setZ(float z)
{
	m_data[2] = z;
}

void agora::math::Float4::setW(float w)
{
	m_data[3] = w;
}

const float* agora::math::Float4::data() const
{
	return &m_data[0];
}

float* agora::math::Float4::data()
{
	return &m_data[0];
}

agora::math::Float4 agora::math::Float4::operator+(Float4 v) const
{
	return Float4(
		getX() + v.getX(),
		getY() + v.getY(),
		getZ() + v.getZ(),
		getW() + v.getW());
}

agora::math::Float4 agora::math::Float4::operator-(Float4 v) const
{
	return Float4(
		getX() - v.getX(),
		getY() - v.getY(),
		getZ() - v.getZ(),
		getW() - v.getW());
}

agora::math::Float4 agora::math::Float4::operator*(Float4 v) const
{
	return Float4(
		getX() * v.getX(),
		getY() * v.getY(),
		getZ() * v.getZ(),
		getW() * v.getW());
}

agora::math::Float4 agora::math::Float4::operator/(Float4 v) const
{
	return Float4(
		getX() / v.getX(),
		getY() / v.getY(),
		getZ() / v.getZ(),
		getW() / v.getW());
}

agora::math::Float4 agora::math::Float4::operator*(float s) const
{
	return Float4(
		getX() * s,
		getY() * s,
		getZ() * s,
		getW() * s);
}

agora::math::Float4 agora::math::Float4::operator/(float s) const
{
	s = 1 / s;
	return operator*(s);
}

agora::math::Float4& agora::math::Float4::operator+=(Float4 v)
{
	m_data[0] += v.getX();
	m_data[1] += v.getY();
	m_data[2] += v.getZ();
	m_data[3] += v.getW();
	return *this;
}

agora::math::Float4& agora::math::Float4::operator-=(Float4 v)
{
	m_data[0] -= v.getX();
	m_data[1] -= v.getY();
	m_data[2] -= v.getZ();
	m_data[3] -= v.getW();
	return *this;
}

agora::math::Float4& agora::math::Float4::operator*=(Float4 v)
{
	m_data[0] *= v.getX();
	m_data[1] *= v.getY();
	m_data[2] *= v.getZ();
	m_data[3] *= v.getW();
	return *this;
}

agora::math::Float4& agora::math::Float4::operator/=(Float4 v)
{
	m_data[0] /= v.getX();
	m_data[1] /= v.getY();
	m_data[2] /= v.getZ();
	m_data[3] /= v.getW();
	return *this;
}

agora::math::Float4& agora::math::Float4::operator*=(float s)
{
	m_data[0] *= s;
	m_data[1] *= s;
	m_data[2] *= s;
	m_data[3] *= s;
	return *this;
}

agora::math::Float4& agora::math::Float4::operator/= (float s)
{
	s = 1 / s;
	operator*=(s);
	return *this;
}