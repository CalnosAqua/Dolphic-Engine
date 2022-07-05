/**	@file	clock.hpp
 *	@brief	汎用時計クラス
 */
#include "util/clock.hpp"

namespace dlph {
	Clock::Clock() noexcept :
		m_begin(),
		m_current(),
		m_latest(),
		m_inited()
	{}

	void Clock::init() noexcept {
		time_t temp;

		temp = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
		m_begin = temp;
		m_latest = temp;
		m_inited = true;
	}

	void Clock::exit() noexcept {
		m_begin = 0;
		m_current = 0;
		m_latest = 0;
		m_inited = false;
	}

	void Clock::update() noexcept {
		if (!m_inited) {
			return;
		}
		time_t temp;

		temp = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
		m_current = m_latest;
		m_latest = temp;
	}

	float const Clock::delta_time() const noexcept {
		float result = 0.0f;
		if (m_inited) {
			result = static_cast<float>(m_latest - m_current) / 1.0E+6f;
		}
		return result;
	}

	float const Clock::difference_time() const noexcept {
		float result = 0.0f;
		if (m_inited) {
			result = static_cast<float>(m_latest - m_begin) / 1.0E+6f;
		}
		return result;
	}
}
