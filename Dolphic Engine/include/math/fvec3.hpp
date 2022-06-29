/**	@file	fvec3.hpp
 *	@brief	単精度浮動小数点数型の三次元ベクトルクラス
 */
#pragma once
#pragma warning(disable : 4324)
#include "structs/flt3.hpp"
#include <initializer_list>

namespace dlph {
	struct Float3;

	/**	@class	FVector3
	 *	@brief	単精度浮動小数点数型の三次元ベクトル
	 */
	class alignas(16) FVector3 final : public Float3 {
	public	:
		//!	@brief	ムーブコンストラクタ
		FVector3(FVector3&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		FVector3(FVector3 const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		FVector3& operator=(FVector3&&) & noexcept = default;
		//!	@brief	コピー代入演算子
		FVector3& operator=(FVector3 const&) & noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		FVector3() noexcept;
		//!	@brief	デストラクタ
		~FVector3() noexcept = default;

		//!	@brief	初期化子コンストラクタ
		explicit FVector3(std::initializer_list<float> const&) noexcept;
		//!	@brief	初期化子コンストラクタ
		constexpr FVector3(float const& x, float const& y, float const& z) noexcept :
			Float3{ x, y, z }
		{}

		//!	@brief	複合加算演算子
		FVector3& operator+=(FVector3 const&) noexcept;
		//!	@brief	複合減算演算子
		FVector3& operator-=(FVector3 const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		FVector3& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		FVector3& operator/=(float const&) noexcept;

		//!	@brief	単項加算演算子
		FVector3 const operator+() const noexcept;
		//!	@brief	単項減算演算子
		FVector3 const operator-() const noexcept;
	};
	//!	@brief	外積関数
	FVector3 const cross(FVector3 const&, FVector3 const&) noexcept;
	//!	@brief	内積関数
	float const dot(FVector3 const&, FVector3 const&) noexcept;

	//!	@brief	正規化関数
	FVector3 const normalize(FVector3 const&) noexcept;
	//!	@brief	大きさの二乗取得関数
	float const sqr_magnitude(FVector3 const&) noexcept;
	//!	@brief	大きさ取得関数
	float const magnitude(FVector3 const&) noexcept;

	//!	@brief	加算演算子
	FVector3 const operator+(FVector3 const&, FVector3 const&) noexcept;
	//!	@brief	減算演算子
	FVector3 const operator-(FVector3 const&, FVector3 const&) noexcept;
	//!	@brief	スカラ倍演算子
	FVector3 const operator*(FVector3 const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	FVector3 const operator*(float const&, FVector3 const&) noexcept;
	//!	@brief	スカラ割演算子
	FVector3 const operator/(FVector3 const&, float const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(FVector3 const&, FVector3 const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(FVector3 const&, FVector3 const&) noexcept;

	//!	@brief	ゼロベクトル
	static FVector3 constexpr FVT3_ZERO = FVector3(0.0f, 0.0f, 0.0f);
}
