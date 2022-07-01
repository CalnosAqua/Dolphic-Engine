/**	@file	d3d12_rend.cpp
 *	@brief	Direct3D12 を利用したレンダラ
 */
#include "d3d12/d3d12_rend.hpp"
#include "d3d12/d3d12_device.hpp"
#include "util/utility.hpp"

namespace dlph {
	D3D12Renderer::D3D12Renderer() noexcept :
		INoncopyable(),
		m_barrier(),
		m_rtv(),
		m_dsv(),
		m_chain(),
		m_queue(),
		m_list(),
		m_fence(),
		m_rect(),
		m_viewport(),
		m_bufferCount(0U),
		m_currentIndex(0U),
		m_color(),
		m_hWnd(nullptr)
	{}

	D3D12Renderer::~D3D12Renderer() noexcept {
		exit();
	}

	bool const D3D12Renderer::init(RendererDesc const& desc) noexcept {
		if (m_hWnd) {
			return true;
		}

		RECT rect;
		GetClientRect(desc.hWnd, &rect);
		unsigned int width = static_cast<unsigned int>(labs(rect.right - rect.left));
		unsigned int height = static_cast<unsigned int>(labs(rect.bottom - rect.top));

#if defined(DEBUG) | defined(_DEBUG)
		{
			ID3D12Debug* debug;
			HRESULT hResult = D3D12GetDebugInterface(
				__uuidof(debug),
				reinterpret_cast<void**>(&debug)
			);
			if (SUCCEEDED(hResult)) {
				debug->EnableDebugLayer();
			}
			safe_release(debug);
		}
#endif

		if (!D3D12Device::getInstance().init()) {
			return false;
		}

		if (!m_queue.init(D3D12CommandType::Direct)) {
			return false;
		}

		SwapChainDesc chain;
		chain.hWnd = desc.hWnd;
		chain.fRate = desc.fRate;
		chain.bSize = desc.bSize;
		chain.cmdQue = m_queue.get();
		chain.fullscreen = desc.fullscreen;
		if (!m_chain.init(chain)) {
			return false;
		}

		if (!m_list.init(D3D12CommandType::Direct)) {
			return false;
		}

		if (!createRenderTargetView(m_rtv, m_chain, desc.bSize)) {
			return false;
		}

		if (!createDepthStencilView(m_dsv, desc.hWnd)) {
			return false;
		}

		m_hWnd = desc.hWnd;
		m_color = desc.color;
		m_bufferCount = desc.bSize;

		m_rect.top = 0U;
		m_rect.bottom = height;
		m_rect.left = 0U;
		m_rect.right = width;

		m_viewport.Height = static_cast<float>(height);
		m_viewport.Width = static_cast<float>(width);
		m_viewport.TopLeftX = 0.0f;
		m_viewport.TopLeftY = 0.0f;
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;

		return true;
	}

	bool const D3D12Renderer::reinit() noexcept {
		if (!m_hWnd) {
			OutputDebugStringA("ERROR : THE RENDERER HAS NOT BEEN INITIALIZED.\n");
			return false;
		}

		RECT rect;
		GetClientRect(m_hWnd, &rect);
		unsigned int width = static_cast<unsigned int>(labs(rect.right - rect.left));
		unsigned int height = static_cast<unsigned int>(labs(rect.bottom - rect.top));

		if (width > 0U && height > 0U) {
			m_rtv.exit();
			m_dsv.exit();

			HRESULT hResult = m_chain->ResizeBuffers(
				m_bufferCount,
				width,
				height,
				DXGI_FORMAT_R8G8B8A8_UNORM,
				DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
			);
			if (FAILED(hResult)) {
				OutputDebugStringA("ERROR : SWAP CHAIN BUFFER SIZE RESIZING FAILED.\n");
				return false;
			}

			if (!createRenderTargetView(m_rtv, m_chain, m_bufferCount)) {
				return false;
			}

			if (!createDepthStencilView(m_dsv, m_hWnd)) {
				return false;
			}
		}

		m_rect.top = 0U;
		m_rect.bottom = height;
		m_rect.left = 0U;
		m_rect.right = width;

		m_viewport.Height = static_cast<float>(height);
		m_viewport.Width = static_cast<float>(width);
		m_viewport.TopLeftX = 0.0f;
		m_viewport.TopLeftY = 0.0f;
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;

		return true;
	}

	void D3D12Renderer::exit() noexcept {
		m_rtv.exit();
		m_dsv.exit();

		m_chain.exit();

		m_queue.exit();
		m_list.exit();

		D3D12Device::getInstance().exit();

		return;
	}

	bool const D3D12Renderer::before_rendering() noexcept {
		D3D12_CPU_DESCRIPTOR_HANDLE rtv, dsv;

		m_currentIndex = m_chain->GetCurrentBackBufferIndex();

		if (!m_list.recording()) {
			return false;
		}

		rtv = m_rtv.getDescriptorHandle(m_currentIndex).cpu;
		dsv = m_dsv.getDescriptorHandle(0).cpu;

		m_barrier.toRenderTargetMode(m_list, m_rtv[m_currentIndex]);

		m_list->OMSetRenderTargets(1U, &rtv, false, &dsv);

		m_list->ClearDepthStencilView(dsv, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0U, 0U, nullptr);

		m_list->ClearRenderTargetView(rtv, m_color.p, 0, nullptr);

		m_list->RSSetViewports(1, &m_viewport);

		m_list->RSSetScissorRects(1, &m_rect);

		return true;
	}

	bool const D3D12Renderer::after_rendering() noexcept {
		m_barrier.toPresentMode(m_list, m_rtv[m_currentIndex]);

		m_list.closing();

		ID3D12CommandList* pCmdLists[] = { m_list.get() };
		m_queue->ExecuteCommandLists(1U, pCmdLists);

		return true;
	}

	bool const D3D12Renderer::presenting() noexcept {
		HRESULT hResult = S_OK;

		hResult = m_chain->Present(1U, 0U);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : PRESENTE FAILED DIRECT3D12 SWAP CHAIN.\n");
			return false;
		}

		return true;
	}

	D3D12CommandList& D3D12Renderer::getCmdList() noexcept {
		return m_list;
	}

	D3D12_RECT const D3D12Renderer::getTrimRect() const noexcept {
		return m_rect;
	}

	D3D12_VIEWPORT const D3D12Renderer::getViewport() const noexcept {
		return m_viewport;
	}

	unsigned int const D3D12Renderer::getFrameBufferSize() const noexcept {
		return m_bufferCount;
	}

	float const D3D12Renderer::getWidth() const noexcept {
		return m_viewport.Width;
	}

	float const D3D12Renderer::getHeight() const noexcept {
		return m_viewport.Height;
	}

	float const D3D12Renderer::getAspectRate() const noexcept {
		return static_cast<float>(m_viewport.Width) / static_cast<float>(m_viewport.Height);
	}

	unsigned int const D3D12Renderer::getCurrentBufferIndex() const noexcept {
		return m_chain->GetCurrentBackBufferIndex();
	}
}
