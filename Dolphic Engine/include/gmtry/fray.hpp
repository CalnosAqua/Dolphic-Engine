/**	@file	fray.hpp
 *	@brief	光線クラス
 */
#pragma once
#include "math/fvec3.hpp"

namespace dlph {
	/**	@class	FRay
	 *	@brief	光線クラス
	 */
	class FRay final {
	public	:
		//!	@brief	ムーブコンストラクタ
		FRay(FRay&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		FRay(FRay const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		FRay& operator=(FRay&&) & noexcept = default;
		//!	@brief	コピー代入演算子
		FRay& operator=(FRay const&) & noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		FRay() noexcept;
		//!	@brief	デストラクタ
		~FRay() noexcept = default;

	private	:
		//!	@brief	中心点
		FVector3 m_center;
		//!	@brief	方向
		FVector3 m_direct;
		//!	@brief	太さ
		float m_thick;
	};
}
