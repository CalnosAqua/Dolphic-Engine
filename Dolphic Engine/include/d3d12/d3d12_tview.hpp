/**	@file	d3d12_tview.hpp
 *	@brief	ビュータイプ列挙体
 */
#pragma once

namespace dlph {
	/**	@enum	D3D12ViewType
	 *	@brief	ビュータイプ
	 */
	enum class D3D12ViewType : unsigned char {
		//!	@brief	未知のビュー
		Unknown,
		//!	@brief	レンダーターゲットビュー
		RTV,
		//!	@brief	深度バッファビュー
		DSV,
		//!	@brief	頂点バッファビュー
		VBV,
		//!	@brief	インデックスバッファビュー
		IBV,
		//!	@brief	定数バッファビュー
		CBV,
		//!	@brief	順序無しアクセスビュー
		UAV,
		//!	@brief	シェーダリソースビュー
		SRV,
		//!	@brief	アクセラレーションストラクションビュー
		ASV,
		//!	@brief	サンプラビュー
		Sampler,
	};
}
