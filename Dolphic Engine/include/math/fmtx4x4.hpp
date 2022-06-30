/**	@file	fmtx4x4.hpp
 *	@brief	単精度浮動小数点数型の四次正方行列クラス
 */
#pragma once
#pragma warning(disable : 4324)
#include "structs/flt4x4.hpp"
#include <initializer_list>

namespace dlph {
	struct Float4x4;
	class FVector4;

	/**	@class	FMatrix4x4
	 *	@brief	単精度浮動小数点数型の四次正方行列
	 */
	class alignas(16) FMatrix4x4 final : public Float4x4 {
	public:
		//! @brief ムーブコンストラクタ
		FMatrix4x4(FMatrix4x4&&) noexcept = default;
		//! @brief コピーコンストラクタ
		FMatrix4x4(FMatrix4x4 const&) noexcept = default;
		//! @brief ムーブ代入演算子
		FMatrix4x4& operator=(FMatrix4x4&&) & noexcept = default;
		//! @brief コピー代入演算子
		FMatrix4x4& operator=(FMatrix4x4 const&) & noexcept = default;

		//! @brief デフォルトコンストラクタ
		FMatrix4x4() noexcept;
		//! @brief デストラクタ
		~FMatrix4x4() noexcept = default;

		//! @brief 初期化子コンストラクタ
		explicit FMatrix4x4(std::initializer_list<float> const&) noexcept;
		//! @brief コンストラクタ
		constexpr FMatrix4x4(Float4x4 const& arg) noexcept :
			Float4x4(arg)
		{}
		//! @brief コンストラクタ
		constexpr FMatrix4x4(
			float const& m00, float const& m01, float const& m02, float const& m03,
			float const& m10, float const& m11, float const& m12, float const& m13,
			float const& m20, float const& m21, float const& m22, float const& m23,
			float const& m30, float const& m31, float const& m32, float const& m33
		) noexcept :
			Float4x4{
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33 }
		{}

		//! @brief 行成分設定関数
		FMatrix4x4& row(unsigned int const&, FVector4 const&) noexcept;
		//! @brief 列成分設定関数
		FMatrix4x4& column(unsigned int const&, FVector4 const&) noexcept;

		//!	@brief 行交換関数
		//! @details 指定した行成分をもう一方の指定した行成分と入れ替えます。
		FMatrix4x4& row_swap(unsigned int const& from, unsigned int const& to) noexcept;
		//!	@brief 列交換関数
		//! @details 指定した列成分をもう一方の指定した列成分と入れ替えます。
		FMatrix4x4& column_swap(unsigned int const& from, unsigned int const& to) noexcept;

		//!	@brief 行拡縮関数
		//! @details 指定した行成分を定数倍します。
		FMatrix4x4& row_scale(unsigned int const& idx, float const&) noexcept;
		//!	@brief 列拡縮関数
		//! @details 指定した列成分を定数倍します。
		FMatrix4x4& column_scale(unsigned int const& idx, float const&) noexcept;

		//!	@brief 行定数倍加算関数
		//! @details 指定した行成分を定数倍したものをもう一方の指定した行成分に加算します。
		FMatrix4x4& row_prosum(unsigned int const& from, unsigned int const& to, float const&) noexcept;
		//!	@brief 列定数倍加算関数
		//! @details 指定した列成分を定数倍したものをもう一方の指定した列成分に加算します。
		FMatrix4x4& column_prosum(unsigned int const& from, unsigned int const& to, float const&) noexcept;

		//! @brief 複合加算演算子
		FMatrix4x4& operator+=(FMatrix4x4 const&) noexcept;
		//! @brief 複合減算演算子
		FMatrix4x4& operator-=(FMatrix4x4 const&) noexcept;
		//! @brief 複合スカラ倍演算子
		FMatrix4x4& operator*=(float const&) noexcept;
		//! @brief 複合スカラ割演算子
		FMatrix4x4& operator/=(float const&) noexcept;

		//! @brief 行成分抽出関数
		FVector4 const row(unsigned int const&) const noexcept;
		//! @brief 列成分抽出関数
		FVector4 const column(unsigned int const&) const noexcept;

		//! @brief 単項加算演算子
		FMatrix4x4 const operator+() const noexcept;
		//! @brief 単項減算演算子
		FMatrix4x4 const operator-() const noexcept;
	};

	//! @brief 転置行列生成関数
	FMatrix4x4 const transpose(FMatrix4x4 const&) noexcept;
	//! @brief 余因子行列生成関数
	FMatrix4x4 const adjoint(FMatrix4x4 const&) noexcept;
	//! @brief 逆行列生成関数
	FMatrix4x4 const inverse(FMatrix4x4 const&) noexcept;
	//! @brief 行列式関数
	float const determinant(FMatrix4x4 const&) noexcept;

	//!	@brief 直積関数
	FMatrix4x4 const direct(FVector4 const&, FVector4 const&) noexcept;
	//! @brief 楔積関数
	FMatrix4x4 const wedge(FVector4 const&, FVector4 const&) noexcept;

	//! @brief 加算演算子
	FMatrix4x4 const operator+(FMatrix4x4 const&, FMatrix4x4 const&) noexcept;
	//! @brief 減算演算子
	FMatrix4x4 const operator-(FMatrix4x4 const&, FMatrix4x4 const&) noexcept;
	//! @brief 乗算演算子
	FMatrix4x4 const operator*(FMatrix4x4 const&, FMatrix4x4 const&) noexcept;
	//! @brief スカラ倍演算子
	FMatrix4x4 const operator*(FMatrix4x4 const&, float const&) noexcept;
	//! @brief スカラ倍演算子
	FMatrix4x4 const operator*(float const&, FMatrix4x4 const&) noexcept;
	//! @brief 除算演算子
	FMatrix4x4 const operator/(FMatrix4x4 const&, FMatrix4x4 const&) noexcept;
	//! @brief スカラ割演算子
	FMatrix4x4 const operator/(FMatrix4x4 const&, float const&) noexcept;
	//! @brief スカラ割演算子
	FMatrix4x4 const operator/(float const&, FMatrix4x4 const&) noexcept;

	//! @brief 行列作用演算子
	FVector4 const operator*(FVector4 const&, FMatrix4x4 const&) noexcept;
	//! @brief 行列作用演算子
	FVector4 const operator*(FMatrix4x4 const&, FVector4 const&) noexcept;

	//! @brief 加算演算子
	bool const operator==(FMatrix4x4 const&, FMatrix4x4 const&) noexcept;
	//! @brief 減算演算子
	bool const operator!=(FMatrix4x4 const&, FMatrix4x4 const&) noexcept;

	//! @brief 零行列
	static FMatrix4x4 constexpr FMTX4x4_ZERO = FMatrix4x4(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);
	//! @brief 単位行列
	static FMatrix4x4 constexpr FMTX4x4_UNIT = FMatrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
