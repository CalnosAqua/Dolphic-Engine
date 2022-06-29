/**	@file	renderer.cpp
 *	@brief	抽象レンダラクラス
 */
#include "dlph/renderer.hpp"

namespace dlph {
	Renderer::Renderer() noexcept :
		ISingleton(),
		color{ 0.0f, 0.0f, 0.0f, 0.0f },
		wnd_width(0U),
		wnd_height(0U),
		queues_cnt(0U),
		lists_cnt(0U),
		backbuffers_cnt(0U),
		frame_rate(0U),
		syncable(false),
		max_wnd(false)
	{}

	Renderer::~Renderer() noexcept {
		exit();
	}
}
