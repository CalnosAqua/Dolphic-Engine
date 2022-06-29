/**	@file	D3D12CommandQueue.hpp
 *	@brief	Direct3D12 用のコマンドキュー
 */
#pragma once
#include "ifs/noncopyable.hpp"
#include "D3D12CommandType.hpp"
#include <d3d12.h>

namespace dlph {
	/**	@class	D3D12CommandQueue
	 *	@brief	Direct3D12 用のデバイスクラス
	 */
	class D3D12CommandQueue final :
		public INoncopyable<D3D12CommandQueue>
	{
	public:
		//!	@brief	ムーブコンストラクタ
		D3D12CommandQueue(D3D12CommandQueue&&) noexcept;
		//!	@brief	ムーブ代入演算子
		D3D12CommandQueue& operator=(D3D12CommandQueue&&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		D3D12CommandQueue() noexcept;
		//!	@brief	デストラクタ
		~D3D12CommandQueue() noexcept;

		//!	@brief	初期化関数
		bool const init(D3D12CommandType const&) noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

		//!	@brief	ポインタ取得
		ID3D12CommandQueue*& get() const noexcept;
		//!	@brief	メンバアクセス演算子
		ID3D12CommandQueue* operator->() const noexcept;

	private:
		//!	@brief	コマンドキュー
		ID3D12CommandQueue* m_queue;
	};
}
