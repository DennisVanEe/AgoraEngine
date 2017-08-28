#pragma once

#include <string>
#include <sstream>

#include "Vec4.hpp"
#include "Vec3.hpp"
#include "Float4.hpp"
#include "Float3.hpp"
#include "Vec4x4.hpp"
#include "Float4x4.hpp"

namespace agora
{
	namespace math
	{
		std::string a_VCALL to_stdstr(Vec4 v);
		std::string a_VCALL to_stdstr(Vec3 v);
		std::string a_VCALL to_stdstr(Float4 v);
		std::string a_VCALL to_stdstr(Float3 v);

		std::string a_VCALL to_stdstr(Vec4x4 m);
		std::string a_VCALL to_stdstr(Float4x4 m);
	}
}

#include "StringConv.inl"