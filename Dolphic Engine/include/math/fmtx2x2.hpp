/**	@file	fmtx2x2.hpp
 *	@brief	単精度浮動小数点数型の二次正方行列クラス
 */
#pragma once
#pragma warning(disable : 4324)
#include "structs/flt2x2.hpp"
#include <initializer_list>

namespace dlph {
	struct Float2x2;
	class FVector2;

	/**	@class	FMatrix2x2
	 *	@brief	単精度浮動小数点数型の二次正方行列
	 */
	class alignas(16) FMatrix2x2 final : public Float2x2 {
	public:
		//! @brief ムーブコンストラクタ
		FMatrix2x2(FMatrix2x2&&) noexcept = default;
		//! @brief コピーコンストラクタ
		FMatrix2x2(FMatrix2x2 const&) noexcept = default;
		//! @brief ムーブ代入演算子
		FMatrix2x2& operator=(FMatrix2x2&&) & noexcept = default;
		//! @brief コピー代入演算子
		FMatrix2x2& operator=(FMatrix2x2 const&) & noexcept = default;

		//! @brief デフォルトコンストラクタ
		FMatrix2x2() noexcept;
		//! @brief デストラクタ
		~FMatrix2x2() noexcept = default;

		//! @brief 初期化子コンストラクタ
		explicit FMatrix2x2(std::initializer_list<float> const&) noexcept;
		//! @brief コンストラクタ
		constexpr FMatrix2x2(
			float const& m00, float const& m01,
			float const& m10, float const& m11
		) noexcept :
			Float2x2{
			m00, m01,
			m10, m11 }
		{}

		//! @brief 行成分設定関数
		FMatrix2x2& row(unsigned int const&, FVector2 const&) noexcept;
		//! @brief 列成分設定関数
		FMatrix2x2& column(unsigned int const&, FVector2 const&) noexcept;

		//!	@brief 行交換関数
		//! @details 指定した行成分をもう一方の指定した行成分と入れ替えます。
		FMatrix2x2& row_swap(unsigned int const& from, unsigned int const& to) noexcept;
		//!	@brief 列交換関数
		//! @details 指定した列成分をもう一方の指定した列成分と入れ替えます。
		FMatrix2x2& column_swap(unsigned int const& from, unsigned int const& to) noexcept;

		//!	@brief 行拡縮関数
		//! @details 指定した行成分を定数倍します。
		FMatrix2x2& row_scale(unsigned int const& idx, float const&) noexcept;
		//!	@brief 列拡縮関数
		//! @details 指定した列成分を定数倍します。
		FMatrix2x2& column_scale(unsigned int const& idx, float const&) noexcept;

		//!	@brief 行定数倍加算関数
		//! @details 指定した行成分を定数倍したものをもう一方の指定した行成分に加算します。
		FMatrix2x2& row_prosum(unsigned int const& from, unsigned int const& to, float const&) noexcept;
		//!	@brief 列定数倍加算関数
		//! @details 指定した列成分を定数倍したものをもう一方の指定した列成分に加算します。
		FMatrix2x2& column_prosum(unsigned int const& from, unsigned int const& to, float const&) noexcept;

		//! @brief 複合加算演算子
		FMatrix2x2& operator+=(FMatrix2x2 const&) noexcept;
		//! @brief 複合減算演算子
		FMatrix2x2& operator-=(FMatrix2x2 const&) noexcept;
		//! @brief 複合スカラ倍演算子
		FMatrix2x2& operator*=(float const&) noexcept;
		//! @brief 複合スカラ割演算子
		FMatrix2x2& operator/=(float const&) noexcept;

		//! @brief 行成分抽出関数
		FVector2 const row(unsigned int const&) const noexcept;
		//! @brief 列成分抽出関数
		FVector2 const column(unsigned int const&) const noexcept;

		//! @brief 単項加算演算子
		FMatrix2x2 const operator+() const noexcept;
		//! @brief 単項減算演算子
		FMatrix2x2 const operator-() const noexcept;
	};

	//! @brief 転置行列生成関数
	FMatrix2x2 const transpose(FMatrix2x2 const&) noexcept;
	//! @brief 余因子行列生成関数
	FMatrix2x2 const adjoint(FMatrix2x2 const&) noexcept;
	//! @brief 逆行列生成関数
	FMatrix2x2 const inverse(FMatrix2x2 const&) noexcept;
	//! @brief 行列式関数
	float const determinant(FMatrix2x2 const&) noexcept;

	//!	@brief 直積関数
	FMatrix2x2 const direct(FVector2 const&, FVector2 const&) noexcept;
	//! @brief 楔積関数
	FMatrix2x2 const wedge(FVector2 const&, FVector2 const&) noexcept;

	//! @brief 加算演算子
	FMatrix2x2 const operator+(FMatrix2x2 const&, FMatrix2x2 const&) noexcept;
	//! @brief 減算演算子
	FMatrix2x2 const operator-(FMatrix2x2 const&, FMatrix2x2 const&) noexcept;
	//! @brief 乗算演算子
	FMatrix2x2 const operator*(FMatrix2x2 const&, FMatrix2x2 const&) noexcept;
	//! @brief スカラ倍演算子
	FMatrix2x2 const operator*(FMatrix2x2 const&, float const&) noexcept;
	//! @brief スカラ倍演算子
	FMatrix2x2 const operator*(float const&, FMatrix2x2 const&) noexcept;
	//! @brief 除算演算子
	FMatrix2x2 const operator/(FMatrix2x2 const&, FMatrix2x2 const&) noexcept;
	//! @brief スカラ割演算子
	FMatrix2x2 const operator/(FMatrix2x2 const&, float const&) noexcept;
	//! @brief スカラ割演算子
	FMatrix2x2 const operator/(float const&, FMatrix2x2 const&) noexcept;

	//! @brief 行列作用演算子
	FVector2 const operator*(FVector2 const&, FMatrix2x2 const&) noexcept;
	//! @brief 行列作用演算子
	FVector2 const operator*(FMatrix2x2 const&, FVector2 const&) noexcept;

	//! @brief 加算演算子
	bool const operator==(FMatrix2x2 const&, FMatrix2x2 const&) noexcept;
	//! @brief 減算演算子
	bool const operator!=(FMatrix2x2 const&, FMatrix2x2 const&) noexcept;

	//! @brief 零行列
	static FMatrix2x2 constexpr FMTX2x2_ZERO = FMatrix2x2(
		0.0f, 0.0f,
		0.0f, 0.0f
	);
	//! @brief 単位行列
	static FMatrix2x2 constexpr FMTX2x2_UNIT = FMatrix2x2(
		1.0f, 0.0f,
		0.0f, 1.0f
	);
}
