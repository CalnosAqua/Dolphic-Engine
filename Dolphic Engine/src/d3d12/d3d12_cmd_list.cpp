/**	@file	d3d12_cmd_list.cpp
 *	@brief	Direct3D12 用のコマンドリスト
 */
#include "d3d12/d3d12_cmd_list.hpp"
#include "d3d12/d3d12_device.hpp"
#include "util/utility.hpp"

namespace dlph {
	D3D12CommandList::D3D12CommandList(D3D12CommandList&& arg) noexcept :
		D3D12CommandList()
	{
		m_alloc = arg.m_alloc;
		m_list = arg.m_list;
		arg.m_alloc = nullptr;
		arg.m_list = nullptr;
	}

	D3D12CommandList& D3D12CommandList::operator=(D3D12CommandList&& rhs) & noexcept {
		exit();

		m_alloc = rhs.m_alloc;
		m_list = rhs.m_list;
		rhs.m_alloc = nullptr;
		rhs.m_list = nullptr;

		return *this;
	}

	D3D12CommandList::D3D12CommandList() noexcept :
		m_alloc(nullptr),
		m_list(nullptr)
	{}

	D3D12CommandList::~D3D12CommandList() noexcept {
		exit();
	}

	bool const D3D12CommandList::init(D3D12CommandType const& type) noexcept {
		if (m_list && m_alloc) {
			return true;
		}
		HRESULT hResult = S_OK;
		D3D12_COMMAND_LIST_TYPE type_;

		switch (type) {
		case D3D12CommandType::Direct:
			type_ = D3D12_COMMAND_LIST_TYPE_DIRECT;
			break;
		case D3D12CommandType::Copy:
			type_ = D3D12_COMMAND_LIST_TYPE_COPY;
			break;
		case D3D12CommandType::Compute:
			type_ = D3D12_COMMAND_LIST_TYPE_COMPUTE;
			break;
		case D3D12CommandType::Bundle:
			type_ = D3D12_COMMAND_LIST_TYPE_BUNDLE;
			break;
		default:
			OutputDebugStringA("ERROR : THE TYPE SETTING IS INCOLLECT.\n");
			return false;
		}

		hResult = D3D12Device::getInstance()->CreateCommandAllocator(
			type_,
			__uuidof(m_alloc),
			reinterpret_cast<void**>(&m_alloc)
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CREATE FAILD COMMAND ALLOCATOR.\n");
			return false;
		}

		hResult = D3D12Device::getInstance()->CreateCommandList(
			0U,
			type_,
			m_alloc,
			nullptr,
			__uuidof(m_list),
			reinterpret_cast<void**>(&m_list)
		);
		if (FAILED(hResult)) {
			safe_release(m_alloc);
			OutputDebugStringA("ERROR : CREATE FAILD COMMAND LIST.\n");
			return false;
		}

		if (!closing()) {
			return false;
		}

		return true;
	}

	void D3D12CommandList::exit() noexcept {
		safe_release(m_list);
		safe_release(m_alloc);
	}

	bool const D3D12CommandList::recording() noexcept {
		HRESULT hResult = S_OK;

		hResult = m_alloc->Reset();
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : RESET FAILD COMMAND ALLOCATOR.\n");
			return false;
		}

		hResult = m_list->Reset(m_alloc, nullptr);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : RESET FAILD COMMAND LIST.\n");
			return false;
		}

		return true;
	}

	bool const D3D12CommandList::closing() noexcept {
		HRESULT hResult = S_OK;

		hResult = m_list->Close();
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : CLOSE FAILD COMMAND LIST.\n");
			return false;
		}

		return true;
	}

	ID3D12GraphicsCommandList6*& D3D12CommandList::get() const noexcept {
		return *const_cast<ID3D12GraphicsCommandList6**>(&m_list);
	}

	ID3D12GraphicsCommandList6* D3D12CommandList::operator->() const noexcept {
		return m_list;
	}
}
