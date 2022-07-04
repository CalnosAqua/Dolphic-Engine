/**	@file	array.hpp
 *	@brief	静的配列クラス
 */
#pragma once
#include <initializer_list>
#include <crtdbg.h>

namespace dlph {
	/**	@class	Array<T, S>
	 *	@brief	静的配列クラス
	 */
	template <typename T, size_t S>
	class Array final {
	public:
		//!	@brief	ムーブコンストラクタ
		Array(Array<T, S>&& arg) noexcept = default;
		//!	@brief	コピーコンストラクタ
		Array(Array<T, S> const& arg) noexcept = default;
		//!	@brief	ムーブ代入演算子
		Array<T, S>& operator=(Array<T, S>&& rhs) & noexcept = default;
		//!	@brief	コピー代入演算子
		Array<T, S>& operator=(Array<T, S> const& rhs) & noexcept = default;

		//!	@brief	初期化子コンストラクタ
		explicit Array(std::initializer_list<T> const& args) noexcept;

		//!	@brief	デフォルトコンストラクタ
		Array() noexcept;
		//!	@brief	デストラクタ
		~Array() noexcept = default;

		//!	@brief	添字演算子
		T& operator[](size_t const& idx) & noexcept;
		//!	@brief	添字演算子
		T operator[](size_t const& idx) const&& noexcept;
		//!	@brief	添字演算子
		T const& operator[](size_t const& idx) const& noexcept;

		//!	@brief	配列の先頭へのポインタ
		T* const begin() const noexcept;
		//!	@brief	配列の末端へのポインタ
		T* const end() const noexcept;

		//!	@brief	配列長
		size_t const size() const noexcept;

		//!	@brief	キャスト演算子
		explicit operator T*() const noexcept;

	private:
		//!	@brief	配列データ
		T m_array[S];
	};

	template<typename T, size_t S>
	inline Array<T, S>::Array(std::initializer_list<T> const& args) noexcept :
		Array()
	{
		size_t idx = 0U;
		for (T const& arg : args) {
			if (idx > S) {
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
#if	defined(_DEBUG) || defined(DEBUG)
		_ASSERT_EXPR(idx < S, L"ERROR : INDEX NUMBER EXCEED ARRAY LENGTH.");
#endif
		return m_array[idx];
	}

	template<typename T, size_t S>
	inline T Array<T, S>::operator[](size_t const& idx) const&& noexcept {
#if	defined(_DEBUG) || defined(DEBUG)
		_ASSERT_EXPR(idx < S, L"ERROR : INDEX NUMBER EXCEED ARRAY LENGTH.");
#endif
		return std::move(m_array[idx]);
	}

	template<typename T, size_t S>
	inline T const& Array<T, S>::operator[](size_t const& idx) const& noexcept {
#if	defined(_DEBUG) || defined(DEBUG)
		_ASSERT_EXPR(idx < S, L"ERROR : INDEX NUMBER EXCEED ARRAY LENGTH.");
#endif
		return m_array[idx];
	}

	template<typename T, size_t S>
	inline T* const Array<T, S>::begin() const noexcept {
		return &m_array[0];
	}

	template<typename T, size_t S>
	inline T* const Array<T, S>::end() const noexcept {
		return &m_array[S];
	}

	template<typename T, size_t S>
	inline size_t const Array<T, S>::size() const noexcept {
		return S;
	}

	template<typename T, size_t S>
	inline Array<T, S>::operator T*() const noexcept {
		return const_cast<T*>(m_array);
	}
}
