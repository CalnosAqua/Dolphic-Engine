/**	@file	D3D12ResourceBarrier.hpp
 *	@brief	Direct3D12 用のリソースバリアクラス宣言ファイル
 */
#pragma once
#include "ifs/noncopyable.hpp"
#include "D3D12CommandList.hpp"
#include <d3d12.h>

namespace dlph {
	/**	@file	D3D12ResourceBarrier
	 *	@brief	Direct3D12 用のリソースバリアクラス
	 */
	class D3D12ResourceBarrier final {
	public	:
		//!	@brief	ムーブコンストラクタ
		D3D12ResourceBarrier(D3D12ResourceBarrier&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		D3D12ResourceBarrier(D3D12ResourceBarrier const&) noexcept = default;
		//!	@brief	ムーブコンストラクタ
		D3D12ResourceBarrier& operator=(D3D12ResourceBarrier&&) & noexcept = default;
		//!	@brief	コピーコンストラクタ
		D3D12ResourceBarrier& operator=(D3D12ResourceBarrier const&) & noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		D3D12ResourceBarrier() noexcept;
		//!	@brief	デストラクタ
		~D3D12ResourceBarrier() noexcept = default;

		//!	@brief	レンダーターゲットモードに切り替える関数
		D3D12ResourceBarrier& toRenderTargetMode(D3D12CommandList&, ID3D12Resource2*&) noexcept;
		//!	@brief	プレゼントモードに切り替える関数
		D3D12ResourceBarrier& toPresentMode(D3D12CommandList&, ID3D12Resource2*&) noexcept;

	private	:
		//!	@brief	リソースバリア
		D3D12_RESOURCE_BARRIER m_barrier;
	};
}
