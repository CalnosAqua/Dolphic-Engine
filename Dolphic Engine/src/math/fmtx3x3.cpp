/**	@file	fmtx3x3.cpp
 *	@brief	単精度浮動小数点数用の三次正方行列クラス
 */
#include "structs/flt2x2.hpp"
#include "structs/flt3.hpp"
#include "math/fmtx3x3.hpp"
#include "math/fmtx2x2.hpp"
#include "math/fvec3.hpp"
#include "math/math.hpp"
#include "math/intrin.hpp"
#include <array>

namespace dlph {
	FMatrix3x3::FMatrix3x3() noexcept :
		FMatrix3x3(FMTX3x3_ZERO)
	{}

	FMatrix3x3::FMatrix3x3(std::initializer_list<float> const& args) noexcept :
		FMatrix3x3(FMTX3x3_ZERO)
	{
		unsigned int idx = 0U;
		for (float const& arg : args) {
			if (idx > 9U) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	FMatrix3x3& FMatrix3x3::row(unsigned int const& idx, FVector3 const& vt) noexcept {
		if (idx < 3U) {
			for (unsigned int i = 0U; i < 3U; ++i) {
				p[idx * 3U + i] = vt.p[i];
			}
		}
		return *this;
	}

	FMatrix3x3& FMatrix3x3::column(unsigned int const& idx, FVector3 const& vt) noexcept {
		if (idx < 3U) {
			for (unsigned int i = 0U; i < 3U; ++i) {
				p[i * 3U + idx] = vt.p[i];
			}
		}
		return *this;
	}

	FMatrix3x3& FMatrix3x3::row_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from < 3U && to < 3U) {
			for (unsigned int i = 0U; i < 3U; ++i) {
				std::swap(p[from * 3U + i], p[to * 3U + i]);
			}
		}
		return *this;
	}

	FMatrix3x3& FMatrix3x3::column_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from < 3U && to < 3U) {
			for (unsigned int i = 0U; i < 3U; ++i) {
				std::swap(p[i * 3U + from], p[i * 3U + to]);
			}
		}
		return *this;
	}

	FMatrix3x3& FMatrix3x3::row_scale(unsigned int const& idx, float const& rate) noexcept {
		if (idx < 3U) {
			for (unsigned int i = 0U; i < 3U; ++i) {
				p[idx * 3U + i] *= rate;
			}
		}
		return *this;
	}

	FMatrix3x3& FMatrix3x3::column_scale(unsigned int const& idx, float const& rate) noexcept {
		if (idx < 3U) {
			for (unsigned int i = 0U; i < 3U; ++i) {
				p[i * 3U + idx] *= rate;
			}
		}
		return *this;
	}

	FMatrix3x3& FMatrix3x3::row_prosum(unsigned int const& from, unsigned int const& to, float const& rate) noexcept {
		if (from < 3U && to < 3U) {
			std::array<float, 2U> tmp;
			for (unsigned int i = 0U; i < 3U; ++i) {
				tmp = { p[to * 3U + i], p[from * 3U + i] * rate };
				p[to * 3U + i] = Math<float>::sum(tmp.data(), static_cast<unsigned int>(tmp.size()));
			}
		}
		return *this;
	}

	FMatrix3x3& FMatrix3x3::column_prosum(unsigned int const& from, unsigned int const& to, float const& rate) noexcept {
		if (from < 3U && to < 3U) {
			std::array<float, 2U> tmp;
			for (unsigned int i = 0U; i < 3U; ++i) {
				tmp = { p[i * 3U + to], p[i * 3U + from] * rate };
				p[i * 3U + to] = Math<float>::sum(tmp.data(), static_cast<unsigned int>(tmp.size()));
			}
		}
		return *this;
	}

	FMatrix3x3& FMatrix3x3::operator+=(FMatrix3x3 const& rhs) noexcept {
		for (unsigned int idx = 0U; idx < 9U; idx += 3U) {
			store(&p[idx], add(load(&p[idx]), load(&rhs.p[idx])));
		}
		return *this;
	}

	FMatrix3x3& FMatrix3x3::operator-=(FMatrix3x3 const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	FMatrix3x3& FMatrix3x3::operator*=(float const& rhs) noexcept {
		vctr tmp = set1(rhs);
		for (unsigned int idx = 0U; idx < 9U; idx += 3U) {
			store(&p[idx], mul(load(&p[idx]), tmp));
		}
		return *this;
	}

	FMatrix3x3& FMatrix3x3::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	FVector3 const FMatrix3x3::row(unsigned int const& idx) const noexcept {
		FVector3 result = FVT3_ZERO;
		if (idx < 3U) {
			for (unsigned int i = 0U; i < 3U; ++i) {
				result.p[i] = p[idx * 3U + i];
			}
		}
		return result;
	}

	FVector3 const FMatrix3x3::column(unsigned int const& idx) const noexcept {
		FVector3 result = FVT3_ZERO;
		if (idx < 3U) {
			for (unsigned int i = 0U; i < 3U; ++i) {
				result.p[i] = p[i * 3U + idx];
			}
		}
		return result;
	}

	FMatrix3x3 const FMatrix3x3::operator+() const noexcept {
		return *this;
	}

	FMatrix3x3 const FMatrix3x3::operator-() const noexcept {
		return *this * -1.0f;
	}

	FMatrix3x3 const transpose(FMatrix3x3 const& arg) noexcept {
		FMatrix3x3 result = arg;
		std::swap(result.m01, result.m10);
		std::swap(result.m02, result.m20);
		std::swap(result.m12, result.m21);
		return result;
	}

	FMatrix3x3 const adjoint(FMatrix3x3 const& arg) noexcept {
		FMatrix3x3 result;
		FMatrix2x2 tmp;

		unsigned int idx1, idx2, idx3;
		unsigned int  dx1, dx2;
		unsigned int  dy1, dy2;

		for (idx1 = 0U; idx1 < 9U; ++idx1) {
			dx1 = idx1 / 3U;
			dy1 = idx1 % 3U;
			for (idx2 = 0U, idx3 = 0U; idx2 < 9U; ++idx2) {
				dx2 = idx2 / 3U;
				dy2 = idx2 % 3U;
				if (dx1 != dx2 && dy1 != dy2) {
					tmp.p[idx3] = arg.p[dy2 * 3U + dx2];
					++idx3;
				}
			}
			result.p[idx1] = determinant(tmp);
			if ((dx1 + dy1) % 2U == 1U) {
				result.p[idx1] *= -1.0f;
			}
		}

		return result;
	}

	FMatrix3x3 const inverse(FMatrix3x3 const& arg) noexcept {
		FMatrix3x3 result = adjoint(arg);
		float size = determinant(arg);
		if (Math<float>::compare(size, 0.0f) > 0.0f) {
			result /= size;
		}
		return result;
	}

	float const determinant(FMatrix3x3 const& arg) noexcept {
		std::array<float, 6U> array = {
			  arg.m00 * arg.m11 * arg.m22,
			  arg.m01 * arg.m12 * arg.m20,
			  arg.m02 * arg.m10 * arg.m21,
			-(arg.m00 * arg.m12 * arg.m21),
			-(arg.m01 * arg.m10 * arg.m22),
			-(arg.m02 * arg.m11 * arg.m20)
		};
		return Math<float>::sum(array.data(), array.size());
	}

	FMatrix3x3 const direct(FVector3 const& lhs, FVector3 const& rhs) noexcept {
		FMatrix3x3 result;
		for (unsigned int idx = 0U; idx < 9U; ++idx) {
			result.p[idx] = lhs.p[idx % 3U] * rhs.p[idx / 3U];
		}
		return result;
	}

	FMatrix3x3 const wedge(FVector3 const& lhs, FVector3 const& rhs) noexcept {
		return direct(lhs, rhs) - direct(rhs, lhs);
	}

	FMatrix3x3 const operator+(FMatrix3x3 const& lhs, FMatrix3x3 const& rhs) noexcept {
		FMatrix3x3 result = lhs;
		result += rhs;
		return result;
	}

	FMatrix3x3 const operator-(FMatrix3x3 const& lhs, FMatrix3x3 const& rhs) noexcept {
		FMatrix3x3 result = lhs;
		result -= rhs;
		return result;
	}

	FMatrix3x3 const operator*(FMatrix3x3 const& lhs, FMatrix3x3 const& rhs) noexcept {
		FMatrix3x3 result;
		for (unsigned int idx = 0U; idx < 9U; ++idx) {
			result.p[idx] = dot(lhs.row(idx % 3U), rhs.column(idx / 3U));
		}
		return result;
	}

	FMatrix3x3 const operator*(FMatrix3x3 const& lhs, float const& rhs) noexcept {
		FMatrix3x3 result = lhs;
		result *= rhs;
		return result;
	}

	FMatrix3x3 const operator*(float const& lhs, FMatrix3x3 const& rhs) noexcept {
		return rhs * lhs;
	}

	FMatrix3x3 const operator/(FMatrix3x3 const& lhs, FMatrix3x3 const& rhs) noexcept {
		return lhs * inverse(rhs);
	}

	FMatrix3x3 const operator/(FMatrix3x3 const& lhs, float const& rhs) noexcept {
		FMatrix3x3 result = lhs;
		result /= rhs;
		return result;
	}

	FMatrix3x3 const operator/(float const& lhs, FMatrix3x3 const& rhs) noexcept {
		return lhs * inverse(rhs);
	}

	FVector3 const operator*(FVector3 const& lhs, FMatrix3x3 const& rhs) noexcept {
		FVector3 result;
		for (unsigned int idx = 0U; idx < 3U; ++idx) {
			result.p[idx] = dot(lhs, rhs.column(idx));
		}
		return result;
	}

	FVector3 const operator*(FMatrix3x3 const& lhs, FVector3 const& rhs) noexcept {
		FVector3 result;
		for (unsigned int idx = 0U; idx < 3U; ++idx) {
			result.p[idx] = dot(lhs.row(idx), rhs);
		}
		return result;
	}

	bool const operator==(FMatrix3x3 const& lhs, FMatrix3x3 const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < 3U; ++idx) {
			result = !Math<float>::compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(FMatrix3x3 const& lhs, FMatrix3x3 const& rhs) noexcept {
		return !(lhs == rhs);
	}
}
