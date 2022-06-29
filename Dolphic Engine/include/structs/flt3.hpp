/**	@file	flt3.hpp
 *	@brief	三成分単精度浮動小数点数型
 */
#pragma once
#pragma warning(disable : 4201)

namespace dlph {
	//!	@brief	成分数
	static unsigned int constexpr FLT3_CNT = 3U;

	/**	@struct	Float3
	 *	@brief	三成分単精度浮動小数点数型
	 */
	struct Float3 {
		union {
			//!	@brief	全成分
			float p[FLT3_CNT];
			struct {
				//!	@brief	第一成分
				float x;
				//!	@brief	第二成分
				float y;
				//!	@brief	第三成分
				float z;
			};
		};
	};
}
