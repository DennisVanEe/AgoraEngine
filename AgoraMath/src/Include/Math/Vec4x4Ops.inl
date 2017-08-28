agora::math::Vec4x4 a_VCALL agora::math::identity_v()
{
	Vec4x4 res;
	res.setRow0(Vec4(1.f, 0.f, 0.f, 0.f));
	res.setRow1(Vec4(0.f, 1.f, 0.f, 0.f));
	res.setRow2(Vec4(0.f, 0.f, 1.f, 0.f));
	res.setRow3(Vec4(0.f, 0.f, 0.f, 1.f));
	return res;
}

agora::math::Vec4x4 a_VCALL agora::math::transpose_v(Vec4x4 m)
{
	__m128 row0 = m.getRow0().data();
	__m128 row1 = m.getRow1().data();
	__m128 row2 = m.getRow2().data();
	__m128 row3 = m.getRow3().data();
	_MM_TRANSPOSE4_PS(row0, row1, row2, row3);
	return Vec4x4(
		Vec4(row0),
		Vec4(row1),
		Vec4(row2),
		Vec4(row3));
}

// Based on code found on forum here: http://forum.devmaster.net/t/sse-mat4-inverse/16799/6 by user Groove
// Modified code to work with my matrix type
agora::math::Vec4x4 a_VCALL agora::math::inverse_v(Vec4x4 m)
{
	__m128 Fac0;
	{
		//  valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		//  valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		//  valType SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		//  valType SubFactor13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		__m128 Swp0a = _mm_shuffle_ps(m.getRow3().data(), m.getRow2().data(), _MM_SHUFFLE(3, 3, 3, 3));
		__m128 Swp0b = _mm_shuffle_ps(m.getRow3().data(), m.getRow2().data(), _MM_SHUFFLE(2, 2, 2, 2));

		__m128 Swp00 = _mm_shuffle_ps(m.getRow2().data(), m.getRow1().data(), _MM_SHUFFLE(2, 2, 2, 2));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(m.getRow2().data(), m.getRow1().data(), _MM_SHUFFLE(3, 3, 3, 3));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac0 = _mm_sub_ps(Mul00, Mul01);
	}

	__m128 Fac1;
	{
		//  valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		//  valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		//  valType SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		//  valType SubFactor14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		__m128 Swp0a = _mm_shuffle_ps(m.getRow3().data(), m.getRow2().data(), _MM_SHUFFLE(3, 3, 3, 3));
		__m128 Swp0b = _mm_shuffle_ps(m.getRow3().data(), m.getRow2().data(), _MM_SHUFFLE(1, 1, 1, 1));

		__m128 Swp00 = _mm_shuffle_ps(m.getRow2().data(), m.getRow1().data(), _MM_SHUFFLE(1, 1, 1, 1));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(m.getRow2().data(), m.getRow1().data(), _MM_SHUFFLE(3, 3, 3, 3));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac1 = _mm_sub_ps(Mul00, Mul01);
	}


	__m128 Fac2;
	{
		//  valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		//  valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		//  valType SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		//  valType SubFactor15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		__m128 Swp0a = _mm_shuffle_ps(m.getRow3().data(), m.getRow2().data(), _MM_SHUFFLE(2, 2, 2, 2));
		__m128 Swp0b = _mm_shuffle_ps(m.getRow3().data(), m.getRow2().data(), _MM_SHUFFLE(1, 1, 1, 1));

		__m128 Swp00 = _mm_shuffle_ps(m.getRow2().data(), m.getRow1().data(), _MM_SHUFFLE(1, 1, 1, 1));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(m.getRow2().data(), m.getRow1().data(), _MM_SHUFFLE(2, 2, 2, 2));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac2 = _mm_sub_ps(Mul00, Mul01);
	}

	__m128 Fac3;
	{
		//  valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		//  valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		//  valType SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		//  valType SubFactor16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		__m128 Swp0a = _mm_shuffle_ps(m.getRow3().data(), m.getRow2().data(), _MM_SHUFFLE(3, 3, 3, 3));
		__m128 Swp0b = _mm_shuffle_ps(m.getRow3().data(), m.getRow2().data(), _MM_SHUFFLE(0, 0, 0, 0));

		__m128 Swp00 = _mm_shuffle_ps(m.getRow2().data(), m.getRow1().data(), _MM_SHUFFLE(0, 0, 0, 0));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(m.getRow2().data(), m.getRow1().data(), _MM_SHUFFLE(3, 3, 3, 3));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac3 = _mm_sub_ps(Mul00, Mul01);
	}

	__m128 Fac4;
	{
		//  valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		//  valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		//  valType SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		//  valType SubFactor17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		__m128 Swp0a = _mm_shuffle_ps(m.getRow3().data(), m.getRow2().data(), _MM_SHUFFLE(2, 2, 2, 2));
		__m128 Swp0b = _mm_shuffle_ps(m.getRow3().data(), m.getRow2().data(), _MM_SHUFFLE(0, 0, 0, 0));

		__m128 Swp00 = _mm_shuffle_ps(m.getRow2().data(), m.getRow1().data(), _MM_SHUFFLE(0, 0, 0, 0));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(m.getRow2().data(), m.getRow1().data(), _MM_SHUFFLE(2, 2, 2, 2));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac4 = _mm_sub_ps(Mul00, Mul01);
	}

	__m128 Fac5;
	{
		//  valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		//  valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		//  valType SubFactor12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		//  valType SubFactor18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		__m128 Swp0a = _mm_shuffle_ps(m.getRow3().data(), m.getRow2().data(), _MM_SHUFFLE(1, 1, 1, 1));
		__m128 Swp0b = _mm_shuffle_ps(m.getRow3().data(), m.getRow2().data(), _MM_SHUFFLE(0, 0, 0, 0));

		__m128 Swp00 = _mm_shuffle_ps(m.getRow2().data(), m.getRow1().data(), _MM_SHUFFLE(0, 0, 0, 0));
		__m128 Swp01 = _mm_shuffle_ps(Swp0a, Swp0a, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp02 = _mm_shuffle_ps(Swp0b, Swp0b, _MM_SHUFFLE(2, 0, 0, 0));
		__m128 Swp03 = _mm_shuffle_ps(m.getRow2().data(), m.getRow1().data(), _MM_SHUFFLE(1, 1, 1, 1));

		__m128 Mul00 = _mm_mul_ps(Swp00, Swp01);
		__m128 Mul01 = _mm_mul_ps(Swp02, Swp03);
		Fac5 = _mm_sub_ps(Mul00, Mul01);
	}

	__m128 SignA = _mm_set_ps(1.0f, -1.0f, 1.0f, -1.0f);
	__m128 SignB = _mm_set_ps(-1.0f, 1.0f, -1.0f, 1.0f);

	// m[1][0]
	// m[0][0]
	// m[0][0]
	// m[0][0]
	__m128 Temp0 = _mm_shuffle_ps(m.getRow1().data(), m.getRow0().data(), _MM_SHUFFLE(0, 0, 0, 0));
	__m128 Vec0 = _mm_shuffle_ps(Temp0, Temp0, _MM_SHUFFLE(2, 2, 2, 0));

	// m[1][1]
	// m[0][1]
	// m[0][1]
	// m[0][1]
	__m128 Temp1 = _mm_shuffle_ps(m.getRow1().data(), m.getRow0().data(), _MM_SHUFFLE(1, 1, 1, 1));
	__m128 Vec1 = _mm_shuffle_ps(Temp1, Temp1, _MM_SHUFFLE(2, 2, 2, 0));

	// m[1][2]
	// m[0][2]
	// m[0][2]
	// m[0][2]
	__m128 Temp2 = _mm_shuffle_ps(m.getRow1().data(), m.getRow0().data(), _MM_SHUFFLE(2, 2, 2, 2));
	__m128 Vec2 = _mm_shuffle_ps(Temp2, Temp2, _MM_SHUFFLE(2, 2, 2, 0));

	// m[1][3]
	// m[0][3]
	// m[0][3]
	// m[0][3]
	__m128 Temp3 = _mm_shuffle_ps(m.getRow1().data(), m.getRow0().data(), _MM_SHUFFLE(3, 3, 3, 3));
	__m128 Vec3 = _mm_shuffle_ps(Temp3, Temp3, _MM_SHUFFLE(2, 2, 2, 0));

	// col0
	// + (Vec1[0] * Fac0[0] - Vec2[0] * Fac1[0] + Vec3[0] * Fac2[0]),
	// - (Vec1[1] * Fac0[1] - Vec2[1] * Fac1[1] + Vec3[1] * Fac2[1]),
	// + (Vec1[2] * Fac0[2] - Vec2[2] * Fac1[2] + Vec3[2] * Fac2[2]),
	// - (Vec1[3] * Fac0[3] - Vec2[3] * Fac1[3] + Vec3[3] * Fac2[3]),
	__m128 Mul00 = _mm_mul_ps(Vec1, Fac0);
	__m128 Mul01 = _mm_mul_ps(Vec2, Fac1);
	__m128 Mul02 = _mm_mul_ps(Vec3, Fac2);
	__m128 Sub00 = _mm_sub_ps(Mul00, Mul01);
	__m128 Add00 = _mm_add_ps(Sub00, Mul02);
	__m128 Inv0 = _mm_mul_ps(SignB, Add00);

	// col1
	// - (Vec0[0] * Fac0[0] - Vec2[0] * Fac3[0] + Vec3[0] * Fac4[0]),
	// + (Vec0[0] * Fac0[1] - Vec2[1] * Fac3[1] + Vec3[1] * Fac4[1]),
	// - (Vec0[0] * Fac0[2] - Vec2[2] * Fac3[2] + Vec3[2] * Fac4[2]),
	// + (Vec0[0] * Fac0[3] - Vec2[3] * Fac3[3] + Vec3[3] * Fac4[3]),
	__m128 Mul03 = _mm_mul_ps(Vec0, Fac0);
	__m128 Mul04 = _mm_mul_ps(Vec2, Fac3);
	__m128 Mul05 = _mm_mul_ps(Vec3, Fac4);
	__m128 Sub01 = _mm_sub_ps(Mul03, Mul04);
	__m128 Add01 = _mm_add_ps(Sub01, Mul05);
	__m128 Inv1 = _mm_mul_ps(SignA, Add01);

	// col2
	// + (Vec0[0] * Fac1[0] - Vec1[0] * Fac3[0] + Vec3[0] * Fac5[0]),
	// - (Vec0[0] * Fac1[1] - Vec1[1] * Fac3[1] + Vec3[1] * Fac5[1]),
	// + (Vec0[0] * Fac1[2] - Vec1[2] * Fac3[2] + Vec3[2] * Fac5[2]),
	// - (Vec0[0] * Fac1[3] - Vec1[3] * Fac3[3] + Vec3[3] * Fac5[3]),
	__m128 Mul06 = _mm_mul_ps(Vec0, Fac1);
	__m128 Mul07 = _mm_mul_ps(Vec1, Fac3);
	__m128 Mul08 = _mm_mul_ps(Vec3, Fac5);
	__m128 Sub02 = _mm_sub_ps(Mul06, Mul07);
	__m128 Add02 = _mm_add_ps(Sub02, Mul08);
	__m128 Inv2 = _mm_mul_ps(SignB, Add02);

	// col3
	// - (Vec1[0] * Fac2[0] - Vec1[0] * Fac4[0] + Vec2[0] * Fac5[0]),
	// + (Vec1[0] * Fac2[1] - Vec1[1] * Fac4[1] + Vec2[1] * Fac5[1]),
	// - (Vec1[0] * Fac2[2] - Vec1[2] * Fac4[2] + Vec2[2] * Fac5[2]),
	// + (Vec1[0] * Fac2[3] - Vec1[3] * Fac4[3] + Vec2[3] * Fac5[3]));
	__m128 Mul09 = _mm_mul_ps(Vec0, Fac2);
	__m128 Mul10 = _mm_mul_ps(Vec1, Fac4);
	__m128 Mul11 = _mm_mul_ps(Vec2, Fac5);
	__m128 Sub03 = _mm_sub_ps(Mul09, Mul10);
	__m128 Add03 = _mm_add_ps(Sub03, Mul11);
	__m128 Inv3 = _mm_mul_ps(SignA, Add03);

	__m128 Row0 = _mm_shuffle_ps(Inv0, Inv1, _MM_SHUFFLE(0, 0, 0, 0));
	__m128 Row1 = _mm_shuffle_ps(Inv2, Inv3, _MM_SHUFFLE(0, 0, 0, 0));
	__m128 Row2 = _mm_shuffle_ps(Row0, Row1, _MM_SHUFFLE(2, 0, 2, 0));

	//  valType Determinant = m[0][0] * Inverse[0][0] 
	//                      + m[0][1] * Inverse[1][0] 
	//                      + m[0][2] * Inverse[2][0] 
	//                      + m[0][3] * Inverse[3][0];
#if defined(__AVX__) || defined(__AVX2__)
	__m128 Det0 = _mm_dp_ps(m.getRow0().data(), Row2, 0xff);
#else // in case dot product wasn't supported
	__m128 temp0 = _mm_mul_ps(m.getRow0().data(), Row2);
	__m128 temp1 = _mm_hadd_ps(temp0, temp0);
	__m128 Det0 = _mm_hadd_ps(temp1, temp1);
#endif
	__m128 Rcp0 = _mm_div_ps(_mm_set_ps1(1.f), Det0);
	//__m128 Rcp0 = _mm_rcp_ps(Det0); // faster, but less accurate (according to forum)

	//  Inverse /= Determinant;
	return Vec4x4(
		Vec4(_mm_mul_ps(Inv0, Rcp0)),
		Vec4(_mm_mul_ps(Inv1, Rcp0)),
		Vec4(_mm_mul_ps(Inv2, Rcp0)),
		Vec4(_mm_mul_ps(Inv3, Rcp0)));
}

agora::math::Vec4x4 a_VCALL agora::math::operator*(float s, Vec4x4 m)
{
	return m * s;
}

agora::math::Vec4x4 a_VCALL agora::math::operator+(float s, Vec4x4 m)
{
	return m + s;
}

agora::math::Vec4x4 a_VCALL agora::math::operator-(float s, Vec4x4 m)
{
	__m128 ssss = _mm_set1_ps(s);

	return Vec4x4(
		Vec4(_mm_sub_ps(ssss, m.getRow0().data())),
		Vec4(_mm_sub_ps(ssss, m.getRow1().data())),
		Vec4(_mm_sub_ps(ssss, m.getRow2().data())),
		Vec4(_mm_sub_ps(ssss, m.getRow3().data())));
}