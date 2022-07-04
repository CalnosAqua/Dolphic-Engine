/**	@file	stdafx.hpp
 *	@brief	プリコンパイル済みヘッダー
 */
#pragma once

#if !defined(_CRT_SECURE_NO_WARNINGS)
#	define _CRT_SECURE_NO_WARNINGS
#endif

#if !defined(_CRT_NON_CONFORMING_SWPRINTFS)
#	define _CRT_NON_CONFORMING_SWPRINTFS
#endif

#include <crtdbg.h>

/*/
//	WINDOWS 用メモリ管理ライブラリ
#pragma comment(lib, "winmm.lib")

//	Vulkan API 読み込み
#pragma comment(lib, "vulkan-1.lib")
/*/

#include <vulkan/vulkan.h>

/*/
//	Direct3D12 読み込み
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")
/*/

/*/
#if defined(_M_ARM) || defined(_M_ARM64)
#	if defined(_DEBUG) || defined(DEBUG)
#		pragma comment(lib, "a64\\Debug\\DirectXTex.lib")
#	else
#		pragma comment(lib, "a64\\Release\\DirectXTex.lib")
#	endif
#elif defined(_M_IX86)
#	if defined(_DEBUG) || defined(DEBUG)
#		pragma comment(lib, "x86\\Debug\\DirectXTex.lib")
#	else
#		pragma comment(lib, "x86\\Release\\DirectXTex.lib")
#	endif
#elif defined(_M_X64)
#	if defined(_DEBUG) || defined(DEBUG)
#		pragma comment(lib, "x64\\Debug\\DirectXTex.lib")
#	else
#		pragma comment(lib, "x64\\Release\\DirectXTex.lib")
#	endif
#endif
/*/

#ifndef NOMINMAX
#	define NOMINMAX
#endif

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include <WICTextureLoader12.h>
#include <DDSTextureLoader12.h>

#include <string>
#include <array>
#include <initializer_list>

#include <memory>
#include <numeric>
#include <chrono>

#if defined(_M_IX86) || defined(_M_X64)
#	include <immintrin.h>
#elif defined(_M_ARM)
#	include <arm_neon.h>
#elif defined(_M_ARM64)
#	include <arm64_neon.h>
#endif
