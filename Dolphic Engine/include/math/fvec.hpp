/**	@file	fvec.hpp
 *	@brief	ベクトルクラス
 */
#pragma once
#include <initializer_list>

namespace dlph {
	/**	@class	FVector<N>
	 *	@brief	単精度浮動小数点数型ベクトルクラス
	 */
	template <size_t N>
	class FVector final {
	public	:
		//!	@brief	ムーブコンストラクタ
		FVector(FVector<N>&&) noexcept = default;
		//!	@brief	コピーコンストラクタ
		FVector(FVector<N> const&) noexcept = default;
		//!	@brief	ムーブ代入演算子
		FVector<N>& operator=(FVector<N>&&) & noexcept = default;
		//!	@brief	コピー代入演算子
		FVector<N>& operator=(FVector<N> const&) & noexcept = default;

		//!	@brief	初期化子コンストラクタ
		FVector(std::initializer_list<float> const&) noexcept;

		//!	@brief	デフォルトコンストラクタ
		FVector() noexcept;
		//!	@brief	デストラクタ
		~FVector() noexcept = default;

		//!	@brief	添字演算子
		float& operator[](size_t const&) & noexcept;
		//!	@brief	添字演算子
		float operator[](size_t const&) const&& noexcept;
		//!	@brief	添字演算子
		float const& operator[](size_t const&) const& noexcept;

		//!	@brief	配列の先頭へのポインタ
		float* const cbegin() const noexcept;
		//!	@brief	配列の先頭へのポインタ
		float* begin() noexcept;
		//!	@brief	配列の末端へのポインタ
		float* const cend() const noexcept;
		//!	@brief	配列の末端へのポインタ
		float* end() noexcept;

		//!	@brief	配列長
		size_t const size() const noexcept;

		//!	@brief	キャスト演算子
		explicit operator float* () const noexcept;

		//!	@brief	複合加算演算子
		FVector<N>& operator+=(FVector<N> const&) noexcept;
		//!	@brief	複合減算演算子
		FVector<N>& operator-=(FVector<N> const&) noexcept;
		//!	@brief	複合スカラ倍演算子
		FVector<N>& operator*=(float const&) noexcept;
		//!	@brief	複合スカラ割演算子
		FVector<N>& operator/=(float const&) noexcept;

		//!	@brief	単項加算演算子
		FVector<N> const operator+() const noexcept;
		//!	@brief	単項減算演算子
		FVector<N> const operator-() const noexcept;

	private	:
		//!	@brief	配列
		float m_array[N];
	};

	//!	@brief	内積関数
	template <size_t N>
	float const dot(FVector<N> const&, FVector<N> const&) noexcept;

	//!	@brief	正規化関数
	template <size_t N>
	FVector<N> const normalize(FVector<N> const&) noexcept;
	//!	@brief	大きさの二乗取得関数
	template <size_t N>
	float const sqr_magnitude(FVector<N> const&) noexcept;
	//!	@brief	大きさ取得関数
	template <size_t N>
	float const magnitude(FVector<N> const&) noexcept;

	//!	@brief	加算演算子
	template <size_t N>
	FVector<N> const operator+(FVector<N> const&, FVector<N> const&) noexcept;
	//!	@brief	減算演算子
	template <size_t N>
	FVector<N> const operator-(FVector<N> const&, FVector<N> const&) noexcept;
	//!	@brief	スカラ倍演算子
	template <size_t N>
	FVector<N> const operator*(FVector<N> const&, float const&) noexcept;
	//!	@brief	スカラ倍演算子
	template <size_t N>
	FVector<N> const operator*(float const&, FVector<N> const&) noexcept;
	//!	@brief	スカラ割演算子
	template <size_t N>
	FVector<N> const operator/(FVector<N> const&, float const&) noexcept;

	//!	@brief	等価比較演算子
	template <size_t N>
	bool const operator==(FVector<N> const&, FVector<N> const&) noexcept;
	//!	@brief	不等価比較演算子
	template <size_t N>
	bool const operator!=(FVector<N> const&, FVector<N> const&) noexcept;
}

#include "fvec.inl"
