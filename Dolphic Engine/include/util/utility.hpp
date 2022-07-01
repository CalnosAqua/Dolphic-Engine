/**	@file	utility.hpp
 *	@brief	便利関数群
 */
#pragma once
#include <string>

namespace dlph {
	/**	@brief COM オブジェクト解放関数
	 *	@param[in] ptr COM オブジェクト
	 */
	template<typename T>
	void safe_release(T*& ptr) noexcept;

	/**	@brief COM オブジェクト解放関数
	 *	@param[in] ptr Vulkan オブジェクト
	 */
	template<typename T>
	void safe_destroy(T*& ptr) noexcept;

	/**	@brief オブジェクト解放関数
	 *	@param[in] ptr オブジェクト
	 */
	template<typename T>
	void safe_delete(T*& ptr) noexcept;
}

#include "utility.inl"
