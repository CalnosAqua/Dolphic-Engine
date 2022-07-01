/**	@file	fpln3.cpp
 *	@brief	平面クラス
 */
#include "gmtry/fpln3.hpp"
#include "math/math.hpp"
#include <numeric>

namespace dlph {
	FPlane3::FPlane3() noexcept :
		m_center(FVT3_ZERO),
		m_posture(FQTR_ZERO),
		m_width(0.0f),
		m_height(0.0f),
		m_horizontal(0U),
		m_vertical(0U)
	{}

	FPlane3& FPlane3::init(
		FVector3 const& center,
		FQuaternion const& posture,
		Float2 const& size,
		UInt2 const& partial_count
	) noexcept {
		m_center = center;
		m_posture = posture;
		m_width = fabsf(size.x);
		m_height = fabsf(size.y);
		m_horizontal = partial_count.x;
		m_vertical = partial_count.y;

		if (Math<float>::compare(m_width, 0.0f) <= 0) {
			m_width = 1.0f;
		}
		if (Math<float>::compare(m_height, 0.0f) <= 0) {
			m_height = 1.0f;
		}
		if (Math<float>::compare(magnitude(m_posture), 1.0f) <= 0) {
			m_posture = normalize(m_posture);
		}
		if (m_posture == FQTR_ZERO) {
			m_posture = FQTR_UNIT;
		}
		if (m_horizontal == 0U) {
			m_horizontal = 1U;
		}
		if (m_vertical == 0U) {
			m_vertical = 1U;
		}

		return *this;
	}

	void FPlane3::exit() noexcept {
		m_center = FVT3_ZERO;
		m_posture = FQTR_ZERO;
		m_width = 0.0f;
		m_height = 0.0f;
		m_horizontal = 0U;
		m_vertical = 0U;
	}
}
