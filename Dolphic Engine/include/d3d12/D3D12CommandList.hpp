/**	@file	D3D12CommandList.hpp
 *	@brief	Direct3D12 用のコマンドリスト
 */
#pragma once
#include "ifs/noncopyable.hpp"
#include "D3D12CommandType.hpp"
#include <d3d12.h>

namespace dlph {
	/**	@class	D3D12CommandList
	 *	@brief	Direct3D12 用のデバイスクラス
	 */
	class D3D12CommandList final :
		public INoncopyable<D3D12CommandList>
	{
	public:
		//!	@brief	ムーブコンストラクタ
		D3D12CommandList(D3D12CommandList&&) noexcept;
		//!	@brief	ムーブ代入演算子
		D3D12CommandList& operator=(D3D12CommandList&&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		D3D12CommandList() noexcept;
		//!	@brief	デストラクタ
		~D3D12CommandList() noexcept;

		//!	@brief	初期化関数
		bool const init(D3D12CommandType const&) noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

		//!	@brief	コマンド記録開始
		bool const recording() noexcept;
		//!	@brief	コマンド記録終了
		bool const closing() noexcept;

		//!	@brief	ポインタ取得
		ID3D12GraphicsCommandList6*& get() const noexcept;
		//!	@brief	メンバアクセス演算子
		ID3D12GraphicsCommandList6* operator->() const noexcept;

	private:
		//!	@brief	コマンドアロケータ
		ID3D12CommandAllocator* m_alloc;
		//!	@brief	コマンドリスト
		ID3D12GraphicsCommandList6* m_list;
	};
}
