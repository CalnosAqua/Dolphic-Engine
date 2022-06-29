/**	@file	avfrt.cpp
 *	@brief	単精度浮動小数点数用の回転量定義ファイル
 */
#include "math/frot.hpp"
#include "math/math.hpp"
#include <numeric>

namespace dlph {
	FRotation::FRotation() noexcept :
		m_angle(0.0f)
	{}

	FRotation& FRotation::radian(float const& arg) noexcept {
		m_angle = arg / PI<float>;
		return *this;
	}

	FRotation& FRotation::degree(float const& arg) noexcept {
		m_angle = arg / 180.0f;
		return *this;
	}

	FRotation& FRotation::operator+=(FRotation const& rhs) noexcept {
		m_angle = Math<float>::sum({ m_angle, rhs.m_angle });
		return *this;
	}

	FRotation& FRotation::operator-=(FRotation const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	FRotation& FRotation::operator*=(float const& rhs) noexcept {
		m_angle *= rhs;
		return *this;
	}

	FRotation& FRotation::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	float const FRotation::radian() const noexcept {
		return m_angle * PI<float>;
	}

	float const FRotation::degree() const noexcept {
		return m_angle * 180.0f;
	}

	FRotation const FRotation::operator+() const noexcept {
		return *this;
	}

	FRotation const FRotation::operator-() const noexcept {
		return *this * -1.0f;
	}

	FRotation const asin(float const& arg) noexcept {
		return FRotation().radian(asinf(arg));
	}

	FRotation const acos(float const& arg) noexcept {
		return FRotation().radian(acosf(arg));
	}

	FRotation const atan(float const& arg) noexcept {
		return FRotation().radian(atanf(arg));
	}

	FRotation const atan(float const& x, float const& y) noexcept {
		return FRotation().radian(atan2f(y, x));
	}

	float const sin(FRotation const& arg) noexcept {
		return sinf(arg.radian());
	}

	float const cos(FRotation const& arg) noexcept {
		return cosf(arg.radian());
	}

	float const tan(FRotation const& arg) noexcept {
		return tanf(arg.radian());
	}

	FRotation const normalized(FRotation const& arg) noexcept {
		float rad = arg.radian();

		while (rad < -PI<float>) {
			rad = Math<float>::sum({ rad, 2.0f * PI<float> });
		}
		while (rad > PI<float>) {
			rad = Math<float>::sum({ rad, -2.0f * PI<float> });
		}

		FRotation result;
		result.radian(rad);
		return result;
	}

	int const round(FRotation const& arg) noexcept {
		float rad = arg.radian() / PI<float>;
		return static_cast<int>(rad * 0.5f);
	}

	FRotation const operator+(FRotation const& lhs, FRotation const& rhs) noexcept {
		FRotation result = lhs;
		result += rhs;
		return result;
	}

	FRotation const operator-(FRotation const& lhs, FRotation const& rhs) noexcept {
		FRotation result = lhs;
		result -= rhs;
		return result;
	}

	FRotation const operator*(FRotation const& lhs, float const& rhs) noexcept {
		FRotation result = lhs;
		result *= rhs;
		return result;
	}

	FRotation const operator*(float const& lhs, FRotation const& rhs) noexcept {
		return rhs * lhs;
	}

	FRotation const operator/(FRotation const& lhs, float const& rhs) noexcept {
		FRotation result = lhs;
		result /= rhs;
		return result;
	}

	bool const operator==(FRotation const& lhs, FRotation const& rhs) noexcept {
		return !Math<float>::compare(lhs.radian(), rhs.radian());
	}

	bool const operator!=(FRotation const& lhs, FRotation const& rhs) noexcept {
		return Math<float>::compare(lhs.radian(), rhs.radian());
	}

	bool const operator<=(FRotation const& lhs, FRotation const& rhs) noexcept {
		return Math<float>::compare(lhs.radian(), rhs.radian()) <= 0;
	}

	bool const operator>=(FRotation const& lhs, FRotation const& rhs) noexcept {
		return Math<float>::compare(lhs.radian(), rhs.radian()) >= 0;
	}

	bool const operator<(FRotation const& lhs, FRotation const& rhs) noexcept {
		return Math<float>::compare(lhs.radian(), rhs.radian()) < 0;
	}

	bool const operator>(FRotation const& lhs, FRotation const& rhs) noexcept {
		return Math<float>::compare(lhs.radian(), rhs.radian()) > 0;
	}
}
