/**	@file	flt2.cpp
 *	@brief	二成分単精度浮動小数点数型
 */
#include "structs/flt2.hpp"

namespace {
	constexpr Float2 set(float const& x, float const& y) noexcept {
		return Float2{ x, y };
	}
}
