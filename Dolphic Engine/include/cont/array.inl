/**	@file	array.inl
 *	@brief	配列クラス
 */
#pragma once
#include "array.hpp"
#include <memory>
#include <crtdbg.h>

namespace dlph {
	template<typename T>
	inline Array<T>::Array(Array<T>&& arg) noexcept :
		Array()
	{
		m_ptr = arg.m_ptr;
		m_size = arg.m_size;
		m_capacity = arg.m_capacity;
		m_alloc = arg.m_alloc;

		arg.m_ptr = nullptr;
		arg.m_size = 0U;
		arg.m_capacity = 0U;
		arg.m_alloc = 0U;
	}

	template<typename T>
	inline Array<T>::Array(Array<T> const& arg) noexcept :
		Array()
	{
		m_size = arg.m_size;
		m_alloc = arg.m_alloc;
		normalize();

		memcpy(m_ptr, arg.m_ptr, sizeof(T) * m_size);
	}

	template<typename T>
	inline Array<T>& Array<T>::operator=(Array<T>&& rhs) & noexcept {
		this->~Array();

		m_ptr = arg.m_ptr;
		m_size = arg.m_size;
		m_capacity = arg.m_capacity;
		m_alloc = arg.m_alloc;

		arg.m_ptr = nullptr;
		arg.m_size = 0U;
		arg.m_capacity = 0U;
		arg.m_alloc = 0U;

		return *this;
	}

	template<typename T>
	inline Array<T>& Array<T>::operator=(Array<T> const& rhs) & noexcept {
		this->~Array();

		m_size = arg.m_size;
		m_alloc = arg.m_alloc;
		normalize();

		memcpy(m_ptr, arg.m_ptr, sizeof(T) * m_size);
		return *this;
	}

	template<typename T>
	inline Array<T>::Array() noexcept :
		m_ptr(nullptr),
		m_size(0U),
		m_capacity(0U),
		m_alloc(0U)
	{}

	template<typename T>
	inline Array<T>::~Array() noexcept {
		if (m_ptr != nullptr) {
			delete[] m_ptr;
			m_ptr = nullptr;
		}
		m_size = 0U;
		m_capacity = 0U;
		m_alloc = 0U;
	}

	template<typename T>
	inline Array<T>::Array(std::initializer_list<T> const& args) noexcept :
		Array()
	{

	}

	template<typename T>
	inline T& Array<T>::operator[](size_t const& idx) & noexcept {
		_ASSERT_EXPR(idx < m_size, L"[ERROR]\nINDEX EXCEED ARRAY LENGTH.\nPLEASE, RESTART APPLICATION.");
		return *(m_ptr + idx);
	}

	template<typename T>
	inline T Array<T>::operator[](size_t const& idx) const&& noexcept {
		_ASSERT_EXPR(idx < m_size, L"[ERROR]\nINDEX EXCEED ARRAY LENGTH.\nPLEASE, RESTART APPLICATION.");
		return std::move(*(m_ptr + idx));
	}

	template<typename T>
	inline T const& Array<T>::operator[](size_t const& idx) const& noexcept {
		_ASSERT_EXPR(idx < m_size, L"[ERROR]\nINDEX EXCEED ARRAY LENGTH.\nPLEASE, RESTART APPLICATION.");
		return *(m_ptr + idx);
	}

	template<typename T>
	inline size_t const Array<T>::size() const noexcept {
		return m_size;
	}

	template<typename T>
	inline T* const Array<T>::begin() const noexcept {
		return m_ptr;
	}

	template<typename T>
	inline T* const Array<T>::end() const noexcept {
		return m_ptr + m_size;
	}

	template<typename T>
	inline Array<T>& Array<T>::insert(size_t const& idx, T&& data) noexcept {
		if (m_size + 1U < m_capacity) {
			expansion();
		}

		size_t index = idx;
		if (index > m_size) {
			index = m_size
		}

		if ((m_size - index) != 0) {
			memmove(m_ptr + index, m_ptr + (index + 1U), sizeof(T) * (m_size - index));
		}
		*(m_ptr + index) = data;

		return *this;
	}

	template<typename T>
	inline Array<T>& Array<T>::insert(size_t const& idx, T const& data) noexcept {
		if (m_size + 1U < m_capacity) {
			expansion();
		}

		size_t index = idx;
		if (index > m_size) {
			index = m_size
		}

		if ((m_size - index) != 0) {
			memmove(m_ptr + index, m_ptr + (index + 1U), sizeof(T) * (m_size - index));
		}
		*(m_ptr + index) = data;

		return *this;
	}

	template<typename T>
	inline Array<T>& Array<T>::insert(size_t const& idx, std::initializer_list<T> const& datas) noexcept {
		T temp[datas.size()]{};
		size_t i = 0U;
		for (T const& data : datas) {
			temp[i] = data;
			++i;
		}
		insert(idx, temp, datas.size());
		return *this;
	}

	template<typename T>
	inline Array<T>& Array<T>::insert(size_t const& idx, T const* const& datas, size_t const& size) noexcept {
		if (m_size + size < m_capacity) {
			size_t capacity, temp;
			temp = m_size + size;
			if (temp % m_alloc != 0U) {
				capacity = 1U;
			}
			else {
				capacity = 0U;
			}
			capacity += temp / m_alloc;
			capacity *= m_alloc;

			if (!reallocate(capacity)) {
				return *this;
			}
		}

		size_t index = idx;
		if (index > m_size) {
			index = m_size
		}

		if ((m_size - index) != 0) {
			memmove(m_ptr + index, m_ptr + (index + size), sizeof(T) * (m_size - index));
		}
		memcpy(m_ptr + index, datas, sizeof(T) * size);

		return *this;
	}

	template<typename T>
	inline Array<T>& Array<T>::push_front(T&& data) noexcept {
		return insert(0U, data);
	}

	template<typename T>
	inline Array<T>& Array<T>::push_front(T const& data) noexcept {
		return insert(0U, data);
	}

	template<typename T>
	inline Array<T>& Array<T>::push_front(std::initializer_list<T> const& datas) noexcept {
		return insert(0U, datas);
	}

	template<typename T>
	inline Array<T>& Array<T>::push_front(T const* const& datas, size_t const& size) noexcept {
		return insert(0U, datas, size);
	}

	template<typename T>
	inline Array<T>& Array<T>::push_back(T&& data) noexcept {
		return insert(m_size, data);
	}

	template<typename T>
	inline Array<T>& Array<T>::push_back(T const& data) noexcept {
		return insert(m_size, data);
	}

	template<typename T>
	inline Array<T>& Array<T>::push_back(std::initializer_list<T> const& datas) noexcept {
		return insert(m_size, datas);
	}

	template<typename T>
	inline Array<T>& Array<T>::push_back(T const* const& datas, size_t const& size) noexcept {
		return insert(m_size, datas, size);
	}

	template<typename T>
	inline Array<T>& Array<T>::remove(size_t const& idx) noexcept {
		size_t index = idx;
		if (index > m_size - 1U) {
			index = m_size - 1U
		}

		if (index != m_size - 1U) {
			memmove(m_ptr + index, m_ptr + index + 1U, sizeof(T) * (m_size - index));
		}
		memset(m_ptr + (m_size - 1U), 0, sizeof(T) * (m_capacity - m_size));
		--m_size;

		return *this;
	}

	template<typename T>
	inline Array<T>& Array<T>::remove(size_t const& min, size_t const& max) noexcept {
		size_t mn, mx, length;
		if (min >= m_size) {
			mn = m_size - 1U;
		}
		if (max >= m_size) {
			mx = m_size - 1U;
		}

		if (mn > mx) {
			size_t tmp;
			tmp	= mn;
			mn	= mx;
			mx	= tmp;
		}
		length = mx - mn;

		memmove(m_ptr + mn, m_ptr + mx, sizeof(T) * (m_size - mx));
		memset(m_ptr + (mn + m_size - length), 0, sizeof(T) * m_capacity - (mn + m_size - length));
		m_size = m_size - length;

		return *this;
	}

	template<typename T>
	inline Array<T>& Array<T>::pop_front(size_t const& size) noexcept {
		size_t count = size;
		if (count >= m_size) {
			return clear();
		}
		memmove(m_ptr + count, m_ptr, sizeof(T) * (m_size - count));
		memset(m_ptr + count, 0, sizeof(T) * (m_size - count));
		m_size -= count;
		return *this;
	}

	template<typename T>
	inline Array<T>& Array<T>::pop_back(size_t const& size) noexcept {
		size_t count = size;
		if (count >= m_size) {
			return clear();
		}
		memset(m_ptr + count, 0, sizeof(T) * (m_size - count));
		m_size -= count;
		return *this;
	}

	template<typename T>
	inline Array<T>& Array<T>::clear() noexcept {
		if (m_ptr != nullptr) {
			delete[] m_ptr;
			m_ptr = nullptr;
		}
		m_size = 0U;
		m_capacity = 0U;
	}

	template<typename T>
	inline Array<T>& Array<T>::reflesh() noexcept {
		normalize();
		return *this;
	}

	template<typename T>
	inline bool const Array<T>::reallocate(size_t const& size) noexcept {
		if (m_alloc == 0U) {
			return false;
		}
		if (size == m_capacity) {
			return true;
		}

		size_t count;
		T* ptr = new T[size];

		if (m_size > size) {
			count = size;
		}
		else {
			count = m_size;
		}

		if (m_ptr != nullptr) {
			memcpy(ptr, m_ptr, sizeof(T) * count);

			// 消去する前に 0 クリアでデータを破壊しておく
			memset(m_ptr, 0, sizeof(T) * m_capacity);
			delete[] m_ptr;
			m_ptr = nullptr;
		}

		m_ptr = ptr;
		ptr = nullptr;

		m_capacity = size;

		return true;
	}

	template<typename T>
	inline bool const Array<T>::normalize() noexcept {
		size_t capacity;
		if (m_size % m_alloc != 0U) {
			capacity = 1U;
		}
		else {
			capacity = 0U;
		}
		capacity += m_size / m_alloc;
		capacity *= m_alloc;
		return reallocate(capacity);
	}

	template<typename T>
	inline bool const Array<T>::expansion(size_t const& pack_size) noexcept {
		size_t capacity;
		capacity = m_capacity;
		capacity += m_alloc * pack_size;
		return reallocate(capacity);
	}
}
