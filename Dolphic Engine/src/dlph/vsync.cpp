/**	@file	vsync.cpp
 *	@brief	抽象同期クラス
 */
#include "dlph/vsync.hpp"

namespace dlph {
	SyncVideo::SyncVideo() noexcept :
		INoncopyable()
	{}

	SyncVideo::~SyncVideo() noexcept {
		exit();
	}
}
