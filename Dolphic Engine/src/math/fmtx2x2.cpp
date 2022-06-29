/**	@file	fmtx2x2.cpp
 *	@brief	単精度浮動小数点数用の二次正方行列クラス
 */
#include "math/fmtx2x2.hpp"
#include "math/math.hpp"
#include "math/intrin.hpp"
#include <array>
#include <utility>

namespace dlph {
	FMatrix2x2::FMatrix2x2() noexcept :
		FMatrix2x2(FMTX2x2_ZERO)
	{}

	FMatrix2x2::FMatrix2x2(std::initializer_list<float> const& args) noexcept :
		FMatrix2x2(FMTX2x2_ZERO)
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

	FMatrix2x2& FMatrix2x2::row(unsigned int const& idx, FVector2 const& vt) noexcept {
		if (idx < 2U) {
			for (unsigned int i = 0U; i < 2U; ++i) {
				p[idx * 2U + i] = vt.p[i];
			}
		}
		return *this;
	}

	FMatrix2x2& FMatrix2x2::column(unsigned int const& idx, FVector2 const& vt) noexcept {
		if (idx < 2U) {
			for (unsigned int i = 0U; i < 2U; ++i) {
				p[i * 2U + idx] = vt.p[i];
			}
		}
		return *this;
	}

	FMatrix2x2& FMatrix2x2::row_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from < 2U && to < 2U) {
			for (unsigned int i = 0U; i < 2U; ++i) {
				std::swap(p[from * 2U + i], p[to * 2U + i]);
			}
		}
		return *this;
	}

	FMatrix2x2& FMatrix2x2::column_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from < 2U && to < 2U) {
			for (unsigned int i = 0U; i < 2U; ++i) {
				std::swap(p[i * 2U + from], p[i * 2U + to]);
			}
		}
		return *this;
	}

	FMatrix2x2& FMatrix2x2::row_scale(unsigned int const& idx, float const& rate) noexcept {
		if (idx < 2U) {
			for (unsigned int i = 0U; i < 2U; ++i) {
				p[idx * 2U + i] *= rate;
			}
		}
		return *this;
	}

	FMatrix2x2& FMatrix2x2::column_scale(unsigned int const& idx, float const& rate) noexcept {
		if (idx < 2U) {
			for (unsigned int i = 0U; i < 2U; ++i) {
				p[i * 2U + idx] *= rate;
			}
		}
		return *this;
	}

	FMatrix2x2& FMatrix2x2::row_prosum(unsigned int const& from, unsigned int const& to, float const& rate) noexcept {
		if (from < 2U && to < 2U) {
			std::array<float, 2U> tmp;
			for (unsigned int i = 0U; i < 2U; ++i) {
				tmp = { p[to * 2U + i], p[from * 2U + i] * rate };
				p[to * 2U + i] = Math<float>::sum(tmp.data(), static_cast<unsigned int>(tmp.size()));
			}
		}
		return *this;
	}

	FMatrix2x2& FMatrix2x2::column_prosum(unsigned int const& from, unsigned int const& to, float const& rate) noexcept {
		if (from < 2U && to < 2U) {
			std::array<float, 2U> tmp;
			for (unsigned int i = 0U; i < 2U; ++i) {
				tmp = { p[i * 2U + to], p[i * 2U + from] * rate };
				p[i * 2U + to] = Math<float>::sum(tmp.data(), static_cast<unsigned int>(tmp.size()));
			}
		}
		return *this;
	}

	FMatrix2x2& FMatrix2x2::operator+=(FMatrix2x2 const& rhs) noexcept {
		store(p, add(load(p), load(rhs.p)));
		return *this;
	}

	FMatrix2x2& FMatrix2x2::operator-=(FMatrix2x2 const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	FMatrix2x2& FMatrix2x2::operator*=(float const& rhs) noexcept {
		store(p, mul(load(p), set1(rhs)));
		return *this;
	}

	FMatrix2x2& FMatrix2x2::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	FVector2 const FMatrix2x2::row(unsigned int const& idx) const noexcept {
		FVector2 result = FVT2_ZERO;
		if (idx < 2U) {
			for (unsigned int i = 0U; i < 2U; ++i) {
				result.p[i] = p[idx * 2U + i];
			}
		}
		return result;
	}

	FVector2 const FMatrix2x2::column(unsigned int const& idx) const noexcept {
		FVector2 result = FVT2_ZERO;
		if (idx < 2U) {
			for (unsigned int i = 0U; i < 2U; ++i) {
				result.p[i] = p[i * 2U + idx];
			}
		}
		return result;
	}

	FMatrix2x2 const FMatrix2x2::operator+() const noexcept {
		return *this;
	}

	FMatrix2x2 const FMatrix2x2::operator-() const noexcept {
		return *this * -1.0f;
	}

	FMatrix2x2 const transpose(FMatrix2x2 const& arg) noexcept {
		FMatrix2x2 result = arg;
		std::swap(result.m01, result.m10);
		return result;
	}

	FMatrix2x2 const adjoint(FMatrix2x2 const& arg) noexcept {
		FMatrix2x2 result;
		
		unsigned int idx1, idx2;
		unsigned int dx1, dx2;
		unsigned int dy1, dy2;

		for (idx1 = 0U; idx1 < 4U; ++idx1) {
			dx1 = idx1 / 2U;
			dy1 = idx1 % 2U;
			for (idx2 = 0U; idx2 < 4U; ++idx2) {
				dx2 = idx2 / 2U;
				dy2 = idx2 % 2U;
				if (dx1 != dx2 && dy1 != dy2) {
					result.p[idx1] = arg.p[dy2 * 2U + dx2];
					break;
				}
			}
			if ((dx1 + dy1) % 2U == 1U) {
				result.p[idx1] *= -1.0f;
			}
		}

		return result;
	}

	FMatrix2x2 const inverse(FMatrix2x2 const& arg) noexcept {
		FMatrix2x2 result = adjoint(arg);
		float size = determinant(arg);
		if (Math<float>::compare(size, 0.0f) > 0.0f) {
			result /= size;
		}
		return result;
	}

	float const determinant(FMatrix2x2 const& arg) noexcept {
		std::array<float, 2U> array = {
			  arg.m00 * arg.m11,
			-(arg.m01 * arg.m10)
		};
		return Math<float>::sum(array.data(), array.size());
	}

	FMatrix2x2 const direct(FVector2 const& lhs, FVector2 const& rhs) noexcept {
		FMatrix2x2 result;
		for (unsigned int idx = 0U; idx < 4U; ++idx) {
			result.p[idx] = lhs.p[idx % 2U] * rhs.p[idx / 2U];
		}
		return result;
	}

	FMatrix2x2 const wedge(FVector2 const& lhs, FVector2 const& rhs) noexcept {
		return direct(lhs, rhs) - direct(rhs, lhs);
	}

	FMatrix2x2 const operator+(FMatrix2x2 const& lhs, FMatrix2x2 const& rhs) noexcept {
		FMatrix2x2 result = lhs;
		result += rhs;
		return result;
	}

	FMatrix2x2 const operator-(FMatrix2x2 const& lhs, FMatrix2x2 const& rhs) noexcept {
		FMatrix2x2 result = lhs;
		result -= rhs;
		return result;
	}

	FMatrix2x2 const operator*(FMatrix2x2 const& lhs, FMatrix2x2 const& rhs) noexcept {
		FMatrix2x2 result;
		for (unsigned int idx = 0U; idx < 4U; ++idx) {
			result.p[idx] = dot(lhs.row(idx % 2U), rhs.column(idx / 2U));
		}
		return result;
	}

	FMatrix2x2 const operator*(FMatrix2x2 const& lhs, float const& rhs) noexcept {
		FMatrix2x2 result = lhs;
		result *= rhs;
		return result;
	}

	FMatrix2x2 const operator*(float const& lhs, FMatrix2x2 const& rhs) noexcept {
		return rhs * lhs;
	}

	FMatrix2x2 const operator/(FMatrix2x2 const& lhs, FMatrix2x2 const& rhs) noexcept {
		return lhs * inverse(rhs);
	}

	FMatrix2x2 const operator/(FMatrix2x2 const& lhs, float const& rhs) noexcept {
		FMatrix2x2 result = lhs;
		result /= rhs;
		return result;
	}

	FMatrix2x2 const operator/(float const& lhs, FMatrix2x2 const& rhs) noexcept {
		return lhs * inverse(rhs);
	}

	FVector2 const operator*(FVector2 const& lhs, FMatrix2x2 const& rhs) noexcept {
		FVector2 result;
		for (unsigned int idx = 0U; idx < 2U; ++idx) {
			result.p[idx] = dot(lhs, rhs.column(idx));
		}
		return result;
	}

	FVector2 const operator*(FMatrix2x2 const& lhs, FVector2 const& rhs) noexcept {
		FVector2 result;
		for (unsigned int idx = 0U; idx < 2U; ++idx) {
			result.p[idx] = dot(lhs.row(idx), rhs);
		}
		return result;
	}

	bool const operator==(FMatrix2x2 const& lhs, FMatrix2x2 const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < 2U; ++idx) {
			result = !Math<float>::compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(FMatrix2x2 const& lhs, FMatrix2x2 const& rhs) noexcept {
		return !(lhs == rhs);
	}
}
