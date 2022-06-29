/**	@file	vector.inl
 *	@brief	動的配列クラス
 */
#pragma once
#include "vector.hpp"
#include <memory>
#include <numeric>
#include <crtdbg.h>

namespace dlph {
	template<typename T>
	inline Vector<T>::Vector(Vector<T>&& arg) noexcept :
		Vector()
	{
		m_alloc = arg.m_alloc;

		m_ptr = arg.m_ptr;
		m_size = arg.m_size;
		scale_normalize();

		arg.m_ptr = nullptr;
		arg.~Vector();
	}

	template<typename T>
	inline Vector<T>::Vector(Vector<T> const& arg) noexcept :
		Vector()
	{
		m_alloc = arg.m_alloc;

		m_size = arg.m_size;
		scale_normalize();

		size_t idx = 0U;
		for (T const& data : arg) {
			*(m_ptr + idx) = data;
			++idx;
		}
	}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(Vector<T>&& rhs) & noexcept {
		if (m_ptr) {
			delete[] m_ptr;
			m_ptr = nullptr;
		}

		m_alloc = arg.m_alloc;

		m_ptr = arg.m_ptr;
		m_size = arg.m_size;
		scale_normalize();

		arg.m_ptr = nullptr;
		arg.~Vector();

		return *this;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(Vector<T> const& rhs) & noexcept {
		if (m_ptr) {
			delete[] m_ptr;
			m_ptr = nullptr;
		}

		m_alloc = arg.m_alloc;

		m_size = arg.m_size;
		scale_normalize();

		size_t idx = 0U;
		for (T const& data : arg) {
			*(m_ptr + idx) = data;
			++idx;
		}

		return *this;
	}

	template<typename T>
	inline Vector<T>::Vector() noexcept :
		m_ptr(nullptr),
		m_size(0U),
		m_capacity(0U),
		m_alloc(0U)
	{}

	template<typename T>
	inline Vector<T>::Vector(std::initializer_list<T> const& args) noexcept :
		Vector()
	{
		m_alloc = 16U;

		m_size = args.m_size;
		scale_normalize();

		size_t idx = 0U;
		for (T const& arg : args) {
			*(m_ptr + idx) = data;
			++idx;
		}
	}

	template<typename T>
	inline Vector<T>::~Vector() noexcept {
		if (m_ptr) {
			delete[] m_ptr;
			m_ptr = nullptr;
		}
		m_size = 0U;
		m_capacity = 0U;
		m_alloc = 0U;
	}

	template<typename T>
	inline size_t const Vector<T>::size() const noexcept {
		return m_size;
	}

	template<typename T>
	inline T* const Vector<T>::begin() const noexcept {
		return m_ptr;
	}

	template<typename T>
	inline T* const Vector<T>::end() const noexcept {
		return m_ptr + m_size;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::alloc_size(size_t const& size) noexcept {
		m_alloc = (size != 0) ? size : 1U;
		return *this;
	}

	template<typename T>
	inline size_t const Vector<T>::alloc_size() const noexcept {
		return m_alloc;
	}

	template<typename T>
	inline T& Vector<T>::operator[](size_t const& idx) & noexcept {
#if defined(_DEBUG) | defined(DEBUG)
		_ASSERT_EXPR(idx < m_size, "ERROR : THE INDEX OUT-NUMBERS THE NUMBER OF DATA.");
#endif
		return *(m_ptr + idx);
	}

	template<typename T>
	inline T Vector<T>::operator[](size_t const& idx) const&& noexcept {
#if defined(_DEBUG) | defined(DEBUG)
		_ASSERT_EXPR(idx < m_size, "ERROR : THE INDEX OUT-NUMBERS THE NUMBER OF DATA.");
#endif
		return std::move(*(m_ptr + idx));
	}

	template<typename T>
	inline T const& Vector<T>::operator[](size_t const& idx) const& noexcept {
#if defined(_DEBUG) | defined(DEBUG)
		_ASSERT_EXPR(idx < m_size, "ERROR : THE INDEX OUT-NUMBERS THE NUMBER OF DATA.");
#endif
		return *(m_ptr + idx);
	}

	template<typename T>
	inline Vector<T>& Vector<T>::insert(size_t const& idx, T&& arg) noexcept {

		/*=========================================
		 *	push_back や push_front はそれぞれ挿入位置の違いだけである為、
		 *	実際はインデックスを調整するだけで実装ができる。
		 */

		size_t index = (idx <= m_size) ? idx : m_size;
		if (m_capacity < m_size + 1U && m_alloc != 0U) {
			scale_up();
		}
		else {
			return *this;
		}

		/*=========================================
		 *	添字の位置にデータを入れる際に前のデータを消してしまう可能性がある為、
		 *	そこに元々あったデータを 0 クリアで壊した上で代入を行う。
		 *	元々のデータはすでに移動を終えているため壊してしまっても問題はない（と思う）。
		 */

		memmove(m_ptr + index, m_ptr + index + 1U, sizeof(T) * (m_size - index));
		memset(m_ptr + index, 0, sizeof(T));
		*(m_ptr + index) = arg;
		arg = T();
		++m_size;
		return *this;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::insert(size_t const& idx, T const& arg) noexcept {

		/*=========================================
		 *	push_back や push_front はそれぞれ挿入位置の違いだけである為、
		 *	実際はインデックスを調整するだけで実装ができる。
		 */

		size_t index = (idx <= m_size) ? idx : m_size;
		if (m_capacity < m_size + 1U && m_alloc != 0U) {
			scale_up();
		}
		else {
			return *this;
		}

		/*=========================================
		 *	添字の位置にデータを入れる際に前のデータを消してしまう可能性がある為、
		 *	そこに元々あったデータを 0 クリアで壊した上で代入を行う。
		 *	元々のデータはすでに移動を終えているため壊してしまっても問題はない（と思う）。
		 */

		memmove(m_ptr + index, m_ptr + index + 1U, sizeof(T) * (m_size - index));
		memset(m_ptr + index, 0, sizeof(T));
		*(m_ptr + index) = arg;
		++m_size;
		return *this;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::insert(size_t const& idx, T* const& ptr, size_t const& size) noexcept {

		/*=========================================
		 *	push_back や push_front はそれぞれ挿入位置の違いだけである為、
		 *	実際はインデックスを調整するだけで実装ができる。
		 */

		size_t index = (idx <= m_size) ? idx : m_size;
		while (m_capacity < m_size + size && m_alloc != 0U) {
			scale_up();
		}

		/*=========================================
		 *	添字の位置にデータを入れる際に前のデータを消してしまう可能性がある為、
		 *	そこに元々あったデータを 0 クリアで壊した上で代入を行う。
		 *	元々のデータはすでに移動を終えているため壊してしまっても問題はない（と思う）。
		 */

		memmove(m_ptr + index, m_ptr + index + size, sizeof(T) * (m_size - index));
		memset(m_ptr + index, 0, sizeof(T) * size);
		for (size_t i = 0U; i < size; ++i) {
			*(m_ptr + index + i) = *(ptr + i);
		}
		m_size += size;
		return *this;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::insert(size_t const& idx, std::initializer_list<T> const& args) noexcept {

		/*=========================================
		 *	push_back や push_front はそれぞれ挿入位置の違いだけである為、
		 *	実際はインデックスを調整するだけで実装ができる。
		 */

		size_t index = (idx <= m_size) ? idx : m_size;
		size_t i = 0U;
		while (m_capacity < m_size + args.size()) {
			scale_up();
		}

		/*=========================================
		 *	添字の位置にデータを入れる際に前のデータを消してしまう可能性がある為、
		 *	そこに元々あったデータを 0 クリアで壊した上で代入を行う。
		 *	元々のデータはすでに移動を終えているため壊してしまっても問題はない（と思う）。
		 */

		memmove(m_ptr + index, m_ptr + index + args.size(), sizeof(T) * (m_size - index));
		memset(m_ptr + index, 0, sizeof(T) * args.size());
		for (T const& arg : args) {
			*(m_ptr + index + i) = arg;
			++i;
		}
		m_size += args.size();
		return *this;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::push_front(T&& data) noexcept {
		return insert(0U, data);
	}

	template<typename T>
	inline Vector<T>& Vector<T>::push_front(T const& data) noexcept {
		return insert(0U, data);
	}

	template<typename T>
	inline Vector<T>& Vector<T>::push_front(T* const& ptr, size_t const& size) noexcept {
		return insert(0U, ptr, size);
	}

	template<typename T>
	inline Vector<T>& Vector<T>::push_front(std::initializer_list<T> const& args) noexcept {
		return insert(0U, args);
	}

	template<typename T>
	inline Vector<T>& Vector<T>::push_back(T&& data) noexcept {
		return insert(m_size, data);
	}

	template<typename T>
	inline Vector<T>& Vector<T>::push_back(T const& data) noexcept {
		return insert(m_size, data);
	}

	template<typename T>
	inline Vector<T>& Vector<T>::push_back(T* const& ptr, size_t const& size) noexcept {
		return insert(m_size, ptr, size);
	}

	template<typename T>
	inline Vector<T>& Vector<T>::push_back(std::initializer_list<T> const& args) noexcept {
		return insert(m_size, args);
	}

	template<typename T>
	inline Vector<T>& Vector<T>::remove(size_t const& idx) noexcept {

		/*=========================================
		 *	pop_back や pop_front はそれぞれ削除位置の違いだけである為、
		 *	実際はインデックスを調整するだけで実装ができる。
		 *	しかし件数が 0 である場合は処理を行う必要はない。
		 */

		if (m_size == 0U) {
			return *this;
		}

		/*=========================================
		 *	デストラクタが必ず呼び出されるようにインデックスを、
		 *	適切な値にした後すぐにデストラクタを呼び出すようにする。
		 *	そして、データを詰める処理を入れる。
		 */

		size_t index = (idx < m_size) ? idx : (m_size - 1U);
		(m_ptr + index)->~T();
		memcpy(m_ptr + index, m_ptr + index + 1U, sizeof(T) * (m_size - index));
		--m_size;
		return *this;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::remove(size_t const& idx1, size_t const& idx2) noexcept {

		/*=========================================
		 *	pop_back や pop_front はそれぞれ削除位置の違いだけである為、
		 *	実際はインデックスを調整するだけで実装ができる。
		 *	しかし件数が 0 である場合は処理を行う必要はない。
		 */

		if (m_size == 0U) {
			return *this;
		}

		/*=========================================
		 *	２つのインデックスがデータ件数に合致する様に処理をした後、
		 *	別途変数に最小値・最大値として保持しておく。
		 *	デストラクタをそれぞれ呼び出すために大きさも保持しておく。
		 */

		size_t min, max, length;
		if (idx1 < idx2) {
			min = (idx1 < m_size) ? idx1 : (m_size - 1U);
			max = (idx2 < m_size) ? idx2 : (m_size - 1U);
		}
		else {
			min = (idx2 < m_size) ? idx2 : (m_size - 1U);
			max = (idx1 < m_size) ? idx1 : (m_size - 1U);
		}
		length = (max - min) + 1U;

		/*=========================================
		 *	デストラクタが必ず呼び出されるようにインデックスを、
		 *	適切な値にした後すぐにデストラクタを呼び出すようにする。
		 *	そして、データを詰める処理を入れる。
		 */

		for (size_t idx = 0U; idx < length; ++idx) {
			(m_ptr + min + idx)->~T();
		}
		memcpy(m_ptr + min, m_ptr + max + 1U, sizeof(T) * (m_size - max));
		--m_size;
		return *this;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::pop_front() noexcept {
		return remove(0U);
	}

	template<typename T>
	inline Vector<T>& Vector<T>::pop_front(size_t const& size) noexcept {
		return remove(0U, size);
	}

	template<typename T>
	inline Vector<T>& Vector<T>::pop_back() noexcept {
		return remove(m_size);
	}

	template<typename T>
	inline Vector<T>& Vector<T>::pop_back(size_t const& size) noexcept {
		return (size < m_size) ? remove(m_size - size, m_size) : clear();
	}

	template<typename T>
	inline Vector<T>& Vector<T>::clear() noexcept {
		if (m_ptr) {
			delete[] m_ptr;
			m_ptr = nullptr;
		}
		m_size = 0U;
		return *this;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::reflesh() noexcept {
		scale_normalize();
		return *this;
	}

	template<typename T>
	inline void Vector<T>::scaling(size_t const& capacity) noexcept {
		m_capacity = capacity;
		T* ptr = nullptr;
		if (m_capacity != 0U) {
			ptr = new T[m_capacity]();
		}

		/*=========================================
		 *	配列長を調整する場合、元々あったデータが消えないようにしないとならない。
		 *	よって通常通りコピーを行うが、元のポインターの先のデータを 0 クリアで壊してから
		 *	delete[] しなくてはならない。
		 */

		if (m_ptr != nullptr) {
			memcpy(ptr, m_ptr, sizeof(T) * m_size);
			memset(m_ptr, 0, sizeof(T) * m_size);
			delete[] m_ptr;
		}
		m_ptr = ptr;
		ptr = nullptr;
	}

	template<typename T>
	inline void Vector<T>::scale_up() noexcept {
		scaling(m_capacity + m_alloc);
	}

	template<typename T>
	inline void Vector<T>::scale_normalize() noexcept {
		scaling(std::lcm(m_size, m_alloc));
	}

	template<typename T>
	inline void swap(Vector<T>& lhs, Vector<T>& rhs) noexcept {
		T* temp = nullptr;
		size_t size = 0U;

		temp = lhs.m_ptr;
		lhs.m_ptr = rhs.m_ptr;
		rhs.m_ptr = temp;
		temp = nullptr;

		size = lhs.m_size;
		lhs.m_size = rhs.m_size;
		rhs.m_size = size;

		size = lhs.m_capacity;
		lhs.m_capacity = rhs.m_capacity;
		rhs.m_capacity = size;

		size = lhs.m_alloc;
		lhs.m_alloc = rhs.m_alloc;
		rhs.m_alloc = size;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::swap(size_t const& idx1, size_t const& idx2) noexcept {
		size_t min, max, length;
		if (idx1 < idx2) {
			min = (idx1 < m_size) ? idx1 : (m_size - 1U);
			max = (idx2 < m_size) ? idx2 : (m_size - 1U);
		}
		else {
			min = (idx2 < m_size) ? idx2 : (m_size - 1U);
			max = (idx1 < m_size) ? idx1 : (m_size - 1U);
		}
		length = max - min;

		T&& temp = std::move(*(m_ptr + min));
		*(m_ptr + min) = std::move(*(m_ptr + max));
		*(m_ptr + max) = temp;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::reverse() noexcept {
		size_t min, max;
		for (min = 0U, max = m_size - 1U; min > max; ++min, --max) {
			swap(min, max);
		}
		return *this;
	}
}
