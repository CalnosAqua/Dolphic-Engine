/**	@file	intrin.cpp
 *	@brief	組み込み関数ラッパー
 */
#include "math/intrin.hpp"

namespace dlph {
#	if defined(_M_IX86) || defined(_M_X64)
	//	X** CPU 用の SIMD 関数ラッパ

	void store(float* ptr, __m128 const& arg) noexcept {
		_mm_store_ps(ptr, arg);
	}

	__m128 const set(float const& x, float const& y, float const& z, float const& w) noexcept {
		float temp[4U] = { x, y, z, w };
		return _mm_load_ps(temp);
	}

	__m128 const set1(float const& arg) noexcept {
		return _mm_set1_ps(arg);
	}

	__m128 const load(float const* const& ptr) noexcept {
		return _mm_load_ps(ptr);
	}

	__m128 const add(__m128 const& lhs, __m128 const& rhs) noexcept {
		return _mm_add_ps(lhs, rhs);
	}

	__m128 const sub(__m128 const& lhs, __m128 const& rhs) noexcept {
		return _mm_sub_ps(lhs, rhs);
	}

	__m128 const mul(__m128 const& lhs, __m128 const& rhs) noexcept {
		return _mm_mul_ps(lhs, rhs);
	}
#	elif defined(_M_ARM) || defined(_M_ARM64)
	//	ARM CPU 用の SIMD 関数ラッパ

	void store(float* ptr, float32x4_t const& arg) noexcept {
		vst1q_f32(ptr, arg);
	}

	float32x4_t const set(float const& x, float const& y, float const& z, float const& w) noexcept {
		float temp[4U] = { x, y, z, w };
		return vld1q_f32(temp);
	}

	float32x4_t const set1(float const& arg) noexcept {
		return vdupq_n_f32(arg);
	}

	float32x4_t const load(float const* const& ptr) noexcept {
		return vld1q_f32(ptr);
	}

	float32x4_t const add(float32x4_t const& lhs, float32x4_t const& rhs) noexcept {
		return vaddq_f32(lhs, rhs);
	}

	float32x4_t const sub(float32x4_t const& lhs, float32x4_t const& rhs) noexcept {
		return vsubq_f32(lhs, rhs);
	}

	float32x4_t const mul(float32x4_t const& lhs, float32x4_t const& rhs) noexcept {
		return vmulq_f32(lhs, rhs);
	}
#	endif
}
