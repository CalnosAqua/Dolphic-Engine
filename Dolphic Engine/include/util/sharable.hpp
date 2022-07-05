/**	@file	sharable.hpp
 *	@brief	共有可物クラス
 */
#pragma once
#include "nonmovable.hpp"

namespace {
	/**	@interface ISharable
	 *	@brief 共有可物クラス
	 */
	template <typename T>
	class ISharable : public INoncopyable<ISharable<T>> {
	public:
		//!	@brief	デストラクタ
		virtual ~ISharable() noexcept { exit(); }
		//!	@brief	インスタンス取得関数
		T& getInstance() const noexcept {
			static T result = T();
			return result;
		}
		//!	@brief	終了関数
		virtual void exit() noexcept = 0;
	protected:
		//!	@brief	デフォルトコンストラクタ
		ISharable() noexcept {}
	};
}
