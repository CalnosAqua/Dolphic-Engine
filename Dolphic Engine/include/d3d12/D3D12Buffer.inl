/**	@file	D3D12Buffer.inl
 *	@brief	Direct3D12 用のバッファクラス
 */
#pragma once

#include "D3D12Device.hpp"

namespace dlph {
	template<typename Vertex>
	bool const createVertexBufferView(D3D12Buffer& buffer, Vertex* vertecies, unsigned int const& size) noexcept {
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
		desc.Width = static_cast<UINT64>(sizeof(Vertex)) * size;
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
			OutputDebugStringA("ERROR : COMMITING FAILED CONSTANT BUFFER RESOURCE.\n");
			return false;
		}

		void* ptr = nullptr;
		buffer[0]->Map(0U, nullptr, &ptr);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : MAPPING FAILED CONSTANT BUFFER RESOURCE.\n");
			return false;
		}

		memcpy(ptr, vertecies, size * sizeof(Vertex));

		buffer[0]->Unmap(0U, nullptr);
		ptr = nullptr;

		D3D12_VERTEX_BUFFER_VIEW view = {};
		view.BufferLocation = buffer[0]->GetGPUVirtualAddress();
		view.SizeInBytes = sizeof(Vertex) * static_cast<unsigned int>(size);
		view.StrideInBytes = sizeof(Vertex);

		return true;
	}
	
	template<typename T>
	bool const createConstantBufferView(D3D12Buffer& buffer, T const& data, unsigned int const& size) noexcept {
		HRESULT hResult = S_OK;

		buffer.init(D3D12ViewType::CBV, size);

		for (unsigned int idx = 0U; idx < size; ++idx) {
			D3D12_HEAP_PROPERTIES prop = {};
			prop.Type = D3D12_HEAP_TYPE_UPLOAD;
			prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			prop.CreationNodeMask = 1U;
			prop.VisibleNodeMask = 1U;

			D3D12_RESOURCE_DESC desc = {};
			desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			desc.Alignment = 0U;
			desc.Width = sizeof(T);
			desc.Height = 1U;
			desc.DepthOrArraySize = 1U;
			desc.MipLevels = 1U;
			desc.Format = DXGI_FORMAT_UNKNOWN;
			desc.SampleDesc.Count = 1U;
			desc.SampleDesc.Quality = 0U;
			desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			desc.Flags = D3D12_RESOURCE_FLAG_NONE;

			D3D12_CONSTANT_BUFFER_VIEW_DESC cbv = {};
			cbv.SizeInBytes = sizeof(T);
			cbv.BufferLocation = buffer.getGPUVirtualAddress(idx);

			hResult = D3D12Device::getInstance()->CreateCommittedResource(
				&prop,
				D3D12_HEAP_FLAG_NONE,
				&desc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				__uuidof(buffer[idx]),
				reinterpret_cast<void**>(&buffer[idx])
			);
			if (FAILED(hResult)) {
				OutputDebugStringA("ERROR : COMMITING FAILED CONSTANT BUFFER RESOURCE.\n");
				return false;
			}

			D3D12Device::getInstance()->CreateConstantBufferView(
				&cbv,
				buffer.getDescriptorHandle(idx).cpu
			);

			hResult = buffer[idx]->Map(
				0U,
				nullptr,
				reinterpret_cast<void**>(&const_cast<T*>(&data))
			);
			if (FAILED(hResult)) {
				OutputDebugStringA("ERROR : MAPPING FAILED CONSTANT BUFFER RESOURCE.\n");
				return false;
			}
		}

		return true;
	}
}
