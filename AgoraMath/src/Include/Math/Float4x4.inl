agora::math::Float4x4::Float4x4()
{
}

agora::math::Float4x4::Float4x4(const float* arr)
{
	m_rows[0] = Float4(arr[0]);
	m_rows[1] = Float4(arr[4]);
	m_rows[2] = Float4(arr[8]);
	m_rows[3] = Float4(arr[12]);
}

agora::math::Float4x4::Float4x4(const Float4* arr)
{
	m_rows[0] = arr[0];
	m_rows[1] = arr[1];
	m_rows[2] = arr[2];
	m_rows[3] = arr[3];
}

agora::math::Float4x4::Float4x4(Float4 r0, Float4 r1, Float4 r2, Float4 r3)
{
	m_rows[0] = r0;
	m_rows[1] = r1;
	m_rows[2] = r2;
	m_rows[3] = r3;
}

agora::math::Float4 agora::math::Float4x4::operator*(Float4 v) const
{
	// dot product accross the columns
	Float4 result;
	result.setX(dot_f(v, m_rows[0]));
	result.setY(dot_f(v, m_rows[1]));
	result.setZ(dot_f(v, m_rows[2]));
	result.setW(dot_f(v, m_rows[3]));
	return result;
}

agora::math::Float4x4 agora::math::Float4x4::operator*(float s) const
{
	return Float4x4(
		s * m_rows[0],
		s * m_rows[1],
		s * m_rows[2],
		s * m_rows[3]);
}

const float* agora::math::Float4x4::data() const
{
	return m_rows[0].data();
}

float* agora::math::Float4x4::data()
{
	return m_rows[0].data();
}

void a_VCALL agora::math::Float4x4::setRow0(Float4 c)
{
	m_rows[0] = c;
}

void a_VCALL agora::math::Float4x4::setRow1(Float4 c)
{
	m_rows[1] = c;
}

void a_VCALL agora::math::Float4x4::setRow2(Float4 c)
{
	m_rows[2] = c;
}

void a_VCALL agora::math::Float4x4::setRow3(Float4 c)
{
	m_rows[3] = c;
}

agora::math::Float4 a_VCALL agora::math::Float4x4::getRow0() const
{
	return m_rows[0];
}

agora::math::Float4 a_VCALL agora::math::Float4x4::getRow1() const
{
	return m_rows[1];
}

agora::math::Float4 a_VCALL agora::math::Float4x4::getRow2() const
{
	return m_rows[2];
}

agora::math::Float4 a_VCALL agora::math::Float4x4::getRow3() const
{
	return m_rows[3];
}
