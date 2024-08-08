#ifndef WIREFRAME_PIXEL_SHADER_COMMON_SHADER_INCLUDE
#define WIREFRAME_PIXEL_SHADER_COMMON_SHADER_INCLUDE

#include "WireframePixelInput.shader"

float4 PS(PixelInput input) : SV_Target0
{
	return input.color;
}

#endif //WIREFRAME_PIXEL_SHADER_COMMON_SHADER_INCLUDE