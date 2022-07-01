/**	@file	uint2.hpp
 *	@brief	二要素自然数構造体
 */
#pragma once

namespace dlph {
	//!	@brief	成分数
	static unsigned int constexpr UINT2_CNT = 2U;

	/**	@struct	UInt2
	 *	@brief	二要素自然数構造体
	 */
	struct UInt2 {
		union {
			//!	@brief	全成分
			unsigned int p[UINT2_CNT];
			struct {
				//!	@brief	第一成分
				unsigned int x;
				//!	@brief	第二成分
				unsigned int y;
			};
		};
	};
}
