/**	@file	FRay.inl
 *	@brief	光線クラス
 */
#pragma once
#include "fray.hpp"

namespace dlph {
	template<typename T>
	inline FRay<T>::FRay() noexcept :
		m_center(),
		m_direct(),
		m_radius(0.0f)
	{}

	template<typename T>
	inline T const FRay<T>::operator[](float const& rate) const noexcept {
		return m_center + m_direct * rate;
	}

	template<typename T>
	inline FRay<T>& FRay<T>::center(T const& arg) const noexcept {
		m_center = arg;
		return *this;
	}

	template<typename T>
	inline FRay<T>& FRay<T>::direction(T const& arg) const noexcept {
		m_direct = arg;
		return *this;
	}

	template<typename T>
	inline FRay<T>& FRay<T>::radius(float const& arg) const noexcept {
		m_radius = arg;
		return *this;
	}

	template<typename T>
	inline T const& FRay<T>::center() const noexcept {
		return m_center;
	}

	template<typename T>
	inline T const& FRay<T>::direction() const noexcept {
		return m_direct;
	}

	template<typename T>
	inline float const& FRay<T>::radius() const noexcept {
		return m_radius;
	}
}
