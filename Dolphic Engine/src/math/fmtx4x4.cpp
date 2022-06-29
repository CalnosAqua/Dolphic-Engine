/**	@file	fmtx4x4.cpp
 *	@brief	単精度浮動小数点数用の四次正方行列クラス
 */
#include "structs/flt3x3.hpp"
#include "structs/flt4.hpp"
#include "math/fmtx4x4.hpp"
#include "math/fmtx3x3.hpp"
#include "math/fvec4.hpp"
#include "math/math.hpp"
#include "math/intrin.hpp"
#include <array>

namespace dlph {
	FMatrix4x4::FMatrix4x4() noexcept :
		FMatrix4x4(FMTX4x4_ZERO)
	{}

	FMatrix4x4::FMatrix4x4(std::initializer_list<float> const& args) noexcept :
		FMatrix4x4(FMTX4x4_ZERO)
	{
		unsigned int idx = 0U;
		for (float const& arg : args) {
			if (idx > 16U) {
				break;
			}
			p[idx] = arg;
			++idx;
		}
	}

	FMatrix4x4& FMatrix4x4::row(unsigned int const& idx, FVector4 const& vt) noexcept {
		if (idx < 4U) {
			for (unsigned int i = 0U; i < 4U; ++i) {
				p[idx * 4U + i] = vt.p[i];
			}
		}
		return *this;
	}

	FMatrix4x4& FMatrix4x4::column(unsigned int const& idx, FVector4 const& vt) noexcept {
		if (idx < 4U) {
			for (unsigned int i = 0U; i < 4U; ++i) {
				p[i * 4U + idx] = vt.p[i];
			}
		}
		return *this;
	}

	FMatrix4x4& FMatrix4x4::row_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from < 4U && to < 4U) {
			for (unsigned int i = 0U; i < 4U; ++i) {
				std::swap(p[from * 4U + i], p[to * 4U + i]);
			}
		}
		return *this;
	}

	FMatrix4x4& FMatrix4x4::column_swap(unsigned int const& from, unsigned int const& to) noexcept {
		if (from < 4U && to < 4U) {
			for (unsigned int i = 0U; i < 4U; ++i) {
				std::swap(p[i * 4U + from], p[i * 4U + to]);
			}
		}
		return *this;
	}

	FMatrix4x4& FMatrix4x4::row_scale(unsigned int const& idx, float const& rate) noexcept {
		if (idx < 4U) {
			for (unsigned int i = 0U; i < 4U; ++i) {
				p[idx * 4U + i] *= rate;
			}
		}
		return *this;
	}

	FMatrix4x4& FMatrix4x4::column_scale(unsigned int const& idx, float const& rate) noexcept {
		if (idx < 4U) {
			for (unsigned int i = 0U; i < 4U; ++i) {
				p[i * 4U + idx] *= rate;
			}
		}
		return *this;
	}

	FMatrix4x4& FMatrix4x4::row_prosum(unsigned int const& from, unsigned int const& to, float const& rate) noexcept {
		if (from < 4U && to < 4U) {
			std::array<float, 2U> tmp;
			for (unsigned int i = 0U; i < 4U; ++i) {
				tmp = { p[to * 4U + i], p[from * 4U + i] * rate };
				p[to * 4U + i] = Math<float>::sum(tmp.data(), static_cast<unsigned int>(tmp.size()));
			}
		}
		return *this;
	}

	FMatrix4x4& FMatrix4x4::column_prosum(unsigned int const& from, unsigned int const& to, float const& rate) noexcept {
		if (from < 4U && to < 4U) {
			std::array<float, 2U> tmp;
			for (unsigned int i = 0U; i < 4U; ++i) {
				tmp = { p[i * 4U + to], p[i * 4U + from] * rate };
				p[i * 4U + to] = Math<float>::sum(tmp.data(), static_cast<unsigned int>(tmp.size()));
			}
		}
		return *this;
	}

	FMatrix4x4& FMatrix4x4::operator+=(FMatrix4x4 const& rhs) noexcept {
		for (unsigned int idx = 0U; idx < 16U; idx += 4U) {
			store(&p[idx], add(load(&p[idx]), load(&rhs.p[idx])));
		}
		return *this;
	}

	FMatrix4x4& FMatrix4x4::operator-=(FMatrix4x4 const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	FMatrix4x4& FMatrix4x4::operator*=(float const& rhs) noexcept {
		vctr tmp = set1(rhs);
		for (unsigned int idx = 0U; idx < 16U; idx += 4U) {
			store(&p[idx], mul(load(&p[idx]), tmp));
		}
		return *this;
	}

	FMatrix4x4& FMatrix4x4::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	FVector4 const FMatrix4x4::row(unsigned int const& idx) const noexcept {
		FVector4 result = FVT4_ZERO;
		if (idx < 4U) {
			for (unsigned int i = 0U; i < 4U; ++i) {
				result.p[i] = p[idx * 4U + i];
			}
		}
		return result;
	}

	FVector4 const FMatrix4x4::column(unsigned int const& idx) const noexcept {
		FVector4 result = FVT4_ZERO;
		if (idx < 4U) {
			for (unsigned int i = 0U; i < 4U; ++i) {
				result.p[i] = p[i * 4U + idx];
			}
		}
		return result;
	}

	FMatrix4x4 const FMatrix4x4::operator+() const noexcept {
		return *this;
	}

	FMatrix4x4 const FMatrix4x4::operator-() const noexcept {
		return *this * -1.0f;
	}

	FMatrix4x4 const transpose(FMatrix4x4 const& arg) noexcept {
		FMatrix4x4 result = arg;
		std::swap(result.m01, result.m10);
		std::swap(result.m02, result.m20);
		std::swap(result.m03, result.m30);
		std::swap(result.m12, result.m21);
		std::swap(result.m13, result.m31);
		std::swap(result.m23, result.m32);
		return result;
	}

	FMatrix4x4 const adjoint(FMatrix4x4 const& arg) noexcept {
		FMatrix4x4 result;
		FMatrix3x3 tmp;

		unsigned int idx1, idx2, idx3;
		unsigned int  dx1, dx2;
		unsigned int  dy1, dy2;

		for (idx1 = 0U; idx1 < 16U; ++idx1) {
			dx1 = idx1 / 4U;
			dy1 = idx1 % 4U;
			for (idx2 = 0U, idx3 = 0U; idx2 < 16U; ++idx2) {
				dx2 = idx2 / 4U;
				dy2 = idx2 % 4U;
				if (dx1 != dx2 && dy1 != dy2) {
					tmp.p[idx3] = arg.p[dy2 * 4U + dx2];
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

	FMatrix4x4 const inverse(FMatrix4x4 const& arg) noexcept {
		FMatrix4x4 result = adjoint(arg);
		float size = determinant(arg);
		if (Math<float>::compare(size, 0.0f) > 0.0f) {
			result /= size;
		}
		return result;
	}

	float const determinant(FMatrix4x4 const& arg) noexcept {
		std::array<float, 24U> array = {
			  arg.m00 * arg.m12 * arg.m22 * arg.m33,
			  arg.m00 * arg.m12 * arg.m23 * arg.m31,
			  arg.m00 * arg.m13 * arg.m21 * arg.m32,
			  arg.m01 * arg.m10 * arg.m23 * arg.m32,
			  arg.m01 * arg.m12 * arg.m10 * arg.m33,
			  arg.m01 * arg.m13 * arg.m22 * arg.m30,
			  arg.m02 * arg.m10 * arg.m21 * arg.m33,
			  arg.m02 * arg.m13 * arg.m20 * arg.m31,
			  arg.m02 * arg.m11 * arg.m23 * arg.m30,
			  arg.m03 * arg.m10 * arg.m22 * arg.m31,
			  arg.m03 * arg.m11 * arg.m20 * arg.m32,
			  arg.m03 * arg.m12 * arg.m21 * arg.m30,
			-(arg.m00 * arg.m13 * arg.m22 * arg.m31),
			-(arg.m00 * arg.m12 * arg.m21 * arg.m33),
			-(arg.m00 * arg.m11 * arg.m23 * arg.m32),
			-(arg.m01 * arg.m10 * arg.m22 * arg.m33),
			-(arg.m01 * arg.m13 * arg.m20 * arg.m32),
			-(arg.m01 * arg.m12 * arg.m23 * arg.m30),
			-(arg.m02 * arg.m12 * arg.m20 * arg.m33),
			-(arg.m02 * arg.m10 * arg.m23 * arg.m31),
			-(arg.m02 * arg.m13 * arg.m21 * arg.m30),
			-(arg.m03 * arg.m10 * arg.m21 * arg.m32),
			-(arg.m03 * arg.m12 * arg.m20 * arg.m31),
			-(arg.m03 * arg.m11 * arg.m22 * arg.m30)
		};
		return Math<float>::sum(array.data(), array.size());
	}

	FMatrix4x4 const direct(FVector4 const& lhs, FVector4 const& rhs) noexcept {
		FMatrix4x4 result;
		for (unsigned int idx = 0U; idx < 16U; ++idx) {
			result.p[idx] = lhs.p[idx % 4U] * rhs.p[idx / 4U];
		}
		return result;
	}

	FMatrix4x4 const wedge(FVector4 const& lhs, FVector4 const& rhs) noexcept {
		return direct(lhs, rhs) - direct(rhs, lhs);
	}

	FMatrix4x4 const operator+(FMatrix4x4 const& lhs, FMatrix4x4 const& rhs) noexcept {
		FMatrix4x4 result = lhs;
		result += rhs;
		return result;
	}

	FMatrix4x4 const operator-(FMatrix4x4 const& lhs, FMatrix4x4 const& rhs) noexcept {
		FMatrix4x4 result = lhs;
		result -= rhs;
		return result;
	}

	FMatrix4x4 const operator*(FMatrix4x4 const& lhs, FMatrix4x4 const& rhs) noexcept {
		FMatrix4x4 result;
		for (unsigned int idx = 0U; idx < 16U; ++idx) {
			result.p[idx] = dot(lhs.row(idx % 4U), rhs.column(idx / 4U));
		}
		return result;
	}

	FMatrix4x4 const operator*(FMatrix4x4 const& lhs, float const& rhs) noexcept {
		FMatrix4x4 result = lhs;
		result *= rhs;
		return result;
	}

	FMatrix4x4 const operator*(float const& lhs, FMatrix4x4 const& rhs) noexcept {
		return rhs * lhs;
	}

	FMatrix4x4 const operator/(FMatrix4x4 const& lhs, FMatrix4x4 const& rhs) noexcept {
		return lhs * inverse(rhs);
	}

	FMatrix4x4 const operator/(FMatrix4x4 const& lhs, float const& rhs) noexcept {
		FMatrix4x4 result = lhs;
		result /= rhs;
		return result;
	}

	FMatrix4x4 const operator/(float const& lhs, FMatrix4x4 const& rhs) noexcept {
		return lhs * inverse(rhs);
	}

	FVector4 const operator*(FVector4 const& lhs, FMatrix4x4 const& rhs) noexcept {
		FVector4 result;
		for (unsigned int idx = 0U; idx < 4U; ++idx) {
			result.p[idx] = dot(lhs, rhs.column(idx));
		}
		return result;
	}

	FVector4 const operator*(FMatrix4x4 const& lhs, FVector4 const& rhs) noexcept {
		FVector4 result;
		for (unsigned int idx = 0U; idx < 4U; ++idx) {
			result.p[idx] = dot(lhs.row(idx), rhs);
		}
		return result;
	}

	bool const operator==(FMatrix4x4 const& lhs, FMatrix4x4 const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < 4U; ++idx) {
			result = !Math<float>::compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	bool const operator!=(FMatrix4x4 const& lhs, FMatrix4x4 const& rhs) noexcept {
		return !(lhs == rhs);
	}
}
