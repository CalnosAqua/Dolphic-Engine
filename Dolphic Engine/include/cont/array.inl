/**	@file	array.inl
 *	@brief	静的配列クラス
 */
#pragma once
#include "array.hpp"

namespace dlph {
	template<typename T, size_t S>
	inline Array<T, S>::Array(std::initializer_list<T> const& args) noexcept :
		Array()
	{
		size_t idx = 0;
		for (T const& arg : args) {
			if (idx >= args.size()) {
				break;
			}
			m_array[idx] = arg;
			++idx;
		}
	}

	template<typename T, size_t S>
	inline Array<T, S>::Array() noexcept :
		m_array{}
	{}

	template<typename T, size_t S>
	inline T& Array<T, S>::operator[](size_t const& idx) & noexcept {
#if defined(DEBUG) | defined(_DEBUG)
		_ASSERT_EXPR(idx < S, "Error : The specified index exceeds the array length.\n");
#endif
		return m_array[idx];
	}

	template<typename T, size_t S>
	inline T Array<T, S>::operator[](size_t const& idx) const&& noexcept {
#if defined(DEBUG) | defined(_DEBUG)
		_ASSERT_EXPR(idx < S, "Error : The specified index exceeds the array length.\n");
#endif
		return std::move(m_array[idx]);
	}

	template<typename T, size_t S>
	inline T const& Array<T, S>::operator[](size_t const& idx) const& noexcept {
#if defined(DEBUG) | defined(_DEBUG)
		_ASSERT_EXPR(idx < S, "Error : The specified index exceeds the array length.\n");
#endif
		return m_array[idx];
	}

	template<typename T, size_t S>
	inline T* const Array<T, S>::begin() const noexcept {
		return const_cast<T*>(&m_array[0]);
	}

	template<typename T, size_t S>
	inline T* const Array<T, S>::end() const noexcept {
		return const_cast<T*>(&m_array[S]);
	}

	template<typename T, size_t S>
	inline size_t const Array<T, S>::size() const noexcept {
		return S;
	}
}
