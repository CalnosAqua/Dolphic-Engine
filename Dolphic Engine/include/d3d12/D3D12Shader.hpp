/**	@file	D3D12Shader.hpp
 *	@brief	Direct3D12 用のシェーダクラス
 */
#pragma once
#include "ifs/noncopyable.hpp"
#include <d3d12.h>

namespace dlph {
	/**	@class	D3D12Shader
	 *	@brief	シェーダ
	 */
	class D3D12Shader final :
		public INoncopyable<D3D12Shader>
	{
	public:
		//!	@brief	ムーブコンストラクタ
		D3D12Shader(D3D12Shader&&) noexcept;
		//!	@brief	ムーブ代入演算子
		D3D12Shader& operator=(D3D12Shader&&) & noexcept;
		
		//!	@brief	デフォルトコンストラクタ
		D3D12Shader() noexcept;
		//!	@brief	デストラクタ
		~D3D12Shader() noexcept;

		//!	@brief	初期化関数
		bool const init(wchar_t const* const&) noexcept;
		//!	@brief	終了関数
		void uninit() noexcept;

		//!	@brief	設定用データ出力関数
		D3D12_SHADER_BYTECODE const get() const noexcept;

	private:
		//!	@brief	シェーダの塊
		ID3DBlob* m_shader;
	};
}
