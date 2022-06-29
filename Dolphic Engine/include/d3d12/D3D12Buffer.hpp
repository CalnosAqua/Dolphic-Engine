/**	@file	D3D12Buffer.hpp
 *	@brief	Direct3D12 用のバッファテンプレートクラス
 */
#pragma once
#pragma warning(disable : 4251)
#include "ifs/noncopyable.hpp"
#include "D3D12ViewType.hpp"
#include "D3D12SwapChain.hpp"
#include <vector>
#include <dxgi1_6.h>
#include <d3d12.h>

namespace dlph {
	/**	@struct	D3D12DescriptorHeap
	 *	@brief	記述子ハンドル
	 */
	struct D3D12DescriptorHandle final {
		//!	@brief	CPU 記述子ハンドル
		D3D12_CPU_DESCRIPTOR_HANDLE cpu;
		//!	@brief	GPU 記述子ハンドル
		D3D12_GPU_DESCRIPTOR_HANDLE gpu;
		//!	@brief	使用可能かどうか
		bool usable;
	};

	/**	@class	D3D12Buffer
	 *	@brief	Direct3D12 用のバッファテンプレート
	 */
	class D3D12Buffer final : public INoncopyable<D3D12Buffer> {
	public	:
		//!	@brief	ムーブコンストラクタ
		D3D12Buffer(D3D12Buffer&&) noexcept;
		//!	@brief	ムーブ代入演算子
		D3D12Buffer& operator=(D3D12Buffer&&) & noexcept;

		//!	@brief	デフォルトコンストラクタ
		D3D12Buffer() noexcept;
		//!	@brief	デストラクタ
		~D3D12Buffer() noexcept;

		//!	@brief	初期化関数
		bool const init(D3D12ViewType const& type, unsigned int const& count) noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

		//!	@brief	記述子ハンドル取得関数
		D3D12DescriptorHandle const getDescriptorHandle(unsigned int const& idx) const noexcept;
		//!	@brief	GPU アドレス取得関数
		D3D12_GPU_VIRTUAL_ADDRESS const getGPUVirtualAddress(unsigned int const& idx) const noexcept;

		//!	@brief	添え字演算子
		ID3D12Resource2*& operator[](unsigned int const& idx)& noexcept;
		//!	@brief	添え字演算子
		ID3D12Resource2* const& operator[](unsigned int const& idx) const& noexcept;

	private	:
		//!	@brief	記述子ヒープ
		ID3D12DescriptorHeap* m_heap;
		//!	@brief	リソース
		std::vector<ID3D12Resource2*> m_rsrces;
		//!	@brief	ヒープの種類
		D3D12ViewType m_type;

		//!	@brief	初期化状態
		bool m_init;
	};

	/**	@brief	深度バッファ生成関数
	 *	@param[in] buffer 対象バッファ
	 *	@param[in] hWnd ウィンドウハンドラ
	 *	@retval true 生成に成功しました。
	 *	@retval false 生成に失敗しました。
	 */
	bool const createDepthStencilView(D3D12Buffer& buffer, HWND const& hWnd) noexcept;

	/**	@brief	レンダーターゲット生成関数
	 *	@param[in] buffer 対象バッファ
	 *	@param[in] swapchain スワップチェイン
	 *	@param[in] size バッファ数
	 *	@retval true 生成に成功しました。
	 *	@retval false 生成に失敗しました。
	 */
	bool const createRenderTargetView(D3D12Buffer& buffer, D3D12SwapChain const& swapchain, unsigned int const& size) noexcept;

	/**	@brief	頂点バッファ生成関数
	 *	@param[in] buffer 対象バッファ
	 *	@param[in] vertex 頂点データの先頭ポインタ
	 *	@param[in] size 頂点数
	 *	@retval true 生成に成功しました。
	 *	@retval false 生成に失敗しました。
	 */
	template <typename Vertex>
	bool const createVertexBufferView(D3D12Buffer& buffer, Vertex* vertecies, unsigned int const& size) noexcept;

	/**	@brief	インデックスバッファ生成関数
	 *	@param[in] buffer 対象バッファ
	 *	@param[in] vertex インデックスデータの先頭ポインタ
	 *	@param[in] size インデックス数
	 *	@retval true 生成に成功しました。
	 *	@retval false 生成に失敗しました。
	 */
	bool const createIndexBufferView(D3D12Buffer& buffer, unsigned int* indecies, unsigned int const& size) noexcept;

	/**	@brief	定数バッファ生成関数
	 *	@param[in] buffer 対象バッファ
	 *	@param[in] vertex インデックスデータの先頭ポインタ
	 *	@param[in] size 定数バッファ数
	 *	@retval true 生成に成功しました。
	 *	@retval false 生成に失敗しました。
	 */
	template <typename T>
	bool const createConstantBufferView(D3D12Buffer& buffer, T const& data, unsigned int const& size) noexcept;
}

#include "D3D12Buffer.inl"
