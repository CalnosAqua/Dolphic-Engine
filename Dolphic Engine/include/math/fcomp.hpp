/**	@file	fcomp.hpp
 *	@brief	単精度浮動小数点数型の複素数クラス
 */
#pragma once
#pragma warning(disable : 4324)
#include "math/t2.hpp"
#include <initializer_list>

namespace dlph {
	/**	@class	FComplex
	 *	@brief	単精度浮動小数点数型の複素数
	 */
	class alignas(16) FComplex final : public Float2 {
	public:
		//!	@brief	ムーブコンストラクタ
		FComplex(FComplex&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		FComplex(FComplex const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		FComplex& operator=(FComplex&&) & noexcept = default;
		//!	@brief	コピー代入演算子
		FComplex& operator=(FComplex const&) & noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		FComplex() noexcept;
		//!	@brief	デストラクタ
		~FComplex() noexcept = default;

		//!	@brief	初期化子コンストラクタ
		explicit FComplex(std::initializer_list<float> const&) noexcept;
		//!	@brief	コンストラクタ
		constexpr FComplex(Float2 const& arg) noexcept :
			Float2(arg)
		{}
		//!	@brief	初期化子コンストラクタ
		constexpr FComplex(float const& x, float const& y) noexcept :
			Float2( x, y )
		{}

		//!	@brief	複合加算演算子
		FComplex& operator+=(FComplex const&) noexcept;
		//!	@brief	複合減算演算子
		FComplex& operator-=(FComplex const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		FComplex& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		FComplex& operator/=(float const&) noexcept;

		//!	@brief	単項加算演算子
		FComplex const operator+() const noexcept;
		//!	@brief	単項減算演算子
		FComplex const operator-() const noexcept;
	};

	//!	@brief	共役元生成関数
	FComplex const conjugate(FComplex const&) noexcept;
	//!	@brief	正規化関数
	FComplex const normalize(FComplex const&) noexcept;
	//!	@brief	逆元生成関数
	FComplex const inverse(FComplex const&) noexcept;

	//!	@brief	大きさの二乗生成関数
	float const sqr_magnitude(FComplex const&) noexcept;
	//!	@brief	大きさ生成関数
	float const magnitude(FComplex const&) noexcept;

	//!	@brief	加算演算子
	FComplex const operator+(FComplex const&, FComplex const&) noexcept;
	//!	@brief	減算演算子
	FComplex const operator-(FComplex const&, FComplex const&) noexcept;
	//!	@brief	スカラ倍演算子
	FComplex const operator*(FComplex const&, FComplex const&) noexcept;
	//!	@brief	スカラ倍演算子
	FComplex const operator*(FComplex const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	FComplex const operator*(float const&, FComplex const&) noexcept;
	//!	@brief	スカラ割演算子
	FComplex const operator/(FComplex const&, FComplex const&) noexcept;
	//!	@brief	スカラ割演算子
	FComplex const operator/(FComplex const&, float const&) noexcept;
	//!	@brief	スカラ割演算子
	FComplex const operator/(float const&, FComplex const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(FComplex const&, FComplex const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(FComplex const&, FComplex const&) noexcept;

	//!	@brief	零元複素数
	static FComplex constexpr FCMP_ZERO = FComplex(0.0f, 0.0f);
	//!	@brief	単位元複素数
	static FComplex constexpr FCMP_UNIT = FComplex(1.0f, 0.0f);
}
