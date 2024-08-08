#pragma once

#include "D3D11Core.h"

namespace EdgeD3D11
{
	using D3DBlobComPtr = ComPtr<ID3DBlob>;

	using D3D11DebugComPtr = ComPtr<ID3D11Debug>;

	using D3D11DeviceComPtr = ComPtr<ID3D11Device>;
	using D3D11DeviceContextComPtr = ComPtr<ID3D11DeviceContext>;

	using D3D11CommandListComPtr = ComPtr<ID3D11CommandList>;

	using D3D11Texture1DComPtr = ComPtr<ID3D11Texture1D>;
	using D3D11Texture2DComPtr = ComPtr<ID3D11Texture2D>;
	using D3D11Texture3DComPtr = ComPtr<ID3D11Texture3D>;

	using D3D11BufferComPtr = ComPtr<ID3D11Buffer>;

	using D3D11InputLayoutComPtr = ComPtr<ID3D11InputLayout>;

	using D3D11VertexShaderComPtr = ComPtr<ID3D11VertexShader>;
	using D3D11PixelShaderComPtr = ComPtr<ID3D11PixelShader>;
	using D3D11ComputeShaderComPtr = ComPtr<ID3D11ComputeShader>;

	using D3D11RenderTargetViewComPtr = ComPtr<ID3D11RenderTargetView>;
	using D3D11DepthStencilViewComPtr = ComPtr<ID3D11DepthStencilView>;

	using D3D11RasterizerStateComPtr = ComPtr<ID3D11RasterizerState>;

	using DXGIFactoryComPtr = ComPtr<IDXGIFactory2>;
	using DXGISwapChainComPtr = ComPtr<IDXGISwapChain1>;
}
