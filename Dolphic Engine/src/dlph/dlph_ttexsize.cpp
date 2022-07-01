/**	@file	dlph_ttexsize.cpp
 *	@brief	Dolphic Engine 用のテクスチャサイズ列挙体
 */
#include "dlph/dlph_ttexsize.hpp"

namespace dlph {
	UInt2 const getSize(TextureSizeType type) noexcept {
		UInt2 result;

		switch (type) {
		case TextureSizeType::Tiny:
			result = { 16U, 16U };
			break;
		case TextureSizeType::Small:
			result = { 32U, 32U };
			break;
		case TextureSizeType::Usual:
			result = { 64U, 64U };
			break;
		case TextureSizeType::Big:
			result = { 128U, 128U };
			break;
		case TextureSizeType::Huge:
			result = { 256U, 256U };
			break;
		case TextureSizeType::Clear:
			result = { 512U, 512U };
			break;
		case TextureSizeType::HighVision:
			result = { 1024U, 1024U };
			break;
		case TextureSizeType::UltraVision:
			result = { 2048U, 2048U };
			break;
		case TextureSizeType::HyperVision:
			result = { 4096U, 4096U };
			break;
		}

		return result;
	}
}
