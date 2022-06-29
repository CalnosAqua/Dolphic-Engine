/**	@file	flt2.hpp
 *	@brief	二成分単精度浮動小数点数型
 */
#pragma once
#pragma warning(disable : 4201)

namespace dlph {
	//!	@brief	成分数
	static unsigned int constexpr FLT2_CNT = 2U;

	/**	@struct	Float2
	 *	@brief	二成分単精度浮動小数点数型
	 */
	struct Float2 final {
		union {
			//!	@brief	全成分
			float p[FLT2_CNT];
			struct {
				//!	@brief	第一成分
				float x;
				//!	@brief	第二成分
				float y;
			};
		};
	};
}
