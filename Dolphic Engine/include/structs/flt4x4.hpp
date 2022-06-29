﻿/**	@file	flt4x4.hpp
 *	@brief	四次正方行列用構造体
 */
#pragma once
#pragma warning(disable : 4201)

namespace dlph {
	//!	@brief	成分数
	static unsigned int constexpr FLT4x4_CNT = 16U;

	/**	@struct	Float4x4
	 *	@brief	四次正方行列用構造体
	 */
	struct Float4x4 final {
		union {
			//!	@brief	全成分
			float p[FLT4x4_CNT];
			//!	@brief	全成分
			float m[FLT4_CNT][FLT4_CNT];
			struct {
				//!	@brief	一行一列目の成分
				float m00;
				//!	@brief	一行二列目の成分
				float m01;
				//!	@brief	一行三列目の成分
				float m02;
				//!	@brief	一行四列目の成分
				float m03;
				//!	@brief	二行一列目の成分
				float m10;
				//!	@brief	二行二列目の成分
				float m11;
				//!	@brief	二行三列目の成分
				float m12;
				//!	@brief	二行四列目の成分
				float m13;
				//!	@brief	三行一列目の成分
				float m20;
				//!	@brief	三行二列目の成分
				float m21;
				//!	@brief	三行三列目の成分
				float m22;
				//!	@brief	三行四列目の成分
				float m23;
				//!	@brief	四行一列目の成分
				float m30;
				//!	@brief	四行二列目の成分
				float m31;
				//!	@brief	四行三列目の成分
				float m32;
				//!	@brief	四行四列目の成分
				float m33;
			};
		};
	};
}
