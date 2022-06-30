/**	@file	fvec2.hpp
 *	@brief	単精度浮動小数点数型の二次元ベクトルクラス
 */
#pragma once
#pragma warning(disable : 4324)
#include "structs/flt2.hpp"
#include <initializer_list>

namespace dlph {
	struct Float2;

	/**	@class	FVector2
	 *	@brief	単精度浮動小数点数型の二次元ベクトル
	 */
	class alignas(16) FVector2 final : public Float2 {
	public:
		//!	@brief	ムーブコンストラクタ
		FVector2(FVector2&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		FVector2(FVector2 const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		FVector2& operator=(FVector2&&) &noexcept = default;
		//!	@brief	コピー代入演算子
		FVector2& operator=(FVector2 const&) & noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		FVector2() noexcept;
		//!	@brief	デストラクタ
		~FVector2() noexcept = default;

		//!	@brief	初期化子コンストラクタ
		explicit FVector2(std::initializer_list<float> const&) noexcept;
		//!	@brief	コンストラクタ
		constexpr FVector2(Float2 const& arg) noexcept :
			Float2(arg)
		{}
		//!	@brief	コンストラクタ
		constexpr FVector2(float const& x, float const& y) noexcept :
			Float2{ x, y }
		{}

		//!	@brief	複合加算演算子
		FVector2& operator+=(FVector2 const&) noexcept;
		//!	@brief	複合減算演算子
		FVector2& operator-=(FVector2 const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		FVector2& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		FVector2& operator/=(float const&) noexcept;

		//!	@brief	単項加算演算子
		FVector2 const operator+() const noexcept;
		//!	@brief	単項減算演算子
		FVector2 const operator-() const noexcept;
	};
	//!	@brief	外積関数
	FVector2 const cross(FVector2 const&) noexcept;
	//!	@brief	内積関数
	float const dot(FVector2 const&, FVector2 const&) noexcept;

	//!	@brief	正規化関数
	FVector2 const normalize(FVector2 const&) noexcept;
	//!	@brief	大きさの二乗取得関数
	float const sqr_magnitude(FVector2 const&) noexcept;
	//!	@brief	大きさ取得関数
	float const magnitude(FVector2 const&) noexcept;

	//!	@brief	加算演算子
	FVector2 const operator+(FVector2 const&, FVector2 const&) noexcept;
	//!	@brief	減算演算子
	FVector2 const operator-(FVector2 const&, FVector2 const&) noexcept;
	//!	@brief	スカラ倍演算子
	FVector2 const operator*(FVector2 const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	FVector2 const operator*(float const&, FVector2 const&) noexcept;
	//!	@brief	スカラ割演算子
	FVector2 const operator/(FVector2 const&, float const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(FVector2 const&, FVector2 const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(FVector2 const&, FVector2 const&) noexcept;

	//!	@brief	ゼロベクトル
	static FVector2 constexpr FVT2_ZERO = FVector2(0.0f, 0.0f);
}
