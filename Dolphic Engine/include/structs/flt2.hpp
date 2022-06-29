/**	@file	flt2.hpp
 *	@brief	二成分単精度浮動小数点数型
 */
#pragma once
#pragma warning(disable : 4201)

namespace {
	/**	@struct	Float2
	 *	@brief	二成分単精度浮動小数点数型
	 */
	struct Float2 {
		union {
			//!	@brief	全成分
			float p[2U];
			struct {
				//!	@brief	第一成分
				float x;
				//!	@brief	第二成分
				float y;
			};
		};
	};

	/**	@brief	設定関数
	 *	@return	設定した値
	 */
	Float2 constexpr set(float const& x = 0.0f, float const& y = 0.0f) noexcept;
}
