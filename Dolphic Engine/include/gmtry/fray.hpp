/**	@file	fray.hpp
 *	@brief	光線クラス
 */
#pragma once

namespace dlph {
	/**	@class	FRay<T>
	 *	@brief	光線クラス
	 */
	template <typename T>
	class FRay final {
	public	:
		//!	@brief	ムーブコンストラクタ
		FRay(FRay<T>&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		FRay(FRay<T> const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		FRay& operator=(FRay<T>&&) & noexcept = default;
		//!	@brief	コピー代入演算子
		FRay& operator=(FRay<T> const&) & noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		FRay() noexcept;
		//!	@brief	デストラクタ
		~FRay() noexcept = default;

		//!	@brief	光線点取得演算子
		T const operator[](float const& rate) const noexcept;

		//!	@brief	中心点設定関数
		FRay<T>& center(T const& arg) const noexcept;
		//!	@brief	方向設定関数
		FRay<T>& direction(T const& arg) const noexcept;
		//!	@brief	半径設定関数
		FRay<T>& radius(float const& arg) const noexcept;

		//!	@brief	中心点取得関数
		T const& center() const noexcept;
		//!	@brief	方向取得関数
		T const& direction() const noexcept;
		//!	@brief	半径取得関数
		float const& radius() const noexcept;

	private	:
		//!	@brief	中心点
		T m_center;
		//!	@brief	方向
		T m_direct;
		//!	@brief	半径
		float m_radius;
	};
}

#include "fray.inl"
