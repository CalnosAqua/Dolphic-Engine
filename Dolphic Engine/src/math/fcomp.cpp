/**	@file	fcomp.cpp
 *	@brief	単精度浮動小数点数型の複素数クラス
 */
#include "math/fcomp.hpp"
#include "math/math.hpp"
#include "math/intrin.hpp"
#include <array>

namespace dlph {
	FComplex::FComplex() noexcept :
		FComplex(FCMP_ZERO)
	{}

	FComplex::FComplex(std::initializer_list<float> const& args) noexcept :
		FComplex(FCMP_ZERO)
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

	FComplex& FComplex::operator+=(FComplex const& rhs) noexcept {
		store(p, add(load(p), load(rhs.p)));
		return *this;
	}

	FComplex& FComplex::operator-=(FComplex const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	FComplex& FComplex::operator*=(float const& rhs) noexcept {
		store(p, mul(load(p), set1(rhs)));
		return *this;
	}

	FComplex& FComplex::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	FComplex const FComplex::operator+() const noexcept {
		return *this;
	}

	FComplex const FComplex::operator-() const noexcept {
		return *this * -1.0f;
	}

	FComplex const conjugate(FComplex const& arg) noexcept {
		FComplex result = arg;
		result.y *= -1.0f;
		return result;
	}

	FComplex const normalize(FComplex const& arg) noexcept {
		FComplex result = arg;
		float length = magnitude(arg);
		if (!Math<float>::compare(length, 0.0f)) {
			result /= length;
		}
		return result;
	}

	FComplex const inverse(FComplex const& arg) noexcept {
		FComplex result = conjugate(arg);
		float length = sqr_magnitude(arg);
		if (!Math<float>::compare(length, 0.0f)) {
			result /= length;
		}
		return result;
	}

	float const sqr_magnitude(FComplex const& arg) noexcept {
		return (arg * conjugate(arg)).x;
	}

	float const magnitude(FComplex const& arg) noexcept {
		return Math<float>::sqrt(sqr_magnitude(arg));
	}

	FComplex const operator+(FComplex const& lhs, FComplex const& rhs) noexcept {
		FComplex result = lhs;
		result += rhs;
		return result;
	}

	FComplex const operator-(FComplex const& lhs, FComplex const& rhs) noexcept {
		FComplex result = lhs;
		result -= rhs;
		return result;
	}

	FComplex const operator*(FComplex const& lhs, FComplex const& rhs) noexcept {
		FComplex result;
		std::array<vctr, 2U> array = {
			set(lhs.x * rhs.x, lhs.x * rhs.y),
			set(-(lhs.y * rhs.y), lhs.y * rhs.x)
		};
		store(result.p, Math<vctr>::sum(array.data(), array.size()));
		return result;
	}

	FComplex const operator*(FComplex const& lhs, float const& rhs) noexcept {
		FComplex result = lhs;
		result *= rhs;
		return result;
	}

	FComplex const operator*(float const& lhs, FComplex const& rhs) noexcept {
		return rhs * lhs;
	}

	FComplex const operator/(FComplex const& lhs, FComplex const& rhs) noexcept {
		return lhs * inverse(rhs);
	}

	FComplex const operator/(FComplex const& lhs, float const& rhs) noexcept {
		FComplex result = lhs;
		result /= rhs;
		return result;
	}

	FComplex const operator/(float const& lhs, FComplex const& rhs) noexcept {
		return inverse(rhs) * lhs;
	}

	bool const operator==(FComplex const& lhs, FComplex const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < 2U; ++idx) {
			result = !Math<float>::compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(FComplex const& lhs, FComplex const& rhs) noexcept {
		return !(lhs == rhs);
	}
}
