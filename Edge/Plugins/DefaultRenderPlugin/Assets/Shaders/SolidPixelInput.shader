#ifndef SOLID_PIXEL_INPUT_SHADER_INCLUDE
#define SOLID_PIXEL_INPUT_SHADER_INCLUDE

struct PixelInput
{
	float4 position : SV_Position;
	float4 normal : NORMAL;
	float4 color : COLOR;
};

#endif //SOLID_PIXEL_INPUT_SHADER_INCLUDE