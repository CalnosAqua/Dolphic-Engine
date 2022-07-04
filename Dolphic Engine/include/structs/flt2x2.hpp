/**	@file	flt2x2.hpp
 *	@brief	二次正方行列用構造体
 */
#pragma once
#pragma warning(disable : 4201)
#include "const.hpp"

namespace dlph {
	/**	@struct	Float2x2
	 *	@brief	二次正方行列用構造体
	 */
	struct Float2x2 {
		union {
			//!	@brief	全成分
			float p[T2x2_CNT];
			//!	@brief	全成分
			float m[T2_CNT][T2_CNT];
			struct {
				//!	@brief	一行一列目の成分
				float m00;
				//!	@brief	一行二列目の成分
				float m01;
				//!	@brief	二行一列目の成分
				float m10;
				//!	@brief	二行二列目の成分
				float m11;
			};
		};
	};
}
