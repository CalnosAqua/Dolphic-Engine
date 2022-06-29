/**	@file	flt4.hpp
 *	@brief	四成分単精度浮動小数点数型
 */
#pragma once
#pragma warning(disable : 4201)

namespace dlph {
	//!	@brief	成分数
	static unsigned int constexpr FLT4_CNT = 4U;

	/**	@struct	Float4
	 *	@brief	四成分単精度浮動小数点数型
	 */
	struct Float4 {
		union {
			//!	@brief	全成分
			float p[FLT4_CNT];
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
	};
}
