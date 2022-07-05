/**	@file	d3d12_swapchain.hpp
 *	@brief	スワップチェイン
 */
#pragma once
#include "util/noncopyable.hpp"
#include <dxgi1_6.h>
#include <d3d12.h>

namespace dlph {
	/** @struct	CHN_DESC
	 *	@brief	スワップチェイン生成用データ一式
	 */
	struct SwapChainDesc final {
		//!	@brief	ウィンドウハンドラ
		HWND hWnd;
		//!	@brief	コマンドキュー
		mutable ID3D12CommandQueue* cmdQue;
		//!	@brief	バッファサイズ
		unsigned int bSize;
		//!	@brief	フレームレート
		unsigned int fRate;
		//!	@brief	ウィンドウ/フルスクリーン モード
		bool fullscreen;
	};

	/**	@enum	D3D12SwapChain
	 *	@brief	スワップチェイン
	 */
	class D3D12SwapChain final :
		public INoncopyable<D3D12SwapChain>
	{
	public:
		//!	@brief	ムーブコンストラクタ
		D3D12SwapChain(D3D12SwapChain&&) noexcept;
		//!	@brief	ムーブ代入演算子
		D3D12SwapChain& operator=(D3D12SwapChain&&) & noexcept;
		
		//!	@brief	デフォルトコンストラクタ
		D3D12SwapChain() noexcept;
		//!	@brief	デストラクタ
		~D3D12SwapChain() noexcept;

		//!	@brief	初期化関数
		bool const init(SwapChainDesc const&) noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

		//!	@brief	取得関数
		IDXGISwapChain4*& get() const noexcept;
		//!	@brief	メンバアクセス演算子
		IDXGISwapChain4* operator->() const noexcept;
	private:
		//!	@brief	スワップチェインポインタ
		IDXGISwapChain4* m_chain;
	};
}
