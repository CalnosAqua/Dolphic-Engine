/**	@file	fvec4.hpp
 *	@brief	単精度浮動小数点数型の四次元ベクトルクラス
 */
#pragma once
#pragma warning(disable : 4201)
#include <initializer_list>

namespace dlph {
	/**	@class	FVector4
	 *	@brief	単精度浮動小数点数型の四次元ベクトル
	 */
	class FVector4 final {
	public:
		union {
			//!	@brief	全成分
			float alignas(16) p[4U];
			struct {
				//!	@brief	第一成分
				float x;
				//!	@brief	第二成分
				float y;
				//!	@brief	第三成分
				float z;
				//!	@brief	第四成分
				float w;
			};
		};

		//!	@brief	ムーブコンストラクタ
		FVector4(FVector4&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		FVector4(FVector4 const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		FVector4& operator=(FVector4&&) & noexcept = default;
		//!	@brief	コピー代入演算子
		FVector4& operator=(FVector4 const&) & noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		FVector4() noexcept;
		//!	@brief	デストラクタ
		~FVector4() noexcept = default;

		//!	@brief	初期化子コンストラクタ
		explicit FVector4(std::initializer_list<float> const&) noexcept;
		//!	@brief	初期化子コンストラクタ
		constexpr FVector4(float const& x, float const& y, float const& z, float const& w) noexcept :
			p{ x, y, z, w }
		{}

		//!	@brief	複合加算演算子
		FVector4& operator+=(FVector4 const&) noexcept;
		//!	@brief	複合減算演算子
		FVector4& operator-=(FVector4 const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		FVector4& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		FVector4& operator/=(float const&) noexcept;

		//!	@brief	単項加算演算子
		FVector4 const operator+() const noexcept;
		//!	@brief	単項減算演算子
		FVector4 const operator-() const noexcept;
	};
	//!	@brief	外積関数
	FVector4 const cross(FVector4 const&, FVector4 const&, FVector4 const&) noexcept;
	//!	@brief	内積関数
	float const dot(FVector4 const&, FVector4 const&) noexcept;

	//!	@brief	正規化関数
	FVector4 const normalize(FVector4 const&) noexcept;
	//!	@brief	大きさの二乗取得関数
	float const sqr_magnitude(FVector4 const&) noexcept;
	//!	@brief	大きさ取得関数
	float const magnitude(FVector4 const&) noexcept;

	//!	@brief	加算演算子
	FVector4 const operator+(FVector4 const&, FVector4 const&) noexcept;
	//!	@brief	減算演算子
	FVector4 const operator-(FVector4 const&, FVector4 const&) noexcept;
	//!	@brief	スカラ倍演算子
	FVector4 const operator*(FVector4 const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	FVector4 const operator*(float const&, FVector4 const&) noexcept;
	//!	@brief	スカラ割演算子
	FVector4 const operator/(FVector4 const&, float const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(FVector4 const&, FVector4 const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(FVector4 const&, FVector4 const&) noexcept;

	//!	@brief	ゼロベクトル
	static FVector4 constexpr FVT4_ZERO = FVector4(0.0f, 0.0f, 0.0f, 0.0f);
}
