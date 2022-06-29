/**	@file	WinWindow.cpp
 *	@brief	Windows 用ウィンドウ管理クラス定義ファイル
 */
#if !defined(_CRT_SECURE_NO_WARNINGS)
#	define _CRT_SECURE_NO_WARNINGS
#endif

#if !defined(_CRT_NON_CONFORMING_SWPRINTFS)
#	define _CRT_NON_CONFORMING_SWPRINTFS
#endif

#include "win/WinWindow.hpp"
#include <numeric>
#include <tchar.h>

namespace dlph {
	WinWindow::WinWindow(WinWindow&& arg) noexcept :
		WinWindow()
	{
		m_hWnd = arg.m_hWnd;
		m_wndName = arg.m_wndName;
		arg.m_hWnd = nullptr;
		arg.m_wndName = nullptr;

		m_inited = arg.m_inited;
	}
	
	WinWindow& WinWindow::operator=(WinWindow&& rhs) noexcept {
		exit();

		m_hWnd = rhs.m_hWnd;
		m_wndName = rhs.m_wndName;
		rhs.m_hWnd = nullptr;
		rhs.m_wndName = nullptr;

		m_inited = rhs.m_inited;
		return *this;
	}

	WinWindow::WinWindow() noexcept :
		m_hWnd(nullptr),
		m_wndName(nullptr),
		m_inited(false)
	{}

	WinWindow::~WinWindow() noexcept {
		exit();
	}

	bool const WinWindow::init(WindwDesc const& data) noexcept {
		if (m_inited) {
			return m_inited;
		}

		WNDCLASSEXA	wndcls = {};

#if defined(DEBUG) || defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
		wndcls.cbSize = sizeof(tagWNDCLASSEXA);
		wndcls.style = data.scalable ? (CS_HREDRAW | CS_VREDRAW) : 0;
		wndcls.lpfnWndProc = data.wnd_proc;
		wndcls.cbClsExtra = 0;
		wndcls.cbWndExtra = 0;
		wndcls.hInstance = data.ins_handler;
		wndcls.hIconSm = nullptr;
		wndcls.hIcon = nullptr;
		wndcls.hCursor = nullptr;
		wndcls.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wndcls.lpszMenuName = nullptr;
		wndcls.lpszClassName = data.cls_name;

		bool state = RegisterClassExA(&wndcls);
		if (!state) {
			OutputDebugStringA("Error : Failed Register Window Class.\n");
			return m_inited;
		}

		m_hWnd = CreateWindowExA(
			0,
			data.cls_name,
			data.wnd_name,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<int>(data.width),
			static_cast<int>(data.height),
			nullptr,
			nullptr,
			data.ins_handler,
			nullptr
		);

		if (!m_hWnd) {
			OutputDebugStringA("Error : Failed Create Window.\n");
			return m_inited;
		}

		ShowWindow(m_hWnd, SW_SHOWNORMAL);
		UpdateWindow(m_hWnd);
		SetFocus(m_hWnd);

		m_wndName = data.wnd_name;

		m_inited = true;
		return m_inited;
	}

	void WinWindow::exit() noexcept {
		if (m_inited) {
			char temp[100];
			memset(temp, 0, 100);
			GetClassNameA(m_hWnd, temp, 100);
			UnregisterClassA(temp, getInstanceHandle());
			m_hWnd = nullptr;
			m_inited = false;
		}
	}

	void WinWindow::showWindowStatus() noexcept {
		static _LARGE_INTEGER start;
		static char view[100];
		static int frame = 0;
		double passtime, microsec;
		_LARGE_INTEGER end;
		_LARGE_INTEGER frq;

		QueryPerformanceFrequency(&frq);

		passtime = 0;
		microsec = 1.0E+6 / static_cast<double>(frq.QuadPart);

		frame++;

		QueryPerformanceCounter(&end);
		passtime = (end.QuadPart - start.QuadPart) * microsec;
		if (passtime > 1.0E+6) {
			QueryPerformanceCounter(&start);

			memset(view, 0, 100);
			sprintf(view, "%s [FPS=%d W=%d H=%d]", m_wndName, frame, getWidth(), getHeight());
			SetWindowTextA(m_hWnd, view);
			frame = 0;
		}
	}

	LRESULT const WinWindow::WindowProcedure(HWND const& hWnd, UINT const& uMsg, WPARAM const& wParam, LPARAM const& lParam) {
		int id = 0;
		switch (uMsg) {
		case WM_CLOSE:
			id = MessageBoxA(hWnd, "終了しますか？", "確認", MB_YESNO | MB_ICONINFORMATION);
			if (id == IDYES) {
				DestroyWindow(hWnd);
			}
			break;
		case WM_KEYDOWN:
			if (GetKeyState(VK_ESCAPE) < 0) {
				id = MessageBoxA(hWnd, "終了しますか？", "確認", MB_YESNO | MB_ICONINFORMATION);
				if (id == IDYES) {
					DestroyWindow(hWnd);
				}
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProcA(hWnd, uMsg, wParam, lParam);
			break;
		}

		return 0;
	}

	MessageState const WinWindow::receivingMessage() noexcept {
		MSG msg;
		memset(&msg, 0, sizeof(MSG));
		if (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				return MessageState::END;
			}
			if (msg.message == WM_SIZING ||msg.message == WM_SIZE) {
				return MessageState::RESIZE;
			}
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
			return MessageState::RECEIVED;
		}
		return MessageState::NOTFOUND;
	}

	RECT const WinWindow::getRectangle() const noexcept {
		RECT result;
		GetClientRect(m_hWnd, &result);
		return result;
	}

	HWND const& WinWindow::getWindowHandle() const noexcept {
		return m_hWnd;
	}

	HINSTANCE const WinWindow::getInstanceHandle() const noexcept {
		HINSTANCE result = reinterpret_cast<HINSTANCE>(static_cast<LONGLONG>(GetWindowLongA(m_hWnd, GWLP_HINSTANCE)));
		return result;
	}

	unsigned int const WinWindow::getWidth() const noexcept {
		RECT temp = getRectangle();
		return static_cast<unsigned int>(labs(temp.right - temp.left));
	}

	unsigned int const WinWindow::getHeight() const noexcept {
		RECT temp = getRectangle();
		return static_cast<unsigned int>(labs(temp.bottom - temp.top));
	}
}
