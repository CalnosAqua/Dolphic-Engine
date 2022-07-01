/**	@file	uint3.hpp
 *	@brief	三要素自然数構造体
 */
#pragma once

namespace dlph {
	//!	@brief	成分数
	static unsigned int constexpr UINT3_CNT = 3U;

	/**	@struct	UInt3
	 *	@brief	三要素自然数構造体
	 */
	struct UInt3 {
		union {
			//!	@brief	全成分
			unsigned int p[UINT3_CNT];
			struct {
				//!	@brief	第一成分
				unsigned int x;
				//!	@brief	第二成分
				unsigned int y;
				//!	@brief	第三成分
				unsigned int z;
			};
		};
	};
}
