/**	@file	noncopyable.hpp
 *	@brief	コピー禁止クラス
 */
#pragma once

namespace {
	/**	@interface INoncopyable
	 *	@brief コピー禁止クラス
	 */
	template <typename T>
	class INoncopyable {
	public	:
		//!	@brief	コピーコンストラクタ
		INoncopyable(INoncopyable<T> const&) noexcept = delete;
		//!	@brief	コピー代入演算子
		INoncopyable<T>& operator=(INoncopyable<T> const&) & noexcept = delete;

		//!	@brief	デフォルトコンストラクタ
		INoncopyable() noexcept {}
		//!	@brief	デストラクタ
		virtual ~INoncopyable() noexcept {}
	};
}
