/**	@file	flt3.hpp
 *	@brief	三成分単精度浮動小数点数型
 */
#pragma once
#pragma warning(disable : 4201)

namespace {
	/**	@struct	Float3
	 *	@brief	三成分単精度浮動小数点数型
	 */
	struct Float3 {
		union {
			//!	@brief	全成分
			float p[3U];
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

	/**	@brief	設定関数
	 *	@return	設定した値
	 */
	Float3 constexpr set(float const& x = 0.0f, float const& y = 0.0f, float const& z = 0.0f) noexcept;
}
