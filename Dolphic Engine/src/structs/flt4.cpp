/**	@file	flt4.cpp
 *	@brief	四成分単精度浮動小数点数型
 */
#include "structs/flt4.hpp"

namespace {
	constexpr Float4 set(float const& x, float const& y, float const& z, float const& w) noexcept {
		return Float4{ x, y, z, w };
	}
}
