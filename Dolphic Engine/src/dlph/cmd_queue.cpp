/**	@file	cmd_queue.cpp
 *	@brief	抽象コマンドキュークラス
 */
#include "dlph/cmd_queue.hpp"

namespace dlph {
	CommandQueue::CommandQueue() noexcept :
		INoncopyable()
	{}

	CommandQueue::~CommandQueue() noexcept {
		exit();
	}
}
