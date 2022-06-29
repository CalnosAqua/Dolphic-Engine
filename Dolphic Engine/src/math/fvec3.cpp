/**	@file	fvec3.cpp
 *	@brief	単精度浮動小数点数型の三次元ベクトルクラス
 */
#include "math/fvec3.hpp"
#include "math/math.hpp"
#include "math/intrin.hpp"
#include <array>

namespace dlph {
	FVector3::FVector3() noexcept :
		FVector3(FVT3_ZERO)
	{}

	FVector3::FVector3(std::initializer_list<float> const& args) noexcept :
		FVector3(FVT3_ZERO)
	{
		unsigned int idx = 0U;
		for (float const& arg : args) {
			if (idx > 3U) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	FVector3& FVector3::operator+=(FVector3 const& rhs) noexcept {
		store(p, add(load(p), load(rhs.p)));
		return *this;
	}

	FVector3& FVector3::operator-=(FVector3 const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	FVector3& FVector3::operator*=(float const& rhs) noexcept {
		store(p, mul(load(p), set1(rhs)));
		return *this;
	}

	FVector3& FVector3::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	FVector3 const FVector3::operator+() const noexcept {
		return *this;
	}

	FVector3 const FVector3::operator-() const noexcept {
		return *this * -1.0f;
	}

	FVector3 const cross(FVector3 const& vt1, FVector3 const& vt2) noexcept {
		FVector3 result;
		std::array<vctr, 2U> temps = {
			set(  vt1.y * vt2.z,    vt1.z * vt2.x,    vt1.x * vt2.y),
			set(-(vt1.z * vt2.y), -(vt1.x * vt2.z), -(vt1.y * vt2.x))
		};
		store(result.p, Math<vctr>::sum(temps.data(), temps.size()));
		return result;
	}

	float const dot(FVector3 const& lhs, FVector3 const& rhs) noexcept {
		float temps[4U];
		store(temps, mul(load(lhs.p), load(rhs.p)));
		return Math<float>::sum(temps, 4U);
	}

	FVector3 const normalize(FVector3 const& arg) noexcept {
		FVector3 result = arg;
		float length = magnitude(arg);
		if (Math<float>::compare(length, 0.0f) > 0) {
			result /= length;
		}
		return result;
	}

	float const sqr_magnitude(FVector3 const& arg) noexcept {
		return dot(arg, arg);
	}

	float const magnitude(FVector3 const& arg) noexcept {
		return Math<float>::sqrt(sqr_magnitude(arg));
	}

	FVector3 const operator+(FVector3 const& lhs, FVector3 const& rhs) noexcept {
		FVector3 result = lhs;
		result += rhs;
		return result;
	}

	FVector3 const operator-(FVector3 const& lhs, FVector3 const& rhs) noexcept {
		FVector3 result = lhs;
		result -= rhs;
		return result;
	}

	FVector3 const operator*(FVector3 const& lhs, float const& rhs) noexcept {
		FVector3 result = lhs;
		result *= rhs;
		return result;
	}

	FVector3 const operator*(float const& lhs, FVector3 const& rhs) noexcept {
		return rhs * lhs;
	}

	FVector3 const operator/(FVector3 const& lhs, float const& rhs) noexcept {
		FVector3 result = lhs;
		result /= rhs;
		return result;
	}

	bool const operator==(FVector3 const& lhs, FVector3 const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < 3U; ++idx) {
			result = !Math<float>::compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(FVector3 const& lhs, FVector3 const& rhs) noexcept {
		return !(lhs == rhs);
	}
}
