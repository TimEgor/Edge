#ifndef WIREFRAME_PIXEL_INPUT_SHADER_INCLUDE
#define WIREFRAME_PIXEL_INPUT_SHADER_INCLUDE

struct PixelInput
{
	float4 position : SV_Position;
	float4 color : COLOR;
};

#endif //WIREFRAME_PIXEL_INPUT_SHADER_INCLUDE