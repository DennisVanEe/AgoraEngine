agora::math::Float4x4 agora::math::identity_f()
{
	Float4x4 res;
	res.setRow0(Float4(1.f, 0.f, 0.f, 0.f));
	res.setRow1(Float4(0.f, 1.f, 0.f, 0.f));
	res.setRow2(Float4(0.f, 0.f, 1.f, 0.f));
	res.setRow3(Float4(0.f, 0.f, 0.f, 1.f));
	return res;
}

agora::math::Float4x4 a_VCALL agora::math::transpose_f(Float4x4 m)
{
	Float4x4 result;
	unsigned* res_ptr = reinterpret_cast<unsigned*>(result.data());
	unsigned* m_ptr = reinterpret_cast<unsigned*>(m.data());

	res_ptr[0] = m_ptr[0] & 0xff000000;
	res_ptr[1] = m_ptr[1] & 0x00ff0000;
	res_ptr[2] = m_ptr[2] & 0x0000ff00;
	res_ptr[3] = m_ptr[3] & 0x000000ff;

	res_ptr[1] |= (m_ptr[0] << 8) & 0xff000000;
	res_ptr[2] |= (m_ptr[0] << 16) & 0xff000000;
	res_ptr[3] |= (m_ptr[0] << 24);

	res_ptr[0] |= (m_ptr[1] >> 8) & 0x00ff0000;
	res_ptr[2] |= (m_ptr[1] << 8) & 0x00ff0000;
	res_ptr[3] |= (m_ptr[1] << 16) & 0x00ff0000;

	res_ptr[0] |= (m_ptr[2] >> 16) & 0x0000ff00;
	res_ptr[1] |= (m_ptr[2] >> 8) & 0x0000ff00;
	res_ptr[3] |= (m_ptr[2] << 8) & 0x0000ff00;

	res_ptr[0] |= (m_ptr[3] >> 24);
	res_ptr[1] |= (m_ptr[3] >> 8) & 0x000000ff;
	res_ptr[2] |= (m_ptr[3] << 8) & 0x000000ff;

	return result;
}

agora::math::Float4x4 a_VCALL agora::math::inverse_f(Float4x4 m)
{
	Float4x4 result;
	float* resultPtr = result.data();
	float* matrixPtr = m.data();

	resultPtr[0] = matrixPtr[5] * matrixPtr[10] * matrixPtr[15] -
		matrixPtr[5] * matrixPtr[11] * matrixPtr[14] -
		matrixPtr[9] * matrixPtr[6] * matrixPtr[15] +
		matrixPtr[9] * matrixPtr[7] * matrixPtr[14] +
		matrixPtr[13] * matrixPtr[6] * matrixPtr[11] -
		matrixPtr[13] * matrixPtr[7] * matrixPtr[10];

	resultPtr[1] = -matrixPtr[1] * matrixPtr[10] * matrixPtr[15] +
		matrixPtr[1] * matrixPtr[11] * matrixPtr[14] +
		matrixPtr[9] * matrixPtr[2] * matrixPtr[15] -
		matrixPtr[9] * matrixPtr[3] * matrixPtr[14] -
		matrixPtr[13] * matrixPtr[2] * matrixPtr[11] +
		matrixPtr[13] * matrixPtr[3] * matrixPtr[10];

	resultPtr[2] = matrixPtr[1] * matrixPtr[6] * matrixPtr[15] -
		matrixPtr[1] * matrixPtr[7] * matrixPtr[14] -
		matrixPtr[5] * matrixPtr[2] * matrixPtr[15] +
		matrixPtr[5] * matrixPtr[3] * matrixPtr[14] +
		matrixPtr[13] * matrixPtr[2] * matrixPtr[7] -
		matrixPtr[13] * matrixPtr[3] * matrixPtr[6];

	resultPtr[3] = -matrixPtr[1] * matrixPtr[6] * matrixPtr[11] +
		matrixPtr[1] * matrixPtr[7] * matrixPtr[10] +
		matrixPtr[5] * matrixPtr[2] * matrixPtr[11] -
		matrixPtr[5] * matrixPtr[3] * matrixPtr[10] -
		matrixPtr[9] * matrixPtr[2] * matrixPtr[7] +
		matrixPtr[9] * matrixPtr[3] * matrixPtr[6];

	resultPtr[4] = -matrixPtr[4] * matrixPtr[10] * matrixPtr[15] +
		matrixPtr[4] * matrixPtr[11] * matrixPtr[14] +
		matrixPtr[8] * matrixPtr[6] * matrixPtr[15] -
		matrixPtr[8] * matrixPtr[7] * matrixPtr[14] -
		matrixPtr[12] * matrixPtr[6] * matrixPtr[11] +
		matrixPtr[12] * matrixPtr[7] * matrixPtr[10];

	resultPtr[5] = matrixPtr[0] * matrixPtr[10] * matrixPtr[15] -
		matrixPtr[0] * matrixPtr[11] * matrixPtr[14] -
		matrixPtr[8] * matrixPtr[2] * matrixPtr[15] +
		matrixPtr[8] * matrixPtr[3] * matrixPtr[14] +
		matrixPtr[12] * matrixPtr[2] * matrixPtr[11] -
		matrixPtr[12] * matrixPtr[3] * matrixPtr[10];

	resultPtr[6] = -matrixPtr[0] * matrixPtr[6] * matrixPtr[15] +
		matrixPtr[0] * matrixPtr[7] * matrixPtr[14] +
		matrixPtr[4] * matrixPtr[2] * matrixPtr[15] -
		matrixPtr[4] * matrixPtr[3] * matrixPtr[14] -
		matrixPtr[12] * matrixPtr[2] * matrixPtr[7] +
		matrixPtr[12] * matrixPtr[3] * matrixPtr[6];

	resultPtr[7] = matrixPtr[0] * matrixPtr[6] * matrixPtr[11] -
		matrixPtr[0] * matrixPtr[7] * matrixPtr[10] -
		matrixPtr[4] * matrixPtr[2] * matrixPtr[11] +
		matrixPtr[4] * matrixPtr[3] * matrixPtr[10] +
		matrixPtr[8] * matrixPtr[2] * matrixPtr[7] -
		matrixPtr[8] * matrixPtr[3] * matrixPtr[6];

	resultPtr[8] = matrixPtr[4] * matrixPtr[9] * matrixPtr[15] -
		matrixPtr[4] * matrixPtr[11] * matrixPtr[13] -
		matrixPtr[8] * matrixPtr[5] * matrixPtr[15] +
		matrixPtr[8] * matrixPtr[7] * matrixPtr[13] +
		matrixPtr[12] * matrixPtr[5] * matrixPtr[11] -
		matrixPtr[12] * matrixPtr[7] * matrixPtr[9];

	resultPtr[9] = -matrixPtr[0] * matrixPtr[9] * matrixPtr[15] +
		matrixPtr[0] * matrixPtr[11] * matrixPtr[13] +
		matrixPtr[8] * matrixPtr[1] * matrixPtr[15] -
		matrixPtr[8] * matrixPtr[3] * matrixPtr[13] -
		matrixPtr[12] * matrixPtr[1] * matrixPtr[11] +
		matrixPtr[12] * matrixPtr[3] * matrixPtr[9];

	resultPtr[10] = matrixPtr[0] * matrixPtr[5] * matrixPtr[15] -
		matrixPtr[0] * matrixPtr[7] * matrixPtr[13] -
		matrixPtr[4] * matrixPtr[1] * matrixPtr[15] +
		matrixPtr[4] * matrixPtr[3] * matrixPtr[13] +
		matrixPtr[12] * matrixPtr[1] * matrixPtr[7] -
		matrixPtr[12] * matrixPtr[3] * matrixPtr[5];

	resultPtr[11] = -matrixPtr[0] * matrixPtr[5] * matrixPtr[11] +
		matrixPtr[0] * matrixPtr[7] * matrixPtr[9] +
		matrixPtr[4] * matrixPtr[1] * matrixPtr[11] -
		matrixPtr[4] * matrixPtr[3] * matrixPtr[9] -
		matrixPtr[8] * matrixPtr[1] * matrixPtr[7] +
		matrixPtr[8] * matrixPtr[3] * matrixPtr[5];

	resultPtr[12] = -matrixPtr[4] * matrixPtr[9] * matrixPtr[14] +
		matrixPtr[4] * matrixPtr[10] * matrixPtr[13] +
		matrixPtr[8] * matrixPtr[5] * matrixPtr[14] -
		matrixPtr[8] * matrixPtr[6] * matrixPtr[13] -
		matrixPtr[12] * matrixPtr[5] * matrixPtr[10] +
		matrixPtr[12] * matrixPtr[6] * matrixPtr[9];

	resultPtr[13] = matrixPtr[0] * matrixPtr[9] * matrixPtr[14] -
		matrixPtr[0] * matrixPtr[10] * matrixPtr[13] -
		matrixPtr[8] * matrixPtr[1] * matrixPtr[14] +
		matrixPtr[8] * matrixPtr[2] * matrixPtr[13] +
		matrixPtr[12] * matrixPtr[1] * matrixPtr[10] -
		matrixPtr[12] * matrixPtr[2] * matrixPtr[9];

	resultPtr[14] = -matrixPtr[0] * matrixPtr[5] * matrixPtr[14] +
		matrixPtr[0] * matrixPtr[6] * matrixPtr[13] +
		matrixPtr[4] * matrixPtr[1] * matrixPtr[14] -
		matrixPtr[4] * matrixPtr[2] * matrixPtr[13] -
		matrixPtr[12] * matrixPtr[1] * matrixPtr[6] +
		matrixPtr[12] * matrixPtr[2] * matrixPtr[5];

	resultPtr[15] = matrixPtr[0] * matrixPtr[5] * matrixPtr[10] -
		matrixPtr[0] * matrixPtr[6] * matrixPtr[9] -
		matrixPtr[4] * matrixPtr[1] * matrixPtr[10] +
		matrixPtr[4] * matrixPtr[2] * matrixPtr[9] +
		matrixPtr[8] * matrixPtr[1] * matrixPtr[6] -
		matrixPtr[8] * matrixPtr[2] * matrixPtr[5];

	float det = matrixPtr[0] * resultPtr[0] + matrixPtr[1] * resultPtr[4] + matrixPtr[2] * resultPtr[8] + matrixPtr[3] * resultPtr[12];

	assert(abs(det) > std::numeric_limits<float>::epsilon());
	det = 1.f / det;

	return result * det;
}

agora::math::Float4x4 a_VCALL agora::math::operator*(float s, Float4x4 m)
{
	return m * s;
}

agora::math::Float4x4 a_VCALL agora::math::operator*(Float4x4 m0, Float4x4 m1)
{
	const float* currMat = m0.data();
	const float* otherMat = m1.data();
	float transMat[16];

	// first tranpose current mat
	m1 = transpose_f(m1);

	// then multiply the results
	Float4x4 result;
	float* resultMat = result.data();

	unsigned counter = 0;
	for (unsigned r = 0; r < 16; r += 4)
	{
		for (unsigned c = 0; c < 16; c += 4)
		{
			resultMat[counter] = 0.f;
			// dot product
			for (int i = 0; i < 4; i++)
			{
				resultMat[counter] += currMat[r + i] * transMat[c + i];
			}
			counter++;
		}
	}

	return result;
}
