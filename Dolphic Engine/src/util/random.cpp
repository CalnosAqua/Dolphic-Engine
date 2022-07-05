/**	@file	random.cpp
 *	@brief	ランダム管理クラス
 */
#include "util/random.hpp"

namespace dlph {
	Random::Random() noexcept :
		m_device(),
		m_twister(m_device()),
		m_min(0.0),
		m_max(1.0)
	{}

	float const Random::min() const noexcept {
		return static_cast<float>(m_min);
	}

	float const Random::max() const noexcept {
		return static_cast<float>(m_max);
	}

	Random& Random::min(float const& val) noexcept {
		double temp = static_cast<double>(val);
		if (val <= m_max) {
			m_min = temp;
		}
		else {
			m_min = m_max;
			m_max = temp;
		}
		return *this;
	}

	Random& Random::max(float const& val) noexcept {
		double temp = static_cast<double>(val);
		if (val >= m_min) {
			m_max = temp;
		}
		else {
			m_max = m_min;
			m_min = temp;
		}
		return *this;
	}

	float const Random::generate() noexcept {
		std::uniform_real_distribution<double> dist(m_min, m_max);
		return static_cast<float>(dist(m_twister));
	}
}
