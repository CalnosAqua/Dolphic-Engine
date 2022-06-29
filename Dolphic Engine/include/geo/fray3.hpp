/**	@file	avfray3.hpp
 *	@brief	三次元光線クラス
 */
#pragma once
#include "math/fvec3.hpp"

namespace dlph {
	/**	@class	FRay3
	 *	@brief	三次元光線
	 */
	class FRay3 final {
	public	:
		//! @brief 中心点
		FVector3 position;
		//! @brief 方向
		FVector3 direction;

		//! @brief デストラクタ
		~FRay3() noexcept = default;
		//! @brief ムーブコンストラクタ
		FRay3(FRay3&&) noexcept = default;
		//! @brief コピーコンストラクタ
		FRay3(FRay3 const&) noexcept = default;
		//! @brief ムーブ代入演算子
		FRay3& operator=(FRay3&&) noexcept = default;
		//! @brief コピー代入演算子
		FRay3& operator=(FRay3 const&) noexcept = default;

		//! @brief デフォルトコンストラクタ
		FRay3() noexcept;
		//! @brief コンストラクタ
		FRay3(FVector3 const& pos, FVector3 const& dir) noexcept;

		//! @brief 添え字演算子
		FVector3 const operator[](float const& rate) noexcept;
	};
}
