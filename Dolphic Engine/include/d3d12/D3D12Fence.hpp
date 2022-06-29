/**	@file	D3D12Fence.hpp
 *	@brief	フェンス
 */
#pragma once
#include "ifs/noncopyable.hpp"
#include "D3D12CommandQueue.hpp"
#include <d3d12.h>

namespace dlph {
	/**	@enum	 D3D12Fence
	 *	@brief	フェンス
	 */
	class D3D12Fence final :
		public INoncopyable<D3D12Fence>
	{
	public:
		//!	@brief	ムーブコンストラクタ
		D3D12Fence(D3D12Fence&&) noexcept;
		//!	@brief	ムーブ代入演算子
		D3D12Fence& operator=(D3D12Fence&&) &  noexcept;
		
		//!	@brief	デフォルトコンストラクタ
		D3D12Fence() noexcept;
		//!	@brief	デストラクタ
		~D3D12Fence() noexcept;

		//!	@brief	初期化関数
		bool const init() noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

		//!	@brief	フェンス待機処理関数 (プレゼント中)
		bool const presenting(D3D12CommandQueue const&) noexcept;
		//!	@brief	フェンス待機処理関数
		void wait(D3D12CommandQueue const&) noexcept;

		//!	@brief	取得関数
		ID3D12Fence1*& get() const noexcept;
		//!	@brief	メンバアクセス演算子
		ID3D12Fence1* operator->() const noexcept;
	private:
		//!	@brief	フェンス
		ID3D12Fence1* m_fence;
		//!	@brief	イベントハンドル
		HANDLE m_event;
		//!	@brief	シグナル
		UINT64 m_signal;
	};
}
