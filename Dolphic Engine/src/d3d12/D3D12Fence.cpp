/**	@file	D3D12Fence.cpp
 *	@brief	フェンス
 */

#include "d3d12/D3D12Fence.hpp"
#include "d3d12/D3D12Device.hpp"
#include "util/utility.hpp"

namespace dlph {
	D3D12Fence::D3D12Fence(D3D12Fence&& arg) noexcept :
		D3D12Fence()
	{
		m_fence = arg.m_fence;
		arg.m_fence = nullptr;

		m_event = arg.m_event;
		arg.m_event = nullptr;

		m_signal = arg.m_signal;
	}

	D3D12Fence& D3D12Fence::operator=(D3D12Fence&& rhs) noexcept {
		exit();

		m_fence = rhs.m_fence;
		rhs.m_fence = nullptr;

		m_event = rhs.m_event;
		rhs.m_event = nullptr;

		m_signal = rhs.m_signal;

		return *this;
	}

	D3D12Fence::D3D12Fence() noexcept :
		INoncopyable(),
		m_fence(nullptr),
		m_event(nullptr),
		m_signal(0U)
	{}

	D3D12Fence::~D3D12Fence() noexcept {
		exit();
	}

	bool const D3D12Fence::init() noexcept {
		if (m_fence && m_event) {
			return true;
		}

		HRESULT hResult = S_OK;

		hResult = D3D12Device::getInstance()->CreateFence(
			0U,
			D3D12_FENCE_FLAG_NONE,
			__uuidof(m_fence),
			reinterpret_cast<void**>(&m_fence)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CREATE FAILED DIRECT3D12 FENCE.\n");
			return false;
		}

		m_signal++;

		m_event = CreateEventA(nullptr, FALSE, FALSE, nullptr);
		if (!m_event) {
			safe_release(m_fence);
			OutputDebugStringA("ERROR : CREATE FAILED FENCE EVENT.\n");
			return false;
		}

		return true;
	}

	void D3D12Fence::exit() noexcept {
		safe_release(m_fence);
		if (m_event != nullptr) {
			CloseHandle(m_event);
			m_event = nullptr;
		}
		m_signal = 0U;
	}

	void D3D12Fence::wait(D3D12CommandQueue const& queue) noexcept {
		HRESULT hResult = S_OK;

		hResult = queue->Signal(m_fence, m_signal);

		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : SIGNAL PROCESS FAILED.\n");
			return;
		}

		hResult = m_fence->SetEventOnCompletion(m_signal, m_event);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : EVENT SETTING PROCESS FAILED.\n");
			return;
		}

		WaitForSingleObjectEx(m_event, INFINITE, FALSE);

		m_signal++;
	}

	bool const D3D12Fence::presenting(D3D12CommandQueue const& queue) noexcept {
		HRESULT hResult = S_OK;
		UINT64 const curValue = m_signal;

		queue->Signal(m_fence, curValue);

		if (m_fence->GetCompletedValue() < m_signal) {
			hResult = m_fence->SetEventOnCompletion(m_signal, m_event);
			if (FAILED(hResult)) {
				OutputDebugStringA("ERROR : EVENT SETTING PROCESS FAILED.\n");
				return false;
			}

			WaitForSingleObjectEx(m_event, INFINITE, FALSE);
		}

		m_signal++;
		return true;
	}

	ID3D12Fence1*& D3D12Fence::get() const noexcept {
		return *const_cast<ID3D12Fence1**>(&m_fence);
	}

	ID3D12Fence1* D3D12Fence::operator->() const noexcept {
		return m_fence;
	}
}
