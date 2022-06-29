/**	@file	vsync.hpp
 *	@brief	抽象同期クラス
 */
#pragma once
#include "ifs/noncopyable.hpp"

namespace dlph {
	/**	@class	SyncVideo
	 *	@brief	抽象同期クラス
	 */
	class SyncVideo : public INoncopyable<SyncVideo> {
	public:
		//!	@brief	ムーブコンストラクタ
		SyncVideo(SyncVideo&&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		SyncVideo& operator=(SyncVideo&&) &noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		SyncVideo() noexcept;
		//!	@brief	デストラクタ
		virtual ~SyncVideo() noexcept;

		//!	@brief	初期化関数
		virtual bool const init() noexcept = 0;
		//!	@brief	終了関数
		virtual void exit() noexcept = 0;
	};
}
