/**	@file	timer.cpp
 *	@brief	汎用タイムスイッチクラス
 */
#include "times/timer.hpp"
#include "math/math.hpp"

namespace dlph {
	Timer::Timer() noexcept :
		m_state(TimerState::Wait),
		m_target(1.0f),
		m_current(0.0f)
	{}

	void Timer::update(Clock const& clock) noexcept {
		if (!Math<float>::compare(m_target, 0.0f) || Math<float>::compare(m_current, m_target) >= 0) {
			return;
		}

		switch (m_state) {
		case TimerState::Wait:
			m_state = TimerState::Progress;
			break;
		case TimerState::Progress:
			m_current += Math<float>::clamp(clock.delta_time(), 0.0f, 1.0f);
			if (Math<float>::compare(m_current, m_target) >= 0) {
				m_state = TimerState::Finish;
				m_current = m_target;
			}
			break;
		}
	}

	void Timer::reset() noexcept {
		m_state = TimerState::Wait;
		m_current = 0.0f;
	}

	void Timer::target_time(float const& arg) noexcept {
		m_target = Math<float>::clamp(arg, 0.0f, FLT_MAX);
	}

	bool const Timer::is_finished() const noexcept {
		return m_state == TimerState::Finish;
	}

	float const Timer::target_time() const noexcept {
		return m_target;
	}

	float const Timer::current_time() const noexcept {
		return m_current;
	}

	float const Timer::progress_rate() const noexcept {
		return m_current / m_target;
	}

	float const Timer::progress_difference() const noexcept {
		return Math<float>::sum({ m_target, -m_current });
	}
}
