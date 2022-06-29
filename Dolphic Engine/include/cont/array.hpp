/**	@file	array.hpp
 *	@brief	静的配列クラス
 */
#pragma once
#include <initializer_list>

namespace dlph {
	/**	@class	Array<T, S>
	 *	@brief	静的配列クラス
	 */
	template <typename T, size_t S>
	class Array final {
	public	:
		//!	@brief	ムーブコンストラクタ
		Array(Array<T, S>&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		Array(Array<T, S> const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		Array<T, S>& operator=(Array<T, S>&&) & noexcept = default;
		//!	@brief	コピー代入演算子
		Array<T, S>& operator=(Array<T, S> const&) & noexcept = default;

		//!	@brief	コンストラクタ
		Array(std::initializer_list<T> const&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		Array() noexcept;
		//!	@brief	デストラクタ
		~Array() noexcept = default;

		//!	@brief	添え字演算子
		T& operator[](size_t const&) & noexcept;
		//!	@brief	添え字演算子
		T operator[](size_t const&) const&& noexcept;
		//!	@brief	添え字演算子
		T const& operator[](size_t const&) const& noexcept;

		//!	@brief	配列の先頭へのポインタ取得関数
		T* const begin() const noexcept;
		//!	@brief	配列の末端へのポインタ取得関数
		T* const end() const noexcept;

		//!	@brief	配列長取得関数
		size_t const size() const noexcept;

	private	:
		//!	@brief	配列
		T m_array[S];
	};
}
