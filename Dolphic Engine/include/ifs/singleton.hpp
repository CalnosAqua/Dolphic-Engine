/**	@file	singleton.hpp
 *	@brief	シングルトンクラス
 */
#pragma once
#include "nonmovable.hpp"

namespace {
	/**	@interface ISingleton
	 *	@brief シングルトンクラス
	 */
	template <typename T>
	class ISingleton : public INonmovable<ISingleton<T>> {
	public:
		//!	@brief	デストラクタ
		virtual ~ISingleton() noexcept { exit(); }
		//!	@brief	インスタンス取得関数
		static T& getInstance() noexcept {
			static T result = T();
			return result;
		}
		//!	@brief	終了関数
		virtual void exit() noexcept = 0;
	protected:
		//!	@brief	デフォルトコンストラクタ
		ISingleton() noexcept {}
	};
}
