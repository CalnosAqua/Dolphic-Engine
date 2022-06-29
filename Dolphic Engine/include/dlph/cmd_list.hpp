/**	@file	cmd_list.hpp
 *	@brief	抽象コマンドリストクラス
 */
#pragma once
#include "ifs/noncopyable.hpp"

namespace dlph {
	/**	@class	CommandList
	 *	@brief	抽象コマンドリストクラス
	 */
	class CommandList : public INoncopyable<CommandList> {
	public:
		//!	@brief	ムーブコンストラクタ
		CommandList(CommandList&&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		CommandList& operator=(CommandList&&) &noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		CommandList() noexcept;
		//!	@brief	デストラクタ
		virtual ~CommandList() noexcept;

		//!	@brief	初期化関数
		virtual bool const init() noexcept = 0;
		//!	@brief	終了関数
		virtual void exit() noexcept = 0;
	};
}
