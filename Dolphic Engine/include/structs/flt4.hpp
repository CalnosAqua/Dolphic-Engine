/**	@file	flt4.hpp
 *	@brief	四成分単精度浮動小数点数型
 */
#pragma once
#pragma warning(disable : 4201)

namespace {
	/**	@struct	Float4
	 *	@brief	四成分単精度浮動小数点数型
	 */
	struct Float4 {
		union {
			//!	@brief	全成分
			float p[4U];
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

	/**	@brief	設定関数
	 *	@return	設定した値
	 */
	Float4 constexpr set(float const& x = 0.0f, float const& y = 0.0f, float const& z = 0.0f, float const& w = 0.0f) noexcept;
}
