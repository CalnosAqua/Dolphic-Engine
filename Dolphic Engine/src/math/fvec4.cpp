/**	@file	fvec4.cpp
 *	@brief	単精度浮動小数点数型の四次元ベクトルクラス
 */
#include "math/fvec4.hpp"
#include "math/math.hpp"
#include "math/intrin.hpp"
#include <array>

namespace dlph {
	FVector4::FVector4() noexcept :
		FVector4(FVT4_ZERO)
	{}

	FVector4::FVector4(std::initializer_list<float> const& args) noexcept :
		FVector4(FVT4_ZERO)
	{
		unsigned int idx = 0U;
		for (float const& arg : args) {
			if (idx > 4U) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	FVector4& FVector4::operator+=(FVector4 const& rhs) noexcept {
		store(p, add(load(p), load(rhs.p)));
		return *this;
	}

	FVector4& FVector4::operator-=(FVector4 const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	FVector4& FVector4::operator*=(float const& rhs) noexcept {
		store(p, mul(load(p), set1(rhs)));
		return *this;
	}

	FVector4& FVector4::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	FVector4 const FVector4::operator+() const noexcept {
		return *this;
	}

	FVector4 const FVector4::operator-() const noexcept {
		return *this * -1.0f;
	}

	FVector4 const cross(FVector4 const& vt1, FVector4 const& vt2, FVector4 const& vt3) noexcept {
		FVector4 result;
		std::array<vctr, 6U> temps = {
			set(vt1.z * vt2.w * vt3.y,vt1.z * vt2.x * vt3.w,vt1.y * vt2.w * vt3.x,vt1.z * vt2.y * vt3.x),
			set(vt1.y * vt2.z * vt3.w,vt1.x * vt2.w * vt3.z,vt1.x * vt2.y * vt3.w,vt1.y * vt2.x * vt3.z),
			set(vt1.w * vt2.y * vt3.z,vt1.w * vt2.z * vt3.x,vt1.w * vt2.x * vt3.y,vt1.x * vt2.z * vt3.y),
			set(-(vt1.z * vt2.y * vt3.w),-(vt1.z * vt2.w * vt3.x),-(vt1.y * vt2.x * vt3.w),-(vt1.z * vt2.x * vt3.y)),
			set(-(vt1.y * vt2.w * vt3.z),-(vt1.x * vt2.z * vt3.w),-(vt1.x * vt2.w * vt3.y),-(vt1.y * vt2.z * vt3.x)),
			set(-(vt1.w * vt2.z * vt3.y),-(vt1.w * vt2.x * vt3.z),-(vt1.w * vt2.y * vt3.x),-(vt1.x * vt2.y * vt3.z))
		};
		store(result.p, Math<vctr>::sum(temps.data(), temps.size()));
		return result;
	}

	float const dot(FVector4 const& lhs, FVector4 const& rhs) noexcept {
		float temps[4U];
		store(temps, mul(load(lhs.p), load(rhs.p)));
		return Math<float>::sum(temps, 4U);
	}

	FVector4 const normalize(FVector4 const& arg) noexcept {
		FVector4 result = arg;
		float length = magnitude(arg);
		if (Math<float>::compare(length, 0.0f) > 0) {
			result /= length;
		}
		return result;
	}

	float const sqr_magnitude(FVector4 const& arg) noexcept {
		return dot(arg, arg);
	}

	float const magnitude(FVector4 const& arg) noexcept {
		return Math<float>::sqrt(sqr_magnitude(arg));
	}

	FVector4 const operator+(FVector4 const& lhs, FVector4 const& rhs) noexcept {
		FVector4 result = lhs;
		result += rhs;
		return result;
	}

	FVector4 const operator-(FVector4 const& lhs, FVector4 const& rhs) noexcept {
		FVector4 result = lhs;
		result -= rhs;
		return result;
	}

	FVector4 const operator*(FVector4 const& lhs, float const& rhs) noexcept {
		FVector4 result = lhs;
		result *= rhs;
		return result;
	}

	FVector4 const operator*(float const& lhs, FVector4 const& rhs) noexcept {
		return rhs * lhs;
	}

	FVector4 const operator/(FVector4 const& lhs, float const& rhs) noexcept {
		FVector4 result = lhs;
		result /= rhs;
		return result;
	}

	bool const operator==(FVector4 const& lhs, FVector4 const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < 4U; ++idx) {
			result = !Math<float>::compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(FVector4 const& lhs, FVector4 const& rhs) noexcept {
		return !(lhs == rhs);
	}
}
