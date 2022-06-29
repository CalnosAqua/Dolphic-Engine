/**	@file	fvec2.cpp
 *	@brief	単精度浮動小数点数型の二次元ベクトルクラス
 */
#include "math/fvec2.hpp"
#include "math/math.hpp"
#include "math/intrin.hpp"

namespace dlph {
	FVector2::FVector2() noexcept :
		FVector2(FVT2_ZERO)
	{}

	FVector2::FVector2(std::initializer_list<float> const& args) noexcept :
		FVector2(FVT2_ZERO)
	{
		unsigned int idx = 0U;
		for (float const& arg : args) {
			if (idx > 2U) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	FVector2& FVector2::operator+=(FVector2 const& rhs) noexcept {
		store(p, add(load(p), load(rhs.p)));
		return *this;
	}

	FVector2& FVector2::operator-=(FVector2 const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	FVector2& FVector2::operator*=(float const& rhs) noexcept {
		store(p, mul(load(p), set1(rhs)));
		return *this;
	}

	FVector2& FVector2::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	FVector2 const FVector2::operator+() const noexcept {
		return *this;
	}

	FVector2 const FVector2::operator-() const noexcept {
		return *this * -1.0f;
	}

	FVector2 const cross(FVector2 const& vt1) noexcept {
		return FVector2(-vt1.y, vt1.x);
	}

	float const dot(FVector2 const& lhs, FVector2 const& rhs) noexcept {
		float temps[4U];
		store(temps, mul(load(lhs.p), load(rhs.p)));
		return Math<float>::sum(temps, 4U);
	}

	FVector2 const normalize(FVector2 const& arg) noexcept {
		FVector2 result = arg;
		float length = magnitude(arg);
		if (Math<float>::compare(length, 0.0f) > 0) {
			result /= length;
		}
		return result;
	}

	float const sqr_magnitude(FVector2 const& arg) noexcept {
		return dot(arg, arg);
	}

	float const magnitude(FVector2 const& arg) noexcept {
		return Math<float>::sqrt(sqr_magnitude(arg));
	}

	FVector2 const operator+(FVector2 const& lhs, FVector2 const& rhs) noexcept {
		FVector2 result = lhs;
		result += rhs;
		return result;
	}

	FVector2 const operator-(FVector2 const& lhs, FVector2 const& rhs) noexcept {
		FVector2 result = lhs;
		result -= rhs;
		return result;
	}

	FVector2 const operator*(FVector2 const& lhs, float const& rhs) noexcept {
		FVector2 result = lhs;
		result *= rhs;
		return result;
	}

	FVector2 const operator*(float const& lhs, FVector2 const& rhs) noexcept {
		return rhs * lhs;
	}

	FVector2 const operator/(FVector2 const& lhs, float const& rhs) noexcept {
		FVector2 result = lhs;
		result /= rhs;
		return result;
	}

	bool const operator==(FVector2 const& lhs, FVector2 const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < 2U; ++idx) {
			result = !Math<float>::compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(FVector2 const& lhs, FVector2 const& rhs) noexcept {
		return !(lhs == rhs);
	}
}
