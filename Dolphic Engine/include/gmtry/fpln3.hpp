/**	@file	fpln3.hpp
 *	@brief	平面クラス
 */
#pragma once
#include "math/mathutil.hpp"
#include "math/fmtx3x3.hpp"
#include "math/fvec3.hpp"

namespace dlph {
	enum class HandSide;
	class FMatrix3x3;
	class FVector3;

	/**	@class	FPlane3
	 *	@brief	平面クラス
	 */
	class FPlane3 final {
	public	:
		//!	@brief	ムーブコンストラクタ
		FPlane3(FPlane3&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		FPlane3(FPlane3 const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		FPlane3& operator=(FPlane3&&) & noexcept = default;
		//!	@brief	コピー代入演算子
		FPlane3& operator=(FPlane3 const&) & noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		FPlane3() noexcept;
		//!	@brief	デストラクタ
		~FPlane3() noexcept = default;

		/**	@brief	初期化関数
		 *	@param[in] 座標値
		 */
		FPlane3& init(FVector3 const& p1, FVector3 const& p2, FVector3 const& p3) noexcept;
		//!	@brief	終了関数
		void exit() noexcept;

		//!	@brief	法線ベクトル取得関数
		FVector3 const normal() const noexcept;
		//!	@brief	従法線ベクトル取得関数
		FVector3 const binormal() const noexcept;
		//!	@brief	接ベクトル取得関数
		FVector3 const tangent() const noexcept;

		//!	@brief	接ベクトル空間変換行列取得関数
		FMatrix3x3 const matrix(HandSide const& hs) const noexcept;

	private	:
		//!	@brief	法線ベクトル
		Float3 m_normal;
		//!	@brief	従法線ベクトル
		Float3 m_binormal;
		//!	@brief	接ベクトル
		Float3 m_tangent;

		//!	@brief	D値
		float m_d;
	};
}
