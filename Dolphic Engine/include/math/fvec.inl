/**	@file	fvec.inl
 *	@brief	ベクトルクラス
 */
#pragma once
#include "fvec.hpp"
#include "math.hpp"
#include "intrin.hpp"
#include <crtdbg.h>

namespace dlph {
	template<size_t N>
	inline FVector<N>::FVector() noexcept :
		m_array{}
	{}

	template<size_t N>
	inline FVector<N>::FVector(std::initializer_list<float> const& args) noexcept :
		FVector()
	{
		unsigned int idx = 0U;
		for (float const& arg : args) {
			if (idx > 4U) {
				break;
			}
			m_array[idx] = arg;
			++idx;
		}
	}

	template<size_t N>
	inline float& FVector<N>::operator[](size_t const& idx) & noexcept {
#if	defined(_DEBUG) || defined(DEBUG)
		_ASSERT_EXPR(idx < N, L"ERROR : INDEX NUMBER EXCEED ARRAY LENGfloatH.");
#endif
		return m_array[idx];
	}

	template<size_t N>
	inline float FVector<N>::operator[](size_t const& idx) const&& noexcept {
#if	defined(_DEBUG) || defined(DEBUG)
		_ASSERT_EXPR(idx < N, L"ERROR : INDEX NUMBER EXCEED ARRAY LENGfloatH.");
#endif
		return move(m_array[idx]);
	}

	template<size_t N>
	inline float const& FVector<N>::operator[](size_t const& idx) const& noexcept {
#if	defined(_DEBUG) || defined(DEBUG)
		_ASSERT_EXPR(idx < N, L"ERROR : INDEX NUMBER EXCEED ARRAY LENGfloatH.");
#endif
		return m_array[idx];
	}

	template<size_t N>
	inline float* const FVector<N>::cbegin() const noexcept {
		return &m_array[0];
	}

	template<size_t N>
	inline float* FVector<N>::begin() noexcept {
		return &m_array[0];
	}

	template<size_t N>
	inline float* const FVector<N>::cend() const noexcept {
		return &m_array[N];
	}

	template<size_t N>
	inline float* FVector<N>::end() noexcept {
		return &m_array[N];
	}

	template<size_t N>
	inline size_t const FVector<N>::size() const noexcept {
		return N;
	}

	template<size_t N>
	inline FVector<N>::operator float* () const noexcept {
		return const_cast<float*>(m_array);
	}

	template<size_t N>
	inline FVector<N>& FVector<N>::operator+=(FVector<N> const& rhs) noexcept {
		for (size_t idx = 0U; idx < N; idx += 4U) {
			store(&m_array[idx], add(load(&m_array[idx]), load(&rhs[idx])));
		}
		return *this;
	}

	template<size_t N>
	inline FVector<N>& FVector<N>::operator-=(FVector<N> const& rhs) noexcept {
		*this += -rhs;
		return *this;
	}

	template<size_t N>
	inline FVector<N>& FVector<N>::operator*=(float const& rhs) noexcept {
		vctr tmp = set1(rhs);
		for (size_t idx = 0U; idx < N; idx += 4U) {
			store(&m_array[idx], mul(load(&m_array[idx]), tmp));
		}
		return *this;
	}

	template<size_t N>
	inline FVector<N>& FVector<N>::operator/=(float const& rhs) noexcept {
		*this *= 1.0f / rhs;
		return *this;
	}

	template<size_t N>
	inline FVector<N> const FVector<N>::operator+() const noexcept {
		return *this;
	}

	template<size_t N>
	inline FVector<N> const FVector<N>::operator-() const noexcept {
		return *this * -1.0f;
	}

	template<size_t N>
	inline float const dot(FVector<N> const& lhs, FVector<N> const& rhs) noexcept {
		float alignas(16) temps[N];
		for (size_t idx = 0U; idx < N; idx += 4U) {
			store(&temps[idx], mul(load(&lhs[idx]), load(&rhs[idx])));
		}
		return Math<float>::sum(temps, N);
	}

	template<size_t N>
	inline FVector<N> const normalize(FVector<N> const& arg) noexcept {
		FVector<N> result = arg;
		float length = magnitude(arg);
		if (Math<float>::compare(length, 0.0f) > 0) {
			result /= length;
		}
		return result;
	}

	template<size_t N>
	inline float const sqr_magnitude(FVector<N> const& arg) noexcept {
		return dot(arg, arg);
	}

	template<size_t N>
	inline float const magnitude(FVector<N> const& arg) noexcept {
		return Math<float>::sqrt(sqr_magnitude(arg));
	}

	template<size_t N>
	inline FVector<N> const operator+(FVector<N> const& lhs, FVector<N> const& rhs) noexcept {
		FVector<N> result = lhs;
		result += rhs;
		return result;
	}

	template<size_t N>
	inline FVector<N> const operator-(FVector<N> const& lhs, FVector<N> const& rhs) noexcept {
		FVector<N> result = lhs;
		result -= rhs;
		return result;
	}

	template<size_t N>
	inline FVector<N> const operator*(FVector<N> const& lhs, float const& rhs) noexcept {
		FVector<N> result = lhs;
		result *= rhs;
		return result;
	}

	template<size_t N>
	inline FVector<N> const operator*(float const& lhs, FVector<N> const& rhs) noexcept {
		return rhs * lhs;
	}

	template<size_t N>
	inline FVector<N> const operator/(FVector<N> const& lhs, float const& rhs) noexcept {
		FVector<N> result = lhs;
		result /= rhs;
		return result;
	}

	template<size_t N>
	inline bool const operator==(FVector<N> const& lhs, FVector<N> const& rhs) noexcept {
		bool result = true;
		for (unsigned int idx = 0U; result && idx < 4U; ++idx) {
			result = !Math<float>::compare(lhs.p[idx], rhs.p[idx]);
		}
		return result;
	}

	template<size_t N>
	inline bool const operator!=(FVector<N> const& lhs, FVector<N> const& rhs) noexcept {
		return !(lhs == rhs);
	}
}
