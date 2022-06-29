/**	@file	WinWindow.hpp
 *	@brief	Windows 用ウィンドウ管理クラス定義ファイル
 */
#pragma once

#if !defined(NOMINMAX)
#	define NOMINMAX
#endif

#include "ifs/noncopyable.hpp"
#include <Windows.h>

namespace dlph {
	/**	@enum	MessageState
	 *	@brief	メッセージの状態一覧
	 */
	enum class MessageState {
		//!	@brief	メッセージを受け取りました。
		RECEIVED,
		//!	@brief	メッセージが届いていませんでした。
		NOTFOUND,
		//!	@brief	拡縮メッセージを受け取りました。
		RESIZE,
		//!	@brief	終了メッセージを受け取りました。
		END
	};

	/**	@enum	WindwDesc
	 *	@brief	ウィンドウ管理クラス初期化用データ一式
	 */
	struct WindwDesc final {
		//!	@brief	インスタンスハンドル
		HINSTANCE		ins_handler;
		//!	@brief	ウィンドウプロシージャ
		WNDPROC			wnd_proc;
		//!	@brief	クラス名
		LPCSTR			cls_name;
		//!	@brief	ウィンドウ名
		LPCSTR			wnd_name;
		//!	@brief	横幅
		unsigned int	width;
		//!	@brief	縦幅
		unsigned int	height;
		//!	@brief	拡縮
		bool			scalable;
	};

	/**	@class	WinWindow
	 *	@brief	WINDOWS 用のウィンドウ
	 */
	class WinWindow final :
		INoncopyable<WinWindow>
	{
	public:
		//!	@brief	コピーコンストラクタ
		WinWindow(WinWindow&&) noexcept;
		//!	@brief	コピー代入演算子
		WinWindow& operator=(WinWindow&&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		WinWindow() noexcept;
		//!	@brief	デストラクタ
		~WinWindow() noexcept;

		//!	@brief	初期化処理関数
		bool const init(WindwDesc const&) noexcept;
		//!	@brief	終了処理関数
		void exit() noexcept;

		//!	@brief	ウィンドウステータス表示処理関数
		void showWindowStatus() noexcept;
		//!	@brief	クラス専属ウィンドウプロシージャ
		LRESULT const WindowProcedure(
			HWND const& hWnd,
			UINT const& iMsg,
			WPARAM const& wParam,
			LPARAM const& lParam
		);
		//!	@brief	メッセージ受理処理関数
		MessageState const receivingMessage() noexcept;

		//!	@brief	矩形生成関数
		RECT const getRectangle() const noexcept;

		//!	@brief	ウィンドウハンドル取得関数
		HWND const& getWindowHandle() const noexcept;
		//!	@brief	インスタンスハンドル取得関数
		HINSTANCE const getInstanceHandle() const noexcept;
		//!	@brief	横幅取得関数
		unsigned int const getWidth() const noexcept;
		//!	@brief	縦幅取得関数
		unsigned int const getHeight() const noexcept;

	private:
		//!	@brief	ウィンドウハンドル
		HWND		m_hWnd;
		//!	@brief	ウィンドウ名
		LPCSTR		m_wndName;
		//!	@brief	初期化済みかどうか
		bool		m_inited;
	};
}
