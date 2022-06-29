/**	@file	fpln3.cpp
 *	@brief	三次元平面方程式・接ベクトル行列クラス
 */

#include "geo/fpln3.hpp"
#include "structs/flt3x3.hpp"
#include "structs/flt3.hpp"
#include <memory>

namespace dlph {
	FPlane3::FPlane3() noexcept :
		m_mtx(FMTX3x3_ZERO),
		m_d(0.0f),
		m_side(HandSide::RHS)
	{}

	FPlane3& FPlane3::init(HandSide const& hs, FVector3 const& pt1, FVector3 const& pt2, FVector3 const& pt3) noexcept {
		FVector3 vt21, vt23, n, t, b;
		m_side = hs;

		vt21 = normalize(pt1 - pt2);
		vt23 = normalize(pt3 - pt2);

		n = cross(vt21, vt23);
		t = normalize(vt21 + vt23);
		b = cross(n, t);

		m_d = -magnitude(n);

		memcpy(&m_mtx.p[0U], t.p, sizeof(float) * 3U);
		memcpy(&m_mtx.p[3U], b.p, sizeof(float) * 3U);
		memcpy(&m_mtx.p[6U], n.p, sizeof(float) * 3U);

		if (m_side == HandSide::RHS) {
			transpose(m_mtx);
		}
		return *this;
	}

	FVector3 const FPlane3::normal() const noexcept {
		static FVector3 constexpr ELEMENT = FVector3(0.0f, 0.0f, 1.0f);
		FVector3 result;
		switch (m_side) {
		case HandSide::LHS:
			result = ELEMENT * m_mtx;
			break;
		case HandSide::RHS:
			result = m_mtx * ELEMENT;
			break;
		}
		return result;
	}

	FVector3 const FPlane3::binormal() const noexcept {
		static FVector3 constexpr ELEMENT = FVector3(0.0f, 1.0f, 0.0f);
		FVector3 result;
		switch (m_side) {
		case HandSide::LHS:
			result = ELEMENT * m_mtx;
			break;
		case HandSide::RHS:
			result = m_mtx * ELEMENT;
			break;
		}
		return result;
	}

	FVector3 const FPlane3::tangent() const noexcept {
		static FVector3 constexpr ELEMENT = FVector3(1.0f, 0.0f, 0.0f);
		FVector3 result;
		switch (m_side) {
		case HandSide::LHS:
			result = ELEMENT * m_mtx;
			break;
		case HandSide::RHS:
			result = m_mtx * ELEMENT;
			break;
		}
		return result;
	}
}
