/**	@file	array.hpp
 *	@brief	静的配列クラス
 */
#pragma once

namespace dlph {
	/**	@class	Array<T>
	 *	@brief	静的配列クラス
	 */
	template <typename T>
	class Array {
	public :
		//!	@brief	ムーブコンストラクタ
		Array(Array<T>&&) noexcept;
		//!	@brief	コピーコンストラクタ
		Array(Array<T> const&) noexcept;
		//!	@brief	ムーブ代入演算子
		Array<T>& operator=(Array<T>&&) & noexcept;
		//!	@brief	コピー代入演算子
		Array<T>& operator=(Array<T> const&) & noexcept;

		//!	@brief	デフォルトコンストラクタ
		Array() noexcept;
		//!	@brief	デストラクタ
		virtual ~Array() noexcept;

		//!	@brief	初期化子コンストラクタ
		explicit Array(std::initializer_list<T> const&) noexcept;
		//!	@brief	初期化子コンストラクタ
		explicit Array(size_t const&) noexcept;

		//!	@brief	配列の先頭へのポインタ (定数)
		float* const cbegin() const noexcept;
		//!	@brief	配列の先頭へのポインタ (変数)
		float* begin() noexcept;
		//!	@brief	配列の末端へのポインタ (定数)
		float* const cend() const noexcept;
		//!	@brief	配列の末端へのポインタ (変数)
		float* end() noexcept;

		//!	@brief	配列長
		size_t const size() const noexcept;

		//!	@brief	添字演算子
		T& operator[](size_t const&) & noexcept;
		//!	@brief	添字演算子
		T operator[](size_t const&) const&& noexcept;
		//!	@brief	添字演算子
		T const& operator[](size_t const&) const& noexcept;

	protected :
		//!	@brief	配列の先頭へのポインタ
		T* m_ptr;
		//!	@brief	配列長
		size_t m_size;
	};
}

#include "array.inl"
