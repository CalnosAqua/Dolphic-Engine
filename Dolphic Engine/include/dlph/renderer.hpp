/**	@file	renderer.hpp
 *	@brief	抽象レンダラクラス
 */
#pragma once
#include "ifs/singleton.hpp"
#include "structs/flt4.hpp"

namespace dlph {
	/**	@class	Renderer
	 *	@brief	抽象レンダラクラス
	 */
	class Renderer : public ISingleton<Renderer> {
	public:
		//!	@brief	デフォルトコンストラクタ
		Renderer() noexcept;
		//!	@brief	デストラクタ
		virtual ~Renderer() noexcept;

		//!	@brief	初期化関数
		virtual bool const init() noexcept = 0;
		//!	@brief	終了関数
		virtual void exit() noexcept = 0;

		//!	@brief	背景色
		Float4 color;
		//!	@brief	ウィンドウ幅
		size_t wnd_width;
		//!	@brief	ウィンドウ高さ
		size_t wnd_height;
		//!	@brief	キューの数
		size_t queues_cnt;
		//!	@brief	リストの数
		size_t lists_cnt;
		//!	@brief	バックバッファの数
		size_t backbuffers_cnt;
		//!	@brief	フレームレート
		size_t frame_rate;
		//!	@brief	同期するかどうか
		bool syncable;
		//!	@brief	最大化するかどうか
		bool max_wnd;
	};
}
