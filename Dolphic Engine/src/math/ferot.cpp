/**	@file	ferot.cpp
 *	@brief	単精度浮動小数点数型のオイラー角クラス
 */
#include "math/ferot.hpp"

namespace dlph {
	FEulerRotation::FEulerRotation() noexcept :
		Element3()
	{}

	FEulerRotation& FEulerRotation::operator+=(FEulerRotation const& rhs) noexcept {
		for (unsigned int idx = 0U; idx < 3U; ++idx) {
			p[idx] += rhs.p[idx];
		}
		return *this;
	}

	FEulerRotation& FEulerRotation::operator-=(FEulerRotation const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	FEulerRotation& FEulerRotation::operator*=(float const& rhs) noexcept {
		for (unsigned int idx = 0U; idx < 3U; ++idx) {
			p[idx] *= rhs;
		}
		return *this;
	}

	FEulerRotation& FEulerRotation::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	FEulerRotation const FEulerRotation::operator+() const noexcept {
		return *this;
	}

	FEulerRotation const FEulerRotation::operator-() const noexcept {
		return *this * -1.0f;
	}

	FEulerRotation const operator+(FEulerRotation const& lhs, FEulerRotation const& rhs) noexcept {
		FEulerRotation result = lhs;
		result += rhs;
		return result;
	}

	FEulerRotation const operator-(FEulerRotation const& lhs, FEulerRotation const& rhs) noexcept {
		FEulerRotation result = lhs;
		result -= rhs;
		return result;
	}

	FEulerRotation const operator*(FEulerRotation const& lhs, float const& rhs) noexcept {
		FEulerRotation result = lhs;
		result *= rhs;
		return result;
	}

	FEulerRotation const operator*(float const& lhs, FEulerRotation const& rhs) noexcept {
		return rhs * lhs;
	}

	FEulerRotation const operator/(FEulerRotation const& lhs, float const& rhs) noexcept {
		FEulerRotation result = lhs;
		result /= rhs;
		return result;
	}

	bool const operator==(FEulerRotation const& lhs, FEulerRotation const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < 3U; ++idx) {
			result = !(lhs.p[idx] == rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(FEulerRotation const& lhs, FEulerRotation const& rhs) noexcept {
		return !(lhs == rhs);
	}
}
