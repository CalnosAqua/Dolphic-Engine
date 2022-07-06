/**	@file	array.inl
 *	@brief	静的配列クラス
 */
#pragma once
#include "array.hpp"

namespace dlph {
	template<typename T>
	inline Array<T>::Array(Array<T>&& arg) noexcept :
		Array()
	{
		m_ptr = arg.m_ptr;
		arg.m_ptr = nullptr;

		m_size = arg.m_size;
		arg.m_size = 0U;
	}

	template<typename T>
	inline Array<T>::Array(Array<T> const& arg) noexcept :
		Array()
	{
		m_size = arg.m_size;
		m_ptr = new T[m_size];

		memcpy(m_ptr, arg.m_ptr, sizeof(T) * m_size);
	}

	template<typename T>
	inline Array<T>& Array<T>::operator=(Array<T>&& rhs) & noexcept {
		if (m_ptr != nullptr) {
			delete[] m_ptr;
		}

		m_ptr = arg.m_ptr;
		arg.m_ptr = nullptr;

		m_size = arg.m_size;
		arg.m_size = 0U;
	}

	template<typename T>
	inline Array<T>& Array<T>::operator=(Array<T> const& rhs) & noexcept {
		if (m_ptr != nullptr) {
			delete[] m_ptr;
		}
		
		m_size = arg.m_size;
		m_ptr = new T[m_size];

		memcpy(m_ptr, arg.m_ptr, sizeof(T) * m_size);
	}

	template<typename T>
	inline Array<T>::Array() noexcept :
		m_ptr(nullptr),
		m_size(0U)
	{}

	template<typename T>
	inline Array<T>::~Array() noexcept {
		if (m_ptr != nullptr) {
			delete[] m_ptr;
		}
		m_ptr = nullptr;
		m_size = 0U;
	}

	template<typename T>
	inline Array<T>::Array(std::initializer_list<T> const& args) noexcept :
		Array()
	{
		m_size = args.m_size;
		m_ptr = new T[m_size];

		size_t idx = 0U;
		for (T const& arg : args) {
			*(m_ptr + idx) = arg;
			++idx;
		}
	}

	template<typename T>
	inline Array<T>::Array(size_t const& size) noexcept :
		Array()
	{
		m_size = size;
		m_ptr = new T[m_size];

		for (size_t idx = 0U; idx < m_size; ++idx) {
			*(m_ptr + idx) = T();
		}
	}

	template<typename T>
	inline float* const Array<T>::cbegin() const noexcept {
		return m_ptr;
	}

	template<typename T>
	inline float* Array<T>::begin() noexcept {
		return m_ptr;
	}

	template<typename T>
	inline float* const Array<T>::cend() const noexcept {
		return m_ptr + m_size;
	}

	template<typename T>
	inline float* Array<T>::end() noexcept {
		return m_ptr + m_size;
	}

	template<typename T>
	inline size_t const Array<T>::size() const noexcept {
		return m_size;
	}

	template<typename T>
	inline T& Array<T>::operator[](size_t const& idx) & noexcept {
#if	defined(_DEBUG) || defined(DEBUG)
		_ASSERT_EXPR(idx < S, L"ERROR : INDEX NUMBER EXCEED ARRAY LENGTH.");
#endif
		return m_array[idx];
	}

	template<typename T>
	inline T Array<T>::operator[](size_t const& idx) const&& noexcept {
#if	defined(_DEBUG) || defined(DEBUG)
		_ASSERT_EXPR(idx < S, L"ERROR : INDEX NUMBER EXCEED ARRAY LENGTH.");
#endif
		return move(m_array[idx]);
	}

	template<typename T>
	inline T const& Array<T>::operator[](size_t const& idx) const& noexcept {
#if	defined(_DEBUG) || defined(DEBUG)
		_ASSERT_EXPR(idx < S, L"ERROR : INDEX NUMBER EXCEED ARRAY LENGTH.");
#endif
		return m_array[idx];
	}
}
