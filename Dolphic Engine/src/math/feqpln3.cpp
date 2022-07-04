/**	@file	feqpln3.cpp
 *	@brief	平面方程式クラス
 */
#include "math/feqpln3.hpp"
#include <memory>

namespace dlph {
	FEqPlane3::FEqPlane3() noexcept :
		m_normal(),
		m_binormal(),
		m_tangent(),
		m_d(0.0f)
	{}

	FEqPlane3& FEqPlane3::init(FVector3 const& p1, FVector3 const& p2, FVector3 const& p3) noexcept {
		FVector3 v21, v23, normal, tangent;

		v21 = normalize(p1 - p2);
		v23 = normalize(p3 - p2);

		normal = cross(v21, v23);
		tangent = normalize(v21 + v23);

		m_normal = normal;
		m_tangent = tangent;
		m_binormal = cross(normal, tangent);
		m_d = -magnitude(normal);

		return *this;
	}

	void FEqPlane3::exit() noexcept {
		m_normal = Float3();
		m_binormal = Float3();
		m_tangent = Float3();
		m_d = 0.0f;
	}

	FVector3 const FEqPlane3::normal() const noexcept {
		return FVector3(m_normal);
	}

	FVector3 const FEqPlane3::binormal() const noexcept {
		return FVector3(m_binormal);
	}

	FVector3 const FEqPlane3::tangent() const noexcept {
		return FVector3(m_tangent);
	}

	FMatrix3x3 const FEqPlane3::matrix(HandSide const& hs) const noexcept {
		FMatrix3x3 result;

		memcpy(&result.p[0U], const_cast<float*>(m_tangent.p), sizeof(float) * T3_CNT);
		memcpy(&result.p[3U], const_cast<float*>(m_binormal.p), sizeof(float) * T3_CNT);
		memcpy(&result.p[6U], const_cast<float*>(m_normal.p), sizeof(float) * T3_CNT);

		if (hs == HandSide::RHS) {
			transpose(result);
		}

		return result;
	}
}
