#pragma once

#include <d3d11.h>
#include <d3dcommon.h>

#include <dxgi1_6.h>

#include <wrl/client.h>

#ifdef TS_CONFIG_DEBUG
#define GRAPHIC_DEBUG
#define SHADER_DEBUG
#endif // TS_CONFIG_DEBUG

#define SHADER_COMPILATION_ERROR

#define TS_D3D11_ObjectRelease(objectComPtr)	\
	if (objectComPtr)							\
	{											\
		objectComPtr->Release();				\
		objectComPtr = nullptr;					\
	}

#define TS_IID(objectPtr) __uuidof(objectPtr)
#define TS_PPV(objectPtr)	reinterpret_cast<void**>(&objectPtr)
#define TS_IID_COM(objectComPtr) __uuidof(objectComPtr.Get())
#define TS_PPV_COM(objectComPtr) reinterpret_cast<void**>(objectComPtr.GetAddressOf())

namespace TS_D3D11
{
	template <typename Type>
	using ComPtr = Microsoft::WRL::ComPtr<Type>;
}