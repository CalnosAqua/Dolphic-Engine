/**	@file	fcomp.hpp
 *	@brief	単精度浮動小数点数型の四元数クラス
 */
#pragma once
#pragma warning(disable : 4201)
#include <initializer_list>

namespace dlph {
	/**	@class	FQuaternion
	 *	@brief	単精度浮動小数点数型の四元数
	 */
	class FQuaternion final {
	public:
		union {
			//!	@brief	全成分
			float alignas(16) p[4U];
			struct {
				//!	@brief	第一虚数成分
				float x;
				//!	@brief	第二虚数成分
				float y;
				//!	@brief	第三虚数成分
				float z;
				//!	@brief	実数成分
				float w;
			};
		};

		//!	@brief	ムーブコンストラクタ
		FQuaternion(FQuaternion&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		FQuaternion(FQuaternion const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		FQuaternion& operator=(FQuaternion&&) & noexcept = default;
		//!	@brief	コピー代入演算子
		FQuaternion& operator=(FQuaternion const&) & noexcept = default;

		//!	@brief	デフォルトコンストラクタ
		FQuaternion() noexcept;
		//!	@brief	デストラクタ
		~FQuaternion() noexcept = default;

		//!	@brief	初期化子コンストラクタ
		explicit FQuaternion(std::initializer_list<float> const&) noexcept;
		//!	@brief	初期化子コンストラクタ
		constexpr FQuaternion(float const& x, float const& y, float const& z, float const& w) noexcept :
			p{ x, y, z, w }
		{}

		//!	@brief	複合加算演算子
		FQuaternion& operator+=(FQuaternion const&) noexcept;
		//!	@brief	複合減算演算子
		FQuaternion& operator-=(FQuaternion const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		FQuaternion& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		FQuaternion& operator/=(float const&) noexcept;

		//!	@brief	単項加算演算子
		FQuaternion const operator+() const noexcept;
		//!	@brief	単項減算演算子
		FQuaternion const operator-() const noexcept;
	};

	//!	@brief	共役元生成関数
	FQuaternion const conjugate(FQuaternion const&) noexcept;
	//!	@brief	正規化関数
	FQuaternion const normalize(FQuaternion const&) noexcept;
	//!	@brief	逆元生成関数
	FQuaternion const inverse(FQuaternion const&) noexcept;

	//!	@brief	大きさの二乗生成関数
	float const sqr_magnitude(FQuaternion const&) noexcept;
	//!	@brief	大きさ生成関数
	float const magnitude(FQuaternion const&) noexcept;

	//!	@brief	加算演算子
	FQuaternion const operator+(FQuaternion const&, FQuaternion const&) noexcept;
	//!	@brief	減算演算子
	FQuaternion const operator-(FQuaternion const&, FQuaternion const&) noexcept;
	//!	@brief	スカラ倍演算子
	FQuaternion const operator*(FQuaternion const&, FQuaternion const&) noexcept;
	//!	@brief	スカラ倍演算子
	FQuaternion const operator*(FQuaternion const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	FQuaternion const operator*(float const&, FQuaternion const&) noexcept;
	//!	@brief	スカラ割演算子
	FQuaternion const operator/(FQuaternion const&, FQuaternion const&) noexcept;
	//!	@brief	スカラ割演算子
	FQuaternion const operator/(FQuaternion const&, float const&) noexcept;
	//!	@brief	スカラ割演算子
	FQuaternion const operator/(float const&, FQuaternion const&) noexcept;

	//!	@brief	等価比較演算子
	bool const operator==(FQuaternion const&, FQuaternion const&) noexcept;
	//!	@brief	不等価比較演算子
	bool const operator!=(FQuaternion const&, FQuaternion const&) noexcept;

	//!	@brief	零元複素数
	static FQuaternion constexpr FQTR_ZERO = FQuaternion(0.0f, 0.0f, 0.0f, 0.0f);
	//!	@brief	単位元複素数
	static FQuaternion constexpr FQTR_UNIT = FQuaternion(0.0f, 0.0f, 0.0f, 1.0f);
}
