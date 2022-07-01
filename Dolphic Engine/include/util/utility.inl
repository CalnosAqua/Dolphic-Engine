/**	@file	utility.inl
 *	@brief	便利関数群
 */
#pragma once
#include <d3d12.h>
#include "utility.hpp"

namespace dlph {
	template<typename T>
	inline void safe_release(T*& ptr) noexcept {
		if (ptr != nullptr) {
			ptr->Release();
			ptr = nullptr;
		}
	}

	template<typename T>
	void safe_destroy(T*& ptr) noexcept {
		if (ptr != nullptr) {
			ptr->destroy();
			ptr = nullptr;
		}
	}

	template<typename T>
	inline void safe_delete(T*& ptr) noexcept {
		if (ptr != nullptr) {
			delete ptr;
			ptr = nullptr;
		}
	}
}
