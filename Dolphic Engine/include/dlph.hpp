/**	@file	dlph.hpp
 *	@brief	エントリヘッダー
 */
#pragma once

#if defined(_M_IX86)
#	if defined(_DEBUG) || defined(DEBUG)
#		pragma comment(lib, "x86\\debug\\dlph.lib")
#	else
#		pragma comment(lib, "x86\\release\\dlph.lib")
#	endif
#elif defined(_M_X64)
#	if defined(_DEBUG) || defined(DEBUG)
#		pragma comment(lib, "x64\\debug\\dlph.lib")
#	else
#		pragma comment(lib, "x64\\release\\dlph.lib")
#	endif
#elif defined(_M_ARM)
#	if defined(_DEBUG) || defined(DEBUG)
#		pragma comment(lib, "a86\\debug\\dlph.lib")
#	else
#		pragma comment(lib, "a86\\release\\dlph.lib")
#	endif
#elif defined(_M_ARM64)
#	if defined(_DEBUG) || defined(DEBUG)
#		pragma comment(lib, "a64\\debug\\dlph.lib")
#	else
#		pragma comment(lib, "a64\\release\\dlph.lib")
#	endif
#endif
