/**	@file	fpln3.hpp
 *	@brief	三次元平面方程式・接ベクトル行列クラス
 */
#pragma once
#include "math/fvec3.hpp"
#include "math/fmtx3x3.hpp"
#include "math/mathutil.hpp"

namespace dlph {
	/**	@class FPlane3
	 *	@brief 三次元平面方程式・接ベクトル行列
	 */
	class FPlane3 final {
	public	:
		//! @brief デストラクタ
		~FPlane3() noexcept = default;
		//! @brief ムーブコンストラクタ
		FPlane3(FPlane3&&) noexcept = default;
		//! @brief コピーコンストラクタ
		FPlane3(FPlane3 const&) noexcept = default;
		//! @brief ムーブ代入演算子
		FPlane3& operator=(FPlane3&&) noexcept = default;
		//! @brief コピー代入演算子
		FPlane3& operator=(FPlane3 const&) noexcept = default;

		//! @brief デフォルトコンストラクタ
		FPlane3() noexcept;

		//! @brief 初期化関数
		FPlane3& init(HandSide const&, FVector3 const&, FVector3 const&, FVector3 const&) noexcept;

		//! @brief 法線取得関数
		FVector3 const normal() const noexcept;
		//! @brief 従法線取得関数
		FVector3 const binormal() const noexcept;
		//! @brief 接ベクトル取得関数
		FVector3 const tangent() const noexcept;

	private	:
		//! @brief 平面の方程式の値
		float m_d;
		//! @brief 接ベクトル空間行列
		FMatrix3x3 m_mtx;
		//! @brief 作用方向
		HandSide m_side;
	};
}
