/**	@file	D3D12CommandQueue.cpp
 *	@brief	Direct3D12 用のコマンドキュークラス
 */

#include "d3d12/D3D12CommandQueue.hpp"
#include "d3d12/D3D12Device.hpp"
#include "util/utility.hpp"

namespace dlph {
	D3D12CommandQueue::D3D12CommandQueue(D3D12CommandQueue&& arg) noexcept :
		D3D12CommandQueue()
	{
		m_queue = arg.m_queue;
		arg.m_queue = nullptr;
	}

	D3D12CommandQueue& D3D12CommandQueue::operator=(D3D12CommandQueue&& rhs) & noexcept {
		exit();
		
		m_queue = rhs.m_queue;
		rhs.m_queue = nullptr;

		return *this;
	}

	D3D12CommandQueue::D3D12CommandQueue() noexcept :
		INoncopyable(),
		m_queue(nullptr)
	{}

	D3D12CommandQueue::~D3D12CommandQueue() noexcept {
		exit();
	}

	bool const D3D12CommandQueue::init(D3D12CommandType const& type) noexcept {
		if (m_queue) {
			return true;
		}

		HRESULT hResult = S_OK;
		D3D12_COMMAND_QUEUE_DESC desc_ = {};

		desc_.NodeMask = 0U;
		desc_.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		desc_.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;

		switch (type) {
		case D3D12CommandType::Direct:
			desc_.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			break;
		case D3D12CommandType::Copy:
			desc_.Type = D3D12_COMMAND_LIST_TYPE_COPY;
			break;
		case D3D12CommandType::Compute:
			desc_.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
			break;
		default:
			OutputDebugStringA("ERROR : THE TYPE SETTING IS INCOLLECT.\n");
			return false;
		}

		hResult = D3D12Device::getInstance()->CreateCommandQueue(
			&desc_,
			__uuidof(m_queue),
			reinterpret_cast<void**>(&m_queue)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CREATE FAILED DIRECT3D12 COMMAND QUEUE.\n");
			return false;
		}

		return true;
	}

	void D3D12CommandQueue::exit() noexcept {
		safe_release(m_queue);
	}

	ID3D12CommandQueue*& D3D12CommandQueue::get() const noexcept {
		return *const_cast<ID3D12CommandQueue**>(&m_queue);
	}

	ID3D12CommandQueue* D3D12CommandQueue::operator->() const noexcept {
		return m_queue;
	}
}
