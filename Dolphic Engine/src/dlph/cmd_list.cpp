/**	@file	cmd_list.cpp
 *	@brief	抽象コマンドリストクラス
 */
#include "dlph/cmd_list.hpp"

namespace dlph {
	CommandList::CommandList() noexcept :
		INoncopyable()
	{}

	CommandList::~CommandList() noexcept {
		exit();
	}
}
