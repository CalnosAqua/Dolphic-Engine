/**	@file	D3D12Buffer.cpp
 *	@brief	Direct3D12 用のバッファクラス
 */

#include "d3d12/D3D12Buffer.hpp"
#include "d3d12/D3D12Device.hpp"
#include "util/utility.hpp"
#include <string>

namespace dlph {
	D3D12Buffer::D3D12Buffer(D3D12Buffer&& arg) noexcept :
		D3D12Buffer()
	{
		m_heap = arg.m_heap;
		arg.m_heap = nullptr;

		m_rsrces.resize(arg.m_rsrces.size());
		for (unsigned int idx = 0U; idx < m_rsrces.size(); ++idx) {
			m_rsrces[idx] = arg.m_rsrces[idx];
			arg.m_rsrces[idx] = nullptr;
		}
		arg.m_rsrces.clear();
	}

	D3D12Buffer& D3D12Buffer::operator=(D3D12Buffer&& rhs) & noexcept {
		m_heap = rhs.m_heap;
		rhs.m_heap = nullptr;

		m_rsrces.resize(rhs.m_rsrces.size());
		for (unsigned int idx = 0U; idx < m_rsrces.size(); ++idx) {
			m_rsrces[idx] = rhs.m_rsrces[idx];
			rhs.m_rsrces[idx] = nullptr;
		}
		rhs.m_rsrces.clear();

		return *this;
	}

	D3D12Buffer::D3D12Buffer() noexcept :
		INoncopyable(),
		m_heap(nullptr),
		m_rsrces(),
		m_type(D3D12ViewType::Unknown),
		m_init(false)
	{}

	D3D12Buffer::~D3D12Buffer() noexcept {
		exit();
	}

	bool const D3D12Buffer::init(D3D12ViewType const& type, unsigned int const& count) noexcept {
		if (m_init) {
			return true;
		}
		if (count != 0U) {
			if (type != D3D12ViewType::Unknown) {
				HRESULT hResult = S_OK;
				D3D12_DESCRIPTOR_HEAP_DESC heap = {};

				heap.NodeMask = 0U;
				heap.NumDescriptors = count;

				switch (type) {
				case D3D12ViewType::RTV:
					heap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
					heap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
					break;
				case D3D12ViewType::DSV:
					heap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
					heap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
					break;
				case D3D12ViewType::CBV:
				case D3D12ViewType::SRV:
				case D3D12ViewType::UAV:
					heap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
					heap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
					break;
				case D3D12ViewType::Sampler:
					heap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
					heap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
					break;
				default:
					OutputDebugStringA("ERROR : SELECT DESCRIPTOR TYPE CORRUPTED.\n");
					return false;
				}

				hResult = D3D12Device::getInstance()->CreateDescriptorHeap(
					&heap,
					__uuidof(m_heap),
					reinterpret_cast<void**>(&m_heap)
				);
				if (FAILED(hResult)) {
					OutputDebugStringA("ERROR : CREATE FAILED DIREDT3D12 DESCRIPTOR HEAP.\n");
					return false;
				}
			}
			m_rsrces.resize(count);
			m_type = type;
			m_init = true;
			return true;
		}
		else {
			OutputDebugStringA("ERROR : BUFFER SIZE IS ZERO.\n");
			return false;
		}
	}

	void D3D12Buffer::exit() noexcept {
		safe_release(m_heap);
		for (auto& rsrc : m_rsrces) {
			safe_release(rsrc);
		}
		m_rsrces.clear();
		m_init = false;
	}

	D3D12DescriptorHandle const D3D12Buffer::getDescriptorHandle(unsigned int const& idx) const noexcept {
		D3D12DescriptorHandle result = {};
		if (m_init) {
			D3D12_DESCRIPTOR_HEAP_TYPE type = D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			size_t incsize = 0U;

			switch (m_type) {
			case D3D12ViewType::RTV:
				type = D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
				break;
			case D3D12ViewType::DSV:
				type = D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
				break;
			case D3D12ViewType::Sampler:
				type = D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
				break;
			default:
				break;
			}

			incsize = D3D12Device::getInstance()->GetDescriptorHandleIncrementSize(type);

			if (m_heap != nullptr) {
				result.cpu = m_heap->GetCPUDescriptorHandleForHeapStart();
				result.gpu = m_heap->GetGPUDescriptorHandleForHeapStart();
				if (idx < m_rsrces.size()) {
					result.cpu.ptr += incsize * static_cast<UINT64>(idx);
					result.gpu.ptr += incsize * static_cast<UINT64>(idx);
					result.usable = true;
				}
			}
		}
		return result;
	}

	D3D12_GPU_VIRTUAL_ADDRESS const D3D12Buffer::getGPUVirtualAddress(unsigned int const& idx) const noexcept {
		D3D12_GPU_VIRTUAL_ADDRESS result = {};
		if (m_init && idx < m_rsrces.size()) {
			result = m_rsrces[idx]->GetGPUVirtualAddress();
		}
		return result;
	}

	ID3D12Resource2*& D3D12Buffer::operator[](unsigned int const& idx)& noexcept {
		return m_rsrces[idx];
	}

	ID3D12Resource2* const& D3D12Buffer::operator[](unsigned int const& idx) const& noexcept {
		return m_rsrces[idx];
	}

	bool const createDepthStencilView(D3D12Buffer& buffer, HWND const& hWnd) noexcept {
		HRESULT hResult = S_OK;

		buffer.init(D3D12ViewType::DSV, 1U);

		RECT rect;
		GetClientRect(hWnd, &rect);
		unsigned int width = static_cast<unsigned int>(labs(rect.right - rect.left));
		unsigned int height = static_cast<unsigned int>(labs(rect.bottom - rect.top));

		D3D12_HEAP_PROPERTIES prop = {};
		prop.Type = D3D12_HEAP_TYPE_DEFAULT;
		prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask = 1U;
		prop.VisibleNodeMask = 1U;

		D3D12_RESOURCE_DESC desc = {};
		desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		desc.Alignment = 0U;
		desc.Width = width;
		desc.Height = height;
		desc.DepthOrArraySize = 1U;
		desc.MipLevels = 0U;
		desc.Format = DXGI_FORMAT_D32_FLOAT;
		desc.SampleDesc.Count = 1U;
		desc.SampleDesc.Quality = 0U;
		desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
		desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

		D3D12_CLEAR_VALUE value = {};
		value.Format = DXGI_FORMAT_D32_FLOAT;
		value.DepthStencil.Depth = 1.0f;
		value.DepthStencil.Stencil = 0U;

		hResult = D3D12Device::getInstance()->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&value,
			__uuidof(buffer[0]),
			reinterpret_cast<void**>(&buffer[0])
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : COMMITING FAILED DEPTH STENCIL RESOURCE.\n");
			return false;
		}

		D3D12_DEPTH_STENCIL_VIEW_DESC dsv = {};
		dsv.Format = DXGI_FORMAT_D32_FLOAT;
		dsv.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		dsv.Flags = D3D12_DSV_FLAG_NONE;

		D3D12Device::getInstance()->CreateDepthStencilView(
			buffer[0],
			&dsv,
			buffer.getDescriptorHandle(0).cpu
		);

		return true;
	}

	bool const createIndexBufferView(D3D12Buffer& buffer, unsigned int* indecies, unsigned int const& size) noexcept {
		HRESULT hResult = S_OK;

		buffer.init(D3D12ViewType::Unknown, 1U);

		D3D12_HEAP_PROPERTIES prop = {};
		prop.Type = D3D12_HEAP_TYPE_UPLOAD;
		prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask = 1;
		prop.VisibleNodeMask = 1;

		D3D12_RESOURCE_DESC desc = {};
		desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		desc.Alignment = 0;
		desc.Width = static_cast<UINT64>(sizeof(unsigned int)) * size;
		desc.Height = 1;
		desc.DepthOrArraySize = 1;
		desc.MipLevels = 1;
		desc.Format = DXGI_FORMAT_UNKNOWN;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc.Flags = D3D12_RESOURCE_FLAG_NONE;

		hResult = D3D12Device::getInstance()->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			__uuidof(buffer[0]),
			reinterpret_cast<void**>(&buffer[0])
		);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : COMMITING FAILED INDEX BUFFER RESOURCE.\n");
			return false;
		}

		void* ptr = nullptr;
		hResult = buffer[0]->Map(0U, nullptr, &ptr);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : MAPPING FAILED INDEX BUFFER RESOURCE.\n");
			return false;
		}

		memcpy(ptr, indecies, static_cast<UINT64>(sizeof(unsigned int)) * size);

		buffer[0]->Unmap(0U, nullptr);
		ptr = nullptr;

		D3D12_INDEX_BUFFER_VIEW view = {};
		view.BufferLocation = buffer.getGPUVirtualAddress(0);
		view.SizeInBytes = sizeof(unsigned int) * size;
		view.Format = DXGI_FORMAT_R32_UINT;

		return true;
	}

	/*/
	bool const createShaderResourceView(D3D12Buffer& buffer, wchar_t const* const& filename) noexcept {
		return false;
	}
	/*/
}
