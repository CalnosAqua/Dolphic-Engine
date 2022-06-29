/**	@file	D3D12Device.hpp
 *	@brief	Direct3D12 用のデバイスクラス
 */
#pragma	once
#include "ifs/singleton.hpp"
#include <d3d12.h>

namespace dlph {
	/**	@file	D3D12Device
	 *	@brief	Direct3D12 用のデバイスクラス
	 */
	class D3D12Device final : public ISingleton<D3D12Device> {
	public	:
		//!	@brief	デフォルトコンストラクタ
		D3D12Device() noexcept;
		//!	@brief	デストラクタ
		~D3D12Device() noexcept;

		//!	@brief	初期化関数
		bool const init() noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

		//!	@brief	ポインタ取得関数
		ID3D12Device8* get() const noexcept;
		//!	@brief	メンバアクセス演算子
		ID3D12Device8* operator->() const noexcept;

	private	:
		//!	@brief	デバイス
		ID3D12Device8* m_device;
	};
}
