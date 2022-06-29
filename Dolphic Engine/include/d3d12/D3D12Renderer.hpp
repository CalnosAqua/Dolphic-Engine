/**	@file	D3D12Renderer.hpp
 *	@brief	Direct3D12 を利用したレンダラ
 */
#pragma once
#include "ifs/noncopyable.hpp"
#include "structs/flt4.hpp"
#include "D3D12ResourceBarrier.hpp"
#include "D3D12Buffer.hpp"
#include "D3D12CommandQueue.hpp"
#include "D3D12CommandList.hpp"
#include "D3D12Fence.hpp"

namespace dlph {
	/**	@struct	RendererDesc
	 *	@brief	レンダラ初期化用データ
	 */
	struct RendererDesc final {
		//!	@brief	ウィンドウハンドラ
		HWND hWnd;
		//!	@brief	背景色
		Float4 color;
		//!	@brief	レンダーターゲットバッファサイズ
		unsigned int bSize;
		//!	@brief	フレームレート
		unsigned int fRate;
		//!	@brief	フルスクリーン設定
		bool fullscreen;
	};

	/**	@file	D3D12Renderer
	 *	@brief	Direct3D12 を利用したレンダラ
	 */
	class D3D12Renderer final :
		public INoncopyable<D3D12Renderer>
	{
	public	:
		//!	@brief	ムーブコンストラクタ
		D3D12Renderer(D3D12Renderer&&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		D3D12Renderer& operator=(D3D12Renderer&&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		D3D12Renderer() noexcept;
		//!	@brief	デストラクタ
		~D3D12Renderer() noexcept;

		//!	@brief	初期化関数
		bool const init(RendererDesc const&) noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

		//!	@brief	再初期化関数
		bool const reinit() noexcept;

		//!	@brief	前レンダリング処理関数
		bool const before_rendering() noexcept;
		//!	@brief	後レンダリング処理関数
		bool const after_rendering() noexcept;
		//!	@brief	描画処理関数
		bool const presenting() noexcept;

		//!	@brief	コマンドリスト取得関数
		D3D12CommandList& getCmdList() noexcept;

		//!	@brief	トリム矩形取得関数
		D3D12_RECT const getTrimRect() const noexcept;
		//!	@brief	ビューポート取得関数
		D3D12_VIEWPORT const getViewport() const noexcept;
		//!	@brief	フレームバッファ数取得関数
		unsigned int const getFrameBufferSize() const noexcept;
		//!	@brief	横幅取得関数
		float const getWidth() const noexcept;
		//!	@brief	縦幅取得関数
		float const getHeight() const noexcept;
		//!	@brief	アスペクト比取得関数
		float const getAspectRate() const noexcept;
		//!	@brief	カレントバッファインデックス取得関数
		unsigned int const getCurrentBufferIndex() const noexcept;

	private	:
		//!	@brief	ウィンドウハンドラ
		HWND m_hWnd;
		//!	@brief	バッファ数
		unsigned int m_bufferCount;
		//!	@brief	現在のフレームインデックス
		unsigned int m_currentIndex;

		//!	@brief	背景色
		Float4 m_color;
		//!	@brief	トリム矩形
		D3D12_RECT m_rect;
		//!	@brief	ビューポート
		D3D12_VIEWPORT m_viewport;

		//!	@brief	リソースバリア
		D3D12ResourceBarrier m_barrier;
		//!	@brief	コマンドキュー
		D3D12CommandQueue m_queue;
		//!	@brief	コマンドリスト
		D3D12CommandList m_list;
		//!	@brief	スワップチェイン
		D3D12SwapChain m_chain;
		//!	@brief	フェンス
		D3D12Fence m_fence;
		//!	@brief	レンダーターゲット
		D3D12Buffer m_rtv;
		//!	@brief	深度バッファ
		D3D12Buffer m_dsv;
	};
}
