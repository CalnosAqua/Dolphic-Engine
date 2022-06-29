/**	@file	D3D12SwapChain.cpp
 *	@brief	スワップチェイン
 */

#include "d3d12/D3D12SwapChain.hpp"
#include "d3d12/D3D12Device.hpp"
#include "util/utility.hpp"

namespace dlph {
	D3D12SwapChain::D3D12SwapChain(D3D12SwapChain&& arg) noexcept :
		D3D12SwapChain()
	{
		m_chain = arg.m_chain;
		arg.m_chain = nullptr;
	}

	D3D12SwapChain& D3D12SwapChain::operator=(D3D12SwapChain&& rhs) noexcept {
		exit();

		m_chain = rhs.m_chain;
		rhs.m_chain = nullptr;

		return *this;
	}

	D3D12SwapChain::D3D12SwapChain() noexcept :
		INoncopyable(),
		m_chain(nullptr)
	{}

	D3D12SwapChain::~D3D12SwapChain() noexcept {
		exit();
	}

	bool const D3D12SwapChain::init(SwapChainDesc const& desc) noexcept {
		if (m_chain) {
			return true;
		}
		RECT rect;
		HRESULT hResult = S_OK;
		unsigned int width, height;

		GetClientRect(desc.hWnd, &rect);
		width = static_cast<unsigned int>(labs(rect.right - rect.left));
		height = static_cast<unsigned int>(labs(rect.bottom - rect.top));

		DXGI_SWAP_CHAIN_DESC desc_ = {};
		desc_.BufferDesc.Width = width;
		desc_.BufferDesc.Height = height;
		desc_.BufferDesc.RefreshRate.Numerator = desc.fRate;
		desc_.BufferDesc.RefreshRate.Denominator = 1;
		desc_.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc_.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc_.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc_.SampleDesc.Count = 1;
		desc_.SampleDesc.Quality = 0;
		desc_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc_.BufferCount = desc.bSize;
		desc_.OutputWindow = desc.hWnd;
		desc_.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		desc_.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		desc_.Windowed = !desc.fullscreen;

		IDXGIFactory4* factory = nullptr;
		hResult = CreateDXGIFactory2(
#			if defined(DEBUG) | defined(_DEBUG)
			DXGI_CREATE_FACTORY_DEBUG,
#			else
			0,
#			endif
			__uuidof(factory),
			reinterpret_cast<void**>(&factory)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CREATE FAILED FACTORY.\n");
			return false;
		}

		IDXGIFactory7* fact = nullptr;
		hResult = factory->QueryInterface(
			__uuidof(fact),
			reinterpret_cast<void**>(&fact)
		);
		safe_release(factory);
		if (FAILED(hResult))
		{
			OutputDebugStringA("ERROR : REVERT FAILED SWAPCHAIN.\n");
			return false;
		}

		IDXGISwapChain* chain = nullptr;
		hResult = fact->CreateSwapChain(
			desc.cmdQue,
			&desc_,
			&chain
		);
		safe_release(fact);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CREATE FAILED SWAPCHAIN.\n");
			return false;
		}

		hResult = chain->QueryInterface(
			__uuidof(m_chain),
			reinterpret_cast<void**>(&m_chain)
		);
		safe_release(chain);
		if (FAILED(hResult))
		{
			OutputDebugStringA("ERROR : REVERT FAILED SWAPCHAIN.\n");
			return false;
		}

		return true;
	}

	void D3D12SwapChain::exit() noexcept {
		safe_release(m_chain);
	}

	IDXGISwapChain4*& D3D12SwapChain::get() const noexcept {
		return *const_cast<IDXGISwapChain4**>(&m_chain);
	}

	IDXGISwapChain4* D3D12SwapChain::operator->() const noexcept {
		return m_chain;
	}
}
