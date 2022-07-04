/**	@file	intrin.hpp
 *	@brief	組み込み関数ラッパー
 */
#pragma once
#include "cont/array.hpp"

#if defined(_M_IX86) || defined(_M_X64)
#	include <immintrin.h>
#elif defined(_M_ARM)
#	include <arm_neon.h>
#elif defined(_M_ARM64)
#	include <arm64_neon.h>
#endif

namespace dlph {
#	if defined(_M_IX86) || defined(_M_X64)
	using vctr = __m128;
#	elif defined(_M_ARM) || defined(_M_ARM64)
	using vctr = float32x4_t;
#	endif

	//!	@brief	復元関数
	void store(float* ptr, vctr const& arg) noexcept;
	//!	@brief	設定関数
	vctr const set(float const& x = 0.0f, float const& y = 0.0f, float const& z = 0.0f, float const& w = 0.0f) noexcept;
	//!	@brief	設定関数
	vctr const set1(float const& arg) noexcept;
	//!	@brief	設定関数
	vctr const load(float const* const& ptr) noexcept;
	//!	@brief	加算関数
	vctr const add(vctr const& lhs, vctr const& rhs) noexcept;
	//!	@brief	減算関数
	vctr const sub(vctr const& lhs, vctr const& rhs) noexcept;
	//!	@brief	乗算関数
	vctr const mul(vctr const& lhs, vctr const& rhs) noexcept;
}
