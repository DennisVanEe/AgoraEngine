std::string a_VCALL agora::math::to_stdstr(Vec4 v)
{
	std::stringstream ss;
	ss << "Vec4{(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ", " << v.getW() << ")}";
	return ss.str();
}

std::string a_VCALL agora::math::to_stdstr(Vec3 v)
{
	std::stringstream ss;
	ss << "Vec3{(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")}";
	return ss.str();
}

std::string a_VCALL agora::math::to_stdstr(Float4 v)
{
	std::stringstream ss;
	ss << "Float4{(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ", " << v.getW() << ")}";
	return ss.str();
}

std::string a_VCALL agora::math::to_stdstr(Float3 v)
{
	std::stringstream ss;
	ss << "Float4{(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")}";
	return ss.str();
}

std::string a_VCALL agora::math::to_stdstr(Vec4x4 m)
{
	Float4 row0(cfloat4(m.getRow0()));
	Float4 row1(cfloat4(m.getRow1()));
	Float4 row2(cfloat4(m.getRow2()));
	Float4 row3(cfloat4(m.getRow3()));

	std::stringstream str;
	str << "Vec4x4{";
	str << "(" << row0.getX() << ", " << row0.getY() << ", " << row0.getZ() << ", " << row0.getW() << "), ";
	str << "(" << row1.getX() << ", " << row1.getY() << ", " << row1.getZ() << ", " << row1.getW() << "), ";
	str << "(" << row2.getX() << ", " << row2.getY() << ", " << row2.getZ() << ", " << row2.getW() << "), ";
	str << "(" << row3.getX() << ", " << row3.getY() << ", " << row3.getZ() << ", " << row3.getW() << ")}";

	return str.str();
}

std::string a_VCALL agora::math::to_stdstr(Float4x4 m)
{
	Float4 row0 = m.getRow0();
	Float4 row1 = m.getRow1();
	Float4 row2 = m.getRow2();
	Float4 row3 = m.getRow3();

	std::stringstream str;
	str << "Float4x4{";
	str << "(" << row0.getX() << ", " << row0.getY() << ", " << row0.getZ() << ", " << row0.getW() << "), ";
	str << "(" << row1.getX() << ", " << row1.getY() << ", " << row1.getZ() << ", " << row1.getW() << "), ";
	str << "(" << row2.getX() << ", " << row2.getY() << ", " << row2.getZ() << ", " << row2.getW() << "), ";
	str << "(" << row3.getX() << ", " << row3.getY() << ", " << row3.getZ() << ", " << row3.getW() << ")}";

	return str.str();
}
