#pragma once

#include <d3d11.h>
#include <d3dcommon.h>

#include <dxgi1_6.h>

#include <wrl/client.h>

#ifdef EDGE_CONFIG_DEBUG
#define GRAPHIC_DEBUG
#define SHADER_DEBUG
#endif // EDGE_CONFIG_DEBUG

#define SHADER_COMPILATION_ERROR

#define EDGE_D3D11_ObjectRelease(objectComPtr)	\
	if (objectComPtr)							\
	{											\
		objectComPtr->Release();				\
		objectComPtr = nullptr;					\
	}

#define EDGE_IID(objectPtr) __uuidof(objectPtr)
#define EDGE_PPV(objectPtr)	reinterpret_cast<void**>(&objectPtr)
#define EDGE_IID_COM(objectComPtr) __uuidof(objectComPtr.Get())
#define EDGE_PPV_COM(objectComPtr) reinterpret_cast<void**>(objectComPtr.GetAddressOf())

namespace EdgeD3D11
{
	template <typename Type>
	using ComPtr = Microsoft::WRL::ComPtr<Type>;
}