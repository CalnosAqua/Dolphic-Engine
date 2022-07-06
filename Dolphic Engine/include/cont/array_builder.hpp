/**	@file	array_builder.hpp
 *	@brief	配列生成クラス
 */
#pragma once
#include "array.hpp"

namespace dlph {
	/**	@class	ArrayBuilder<T>
	 *	@brief	配列生成クラス
	 */
	template <typename T>
	class ArrayBuilder : public Array<T> {
	public:
		//!	@brief	代入演算子
		ArrayBuilder<T>& operator=(Array<T>&&) noexcept;
		//!	@brief	代入演算子
		ArrayBuilder<T>& operator=(Array<T> const&) noexcept;

		//!	@brief	ムーブコンストラクタ
		ArrayBuilder(ArrayBuilder<T>&&) noexcept;
		//!	@brief	コピーコンストラクタ
		ArrayBuilder(ArrayBuilder<T> const&) noexcept;
		//!	@brief	ムーブ代入演算子
		ArrayBuilder<T>& operator=(ArrayBuilder<T>&&) & noexcept;
		//!	@brief	コピー代入演算子
		ArrayBuilder<T>& operator=(ArrayBuilder<T> const&) & noexcept;

		//!	@brief	デフォルトコンストラクタ
		ArrayBuilder() noexcept;
		//!	@brief	デストラクタ
		~ArrayBuilder() noexcept;

		//!	@brief	コンストラクタ
		explicit ArrayBuilder(size_t const&) noexcept;
		//!	@brief	初期化子コンストラクタ
		explicit ArrayBuilder(std::initializer_list<T> const&) noexcept;

		//!	@brief	分離関数
		ArrayBuilder<T>& separate(ArrayBuilder<T> const&) noexcept;
		//!	@brief	結合関数
		ArrayBuilder<T>& connect(ArrayBuilder<T> const&) noexcept;

		//!	@brief	追加関数
		ArrayBuilder<T>& add(T&&) noexcept;
		//!	@brief	追加関数
		ArrayBuilder<T>& add(T const&) noexcept;
		//!	@brief	追加関数
		ArrayBuilder<T>& add(Array<T> const&) noexcept;
		//!	@brief	追加関数
		ArrayBuilder<T>& add(T const* const&, size_t const&) noexcept;
		//!	@brief	追加関数
		ArrayBuilder<T>& add(std::initializer_list<T> const&) noexcept;

		//!	@brief	追加関数
		ArrayBuilder<T>& add(size_t const&, T&&) noexcept;
		//!	@brief	追加関数
		ArrayBuilder<T>& add(size_t const&, T const&) noexcept;
		//!	@brief	追加関数
		ArrayBuilder<T>& add(size_t const&, Array<T> const&) noexcept;
		//!	@brief	追加関数
		ArrayBuilder<T>& add(size_t const&, T const* const&, size_t const&) noexcept;
		//!	@brief	追加関数
		ArrayBuilder<T>& add(size_t const&, std::initializer_list<T> const&) noexcept;

		//!	@brief	除去関数
		ArrayBuilder<T>& remove(size_t const&) noexcept;
		//!	@brief	除去関数
		ArrayBuilder<T>& remove(size_t const&, size_t const&) noexcept;
	};
}
