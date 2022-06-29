/**	@file	fcomp.cpp
 *	@brief	単精度浮動小数点数型の複素数クラス
 */
#include "math/fquat.hpp"
#include "math/math.hpp"
#include "math/intrin.hpp"
#include <array>

namespace dlph {
	FQuaternion::FQuaternion() noexcept :
		FQuaternion(FQTR_ZERO)
	{}

	FQuaternion::FQuaternion(std::initializer_list<float> const& args) noexcept :
		FQuaternion(FQTR_ZERO)
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

	FQuaternion& FQuaternion::operator+=(FQuaternion const& rhs) noexcept {
		store(p, add(load(p), load(rhs.p)));
		return *this;
	}

	FQuaternion& FQuaternion::operator-=(FQuaternion const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	FQuaternion& FQuaternion::operator*=(float const& rhs) noexcept {
		store(p, mul(load(p), set1(rhs)));
		return *this;
	}

	FQuaternion& FQuaternion::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	FQuaternion const FQuaternion::operator+() const noexcept {
		return *this;
	}

	FQuaternion const FQuaternion::operator-() const noexcept {
		return *this * -1.0f;
	}

	FQuaternion const conjugate(FQuaternion const& arg) noexcept {
		FQuaternion result = -arg;
		result.w *= -1.0f;
		return result;
	}

	FQuaternion const normalize(FQuaternion const& arg) noexcept {
		FQuaternion result = arg;
		float length = magnitude(arg);
		if (!Math<float>::compare(length, 0.0f)) {
			result /= length;
		}
		return result;
	}

	FQuaternion const inverse(FQuaternion const& arg) noexcept {
		FQuaternion result = conjugate(arg);
		float length = sqr_magnitude(arg);
		if (!Math<float>::compare(length, 0.0f)) {
			result /= length;
		}
		return result;
	}

	float const sqr_magnitude(FQuaternion const& arg) noexcept {
		return (arg * conjugate(arg)).w;
	}

	float const magnitude(FQuaternion const& arg) noexcept {
		return Math<float>::sqrt(sqr_magnitude(arg));
	}

	FQuaternion const operator+(FQuaternion const& lhs, FQuaternion const& rhs) noexcept {
		FQuaternion result = lhs;
		result += rhs;
		return result;
	}

	FQuaternion const operator-(FQuaternion const& lhs, FQuaternion const& rhs) noexcept {
		FQuaternion result = lhs;
		result -= rhs;
		return result;
	}

	FQuaternion const operator*(FQuaternion const& lhs, FQuaternion const& rhs) noexcept {
		FQuaternion result;
		std::array<vctr, 4U> temps = {
			set(lhs.x * rhs.w,lhs.y * rhs.w,lhs.z * rhs.w,lhs.w * rhs.w),
			set(lhs.w * rhs.x,lhs.w * rhs.y,lhs.w * rhs.z,-(lhs.x * rhs.x)),
			set(lhs.y * rhs.z,lhs.z * rhs.x,lhs.x * rhs.y,-(lhs.y * rhs.y)),
			set(-(lhs.z * rhs.y),-(lhs.x * rhs.z),-(lhs.y * rhs.x),-(lhs.z * rhs.z))
		};
		store(result.p, Math<vctr>::sum(temps.data(), temps.size()));
		return result;
	}

	FQuaternion const operator*(FQuaternion const& lhs, float const& rhs) noexcept {
		FQuaternion result = lhs;
		result *= rhs;
		return result;
	}

	FQuaternion const operator*(float const& lhs, FQuaternion const& rhs) noexcept {
		return rhs * lhs;
	}

	FQuaternion const operator/(FQuaternion const& lhs, FQuaternion const& rhs) noexcept {
		return lhs * inverse(rhs);
	}

	FQuaternion const operator/(FQuaternion const& lhs, float const& rhs) noexcept {
		FQuaternion result = lhs;
		result /= rhs;
		return result;
	}

	FQuaternion const operator/(float const& lhs, FQuaternion const& rhs) noexcept {
		return inverse(rhs) * lhs;
	}

	bool const operator==(FQuaternion const& lhs, FQuaternion const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < 4U; ++idx) {
			result = !Math<float>::compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(FQuaternion const& lhs, FQuaternion const& rhs) noexcept {
		return !(lhs == rhs);
	}
}
