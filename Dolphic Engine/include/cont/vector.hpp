/**	@file	vector.hpp
 *	@brief	動的配列クラス
 */
#pragma once
#include <initializer_list>

namespace dlph {
	/**	@class	Vector<T>
	 *	@brief	静的配列クラス
	 */
	template <typename T>
	class Vector final {
	public:
		//!	@brief	ムーブコンストラクタ
		Vector(Vector<T>&&) noexcept;
		//!	@brief	コピーコンストラクタ
		Vector(Vector<T> const&) noexcept;
		//!	@brief	ムーブ代入演算子
		Vector<T>& operator=(Vector<T>&&) & noexcept;
		//!	@brief	コピー代入演算子
		Vector<T>& operator=(Vector<T> const&) & noexcept;

		//!	@brief	コンストラクタ
		Vector(std::initializer_list<T> const&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		Vector() noexcept;
		//!	@brief	デストラクタ
		~Vector() noexcept;

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

		//! @brief 確保基準長
		Vector<T>& alloc_size(size_t const&) noexcept;
		//! @brief 確保基準長
		size_t const alloc_size() const noexcept;

		//!	@brief 挿入関数（単体データ：ムーブ）
		Vector<T>& insert(size_t const&, T&&) noexcept;
		//!	@brief 挿入関数（単体データ：コピー）
		Vector<T>& insert(size_t const&, T const&) noexcept;
		//!	@brief 挿入関数（ポインタ配列）
		Vector<T>& insert(size_t const&, T* const&, size_t const&) noexcept;
		//!	@brief 挿入関数（初期化子リスト）
		Vector<T>& insert(size_t const&, std::initializer_list<T> const&) noexcept;

		//!	@brief 先頭追加関数（単体データ：ムーブ）
		Vector<T>& push_front(T&&) noexcept;
		//!	@brief 先頭追加関数（単体データ：コピー）
		Vector<T>& push_front(T const&) noexcept;
		//!	@brief 先頭追加関数（ポインタ配列）
		Vector<T>& push_front(T* const&, size_t const&) noexcept;
		//!	@brief 先頭追加関数（初期化子リスト）
		Vector<T>& push_front(std::initializer_list<T> const&) noexcept;

		//!	@brief 末端追加関数（単体データ：ムーブ）
		Vector<T>& push_back(T&&) noexcept;
		//!	@brief 末端追加関数（単体データ：コピー）
		Vector<T>& push_back(T const&) noexcept;
		//!	@brief 末端追加関数（ポインタ配列）
		Vector<T>& push_back(T* const&, size_t const&) noexcept;
		//!	@brief 末端追加関数（初期化子リスト）
		Vector<T>& push_back(std::initializer_list<T> const&) noexcept;

		//!	@brief 消去関数（単一）
		Vector<T>& remove(size_t const&) noexcept;
		//!	@brief 消去関数（範囲）
		Vector<T>& remove(size_t const&, size_t const&) noexcept;

		//!	@brief 先頭取出関数（単一）
		Vector<T>& pop_front() noexcept;
		//!	@brief 先頭取出関数（範囲）
		Vector<T>& pop_front(size_t const&) noexcept;

		//!	@brief 末端取出関数（単一）
		Vector<T>& pop_back() noexcept;
		//!	@brief 末端取出関数（範囲）
		Vector<T>& pop_back(size_t const&) noexcept;

		//!	@brief	クリア関数
		Vector<T>& clear() noexcept;
		//!	@brief	配列長最適化関数
		Vector<T>& reflesh() noexcept;

		//!	@brief	ベクタ配列ごと交換する関数
		template <typename T>
		friend void swap(Vector<T>&, Vector<T>&) noexcept;
		//!	@brief 交換関数
		Vector<T>& swap(size_t const&, size_t const&) noexcept;
		//!	@brief 反転関数
		Vector<T>& reverse() noexcept;

	private:
		//! @brief 配列長変更関数
		void scaling(size_t const&) noexcept;
		//! @brief 配列長拡張関数
		void scale_up() noexcept;
		//! @brief 配列長正規化関数
		void scale_normalize() noexcept;

		//!	@brief	配列の先頭へのポインタ
		T* m_ptr;
		//!	@brief	データ件数
		size_t m_size;
		//! @brief	容量
		size_t m_capacity;
		//!	@brief	確保基準長
		size_t m_alloc;
	};
}
