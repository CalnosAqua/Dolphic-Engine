/**	@file	stdafx.hpp
 *	@brief	プリコンパイル済みヘッダー
 */
#pragma once

#if defined(_M_IX86) || defined(_M_X64)
#	include <immintrin.h>
#elif defined(_M_ARM)
#	include <arm_neon.h>
#elif defined(_M_ARM64)
#	include <arm64_neon.h>
#endif
