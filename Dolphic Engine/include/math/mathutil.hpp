/**	@file	mathutil.hpp
 *	@brief	便利な数学関数群
 */
#pragma once

namespace dlph {
	class FRotation;
	class FEulerRotation;
	class FComplex;
	class FQuaternion;
	class FVector2;
	class FVector3;
	class FVector4;
	class FMatrix2x2;
	class FMatrix3x3;
	class FMatrix4x4;

	/**	@enum HandSide
	 *	@brief 作用方向一覧
	 */
	enum class HandSide {
		//!	@brief 左手系(行作用)
		LHS,
		//!	@brief 右手系(列作用)
		RHS
	};

	/**	@enum SkewType2
	 *	@brief 二次元空間剪断方向
	 */
	enum class SkewType2 {
		//!	@brief 第一成分基準(X軸)
		PRI,
		//!	@brief 第二成分基準(Y軸)
		SEC
	};

	/**	@enum SkewType3
	 *	@brief 三次元空間剪断方向
	 */
	enum class SkewType3 {
		//!	@brief XY平面上の第一成分基準(X軸)
		XYP,
		//!	@brief XY平面上の第二成分基準(Y軸)
		XYS,
		//!	@brief XZ平面上の第一成分基準(X軸)
		XZP,
		//!	@brief XZ平面上の第二成分基準(Z軸)
		XZS,
		//!	@brief YZ平面上の第一成分基準(Y軸)
		YZP,
		//!	@brief YZ平面上の第二成分基準(Z軸)
		YZS
	};

	/**	@brief 線形補間関数
	 *	@return 補間された値
	 */
	template <typename T>
	T const lerp(T const& begin, T const& end, float const& rate) noexcept;
	/**	@brief 球面線形補間関数
	 *	@return 補間された値
	 */
	template <typename T>
	T const slerp(T const& begin, T const& end, float const& rate) noexcept;
	/**	@brief 跳ね返りベクトル生成関数
	 *	@return 跳ね返りベクトル
	 */
	template <typename T>
	T const bounce(T const& dir, T const& nor, float const& rate) noexcept;
	/**	@brief 角度生成関数
	 *	@return 角度
	 */
	template <typename T>
	FRotation const angle(T const& base, T const& tar) noexcept;

	//!	@brief 複素数→行列 変換関数
	FMatrix3x3 const toMtx(FComplex const&) noexcept;
	//!	@brief 回転量→行列 変換関数
	FMatrix3x3 const toMtx(FRotation const&) noexcept;
	//!	@brief 四元数→行列 変換関数
	FMatrix4x4 const toMtx(FQuaternion const&) noexcept;
	//!	@brief オイラー角→行列 変換関数
	FMatrix4x4 const toMtx(FEulerRotation const&) noexcept;
	//!	@brief 複素数→回転量 変換関数
	FRotation const toRot(FComplex const&) noexcept;
	//!	@brief 行列→回転量 変換関数
	FRotation const toRot(FMatrix3x3 const&) noexcept;
	//!	@brief 四元数→オイラー角 変換関数
	FEulerRotation const toRot(FQuaternion const&) noexcept;
	//!	@brief 行列→オイラー角 変換関数
	FEulerRotation const toRot(FMatrix4x4 const&) noexcept;
	//!	@brief 行列→複素数 変換関数
	FComplex const toCmp(FMatrix3x3 const&) noexcept;
	//!	@brief 回転量→複素数 変換関数
	FComplex const toCmp(FRotation const&) noexcept;
	//!	@brief 行列→四元数 変換関数
	FQuaternion const toQt(FMatrix4x4 const&) noexcept;
	//!	@brief オイラー角→四元数 変換関数
	FQuaternion const toQt(FEulerRotation const&) noexcept;

	/**	@brief 移動行列生成関数
	 *	@return 移動行列
	 */
	FMatrix3x3 const makeTransit(HandSide const&, FVector2 const&) noexcept;
	/**	@brief 移動行列生成関数
	 *	@return 移動行列
	 */
	FMatrix4x4 const makeTransit(HandSide const&, FVector3 const&) noexcept;
	/**	@brief 回転行列生成関数
	 *	@return 回転行列
	 */
	FMatrix4x4 const makeRotate(HandSide const&, FQuaternion const&) noexcept;
	/**	@brief 回転行列生成関数
	 *	@return 回転行列
	 */
	FMatrix3x3 const makeRotate(HandSide const&, FRotation const&) noexcept;
	/**	@brief 回転行列生成関数
	 *	@return 回転行列
	 */
	FMatrix4x4 const makeRotate(HandSide const&, FVector3 const&, FRotation const&) noexcept;
	/**	@brief 拡縮行列生成関数
	 *	@return 拡縮行列
	 */
	FMatrix3x3 const makeScaler(FVector2 const&) noexcept;
	/**	@brief 拡縮行列生成関数
	 *	@return 拡縮行列
	 */
	FMatrix4x4 const makeScaler(FVector3 const&) noexcept;
	/**	@brief 剪断行列生成関数
	 *	@return 剪断行列
	 */
	FMatrix3x3 const makeSkew(HandSide const&, SkewType2 const&, FRotation const&) noexcept;
	/**	@brief 剪断行列生成関数
	 *	@return 剪断行列
	 */
	FMatrix4x4 const makeSkew(HandSide const&, SkewType3 const&, FRotation const&) noexcept;
}

#include "mathutil.inl"
