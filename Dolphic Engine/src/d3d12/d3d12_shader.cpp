/**	@file	d3d12_shader.cpp
 *	@brief	シェーダ
 */
#include "d3d12/d3d12_shader.hpp"
#include "d3d12/d3d12_device.hpp"
#include "util/utility.hpp"
#include <d3dcompiler.h>

namespace dlph {
	D3D12Shader::D3D12Shader(D3D12Shader&& arg) noexcept :
		D3D12Shader()
	{
		m_shader = arg.m_shader;
		arg.m_shader = nullptr;
	}

	D3D12Shader& D3D12Shader::operator=(D3D12Shader&& rhs) & noexcept {
		uninit();

		m_shader = rhs.m_shader;
		rhs.m_shader = nullptr;

		return *this;
	}

	D3D12Shader::D3D12Shader() noexcept :
		INoncopyable(),
		m_shader(nullptr)
	{}

	D3D12Shader::~D3D12Shader() noexcept {
		uninit();
	}

	bool const D3D12Shader::init(wchar_t const* const& path) noexcept {
		std::wstring name = path;
		HRESULT hResult = D3DReadFileToBlob(name.c_str(), &m_shader);
		if (FAILED(hResult)) {
			OutputDebugStringA("ERROR : LOADING FAILED SHADER FILE.\n");
			return false;
		}
		return true;
	}

	void D3D12Shader::uninit() noexcept {
		safe_release(m_shader);
	}

	D3D12_SHADER_BYTECODE const D3D12Shader::get() const noexcept {
		D3D12_SHADER_BYTECODE result;
		result.pShaderBytecode = m_shader->GetBufferPointer();
		result.BytecodeLength = m_shader->GetBufferSize();
		return result;
	}
}
