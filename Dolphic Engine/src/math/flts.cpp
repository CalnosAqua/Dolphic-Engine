/**	@file	flts.cpp
 *	@brief	テンソル便利関数群
 */
#include "math/flts.hpp"
#include "math/const.hpp"

namespace dlph {
	Float2 constexpr set_vt(float const& x, float const& y) noexcept {
		return Float2( x, y );
	}

	Float3 constexpr set_vt(float const& x, float const& y, float const& z) noexcept {
		return Float3( x, y, z );
	}

	Float4 constexpr set_vt(float const& x, float const& y, float const& z, float const& w) noexcept {
		return Float4( x, y, z, w );
	}

	Float2x2 constexpr set_mtx(
		float const& m00, float const& m01,
		float const& m10, float const& m11
	) noexcept {
		return Float2x2{
			m00, m01,
			m10, m11
		};
	}

	Float3x3 constexpr set_mtx(
		float const& m00, float const& m01, float const& m02,
		float const& m10, float const& m11, float const& m12,
		float const& m20, float const& m21, float const& m22
	) noexcept {
		return Float3x3{
			m00, m01, m02,
			m10, m11, m12,
			m20, m21, m22
		};
	}

	Float4x4 constexpr set_mtx(
		float const& m00, float const& m01, float const& m02, float const& m03,
		float const& m10, float const& m11, float const& m12, float const& m13,
		float const& m20, float const& m21, float const& m22, float const& m23,
		float const& m30, float const& m31, float const& m32, float const& m33
	) noexcept {
		return Float4x4{
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33
		};
	}

	void set_mtx_column(Float2x2& mtx, Float2 const& vt, unsigned int const& idx) noexcept {
		if (idx < T2_CNT) {
			for (unsigned int i = 0; i < T2_CNT; ++i) {
				mtx.p[i * T2_CNT + idx] = vt.p[i];
			}
		}
	}

	void set_mtx_column(Float3x3& mtx, Float3 const& vt, unsigned int const& idx) noexcept {
		if (idx < T3_CNT) {
			for (unsigned int i = 0; i < T3_CNT; ++i) {
				mtx.p[i * T3_CNT + idx] = vt.p[i];
			}
		}
	}

	void set_mtx_column(Float4x4& mtx, Float4 const& vt, unsigned int const& idx) noexcept {
		if (idx < T4_CNT) {
			for (unsigned int i = 0; i < T4_CNT; ++i) {
				mtx.p[i * T4_CNT + idx] = vt.p[i];
			}
		}
	}

	void set_mtx_row(Float2x2& mtx, Float2 const& vt, unsigned int const& idx) noexcept {
		if (idx < T2_CNT) {
			for (unsigned int i = 0; i < T2_CNT; ++i) {
				mtx.p[idx * T2_CNT + i] = vt.p[i];
			}
		}
	}

	void set_mtx_row(Float3x3& mtx, Float3 const& vt, unsigned int const& idx) noexcept {
		if (idx < T3_CNT) {
			for (unsigned int i = 0; i < T3_CNT; ++i) {
				mtx.p[idx * T3_CNT + i] = vt.p[i];
			}
		}
	}

	void set_mtx_row(Float4x4& mtx, Float4 const& vt, unsigned int const& idx) noexcept {
		if (idx < T4_CNT) {
			for (unsigned int i = 0; i < T4_CNT; ++i) {
				mtx.p[idx * T4_CNT + i] = vt.p[i];
			}
		}
	}

	void trns_mtx(Float2x2& mtx) noexcept {
		float tmp;

		//	m01 <--> m10
		tmp		= mtx.m01;
		mtx.m01	= mtx.m10;
		mtx.m10	= tmp;
	}

	void trns_mtx(Float3x3& mtx) noexcept {
		float tmp;

		//	m01 <--> m10
		tmp		= mtx.m01;
		mtx.m01 = mtx.m10;
		mtx.m10 = tmp;

		//	m02 <--> m20
		tmp		= mtx.m02;
		mtx.m02 = mtx.m20;
		mtx.m20 = tmp;

		//	m12 <--> m21
		tmp		= mtx.m12;
		mtx.m12 = mtx.m21;
		mtx.m21 = tmp;
	}

	void trns_mtx(Float4x4& mtx) noexcept {
		float tmp;

		//	m01 <--> m10
		tmp		= mtx.m01;
		mtx.m01 = mtx.m10;
		mtx.m10 = tmp;

		//	m02 <--> m20
		tmp		= mtx.m02;
		mtx.m02 = mtx.m20;
		mtx.m20 = tmp;

		//	m03 <--> m30
		tmp		= mtx.m03;
		mtx.m03 = mtx.m30;
		mtx.m30 = tmp;

		//	m12 <--> m21
		tmp		= mtx.m12;
		mtx.m12 = mtx.m21;
		mtx.m21 = tmp;

		//	m13 <--> m31
		tmp		= mtx.m13;
		mtx.m13 = mtx.m31;
		mtx.m31 = tmp;

		//	m23 <--> m32
		tmp		= mtx.m23;
		mtx.m23 = mtx.m32;
		mtx.m32 = tmp;
	}

	Float2 const sep_column(Float2x2 const& mtx, unsigned int const& idx) noexcept {
		Float2 result{};
		if (idx < T2_CNT) {
			for (unsigned int i = 0; i < T2_CNT; ++i) {
				result.p[i] = mtx.p[i * T2_CNT + idx];
			}
		}
		return result;
	}

	Float3 const sep_column(Float3x3 const& mtx, unsigned int const& idx) noexcept {
		Float3 result{};
		if (idx < T3_CNT) {
			for (unsigned int i = 0; i < T3_CNT; ++i) {
				result.p[i] = mtx.p[i * T3_CNT + idx];
			}
		}
		return result;
	}

	Float4 const sep_column(Float4x4 const& mtx, unsigned int const& idx) noexcept {
		Float4 result{};
		if (idx < T4_CNT) {
			for (unsigned int i = 0; i < T4_CNT; ++i) {
				result.p[i] = mtx.p[i * T4_CNT + idx];
			}
		}
		return result;
	}

	Float2 const sep_row(Float2x2 const& mtx, unsigned int const& idx) noexcept {
		Float2 result{};
		if (idx < T2_CNT) {
			for (unsigned int i = 0; i < T2_CNT; ++i) {
				result.p[i] = mtx.p[idx * T2_CNT + i];
			}
		}
		return result;
	}

	Float3 const sep_row(Float3x3 const& mtx, unsigned int const& idx) noexcept {
		Float3 result{};
		if (idx < T3_CNT) {
			for (unsigned int i = 0; i < T3_CNT; ++i) {
				result.p[i] = mtx.p[idx * T3_CNT + i];
			}
		}
		return result;
	}

	Float4 const sep_row(Float4x4 const& mtx, unsigned int const& idx) noexcept {
		Float4 result{};
		if (idx < T4_CNT) {
			for (unsigned int i = 0; i < T4_CNT; ++i) {
				result.p[i] = mtx.p[idx * T4_CNT + i];
			}
		}
		return result;
	}
}
