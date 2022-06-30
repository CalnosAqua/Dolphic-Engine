/**	@file	array.hpp
 *	@brief	配列クラス
 */
#pragma once
#include <initializer_list>

namespace dlph {
    /**	@class	Array<T>
     *	@brief	配列クラス
     */
	template <typename T>
	class Array final {
	public	:
		//!	@brief	ムーブコンストラクタ
		Array(Array<T>&& arg) noexcept;
		//!	@brief	コピーコンストラクタ
		Array(Array<T> const& arg) noexcept;
		//!	@brief	ムーブ代入演算子
		Array<T>& operator=(Array<T>&& rhs) & noexcept;
		//!	@brief	コピー代入演算子
		Array<T>& operator=(Array<T> const& rhs) & noexcept;

		//!	@brief	デフォルトコンストラクタ
		Array() noexcept;
		//!	@brief	デコンストラクタ
		~Array() noexcept;

		//!	@brief	初期化子コンストラクタ
		Array(std::initializer_list<T> const& args) noexcept;

		//!	@brief	添え字演算子
		T& operator[](size_t const& idx) & noexcept;
		//!	@brief	添え字演算子
		T operator[](size_t const& idx) const&& noexcept;
		//!	@brief	添え字演算子
		T const& operator[](size_t const& idx) const& noexcept;

		//!	@brief	配列長取得関数
		size_t const size() const noexcept;

		//!	@brief	配列の先頭へのポインタ取得関数
		T* const begin() const noexcept;
		//!	@brief	配列の末端へのポインタ取得関数
		T* const end() const noexcept;

		//!	@brief	挿入関数
		Array<T>& insert(size_t const& idx, T&& data) noexcept;
		//!	@brief	挿入関数
		Array<T>& insert(size_t const& idx, T const& data) noexcept;
		//!	@brief	挿入関数
		Array<T>& insert(size_t const& idx, std::initializer_list<T> const& datas) noexcept;
		//!	@brief	挿入関数
		Array<T>& insert(size_t const& idx, T const* const& datas, size_t const& size) noexcept;

		//!	@brief	先頭に追加する関数
		Array<T>& push_front(T&& data) noexcept;
		//!	@brief	先頭に追加する関数
		Array<T>& push_front(T const& data) noexcept;
		//!	@brief	先頭に追加する関数
		Array<T>& push_front(std::initializer_list<T> const& datas) noexcept;
		//!	@brief	先頭に追加する関数
		Array<T>& push_front(T const* const& datas, size_t const& size) noexcept;

		//!	@brief	末端に追加する関数
		Array<T>& push_back(T&& data) noexcept;
		//!	@brief	末端に追加する関数
		Array<T>& push_back(T const& data) noexcept;
		//!	@brief	末端に追加する関数
		Array<T>& push_back(std::initializer_list<T> const& datas) noexcept;
		//!	@brief	末端に追加する関数
		Array<T>& push_back(T const* const& datas, size_t const& size) noexcept;

		//!	@brief	除去関数
		Array<T>& remove(size_t const& idx) noexcept;
		//!	@brief	除去関数
		Array<T>& remove(size_t const& min, size_t const& max) noexcept;

		//!	@brief	指定された個数分先頭から除去する関数
		Array<T>& pop_front(size_t const& size) noexcept;
		//!	@brief	指定された個数分末端から除去する関数
		Array<T>& pop_back(size_t const& size) noexcept;

		//!	@brief	クリア関数
		Array<T>& clear() noexcept;
		//!	@brief	リフレッシュ関数
		Array<T>& reflesh() noexcept;

	private	:
		//!	@brief	配列へのポインタ
		T* m_ptr;
		//!	@brief	配列長
		size_t m_size;
		//!	@brief	配列容量
		size_t m_capacity;
		//!	@brief	確保基準容量
		size_t m_alloc;

		//!	@brief	配列容量調節関数
		bool const reallocate(size_t const& size) noexcept;
		//!	@brief	配列容量正規化関数
		bool const normalize() noexcept;
		//!	@brief	配列容量拡張関数
		bool const expansion(size_t const& pack_size = 1U) noexcept;
	};
}

#include "array.inl"
