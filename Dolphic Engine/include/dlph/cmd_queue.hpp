/**	@file	cmd_queue.hpp
 *	@brief	抽象コマンドキュークラス
 */
#pragma once
#include "ifs/noncopyable.hpp"

namespace dlph {
	/**	@class	CommandQueue
	 *	@brief	抽象コマンドキュークラス
	 */
	class CommandQueue : public INoncopyable<CommandQueue> {
	public	:
		//!	@brief	ムーブコンストラクタ
		CommandQueue(CommandQueue&&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CommandQueue& operator=(CommandQueue&&) & noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CommandQueue() noexcept;
		//!	@brief	デストラクタ
		virtual ~CommandQueue() noexcept;

		//!	@brief	初期化関数
		virtual bool const init() noexcept = 0;
		//!	@brief	終了関数
		virtual void exit() noexcept = 0;
	};
}
