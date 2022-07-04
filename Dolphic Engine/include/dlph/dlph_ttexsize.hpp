/**	@file	dlph_ttexsize.hpp
 *	@brief	Dolphic Engine 用のテクスチャサイズ列挙体
 */
#pragma once
#include "structs/t2.hpp"

namespace dlph {
	enum class TextureSizeType : unsigned char {
		//!	@brief	16 x 16
		Tiny,
		//!	@brief	32 x 32
		Small,
		//!	@brief	64 x 64
		Usual,
		//!	@brief	128 x 128
		Big,
		//!	@brief	256 x 256
		Huge,
		//!	@brief	512 x 512
		Clear,
		//!	@brief	1024 x 1024
		HighVision,
		//!	@brief	2048 x 2048
		UltraVision,
		//!	@brief	4096 x 4096
		HyperVision
	};

	UInt2 const getSize(TextureSizeType type) noexcept;
}
