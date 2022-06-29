/**	@file	frot.hpp
 *	@brief	単精度浮動小数点数型の回転量クラス
 */
#pragma once

namespace dlph {
	/**	@class	FRotation
	 *	@brief	単精度浮動小数点数型の回転量
	 */
	class FRotation final {
	public:
		//!	@brief	ムーブコンストラクタ
		FRotation(FRotation&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		FRotation(FRotation const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		FRotation& operator=(FRotation&&) noexcept = default;
		//!	@brief	コピー代入演算子
		FRotation& operator=(FRotation const&) noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		FRotation() noexcept;
		//!	@brief	デストラクタ
		~FRotation() noexcept = default;

		//! @brief 回転量設定関数（弧度法）
		FRotation& radian(float const&) noexcept;
		//! @brief 回転量設定関数（度数法）
		FRotation& degree(float const&) noexcept;

		//!	@brief	複合加算演算子
		FRotation& operator+=(FRotation const&) noexcept;
		//!	@brief	複合減算演算子
		FRotation& operator-=(FRotation const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		FRotation& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		FRotation& operator/=(float const&) noexcept;

		//! @brief 回転量取得関数（弧度法）
		float const radian() const noexcept;
		//! @brief 回転量取得関数（度数法）
		float const degree() const noexcept;

		//!	@brief	単項加算演算子
		FRotation const operator+() const noexcept;
		//!	@brief	単項減算演算子
		FRotation const operator-() const noexcept;

	private:
		//!	@brief	角度データ
		float m_angle;
	};

	//! @brief 正弦関数
	FRotation const asin(float const&) noexcept;
	//! @brief 余弦関数
	FRotation const acos(float const&) noexcept;
	//! @brief 正接関数
	FRotation const atan(float const&) noexcept;
	//! @brief 正接関数
	FRotation const atan(float const& x, float const& y) noexcept;

	//! @brief 正弦関数
	float const sin(FRotation const&) noexcept;
	//! @brief 余弦関数
	float const cos(FRotation const&) noexcept;
	//! @brief 正接関数
	float const tan(FRotation const&) noexcept;

	//!	@brief	角度化関数
	FRotation const normalized(FRotation const&) noexcept;
	//!	@brief	回転数取得関数
	int const round(FRotation const&) noexcept;

	//!	@brief	加算演算子
	FRotation const operator+(FRotation const&, FRotation const&) noexcept;
	//!	@brief	減算演算子
	FRotation const operator-(FRotation const&, FRotation const&) noexcept;
	//!	@brief	スカラ倍演算子
	FRotation const operator*(FRotation const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	FRotation const operator*(float const&, FRotation const&) noexcept;
	//!	@brief	スカラ割演算子
	FRotation const operator/(FRotation const&, float const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(FRotation const&, FRotation const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(FRotation const&, FRotation const&) noexcept;
	//! @brief 小なりイコール演算子
	bool const operator<=(FRotation const&, FRotation const&) noexcept;
	//! @brief 大なりイコール演算子
	bool const operator>=(FRotation const&, FRotation const&) noexcept;
	//! @brief 小なり演算子
	bool const operator<(FRotation const&, FRotation const&) noexcept;
	//! @brief 大なり演算子
	bool const operator>(FRotation const&, FRotation const&) noexcept;
}
