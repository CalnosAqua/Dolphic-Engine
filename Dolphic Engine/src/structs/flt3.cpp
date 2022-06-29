/**	@file	flt3.cpp
 *	@brief	三成分単精度浮動小数点数型
 */
#include "structs/flt3.hpp"

namespace {
	constexpr Float3 set(float const& x, float const& y, float const& z) noexcept {
		return Float3{ x, y, z };
	}
}
