/**	@file	ferot.hpp
 *	@brief	単精度浮動小数点数型のオイラー角クラス
 */
#pragma once
#pragma warning(disable : 4201)
#include "math/t3.hpp"
#include "frot.hpp"

namespace dlph {
	/**	@class	FEulerRotation
	 *	@brief	単精度浮動小数点数型のオイラー角
	 */
	class FEulerRotation final : public Element3<FRotation> {
	public:
		//! @brief ムーブコンストラクタ
		FEulerRotation(FEulerRotation&&) noexcept = default;
		//! @brief コピーコンストラクタ
		FEulerRotation(FEulerRotation const&) noexcept = default;
		//! @brief ムーブ代入演算子
		FEulerRotation& operator=(FEulerRotation&&) & noexcept = default;
		//! @brief コピー代入演算子
		FEulerRotation& operator=(FEulerRotation const&) & noexcept = default;

		//! @brief デフォルトコンストラクタ
		FEulerRotation() noexcept;
		//! @brief デストラクタ
		~FEulerRotation() noexcept = default;

		//! @brief 複合加算演算子
		FEulerRotation& operator+=(FEulerRotation const&) noexcept;
		//! @brief 複合減算演算子
		FEulerRotation& operator-=(FEulerRotation const&) noexcept;
		//! @brief 複合スカラ倍演算子
		FEulerRotation& operator*=(float const&) noexcept;
		//! @brief 複合スカラ割演算子
		FEulerRotation& operator/=(float const&) noexcept;

		//! @brief 単項加算演算子
		FEulerRotation const operator+() const noexcept;
		//! @brief 単項減算演算子
		FEulerRotation const operator-() const noexcept;
	};

	//! @brief 加算演算子
	FEulerRotation const operator+(FEulerRotation const&, FEulerRotation const&) noexcept;
	//! @brief 減算演算子
	FEulerRotation const operator-(FEulerRotation const&, FEulerRotation const&) noexcept;
	//! @brief スカラ倍演算子
	FEulerRotation const operator*(FEulerRotation const&, float const&) noexcept;
	//! @brief スカラ倍演算子
	FEulerRotation const operator*(float const&, FEulerRotation const&) noexcept;
	//! @brief スカラ割演算子
	FEulerRotation const operator/(FEulerRotation const&, float const&) noexcept;

	//! @brief 等価比較演算子
	bool const operator==(FEulerRotation const&, FEulerRotation const&) noexcept;
	//! @brief 不等価比較演算子
	bool const operator!=(FEulerRotation const&, FEulerRotation const&) noexcept;
}
