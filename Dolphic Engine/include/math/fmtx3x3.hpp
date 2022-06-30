/**	@file	fmtx3x3.hpp
 *	@brief	単精度浮動小数点数型の三次正方行列クラス
 */
#pragma once
#pragma warning(disable : 4324)
#include "structs/flt3x3.hpp"
#include <initializer_list>

namespace dlph {
	struct Float3x3;
	class FVector3;

	/**	@class	FMatrix3x3
	 *	@brief	単精度浮動小数点数型の三次正方行列
	 */
	class alignas(16) FMatrix3x3 final : public Float3x3 {
	public:
		//! @brief ムーブコンストラクタ
		FMatrix3x3(FMatrix3x3&&) noexcept = default;
		//! @brief コピーコンストラクタ
		FMatrix3x3(FMatrix3x3 const&) noexcept = default;
		//! @brief ムーブ代入演算子
		FMatrix3x3& operator=(FMatrix3x3&&) & noexcept = default;
		//! @brief コピー代入演算子
		FMatrix3x3& operator=(FMatrix3x3 const&) & noexcept = default;

		//! @brief デフォルトコンストラクタ
		FMatrix3x3() noexcept;
		//! @brief デストラクタ
		~FMatrix3x3() noexcept = default;

		//! @brief 初期化子コンストラクタ
		explicit FMatrix3x3(std::initializer_list<float> const&) noexcept;
		//! @brief コンストラクタ
		constexpr FMatrix3x3(Float3x3 const& arg) noexcept :
			Float3x3(arg)
		{}
		//! @brief コンストラクタ
		constexpr FMatrix3x3(
			float const& m00, float const& m01, float const& m02,
			float const& m10, float const& m11, float const& m12,
			float const& m20, float const& m21, float const& m22
		) noexcept :
			Float3x3{
			m00, m01, m02,
			m10, m11, m12,
			m20, m21, m22 }
		{}

		//! @brief 行成分設定関数
		FMatrix3x3& row(unsigned int const&, FVector3 const&) noexcept;
		//! @brief 列成分設定関数
		FMatrix3x3& column(unsigned int const&, FVector3 const&) noexcept;

		//!	@brief 行交換関数
		//! @details 指定した行成分をもう一方の指定した行成分と入れ替えます。
		FMatrix3x3& row_swap(unsigned int const& from, unsigned int const& to) noexcept;
		//!	@brief 列交換関数
		//! @details 指定した列成分をもう一方の指定した列成分と入れ替えます。
		FMatrix3x3& column_swap(unsigned int const& from, unsigned int const& to) noexcept;

		//!	@brief 行拡縮関数
		//! @details 指定した行成分を定数倍します。
		FMatrix3x3& row_scale(unsigned int const& idx, float const&) noexcept;
		//!	@brief 列拡縮関数
		//! @details 指定した列成分を定数倍します。
		FMatrix3x3& column_scale(unsigned int const& idx, float const&) noexcept;

		//!	@brief 行定数倍加算関数
		//! @details 指定した行成分を定数倍したものをもう一方の指定した行成分に加算します。
		FMatrix3x3& row_prosum(unsigned int const& from, unsigned int const& to, float const&) noexcept;
		//!	@brief 列定数倍加算関数
		//! @details 指定した列成分を定数倍したものをもう一方の指定した列成分に加算します。
		FMatrix3x3& column_prosum(unsigned int const& from, unsigned int const& to, float const&) noexcept;

		//! @brief 複合加算演算子
		FMatrix3x3& operator+=(FMatrix3x3 const&) noexcept;
		//! @brief 複合減算演算子
		FMatrix3x3& operator-=(FMatrix3x3 const&) noexcept;
		//! @brief 複合スカラ倍演算子
		FMatrix3x3& operator*=(float const&) noexcept;
		//! @brief 複合スカラ割演算子
		FMatrix3x3& operator/=(float const&) noexcept;

		//! @brief 行成分抽出関数
		FVector3 const row(unsigned int const&) const noexcept;
		//! @brief 列成分抽出関数
		FVector3 const column(unsigned int const&) const noexcept;

		//! @brief 単項加算演算子
		FMatrix3x3 const operator+() const noexcept;
		//! @brief 単項減算演算子
		FMatrix3x3 const operator-() const noexcept;
	};

	//! @brief 転置行列生成関数
	FMatrix3x3 const transpose(FMatrix3x3 const&) noexcept;
	//! @brief 余因子行列生成関数
	FMatrix3x3 const adjoint(FMatrix3x3 const&) noexcept;
	//! @brief 逆行列生成関数
	FMatrix3x3 const inverse(FMatrix3x3 const&) noexcept;
	//! @brief 行列式関数
	float const determinant(FMatrix3x3 const&) noexcept;

	//!	@brief 直積関数
	FMatrix3x3 const direct(FVector3 const&, FVector3 const&) noexcept;
	//! @brief 楔積関数
	FMatrix3x3 const wedge(FVector3 const&, FVector3 const&) noexcept;

	//! @brief 加算演算子
	FMatrix3x3 const operator+(FMatrix3x3 const&, FMatrix3x3 const&) noexcept;
	//! @brief 減算演算子
	FMatrix3x3 const operator-(FMatrix3x3 const&, FMatrix3x3 const&) noexcept;
	//! @brief 乗算演算子
	FMatrix3x3 const operator*(FMatrix3x3 const&, FMatrix3x3 const&) noexcept;
	//! @brief スカラ倍演算子
	FMatrix3x3 const operator*(FMatrix3x3 const&, float const&) noexcept;
	//! @brief スカラ倍演算子
	FMatrix3x3 const operator*(float const&, FMatrix3x3 const&) noexcept;
	//! @brief 除算演算子
	FMatrix3x3 const operator/(FMatrix3x3 const&, FMatrix3x3 const&) noexcept;
	//! @brief スカラ割演算子
	FMatrix3x3 const operator/(FMatrix3x3 const&, float const&) noexcept;
	//! @brief スカラ割演算子
	FMatrix3x3 const operator/(float const&, FMatrix3x3 const&) noexcept;

	//! @brief 行列作用演算子
	FVector3 const operator*(FVector3 const&, FMatrix3x3 const&) noexcept;
	//! @brief 行列作用演算子
	FVector3 const operator*(FMatrix3x3 const&, FVector3 const&) noexcept;

	//! @brief 加算演算子
	bool const operator==(FMatrix3x3 const&, FMatrix3x3 const&) noexcept;
	//! @brief 減算演算子
	bool const operator!=(FMatrix3x3 const&, FMatrix3x3 const&) noexcept;

	//! @brief 零行列
	static FMatrix3x3 constexpr FMTX3x3_ZERO = FMatrix3x3(
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	);
	//! @brief 単位行列
	static FMatrix3x3 constexpr FMTX3x3_UNIT = FMatrix3x3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);
}
