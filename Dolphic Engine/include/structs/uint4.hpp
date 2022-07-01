/**	@file	uint4.hpp
 *	@brief	四要素自然数構造体
 */
#pragma once

namespace dlph {
	//!	@brief	成分数
	static unsigned int constexpr UINT4_CNT = 4U;

	/**	@struct	UInt4
	 *	@brief	四要素自然数構造体
	 */
	struct UInt4 {
		union {
			//!	@brief	全成分
			unsigned int p[UINT4_CNT];
			struct {
				//!	@brief	第一成分
				unsigned int x;
				//!	@brief	第二成分
				unsigned int y;
				//!	@brief	第三成分
				unsigned int z;
				//!	@brief	第四成分
				unsigned int w;
			};
		};
	};
}
