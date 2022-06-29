/**	@file	nonmovable.hpp
 *	@brief	コピーとムーブ禁止クラス
 */
#pragma once
#include "noncopyable.hpp"

namespace {
	/**	@interface INonmovable
	 *	@brief コピーとムーブ禁止クラス
	 */
	template <typename T>
	class INonmovable : public INoncopyable<INonmovable<T>> {
	public:
		//!	@brief	ムーブコンストラクタ
		INonmovable(INonmovable<T>&&) noexcept = delete;
		//!	@brief	ムーブ代入演算子
		INonmovable<T>& operator=(INonmovable<T>&&) & noexcept = delete;

		//!	@brief	デフォルトコンストラクタ
		INonmovable() noexcept {}
		//!	@brief	デストラクタ
		virtual ~INonmovable() noexcept {}
	};
}
