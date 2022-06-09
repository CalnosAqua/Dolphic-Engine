/**	@file	dlph.hpp
 *	@brief	ドルフィックエンジン用エントリーヘッダー
 */
#pragma once

#if defined(_M_IX86)
#	if defined(_DEBUG) || defined(DEBUG)
#		pragma comment(lib, "dlph_x86d.lib")
#	else
#		pragma comment(lib, "dlph_x86.lib")
#	endif
#elif defined(_M_X64)
#	if defined(_DEBUG) || defined(DEBUG)
#		pragma comment(lib, "dlph_x64d.lib")
#	else
#		pragma comment(lib, "dlph_x64.lib")
#	endif
#elif defined(_M_ARM)
#	if defined(_DEBUG) || defined(DEBUG)
#		pragma comment(lib, "dlph_a86d.lib")
#	else
#		pragma comment(lib, "dlph_a86.lib")
#	endif
#elif defined(_M_ARM64)
#	if defined(_DEBUG) || defined(DEBUG)
#		pragma comment(lib, "dlph_a64d.lib")
#	else
#		pragma comment(lib, "dlph_a64.lib")
#	endif
#endif
